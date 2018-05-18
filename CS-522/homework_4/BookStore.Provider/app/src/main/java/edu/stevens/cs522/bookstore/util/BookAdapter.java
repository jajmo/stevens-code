package edu.stevens.cs522.bookstore.util;


import android.content.Context;
import android.database.Cursor;
import android.view.View;
import android.widget.ResourceCursorAdapter;
import android.widget.TextView;

import edu.stevens.cs522.bookstore.contracts.BookContract;

/**
 * Created by dduggan.
 */

public class BookAdapter extends ResourceCursorAdapter {

    protected final static int ROW_LAYOUT = android.R.layout.simple_list_item_2;

    public BookAdapter(Context context, Cursor cursor) {
        super(context, ROW_LAYOUT, cursor, 0);
    }

    @Override
    public void bindView(View view, Context context, Cursor cursor) {
        TextView title = (TextView) view.findViewById(android.R.id.text1);
        TextView author = (TextView) view.findViewById(android.R.id.text2);
        String[] authors = BookContract.getAuthors(cursor);

        String authortext = authors[0];
        if (authors.length > 1)
            authortext += " et al.";

        title.setText(BookContract.getTitle(cursor));
        author.setText(authortext);
    }
}