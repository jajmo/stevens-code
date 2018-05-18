package edu.stevens.cs522.chat.contracts;

import android.content.ContentValues;
import android.database.Cursor;
import android.net.Uri;
import android.provider.BaseColumns;

import com.google.common.net.InetAddresses;

import java.net.InetAddress;
import java.util.Date;

import edu.stevens.cs522.chat.util.InetAddressUtils;

/**
 * Created by dduggan.
 */

public class PeerContract extends BaseContract {
    public static final Uri CONTENT_URI = CONTENT_URI(AUTHORITY, "Peer");
    public static final Uri CONTENT_URI(long id) {
        return CONTENT_URI(Long.toString(id));
    }
    public static final Uri CONTENT_URI(String id) {
        return withExtendedPath(CONTENT_URI, id);
    }

    public static final String CONTENT_PATH = CONTENT_PATH(CONTENT_URI);
    public static final String CONTENT_PATH_ITEM = CONTENT_PATH(CONTENT_URI("#"));

    public static final String ID = _ID;
    public static final String NAME = "name";
    public static final String TIMESTAMP = "timestamp";
    public static final String NAME_INDEX = "PeerNameIndex";
    public static final String LONGITUDE = "longitude";
    public static final String LATITUDE = "latitude";

    public static final String[] COLUMNS = { ID, NAME, TIMESTAMP, LONGITUDE, LATITUDE };

    public static String contentType(String content) {
        return "vnd.android.cursor/vnd." + AUTHORITY + "." + content + "s";
    }

    public static String contentItemType(String content) {
        return "vnd.android.cursor.item/vnd." + AUTHORITY + "." + content;
    }

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

    private static int longitudeColumn = -1;
    public static double getLongitude(Cursor cursor) {
        if (longitudeColumn < 0) {
            longitudeColumn = cursor.getColumnIndexOrThrow(LONGITUDE);
        }
        return cursor.getDouble(longitudeColumn);
    }
    public static void putLongitude(ContentValues out, double longitude) {
        out.put(LONGITUDE, longitude);
    }

    private static int latitudeColumn = -1;
    public static double getLatitude(Cursor cursor) {
        if (latitudeColumn < 0) {
            latitudeColumn = cursor.getColumnIndexOrThrow(LATITUDE);
        }
        return cursor.getDouble(latitudeColumn);
    }
    public static void putLatitude(ContentValues out, double latitude) {
        out.put(LATITUDE, latitude);
    }
}
