package edu.stevens.cs522.chat.rest;

import android.net.Uri;
import android.os.Parcel;
import android.util.JsonReader;
import android.util.JsonWriter;
import android.util.Log;

import java.io.IOException;
import java.io.StringWriter;
import java.net.HttpURLConnection;
import java.util.Date;
import java.util.HashMap;
import java.util.Map;
import java.util.UUID;

import edu.stevens.cs522.chat.util.DateUtils;

/**
 * Created by dduggan.
 */

public class PostMessageRequest extends Request {

    public String chatRoom;
    public String message;

    public PostMessageRequest(long senderId, UUID clientID, String chatRoom, String message) {
        super(senderId, clientID);
        this.chatRoom = chatRoom;
        this.message = message;
    }

    @Override
    public String getRequestEntity() throws IOException {
        StringWriter wr = new StringWriter();
        JsonWriter jw = new JsonWriter(wr);

        jw.beginObject();
        jw.name("chatroom");
        jw.value(this.chatRoom);
        jw.name("text");
        jw.value(this.message);
        jw.endObject();

        return wr.toString();
    }

    @Override
    public Response getResponse(HttpURLConnection connection, JsonReader rd) throws IOException{
        return new PostMessageResponse(connection);
    }

    @Override
    public Response process(RequestProcessor processor) {
        return processor.perform(this);
    }

    @Override
    public int describeContents() {
        return 0;
    }

    @Override
    public void writeToParcel(Parcel dest, int flags) {
        super.writeToParcel(dest, flags);
        dest.writeString(this.chatRoom);
        dest.writeString(this.message);
    }

    public PostMessageRequest(Parcel in) {
        super(in);
        this.chatRoom = in.readString();
        this.message = in.readString();
    }

    public static Creator<PostMessageRequest> CREATOR = new Creator<PostMessageRequest>() {
        @Override
        public PostMessageRequest createFromParcel(Parcel source) {
            return new PostMessageRequest(source);
        }

        @Override
        public PostMessageRequest[] newArray(int size) {
            return new PostMessageRequest[size];
        }
    };

}
