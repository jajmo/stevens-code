package edu.stevens.cs522.chat.contracts;

import android.content.ContentValues;
import android.database.Cursor;
import android.net.Uri;
import android.provider.BaseColumns;

import java.util.Date;

/**
 * Created by dduggan.
 */

public class MessageContract extends BaseContract {
    public static final Uri CONTENT_URI = CONTENT_URI(AUTHORITY, "Message");

    public static final Uri CONTENT_URI(long id) {
        return CONTENT_URI(Long.toString(id));
    }

    public static final Uri CONTENT_URI(String id) {
        return withExtendedPath(CONTENT_URI, id);
    }

    public static final String CONTENT_PATH = CONTENT_PATH(CONTENT_URI);
    public static final String CONTENT_PATH_ITEM = CONTENT_PATH(CONTENT_URI("#"));

    public static final String ID = _ID;
    public static final String MESSAGE_TEXT = "message_text";
    public static final String TIMESTAMP = "timestamp";
    public static final String SENDER = "sender";
    public static final String SENDER_ID = "sender_id";
    public static final String SEQUENCE_NUM = "sequence_num";
    public static final String PEER_INDEX = "PeerIndex";
    public static final String CHAT_ROOM = "chat_room";

    public static String contentType(String content) {
        return "vnd.android.cursor/vnd." + AUTHORITY + "." + content + "s";
    }

    public static String contentItemType(String content) {
        return "vnd.android.cursor.item/vnd." + AUTHORITY + "." + content;
    }

    private static int idColumn = -1;
    public static long getId(Cursor cursor) {
        if (idColumn < 0) {
            idColumn = cursor.getColumnIndexOrThrow(ID);
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
    public static void putTimestamp(ContentValues out, Date timestamp) {
        out.put(TIMESTAMP, timestamp.getTime());
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

    private static int sequenceNumColumn = -1;
    public static long getSequenceNum(Cursor cursor) {
        if (sequenceNumColumn < 0) {
            sequenceNumColumn = cursor.getColumnIndexOrThrow(SEQUENCE_NUM);
        }
        return cursor.getLong(sequenceNumColumn);
    }
    public static void putSequenceNum(ContentValues out, long sequenceNum) { out.put(SEQUENCE_NUM, sequenceNum); }

    private static int chatRoomColumn = -1;
    public static String getChatRoom(Cursor cursor) {
        if (chatRoomColumn < 0) {
            chatRoomColumn = cursor.getColumnIndexOrThrow(CHAT_ROOM);
        }
        return cursor.getString(chatRoomColumn);
    }
    public static void putChatRoom(ContentValues out, String chatRoom) {
        out.put(CHAT_ROOM, chatRoom);
    }

    private static int senderIdColumn = -1;
    public static long getSenderId(Cursor cursor) {
        if (senderIdColumn < 0) {
            senderColumn = cursor.getColumnIndexOrThrow(SENDER_ID);
        }
        return cursor.getLong(senderIdColumn);
    }
    public static void putSenderId(ContentValues out, long id) {
        out.put(SENDER_ID, id);
    }
}
