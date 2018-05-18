package edu.stevens.cs522.bookstore.providers;

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

import edu.stevens.cs522.bookstore.contracts.AuthorContract;
import edu.stevens.cs522.bookstore.contracts.BookContract;
import edu.stevens.cs522.bookstore.entities.Author;

import static edu.stevens.cs522.bookstore.contracts.BookContract.AUTHORS;
import static edu.stevens.cs522.bookstore.contracts.BookContract.CONTENT_PATH;
import static edu.stevens.cs522.bookstore.contracts.BookContract.CONTENT_PATH_ITEM;
import static edu.stevens.cs522.bookstore.contracts.BookContract.getId;

public class BookProvider extends ContentProvider {
    public BookProvider() {}

    private static final String AUTHORITY = BookContract.AUTHORITY;

    private static final String CONTENT_PATH = BookContract.CONTENT_PATH;
    private static final String CONTENT_PATH_ITEM = BookContract.CONTENT_PATH_ITEM;

    private static final String DATABASE_NAME = "books.db";
    private static final int DATABASE_VERSION = 1;
    private static final String BOOKS_TABLE = "books";
    private static final String AUTHORS_TABLE = "authors";

    // Create the constants used to differentiate between the different URI  requests.
    private static final int ALL_ROWS = 1;
    private static final int SINGLE_ROW = 2;

    // Base queries
    private static final String BASE_QUERY_BEFORE_GROUP = "SELECT "
            + BOOKS_TABLE + "." + BookContract.ID + ", "
            + BookContract.TITLE + ", "
            + BookContract.PRICE + ", "
            + BookContract.ISBN + ", "
            + "GROUP_CONCAT(" + AuthorContract.NAME + ", '" + BookContract.SEPARATOR_CHAR + "') AS " + BookContract.AUTHORS
            + " FROM " + BOOKS_TABLE
            + " LEFT JOIN " + AUTHORS_TABLE + " ON "
            + BOOKS_TABLE + "." + BookContract.ID + " = " + AUTHORS_TABLE + "." + AuthorContract.BOOK_FK + " ";
    private static final String BASE_QUERY_GROUP = " GROUP BY " +
            BOOKS_TABLE + "." + BookContract.ID + ", " + BookContract.TITLE + ", " + BookContract.PRICE + ", " + BookContract.ISBN;

    public static class DbHelper extends SQLiteOpenHelper {

        private static final String CREATE_BOOKS = "CREATE TABLE " + BOOKS_TABLE + " ("
                + BookContract.ID+ " INTEGER PRIMARY KEY, "
                + BookContract.TITLE + " TEXT NOT NULL, "
                + BookContract.PRICE + " TEXT NOT NULL, "
                + BookContract.ISBN + " TEXT NOT NULL);";

        private static final String CREATE_AUTHORS = "CREATE TABLE " + AUTHORS_TABLE + " ("
                + AuthorContract.ID + " INTEGER PRIMARY KEY, "
                + AuthorContract.NAME + " TEXT, "
                + AuthorContract.BOOK_FK + " INTEGER NOT NULL, "
                + "FOREIGN KEY (" + AuthorContract.BOOK_FK + ") REFERENCES " + BOOKS_TABLE + "(" + BookContract.ID + ") "
                + "ON DELETE CASCADE);"
                + " CREATE INDEX " + AuthorContract.BOOK_IDX + " ON " + AUTHORS_TABLE + "(" + AuthorContract.BOOK_FK + ");";

        public DbHelper(Context context, String name, CursorFactory factory, int version) {
            super(context, name, factory, version);
        }

        @Override
        public void onCreate(SQLiteDatabase db) {
            db.execSQL(CREATE_BOOKS);
            db.execSQL(CREATE_AUTHORS);
        }

        @Override
        public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
            if (oldVersion != newVersion) {
                db.execSQL("DROP TABLE IF EXISTS " + BOOKS_TABLE);
                db.execSQL("DROP TABLE IF EXISTS " + AUTHORS_TABLE);
                onCreate(db);
            }
        }

