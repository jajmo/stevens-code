package edu.stevens.cs522.chat.entities;

import android.content.ContentValues;
import android.database.Cursor;
import android.os.Parcel;
import android.os.Parcelable;

import java.util.Date;

import edu.stevens.cs522.chat.contracts.MessageContract;

/**
 * Created by dduggan.
 */

public class ChatMessage implements Parcelable {

    public long id;

    public String messageText;
    public String chatRoom;
    public Date timestamp;
    public String sender;
    public long senderId;
    public long sequenceNum;

    public ChatMessage() {}

    public ChatMessage(Parcel in) {
        this.id = in.readLong();
        this.messageText = in.readString();
        this.timestamp = (Date) in.readValue(Date.class.getClassLoader());
        this.sender = in.readString();
        this.senderId = in.readLong();
        this.sequenceNum = in.readInt();
        this.chatRoom = in.readString();
    }

    public ChatMessage(Cursor in) {
        this.id = MessageContract.getId(in);
        this.messageText = MessageContract.getMessageText(in);
        this.timestamp = MessageContract.getTimestamp(in);
        this.sender = MessageContract.getSender(in);
        this.senderId = MessageContract.getSenderId(in);
        this.sequenceNum = MessageContract.getSequenceNum(in);
        this.chatRoom = MessageContract.getChatRoom(in);
    }

    public void writeToProvier(ContentValues out) {
        MessageContract.putMessageText(out, this.messageText);
        MessageContract.putTimestamp(out, this.timestamp);
        MessageContract.putSender(out, this.sender);
        MessageContract.putSenderId(out, this.senderId);
        MessageContract.putSequenceNum(out, this.sequenceNum);
        MessageContract.putChatRoom(out, this.chatRoom);
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
        out.writeLong(this.sequenceNum);
        out.writeString(this.chatRoom);
    }

    public static final Parcelable.Creator<ChatMessage> CREATOR =
            new Parcelable.Creator<ChatMessage>() {
                @Override
                public ChatMessage createFromParcel(Parcel source) {
                    return new ChatMessage(source);
                }

                @Override
                public ChatMessage[] newArray(int size) {
                    return new ChatMessage[size];
                }
            };
}
