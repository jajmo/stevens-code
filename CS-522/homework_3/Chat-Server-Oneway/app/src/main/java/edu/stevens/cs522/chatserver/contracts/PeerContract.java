package edu.stevens.cs522.chatserver.contracts;

import android.content.ContentValues;
import android.database.Cursor;
import android.provider.BaseColumns;

import com.google.common.net.InetAddresses;

import java.net.InetAddress;
import java.util.Date;

/**
 * Created by dduggan.
 */

public class PeerContract implements BaseColumns {
    public static final String _ID = "_id";
    public static final String NAME = "name";
    public static final String TIMESTAMP = "timestamp";
    public static final String ADDRESS = "address";
    public static final String PORT = "port";
    public static final String NAME_INDEX = "PeerNameIndex";

    private static int idColumn = -1;
    public static long getId(Cursor cursor) {
        if (idColumn < 0) {
            idColumn = cursor.getColumnIndexOrThrow(_ID);
        }
        return cursor.getLong(idColumn);
    }

    private static int nameColumn = -1;
    public static String getName(Cursor cursor) {
        if (nameColumn < 0) {
            nameColumn = cursor.getColumnIndexOrThrow(NAME);
        }
        return cursor.getString(nameColumn);
    }
    public static void putName(ContentValues out, String name) {
        out.put(NAME, name);
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

    private static int addressColumn = -1;
    public static InetAddress getAddress(Cursor cursor) {
        if (addressColumn < 0) {
            addressColumn = cursor.getColumnIndexOrThrow(ADDRESS);
        }
        return InetAddresses.forString(cursor.getString(addressColumn));
    }
    public static void putAddress(ContentValues out, InetAddress address) {
        out.put(ADDRESS, address.getHostAddress());
    }

    private static int portColumn = -1;
    public static int getPort(Cursor cursor) {
        if (portColumn < 0) {
            portColumn = cursor.getColumnIndexOrThrow(PORT);
        }
        return cursor.getInt(portColumn);
    }
    public static void putPort(ContentValues out, int port) {
        out.put(PORT, port);
    }
}