        @Override
        public void onOpen(SQLiteDatabase db) {
            db.execSQL("PRAGMA foreign_keys=ON;");
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
        uriMatcher.addURI(AUTHORITY, CONTENT_PATH, ALL_ROWS);
        uriMatcher.addURI(AUTHORITY, CONTENT_PATH_ITEM, SINGLE_ROW);
    }

    @Override
    public String getType(Uri uri) {
        switch (uriMatcher.match(uri)) {
            case ALL_ROWS:
                return BookContract.contentType("book");
            case SINGLE_ROW:
                return BookContract.contentItemType("book");
            default:
                throw new IllegalStateException("getType: bad case");
        }
    }

    @Override
    public Uri insert(Uri uri, ContentValues values) {
        SQLiteDatabase db = dbHelper.getWritableDatabase();
        ContentValues cv;
        switch (uriMatcher.match(uri)) {
            case ALL_ROWS:
                Author[] authors = Author.fromStringArray(BookContract.readStringArray((String) values.get(BookContract.AUTHORS)));
                values.remove(BookContract.AUTHORS);
                long id = db.insert(BOOKS_TABLE, null, values);

                if (id > 0) {
                    for (Author a : authors) {
                        cv = new ContentValues();
                        a.writeToProvider(cv, id);
                        db.insert(AUTHORS_TABLE, null, cv);
                    }
                    Uri instanceUri = BookContract.CONTENT_URI(id);
                    ContentResolver cr = getContext().getContentResolver();
                    cr.notifyChange(instanceUri, null);
                    return instanceUri;
                }

                throw new SQLException("insert failed");
            case SINGLE_ROW:
                throw new IllegalArgumentException("insert expects a whole-table URI");
            default:
                throw new IllegalStateException("insert: bad case");
        }
    }

    @Override
    public Cursor query(Uri uri, String[] projection, String selection,
                        String[] selectionArgs, String sortOrder) {
        SQLiteDatabase db = dbHelper.getReadableDatabase();
        Cursor cursor;
        switch (uriMatcher.match(uri)) {
            case ALL_ROWS:
                cursor = db.rawQuery(BASE_QUERY_BEFORE_GROUP + BASE_QUERY_GROUP, null);
                cursor.moveToFirst();
                break;
            case SINGLE_ROW:
                String selection2 = BOOKS_TABLE + "." + BookContract.ID + "=?";
                String[] args = new String[]{ Long.toString(BookContract.getId(uri)) };
                cursor = db.rawQuery(BASE_QUERY_BEFORE_GROUP + "WHERE " + selection2 + BASE_QUERY_GROUP, args);
                if (!cursor.moveToFirst())
                    throw new IllegalArgumentException("query: invalid id");
                break;
            default:
                throw new IllegalStateException("query: bad case");
        }

        ContentResolver cr = getContext().getContentResolver();
        cursor.setNotificationUri(cr, uri);
        return cursor;
    }

    @Override
    public int update(Uri uri, ContentValues values, String selection,
                      String[] selectionArgs) {
        throw new IllegalStateException("Update of books not supported");
    }

    @Override
    public int delete(Uri uri, String selection, String[] selectionArgs) {
        SQLiteDatabase db = dbHelper.getWritableDatabase();
        Uri instanceUri;
        int deleted;
        String id = null;
        switch (uriMatcher.match(uri)) {
            case ALL_ROWS:
                deleted = db.delete(BOOKS_TABLE, selection, selectionArgs);
                break;
            case SINGLE_ROW:
                id = Long.toString(BookContract.getId(uri));
                String where = BookContract._ID + "=?";
                String authorWhere = AuthorContract.BOOK_FK + "=?";
                String[] args = new String[]{ id };
                deleted = db.delete(BOOKS_TABLE, where, args);
                db.delete(AUTHORS_TABLE, authorWhere, args); // ON DELETE CASCADE wasn't working properly
                break;
            default:
                throw new IllegalStateException("delete: bad case");
        }

        if (deleted > 0) {
            if (uriMatcher.match(uri) == SINGLE_ROW)
                instanceUri = BookContract.CONTENT_URI(id);
            else
                instanceUri = BookContract.CONTENT_URI;
            ContentResolver cr = getContext().getContentResolver();
            cr.notifyChange(instanceUri, null);
        }

        return deleted;
    }

}
