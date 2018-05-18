package edu.stevens.cs522.bookstore.managers;

import android.app.Activity;
import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.net.Uri;
import android.util.Log;

import java.util.List;
import java.util.Set;

import edu.stevens.cs522.bookstore.async.AsyncContentResolver;
import edu.stevens.cs522.bookstore.async.IContinue;
import edu.stevens.cs522.bookstore.async.IEntityCreator;
import edu.stevens.cs522.bookstore.async.QueryBuilder;
import edu.stevens.cs522.bookstore.async.QueryBuilder.IQueryListener;
import edu.stevens.cs522.bookstore.async.SimpleQueryBuilder;
import edu.stevens.cs522.bookstore.contracts.AuthorContract;
import edu.stevens.cs522.bookstore.contracts.BookContract;
import edu.stevens.cs522.bookstore.entities.Book;

/**
 * Created by dduggan.
 */

public class BookManager extends Manager<Book> {

    private static final int LOADER_ID = 1;

    private static final IEntityCreator<Book> creator = new IEntityCreator<Book>() {
        @Override
        public Book create(Cursor cursor) {
            return new Book(cursor);
        }
    };

    private AsyncContentResolver contentResolver;

    public BookManager(Activity context) {
        super(context, creator, LOADER_ID);
        contentResolver = new AsyncContentResolver(context.getContentResolver());
    }

    public void getAllBooksAsync(IQueryListener<Book> listener) {
        executeQuery(BookContract.CONTENT_URI, listener);
    }

    public void getBookAsync(long id, final IContinue<Book> callback) {
        executeSimpleQuery(BookContract.CONTENT_URI(id), new SimpleQueryBuilder.ISimpleQueryListener<Book>() {
            @Override
            public void handleResults(List<Book> results) {
                if (results.size() < 1)
                    throw new IllegalArgumentException("Invalid book ID");
                callback.kontinue(results.get(0));
            }
        });
    }

    public void persistAsync(final Book book) {
        ContentValues cv = new ContentValues();
        book.writeToProvider(cv);
        this.contentResolver.insertAsync(BookContract.CONTENT_URI, cv, new IContinue<Uri>() {
            @Override
            public void kontinue(Uri value) {
                book.id = BookContract.getId(value);
            }
        });
    }

    public void deleteAllAsync() {
        this.contentResolver.deleteAsync(BookContract.CONTENT_URI, null, null);
    }

    public void deleteBooksAsync(Set<Long> toBeDeleted) {
        Long[] ids = new Long[toBeDeleted.size()];
        toBeDeleted.toArray(ids);
        String[] args = new String[ids.length];

        StringBuilder sb = new StringBuilder();
        if (ids.length > 0) {
            sb.append(BookContract.ID);
            sb.append("=?");
            args[0] = ids[0].toString();
            for (int ix=1; ix<ids.length; ix++) {
                sb.append(" or ");
                sb.append(BookContract.ID);
                sb.append("=?");
                args[ix] = ids[ix].toString();
            }
        }

        String select = sb.toString();
        contentResolver.deleteAsync(BookContract.CONTENT_URI, select, args);
    }
}
