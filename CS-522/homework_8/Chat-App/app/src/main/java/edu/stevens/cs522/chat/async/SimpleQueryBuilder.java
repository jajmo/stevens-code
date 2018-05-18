package edu.stevens.cs522.chat.async;

import android.app.Activity;
import android.content.Context;
import android.database.Cursor;
import android.net.Uri;
import android.util.Log;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by dduggan.
 */

public class SimpleQueryBuilder<T> implements IContinue<Cursor>{

    private IEntityCreator<T> helper;
    private ISimpleQueryListener<T> listener;

    public interface ISimpleQueryListener<T> {
        void handleResults(List<T> results);
    }

    private SimpleQueryBuilder(IEntityCreator<T> helper, ISimpleQueryListener<T> listener) {
        this.helper = helper;
        this.listener = listener;
    }

    public static <T> void executeQuery(Context context, Uri uri, String[] projection, String selection,
                                        String[] selectionArgs, IEntityCreator<T> helper,
                                        ISimpleQueryListener<T> listener) {
        SimpleQueryBuilder<T> qb = new SimpleQueryBuilder<>(helper, listener);
        AsyncContentResolver resolver = new AsyncContentResolver(context.getContentResolver());
        resolver.queryAsync(uri, projection, selection, selectionArgs, null, qb);
    }

    public static <T> void executeQuery(Context context, Uri uri, IEntityCreator<T> helper,
                                        ISimpleQueryListener<T> listener) {
        executeQuery(context, uri, null, null, null, helper, listener);
    }

    @Override
    public void kontinue(Cursor value) {
        List<T> instances = new ArrayList<>();
        if (value.moveToFirst()) {
            do {
                T instance = helper.create(value);
                instances.add(instance);
            } while (value.moveToNext());
        }
        value.close();
        listener.handleResults(instances);
    }

}
