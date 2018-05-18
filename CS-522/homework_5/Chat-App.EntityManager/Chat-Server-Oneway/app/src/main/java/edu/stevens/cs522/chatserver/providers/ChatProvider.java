package edu.stevens.cs522.chatserver.providers;

import android.content.ContentProvider;
import android.content.ContentResolver;
import android.content.ContentValues;
import android.content.Context;
import android.content.UriMatcher;
import android.database.Cursor;
import android.database.SQLException;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteDatabase.CursorFactory;
import android.database.sqlite.SQLiteOpenHelper;
import android.net.Uri;
import android.util.Log;

import edu.stevens.cs522.chatserver.contracts.BaseContract;
import edu.stevens.cs522.chatserver.contracts.MessageContract;
import edu.stevens.cs522.chatserver.contracts.PeerContract;

public class ChatProvider extends ContentProvider {

    public ChatProvider() {}

    private static final String AUTHORITY = BaseContract.AUTHORITY;
    private static final String MESSAGE_CONTENT_PATH = MessageContract.CONTENT_PATH;
    private static final String MESSAGE_CONTENT_PATH_ITEM = MessageContract.CONTENT_PATH_ITEM;
    private static final String PEER_CONTENT_PATH = PeerContract.CONTENT_PATH;
    private static final String PEER_CONTENT_PATH_ITEM = PeerContract.CONTENT_PATH_ITEM;


    private static final String DATABASE_NAME = "chat.db";
    private static final int DATABASE_VERSION = 1;
    private static final String MESSAGES_TABLE = "messages";
    private static final String PEERS_TABLE = "peers";

    // Create the constants used to differentiate between the different URI  requests.
    private static final int MESSAGES_ALL_ROWS = 1;
    private static final int MESSAGES_SINGLE_ROW = 2;
    private static final int PEERS_ALL_ROWS = 3;
    private static final int PEERS_SINGLE_ROW = 4;

    public static class DbHelper extends SQLiteOpenHelper {

        private static final String CREATE_PEER = "CREATE TABLE " + PEERS_TABLE + " ("
                + PeerContract._ID + " INTEGER PRIMARY KEY, "
                + PeerContract.NAME + " TEXT NOT NULL, "
                + PeerContract.TIMESTAMP + " BIGINT NOT NULL, "
                + PeerContract.ADDRESS + " TEXT NOT NULL, "
                + PeerContract.PORT + " INTEGER NOT NULL);";

        private static final String CREATE_MESSAGE = "CREATE TABLE " + MESSAGES_TABLE + " ("
                + MessageContract._ID + " INTEGER PRIMARY KEY, "
                + MessageContract.MESSAGE_TEXT + " TEXT, "
                + MessageContract.TIMESTAMP + " BIGINT NOT NULL, "
                + MessageContract.SENDER + " TEXT NOT NULL, "
                + MessageContract.SENDER_ID + " INTEGER NOT NULL, "
                + "FOREIGN KEY (" + MessageContract.SENDER_ID + ") REFERENCES "
                + PEERS_TABLE + "(" + PeerContract._ID + ") ON DELETE CASCADE);"
                + "CREATE INDEX " + MessageContract.PEER_INDEX + " ON " + MESSAGES_TABLE + "(" + MessageContract.SENDER_ID + ");"
                + "CREATE INDEX " + PeerContract.NAME_INDEX + " ON " + PEERS_TABLE + "(" + PeerContract.NAME + ");";

        public DbHelper(Context context, String name, CursorFactory factory, int version) {
            super(context, name, factory, version);
        }

        @Override
        public void onCreate(SQLiteDatabase db) {
            db.execSQL(CREATE_PEER);
            db.execSQL(CREATE_MESSAGE);
        }

