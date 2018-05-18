package edu.stevens.cs522.chat.rest;

import android.content.Context;
import android.net.Uri;
import android.os.ResultReceiver;
import android.util.JsonReader;
import android.util.JsonWriter;
import android.util.Log;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.lang.reflect.Array;
import java.security.InvalidParameterException;
import java.sql.Date;
import java.util.ArrayList;

import edu.stevens.cs522.chat.entities.ChatMessage;
import edu.stevens.cs522.chat.entities.Peer;
import edu.stevens.cs522.chat.managers.MessageManager;
import edu.stevens.cs522.chat.managers.PeerManager;
import edu.stevens.cs522.chat.managers.RequestManager;
import edu.stevens.cs522.chat.managers.TypedCursor;
import edu.stevens.cs522.chat.settings.Settings;
import edu.stevens.cs522.chat.util.DateUtils;
import edu.stevens.cs522.chat.util.StringUtils;

/**
 * Created by dduggan.
 */

public class RequestProcessor {

    private Context context;
    private RestMethod restMethod;
    private RequestManager requestManager;
    private PeerManager peerManager;

    public RequestProcessor(Context context) {
        this.context = context;
        this.restMethod = new RestMethod(context);

        // Used for SYNC
        this.requestManager = new RequestManager(context);
        this.peerManager = new PeerManager(context);
    }

    public Response process(Request request) {
        return request.process(this);
    }

    public Response perform(RegisterRequest request) {
        Response response = restMethod.perform(request);
        if (response instanceof RegisterResponse) {
            Settings.saveSenderId(this.context, ((RegisterResponse) response).senderId);
        }
        return response;
    }

    public Response perform(PostMessageRequest request) {
        ChatMessage m = new ChatMessage();
        m.chatRoom = request.chatRoom;
        m.messageText = request.message;
        m.senderId = Settings.getSenderId(this.context);
        m.timestamp = DateUtils.now();
        m.sender = Settings.getChatName(this.context);
        m.sequenceNum = 0;

        if (!Settings.SYNC) {
            MessageManager manager = new MessageManager(this.context);
            manager.persistAsync(m);

            Response response = restMethod.perform(request);

            if (response instanceof PostMessageResponse) {
                m.sequenceNum = ((PostMessageResponse) response).messageId;
                manager.updateAsync(m);
            }

            return response;
        } else {
            requestManager.persist(m);
            return request.getDummyResponse();
        }
    }

    /**
     * For SYNC: perform a sync using a request manager
     * @param request
     * @return
     */
    public Response perform(SynchronizeRequest request) {
        RestMethod.StreamingResponse response = null;
        request.lastSequenceNumber = requestManager.getLastSequenceNumber();
        final TypedCursor<ChatMessage> messages = requestManager.getUnsentMessages();
        try {
            /*
             * This is the callback from streaming new local messages to the server.
             */
            RestMethod.StreamingOutput out = new RestMethod.StreamingOutput() {
                @Override
                public void write(final OutputStream os) throws IOException {
                    try {
                        BufferedOutputStream bf = new BufferedOutputStream(os);
                        OutputStreamWriter ow = new OutputStreamWriter(bf);
                        JsonWriter wr = new JsonWriter(ow);
                        wr.beginArray();

                        if (messages.moveToFirst()) {
                            do {
                                ChatMessage m = messages.getEntity();
                                wr.beginObject();

                                wr.name("chatroom");
                                wr.value(m.chatRoom);
                                wr.name("timestamp");
                                wr.value(m.timestamp.getTime());
                                wr.name("latitude");
                                wr.value(m.latitude);
                                wr.name("longitude");
                                wr.value(m.longitude);
                                wr.name("text");
                                wr.value(m.messageText);

                                wr.endObject();
                            } while (messages.moveToNext());
                        }

                        wr.endArray();
                        wr.flush();
                    } finally {
                        messages.close();
                    }
                }
            };
            /*
             * Connect to the server and upload messages not yet shared.
             */
            response = restMethod.perform(request, out);

            /*
             * Stream downloaded peer and message information, and update the database.
             * The connection is closed in the finally block below.
             */
            JsonReader rd = new JsonReader(new InputStreamReader(new BufferedInputStream(response.getInputStream()), StringUtils.CHARSET));
            ArrayList<Peer> peers = null;
            ArrayList<ChatMessage> newMessages = null;
            String next;
            rd.beginObject();

            next = rd.nextName();

            if (next.equals("clients"))
                peers = handlePeers(rd);
            else if (next.equals("messages"))
                newMessages = handleMessages(rd);

            next = rd.nextName();

            if (next.equals("clients"))
                peers = handlePeers(rd);
            else if (next.equals("messages"))
                newMessages = handleMessages(rd);

            rd.endObject();

            if (peers == null || newMessages == null)
                throw new InvalidParameterException("Invalid response from server");

            for (Peer p : peers) {
                peerManager.persistSync(p); // On background thread, okay to do this
            }

            for (ChatMessage message : newMessages) {
                message.id = requestManager.getMessageID(message, context);
                if (message.id < 0) {
                    Peer p = peerManager.getPeerSync(message.senderId);
                    if (p != null) {
                        message.sender = p.name;
                        this.requestManager.persist(message);
                    }
                } else {
                    requestManager.updateSeqNum(message.id, message.sequenceNum);
                }
            }

            return response.getResponse();

        } catch (IOException e) {
            return new ErrorResponse(0, ErrorResponse.Status.SERVER_ERROR, e.getMessage());

        } finally {
            if (response != null) {
                response.disconnect();
            }
        }
    }

    private ArrayList<Peer> handlePeers(JsonReader rd) {
        ArrayList<Peer> res = new ArrayList<>();

        try {
            rd.beginArray();
            while (rd.hasNext()) {
                Peer next = new Peer();
                rd.beginObject();
                do {
                    String token = rd.nextName();

                    switch (token) {
                        case "id":
                            next.id = rd.nextLong();
                            break;
                        case "username":
                            next.name = rd.nextString();
                            break;
                        case "timestamp":
                            next.timestamp = new Date(rd.nextLong());
                            break;
                        case "latitude":
                            next.latitude = rd.nextDouble();
                            break;
                        case "longitude":
                            next.longitude = rd.nextDouble();
                            break;
                        default: // Unknown JSON key
                            rd.skipValue();
                            break;
                    }

                } while (rd.hasNext());

                res.add(next);
                rd.endObject();
            }

            rd.endArray();
        } catch(Exception e) {}

        return res;
    }

    private ArrayList<ChatMessage> handleMessages(JsonReader rd) {
        ArrayList<ChatMessage> res = new ArrayList<>();

        try {
            rd.beginArray();
            while (rd.hasNext()) {
                ChatMessage next = new ChatMessage();
                rd.beginObject();
                do {
                    String token = rd.nextName();

                    switch (token) {
                        case "chatroom":
                            next.chatRoom = rd.nextString();
                            break;
                        case "timestamp":
                            next.timestamp = new Date(rd.nextLong());
                            break;
                        case "latitude":
                            next.latitude = rd.nextDouble();
                            break;
                        case "longitude":
                            next.longitude = rd.nextDouble();
                            break;
                        case "seqnum":
                            next.sequenceNum = rd.nextLong();
                            break;
                        case "sender":
                            next.senderId = rd.nextLong();
                            break;
                        case "text":
                            next.messageText = rd.nextString();
                            break;
                        default: // Unknown JSON key
                            rd.skipValue();
                            break;
                    }

                } while (rd.hasNext());

                res.add(next);
                rd.endObject();
            }

            rd.endArray();
        } catch(Exception e) {}

        return res;
    }
}
