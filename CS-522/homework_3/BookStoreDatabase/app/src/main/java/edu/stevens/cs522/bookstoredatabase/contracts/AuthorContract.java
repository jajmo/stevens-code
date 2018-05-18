package edu.stevens.cs522.bookstoredatabase.contracts;

import android.content.ContentValues;
import android.database.Cursor;
import android.provider.BaseColumns;

import edu.stevens.cs522.bookstoredatabase.entities.Author;

import static android.R.attr.author;

/**
 * Created by dduggan.
 */

public class AuthorContract implements BaseColumns {

    public static final String _ID = "_id";
    public static final String FIRST_NAME = "first";
    public static final String MIDDLE_INITIAL = "initial";
    public static final String LAST_NAME = "last";
    public static final String BOOK_FK = "book_fk";

    /*
     * FIRST_NAME column
     */
    private static int firstNameColumn = -1;
    public static String getFirstName(Cursor cursor) {
        if (firstNameColumn < 0) {
            firstNameColumn =  cursor.getColumnIndexOrThrow(FIRST_NAME);;
        }
        return cursor.getString(firstNameColumn);
    }

    public static void putFirstName(ContentValues values, String firstName) {
        values.put(FIRST_NAME, firstName);
    }

    private static int middleNameColumn = -1;
    public static String getMiddleName(Cursor cursor) {
        if (middleNameColumn < 0) {
            middleNameColumn = cursor.getColumnIndexOrThrow(MIDDLE_INITIAL);
        }
        return cursor.getString(middleNameColumn);
    }
    public static void putMiddleName(ContentValues values, String middleName) {
        values.put(MIDDLE_INITIAL, middleName);
    }

    private static int lastNameColumn = -1;
    public static String getLastName(Cursor cursor) {
        if (lastNameColumn < 0) {
            lastNameColumn = cursor.getColumnIndexOrThrow(LAST_NAME);
        }
        return cursor.getString(lastNameColumn);
    }
    public static void putLastName(ContentValues values, String lastName) {
        values.put(LAST_NAME, lastName);
    }

    public static void putBookFk(ContentValues values, long bookFk) {
        values.put(BOOK_FK, bookFk);
    }
}
