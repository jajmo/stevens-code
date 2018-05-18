package edu.stevens.cs522.chatserver.databases;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.SQLException;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

import edu.stevens.cs522.chatserver.contracts.MessageContract;
import edu.stevens.cs522.chatserver.contracts.PeerContract;
import edu.stevens.cs522.chatserver.entities.Message;
import edu.stevens.cs522.chatserver.entities.Peer;

/**
 * Created by dduggan.
 */

public class MessagesDbAdapter {

    private static final String DATABASE_NAME = "messages.db";
    private static final String MESSAGE_TABLE = "messages";
    private static final String PEER_TABLE = "view_peers";

    private static final int DATABASE_VERSION = 9;
    private DatabaseHelper dbHelper;
    private SQLiteDatabase db;


    public static class DatabaseHelper extends SQLiteOpenHelper {

        private static final String CREATE_PEER = "CREATE TABLE " + PEER_TABLE + " ("
                + PeerContract._ID + " INTEGER PRIMARY KEY, "
                + PeerContract.NAME + " TEXT NOT NULL, "
                + PeerContract.TIMESTAMP + " BIGINT NOT NULL, "
                + PeerContract.ADDRESS + " TEXT NOT NULL, "
                + PeerContract.PORT + " INTEGER NOT NULL);";

        private static final String CREATE_MESSAGE = "CREATE TABLE " + MESSAGE_TABLE + " ("
                + MessageContract._ID + " INTEGER PRIMARY KEY, "
                + MessageContract.MESSAGE_TEXT + " TEXT, "
                + MessageContract.TIMESTAMP + " BIGINT NOT NULL, "
                + MessageContract.SENDER + " TEXT NOT NULL, "
                + MessageContract.SENDER_ID + " INTEGER NOT NULL, "
                + "FOREIGN KEY (" + MessageContract.SENDER_ID + ") REFERENCES "
                + PEER_TABLE + "(" + PeerContract._ID + ") ON DELETE CASCADE);"
                + "CREATE INDEX " + MessageContract.PEER_INDEX + " ON " + MESSAGE_TABLE + "(" + MessageContract.SENDER_ID + ");"
                + "CREATE INDEX " + PeerContract.NAME_INDEX + " ON " + PEER_TABLE + "(" + PeerContract.NAME + ");";

        public DatabaseHelper(Context context, String name, SQLiteDatabase.CursorFactory factory, int version) {
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
                db.execSQL("DROP TABLE IF EXISTS " + MESSAGE_TABLE);
                db.execSQL("DROP TABLE IF ExISTS " + PEER_TABLE);
                onCreate(db);
            }
        }
    }


    public MessagesDbAdapter(Context _context) {
        dbHelper = new DatabaseHelper(_context, DATABASE_NAME, null, DATABASE_VERSION);
    }

    public void open() throws SQLException {
        this.db = dbHelper.getWritableDatabase();
        db.execSQL("PRAGMA foreign_keys=ON;");
    }

    public Cursor fetchAllMessages() {
        String[] projection = {MessageContract._ID, MessageContract.MESSAGE_TEXT, MessageContract.SENDER};
        return this.db.query(MESSAGE_TABLE, projection, null, null, null, null, null);
    }

    public Cursor fetchAllPeers() {
        String[] projection = {PeerContract._ID, PeerContract.NAME};
        return this.db.query(PEER_TABLE, projection, null, null, null, null, null);
    }

    public Peer fetchPeer(long peerId) {
        String where = PeerContract._ID + " =?";
        String[] whereArgs = {Long.toString(peerId)};
        Cursor c = this.db.query(PEER_TABLE, null, where, whereArgs, null, null, null);
        if (c.moveToFirst())
            return new Peer(c);
        throw new SQLException("Invalid peer ID");
    }

    public Cursor fetchMessagesFromPeer(Peer peer) {
        String where = MessageContract.SENDER_ID + " =?";
        String[] whereArgs = {Long.toString(peer.id)};
        return this.db.query(MESSAGE_TABLE, null, where, whereArgs, null, null, null);
    }

    public void persist(Message message) throws SQLException {
        ContentValues cv = new ContentValues();
        message.writeToProvier(cv);
        this.db.insert(MESSAGE_TABLE, null, cv);
    }

    /**
     * Add a peer record if it does not already exist; update information if it is already defined.
     * @param peer
     * @return The database key of the (inserted or updated) peer record
     * @throws SQLException
     */
    public long persist(Peer peer) throws SQLException {
        String selection = PeerContract.NAME + "=?";
        String[] selectionArgs = {peer.name};
        Cursor c = db.query(PEER_TABLE, null, selection, selectionArgs, null, null, null);
        if (c.moveToFirst()) {
            // Peer already in database - update timestamp
            Peer p = new Peer(c);
            p.updateTimestamp();
            ContentValues cv = new ContentValues();
            p.writeToProvider(cv);
            return this.db.update(PEER_TABLE, cv, selection, selectionArgs);
        } else {
            // Peer not in database
            ContentValues cv = new ContentValues();
            peer.writeToProvider(cv);
            peer.id = this.db.insert(PEER_TABLE, null, cv);
            return peer.id;
        }
    }

    public void close() {
        this.db.close();
    }
}