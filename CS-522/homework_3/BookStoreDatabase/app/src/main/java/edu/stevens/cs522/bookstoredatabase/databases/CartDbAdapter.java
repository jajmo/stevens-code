package edu.stevens.cs522.bookstoredatabase.databases;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.SQLException;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.util.Log;

import edu.stevens.cs522.bookstoredatabase.contracts.AuthorContract;
import edu.stevens.cs522.bookstoredatabase.contracts.BookContract;
import edu.stevens.cs522.bookstoredatabase.entities.Author;
import edu.stevens.cs522.bookstoredatabase.entities.Book;

/**
 * Created by dduggan.
 */

public class CartDbAdapter {

    private static final String DATABASE_NAME = "books.db";
    private static final String BOOK_TABLE = "books";
    private static final String AUTHOR_TABLE = "authors";

    // Book columns
    public static final String BOOK_ID = BookContract._ID;
    public static final String TITLE = BookContract.TITLE;
    public static final String PRICE = BookContract.PRICE;
    public static final String ISBN = BookContract.ISBN;
    public static final String AUTHORS = BookContract.AUTHORS;

    // Author columns
    public static final String AUTHOR_ID = AuthorContract._ID;
    public static final String FIRST_NAME = AuthorContract.FIRST_NAME;
    public static final String MIDDLE_NAME = AuthorContract.MIDDLE_INITIAL;
    public static final String LAST_NAME = AuthorContract.LAST_NAME;
    public static final String BOOK_FK = AuthorContract.BOOK_FK;
    public static final String BOOK_IDX = "AuthorsBookIndex";

    // Base queries
    private static final String BASE_QUERY_BEFORE_GROUP = "SELECT "
            + BOOK_TABLE + "." + BOOK_ID + ", "
            + TITLE + ", "
            + PRICE + ", "
            + ISBN + ", "
            + "GROUP_CONCAT(COALESCE(" + FIRST_NAME + ", '') || ' ' || COALESCE("
            + MIDDLE_NAME + ", '') || ' ' || COALESCE(" + LAST_NAME + ", ''), " +
            "'" + BookContract.SEPARATOR_CHAR + "') AS " + AUTHORS
            + " FROM " + BOOK_TABLE
            + " LEFT JOIN " + AUTHOR_TABLE + " ON "
            + BOOK_TABLE + "." + BOOK_ID + " = " + AUTHOR_TABLE + "." + BOOK_FK + " ";
    private static final String BASE_QUERY_GROUP = " GROUP BY " +
            BOOK_TABLE + "." + BOOK_ID + ", " + TITLE + ", " + PRICE + ", " + ISBN;

    private static final int DATABASE_VERSION = 3;

    private DatabaseHelper dbHelper;
    private SQLiteDatabase db;
    private final Context context;

    public static class DatabaseHelper extends SQLiteOpenHelper {

        private static final String CREATE_BOOKS = "CREATE TABLE " + BOOK_TABLE + " ("
                + BOOK_ID + " INTEGER PRIMARY KEY, "
                + TITLE + " TEXT NOT NULL, "
                + PRICE + " TEXT NOT NULL, "
                + ISBN + " TEXT NOT NULL);";

        private static final String CREATE_AUTHORS = "CREATE TABLE " + AUTHOR_TABLE + " ("
                + AUTHOR_ID + " INTEGER PRIMARY KEY, "
                + FIRST_NAME + " TEXT, "
                + MIDDLE_NAME + " TEXT, "
                + LAST_NAME + " TEXT, "
                + BOOK_FK + " INTEGER NOT NULL, "
                + "FOREIGN KEY (" + BOOK_FK + ") REFERENCES " + BOOK_TABLE + "(" + BOOK_ID + ") "
                + "ON DELETE CASCADE);"
                + " CREATE INDEX " + BOOK_IDX + " ON " + AUTHOR_TABLE + "(" + BOOK_FK + ");";

        public DatabaseHelper(Context context, String name, SQLiteDatabase.CursorFactory factory, int version) {
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
                db.execSQL("DROP TABLE IF EXISTS " + BOOK_TABLE);
                db.execSQL("DROP TABLE IF EXISTS " + AUTHOR_TABLE);
                onCreate(db);
            }
        }
    }

    public CartDbAdapter(Context _context) {
        this.context = _context;
        this.dbHelper = new DatabaseHelper(context, DATABASE_NAME, null, DATABASE_VERSION);
    }

    public CartDbAdapter open() throws SQLException {
        this.db = dbHelper.getWritableDatabase();
        db.execSQL("PRAGMA foreign_keys=ON;");
        return this;
    }

    public Cursor fetchAllBooks() {
        return db.rawQuery(BASE_QUERY_BEFORE_GROUP + BASE_QUERY_GROUP, null);
    }

    public Book fetchBook(long rowId) {
        String selection = "WHERE " + BOOK_TABLE + "." + BOOK_ID + " = " + rowId;
        Cursor c = db.rawQuery(BASE_QUERY_BEFORE_GROUP + selection + BASE_QUERY_GROUP, null);
        if (!c.moveToFirst())
            throw new SQLException("Invalid ID");
        return new Book(c);
    }

    public void persist(Book book) throws SQLException {
        ContentValues cv = new ContentValues();
        book.writeToProvider(cv);
        long id = db.insert(BOOK_TABLE, null, cv);
        this.persist(book.authors, id);
    }

    public void persist(Author[] author, long id) throws SQLException {
        int i;

        for (i = 0; i < author.length; i++) {
            ContentValues cv = new ContentValues();
            author[i].writeToProvder(cv);
            AuthorContract.putBookFk(cv, id);
            db.insert(AUTHOR_TABLE, null, cv);
        }
    }

    public boolean delete(Book book) {
        String where = BOOK_ID + " = " + book.id;
        db.delete(BOOK_TABLE, where, null);
        return false;
    }

    public boolean delete(long id) {
        String where = BOOK_ID + " = " + id;
        db.delete(BOOK_TABLE, where, null);
        return false;
    }

    public boolean deleteAll() {
        db.execSQL("DELETE FROM " + BOOK_TABLE);
        return false;
    }

    public void close() {
        this.db.close();
    }
}
