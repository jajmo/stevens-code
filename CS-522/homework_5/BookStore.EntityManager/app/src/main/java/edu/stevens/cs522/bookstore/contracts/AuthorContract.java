package edu.stevens.cs522.bookstore.contracts;

import android.content.ContentValues;
import android.database.Cursor;
import android.net.Uri;
import android.provider.BaseColumns;

/**
 * Created by dduggan.
 */

public class AuthorContract implements BaseColumns {

    public static final String ID = _ID;
    public static final String NAME = "name";
    public static final String BOOK_FK = "book_fk";
    public static final String BOOK_IDX = "AuthorsBookIndex";

    private static int idColumn = -1;
    public static long getId(Cursor cursor) {
        if (idColumn < 0) {
            idColumn = cursor.getColumnIndexOrThrow(ID);
        }
        return cursor.getLong(idColumn);
    }

    private static int nameColumn = -1;
    public static String getFirstName(Cursor cursor) {
        if (nameColumn < 0) {
            nameColumn =  cursor.getColumnIndexOrThrow(NAME);;
        }
        return cursor.getString(nameColumn);
    }
    public static void putFirstName(ContentValues values, String firstName) {
        values.put(NAME, firstName);
    }

    public static void putBookId(ContentValues values, long fk) {
        values.put(BOOK_FK, fk);
    }
}
