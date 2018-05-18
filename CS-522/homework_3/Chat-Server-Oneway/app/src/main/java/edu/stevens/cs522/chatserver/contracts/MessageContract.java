package edu.stevens.cs522.chatserver.contracts;

import android.content.ContentValues;
import android.database.Cursor;
import android.provider.BaseColumns;

import java.util.Date;

/**
 * Created by dduggan.
 */

public class MessageContract implements BaseColumns {

    public static final String _ID = "_id";
    public static final String MESSAGE_TEXT = "message_text";
    public static final String TIMESTAMP = "timestamp";
    public static final String SENDER = "sender";
    public static final String SENDER_ID = "sender_id";
    //public static final String PEER_FK = "peer_fk";
    public static final String PEER_INDEX = "MessagesPeerIndex";

    private static int idColumn = -1;
    public static long getId(Cursor cursor) {
        if (idColumn < 0) {
            idColumn = cursor.getColumnIndexOrThrow(_ID);
        }
        return cursor.getLong(idColumn);
    }

    private static int messageTextColumn = -1;
    public static String getMessageText(Cursor cursor) {
        if (messageTextColumn < 0) {
            messageTextColumn = cursor.getColumnIndexOrThrow(MESSAGE_TEXT);
        }
        return cursor.getString(messageTextColumn);
    }
    public static void putMessageText(ContentValues out, String messageText) {
        out.put(MESSAGE_TEXT, messageText);
    }

    private static int timestampColumn = -1;
    public static Date getTimestamp(Cursor cursor) {
        if (timestampColumn < 0) {
            timestampColumn = cursor.getColumnIndexOrThrow(TIMESTAMP);
        }
        return new Date(cursor.getLong(timestampColumn));
    }
    public static void putTimestamp(ContentValues out, Date date) {
        out.put(TIMESTAMP, date.getTime());
    }

    private static int senderColumn = -1;
    public static String getSender(Cursor cursor) {
        if (senderColumn < 0) {
            senderColumn = cursor.getColumnIndexOrThrow(SENDER);
        }
        return cursor.getString(senderColumn);
    }
    public static void putSender(ContentValues out, String sender) {
        out.put(SENDER, sender);
    }

    private static int senderIdColumn = -1;
    public static long getSenderId(Cursor cursor) {
        if (senderIdColumn < 0) {
            senderIdColumn = cursor.getColumnIndexOrThrow(SENDER_ID);
        }
        return cursor.getLong(senderIdColumn);
    }
    public static void putSenderId(ContentValues out, long id) {
        out.put(SENDER_ID, id);
    }
}
