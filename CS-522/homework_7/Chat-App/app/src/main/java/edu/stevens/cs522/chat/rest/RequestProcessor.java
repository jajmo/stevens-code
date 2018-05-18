package edu.stevens.cs522.chat.rest;

import android.content.Context;
import android.net.Uri;
import android.util.Log;

import edu.stevens.cs522.chat.entities.ChatMessage;
import edu.stevens.cs522.chat.managers.MessageManager;
import edu.stevens.cs522.chat.settings.Settings;
import edu.stevens.cs522.chat.util.DateUtils;

/**
 * Created by dduggan.
 */

public class RequestProcessor {

    private Context context;
    private RestMethod restMethod;

    public RequestProcessor(Context context) {
        this.context = context;
        this.restMethod = new RestMethod(context);
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
        MessageManager manager = new MessageManager(this.context);
        manager.persistAsync(m);

        Response response = restMethod.perform(request);

        if (response instanceof PostMessageResponse) {
            m.sequenceNum = ((PostMessageResponse) response).messageId;
            manager.updateAsync(m);
        }
        return response;
    }

}