        @Override
        public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
            if (oldVersion != newVersion) {
                db.execSQL("DROP TABLE IF EXISTS " + MESSAGES_TABLE);
                db.execSQL("DROP TABLE IF EXISTS " + PEERS_TABLE);
                onCreate(db);
            }
        }
    }

    private DbHelper dbHelper;

    @Override
    public boolean onCreate() {
        // Initialize your content provider on startup.
        dbHelper = new DbHelper(getContext(), DATABASE_NAME, null, DATABASE_VERSION);
        return true;
    }

    // Used to dispatch operation based on URI
    private static final UriMatcher uriMatcher;

    // uriMatcher.addURI(AUTHORITY, CONTENT_PATH, OPCODE)
    static {
        uriMatcher = new UriMatcher(UriMatcher.NO_MATCH);
        uriMatcher.addURI(AUTHORITY, MESSAGE_CONTENT_PATH, MESSAGES_ALL_ROWS);
        uriMatcher.addURI(AUTHORITY, MESSAGE_CONTENT_PATH_ITEM, MESSAGES_SINGLE_ROW);
        uriMatcher.addURI(AUTHORITY, PEER_CONTENT_PATH, PEERS_ALL_ROWS);
        uriMatcher.addURI(AUTHORITY, PEER_CONTENT_PATH_ITEM, PEERS_SINGLE_ROW);
    }

    @Override
    public String getType(Uri uri) {
        switch (uriMatcher.match(uri)) {
            case MESSAGES_ALL_ROWS:
                return MessageContract.contentType("message");
            case MESSAGES_SINGLE_ROW:
                return MessageContract.contentItemType("message");
            case PEERS_ALL_ROWS:
                return PeerContract.contentType("peer");
            case PEERS_SINGLE_ROW:
                return PeerContract.contentItemType("peer");
            default:
                throw new IllegalStateException("getType: bad case");
        }
    }

    @Override
    public Uri insert(Uri uri, ContentValues values) {
        SQLiteDatabase db = dbHelper.getWritableDatabase();
        long id;
        switch (uriMatcher.match(uri)) {
            case MESSAGES_ALL_ROWS:
                id = db.insert(MESSAGES_TABLE, null, values);
                if (id > 0) {
                    Uri instance = MessageContract.CONTENT_URI(id);
                    ContentResolver cr = getContext().getContentResolver();
                    cr.notifyChange(instance, null);
                    return instance;
                }

                throw new SQLException("message insertion error");
            case PEERS_ALL_ROWS:
                id = db.insert(PEERS_TABLE, null, values);
                if (id > 0) {
                    Uri instance = PeerContract.CONTENT_URI(id);
                    ContentResolver cr = getContext().getContentResolver();
                    cr.notifyChange(instance, null);
                    return instance;
                }

                throw new SQLException("peer insertion error");
            case MESSAGES_SINGLE_ROW:
            case PEERS_SINGLE_ROW:
                throw new IllegalArgumentException("insert expects a whole-table URI");
            default:
                throw new IllegalStateException("insert: bad case");
        }
    }

    @Override
    public Cursor query(Uri uri, String[] projection, String selection,
                        String[] selectionArgs, String sortOrder) {
        SQLiteDatabase db = dbHelper.getReadableDatabase();
        String where, whereArgs[], projection2[];
        Cursor c;
        switch (uriMatcher.match(uri)) {
            case MESSAGES_ALL_ROWS:
                projection2 = new String[]{ MessageContract.ID, MessageContract.SENDER, MessageContract.MESSAGE_TEXT };
                c = db.query(MESSAGES_TABLE, projection2, selection, selectionArgs, null, null, sortOrder);
                break;
            case PEERS_ALL_ROWS:
                projection2 = new String[]{ PeerContract.ID, PeerContract.NAME, PeerContract.TIMESTAMP, PeerContract.ADDRESS, PeerContract.PORT };
                c = db.query(PEERS_TABLE, projection2, selection, selectionArgs, null, null, sortOrder);
                break;
            case MESSAGES_SINGLE_ROW:
                where = MessageContract.ID + "=?";
                whereArgs = new String[]{ Long.toString(MessageContract.getId(uri)) };
                c = db.query(MESSAGES_TABLE, projection, where, whereArgs, null, null, null, sortOrder);
                break;
            case PEERS_SINGLE_ROW:
                where = PeerContract.ID + "=?";
                whereArgs = new String[]{ Long.toString(PeerContract.getId(uri)) };
                c = db.query(PEERS_TABLE, projection, where, whereArgs, null, null, null, sortOrder);
                break;
            default:
                throw new IllegalStateException("insert: bad case");
        }

        c.moveToFirst();
        c.setNotificationUri(getContext().getContentResolver(), uri);
        return c;
    }

    @Override
    public int update(Uri uri, ContentValues values, String selection,
                      String[] selectionArgs) {
        SQLiteDatabase db = dbHelper.getWritableDatabase();
        int updated;

        switch (uriMatcher.match(uri)) {
            case MESSAGES_SINGLE_ROW:
            case MESSAGES_ALL_ROWS:
                updated = db.update(MESSAGES_TABLE, values, selection, selectionArgs);
                break;
            case PEERS_SINGLE_ROW:
            case PEERS_ALL_ROWS:
                updated = db.update(PEERS_TABLE, values, selection, selectionArgs);
                break;
            default:
                throw new IllegalStateException("update: expects 1 item URI");
        }

        return updated;
    }

    @Override
    public int delete(Uri uri, String selection, String[] selectionArgs) {
        SQLiteDatabase db = dbHelper.getWritableDatabase();
        String where, whereArgs[];
        int count;
        switch (uriMatcher.match(uri)) {
            case MESSAGES_ALL_ROWS:
                count = db.delete(MESSAGES_TABLE, selection, selectionArgs);
                break;
            case MESSAGES_SINGLE_ROW:
                where = MessageContract.ID + "=?";
                whereArgs = new String[]{ Long.toString(MessageContract.getId(uri)) };
                count = db.delete(MESSAGES_TABLE, where, whereArgs);
                break;
            case PEERS_ALL_ROWS:
                where = PeerContract.ID + "=?";
                whereArgs = new String[]{ Long.toString(PeerContract.getId(uri)) };
                count = db.delete(PEERS_TABLE, where, whereArgs);
                break;
            case PEERS_SINGLE_ROW:
                count = db.delete(PEERS_TABLE, selection, selectionArgs);
                break;
            default:
                throw new IllegalStateException("delete: bad case");
        }

        if (count > 0) {
            ContentResolver cr = getContext().getContentResolver();
            cr.notifyChange(uri, null);
        }

        return count;
    }

}
