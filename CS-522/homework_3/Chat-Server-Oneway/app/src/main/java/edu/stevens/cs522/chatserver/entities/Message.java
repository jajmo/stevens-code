package edu.stevens.cs522.chatserver.entities;

import android.content.ContentValues;
import android.database.Cursor;
import android.os.Parcel;
import android.os.Parcelable;

import java.util.Date;

import edu.stevens.cs522.chatserver.contracts.MessageContract;

/**
 * Created by dduggan.
 */

public class Message implements Parcelable {

    public long id;
    public String messageText;
    public Date timestamp;
    public String sender;
    public long senderId;

    public Message() {}

    public Message(Parcel in) {
        this.id = in.readLong();
        this.messageText = in.readString();
        this.timestamp = (Date) in.readValue(Date.class.getClassLoader());
        this.sender = in.readString();
        this.senderId = in.readLong();
    }

    public Message(Cursor in) {
        this.id = MessageContract.getId(in);
        this.messageText = MessageContract.getMessageText(in);
        this.timestamp = MessageContract.getTimestamp(in);
        this.sender = MessageContract.getSender(in);
        this.senderId = MessageContract.getSenderId(in);
    }

    public void writeToProvier(ContentValues out) {
        MessageContract.putMessageText(out, this.messageText);
        MessageContract.putTimestamp(out, this.timestamp);
        MessageContract.putSender(out, this.sender);
        MessageContract.putSenderId(out, this.senderId);
    }

    @Override
    public int describeContents() {
        return 0;
    }

    @Override
    public void writeToParcel(Parcel out, int flags) {
        out.writeLong(this.id);
        out.writeString(this.messageText);
        out.writeValue(this.timestamp);
        out.writeString(this.sender);
        out.writeLong(this.senderId);
    }

    public static final Creator<Message> CREATOR =
            new Creator<Message>() {
                @Override
                public Message createFromParcel(Parcel source) {
                    return new Message(source);
                }

                @Override
                public Message[] newArray(int size) {
                    return new Message[size];
                }
            };
}
