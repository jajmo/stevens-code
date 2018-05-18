package edu.stevens.cs522.chatserver.async;

import android.app.Activity;
import android.app.LoaderManager;
import android.content.Context;
import android.content.CursorLoader;
import android.content.Loader;
import android.database.Cursor;
import android.net.Uri;
import android.os.Bundle;

import edu.stevens.cs522.chatserver.managers.TypedCursor;

/**
 * Created by dduggan.
 */

public class QueryBuilder<T> implements LoaderManager.LoaderCallbacks {

    public static interface IQueryListener<T> {
        public void handleResults(TypedCursor<T> results);
        public void closeResults();
    }

    private int loaderID;
    private Context context;
    private Uri uri;
    private IQueryListener<T> listener;
    private IEntityCreator<T> creator;

    private QueryBuilder(String tag, Activity context, Uri uri, int loaderId,
                         IEntityCreator<T> creator, IQueryListener<T> listener) {
        this.loaderID = loaderId;
        this.context = context;
        this.uri = uri;
        this.listener = listener;
        this.creator = creator;
    }

    public static <T> void executeQuery(String tag, Activity context, Uri uri, int loaderId,
                                        IEntityCreator<T> creator, IQueryListener<T> listener) {
        executeQuery(tag, context, uri, loaderId, null, null, null, creator, listener);
    }

    public static <T> void executeQuery(String tag, Activity context, Uri uri, int loaderId, String[] projection,
                                        String selection, String[] selectionArgs, IEntityCreator<T> creator,
                                        IQueryListener<T> listener) {
        QueryBuilder<T> qb = new QueryBuilder<>(tag, context, uri, loaderId, creator, listener);
        LoaderManager lm = context.getLoaderManager();
        lm.initLoader(loaderId, null, qb);
    }

    public static <T> void reexecuteQuery(String tag, Activity context, Uri uri, int loaderId, String[] projection,
                                          String selection, String[] selectionArgs, IEntityCreator<T> creator,
                                          IQueryListener<T> listener) {
        QueryBuilder<T> qb = new QueryBuilder<>(tag, context, uri, loaderId, creator, listener);
        LoaderManager lm = context.getLoaderManager();
        lm.restartLoader(loaderId, null, qb);
    }

    @Override
    public Loader onCreateLoader(int id, Bundle args) {
        if (id == loaderID) {
            return new CursorLoader(context, uri, null, null, null, null);
        }

        throw new IllegalStateException("Unexpected loader ID");
    }

    @Override
    public void onLoadFinished(Loader loader, Object cursor) {
        if (loader.getId() == loaderID) {
            this.listener.handleResults(new TypedCursor<>((Cursor) cursor, creator));
        } else {
            throw new IllegalStateException("Unexpected loader ID");
        }
    }

    @Override
    public void onLoaderReset(Loader loader) {
        if (loader.getId() == loaderID) {
            listener.closeResults();
        } else {
            throw new IllegalStateException("Unexpected loader ID");
        }
    }
}
