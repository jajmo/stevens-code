package edu.stevens.cs522.bookstore.activities;

import android.app.Activity;
import android.app.LoaderManager;
import android.content.AsyncQueryHandler;
import android.content.ContentValues;
import android.content.CursorLoader;
import android.content.Intent;
import android.content.Loader;
import android.database.Cursor;
import android.os.Bundle;
import android.view.ActionMode;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.widget.AbsListView;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.ListView;
import android.widget.SimpleCursorAdapter;
import android.widget.TextView;

import java.util.HashSet;
import java.util.Set;

import edu.stevens.cs522.bookstore.R;
import edu.stevens.cs522.bookstore.contracts.AuthorContract;
import edu.stevens.cs522.bookstore.contracts.BookContract;
import edu.stevens.cs522.bookstore.entities.Author;
import edu.stevens.cs522.bookstore.entities.Book;
import edu.stevens.cs522.bookstore.providers.BookProvider;
import edu.stevens.cs522.bookstore.util.BookAdapter;

public class MainActivity extends Activity implements OnItemClickListener, AbsListView.MultiChoiceModeListener, LoaderManager.LoaderCallbacks {
	
	// Use this when logging errors and warnings.
	@SuppressWarnings("unused")
	private static final String TAG = MainActivity.class.getCanonicalName();
	
	// These are request codes for subactivity request calls
	static final private int ADD_REQUEST = 1;
	static final private int CHECKOUT_REQUEST = ADD_REQUEST + 1;
    static final private int LOADER_ID = 1;

    BookAdapter bookAdapter;

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

        if (savedInstanceState != null) {
            getLoaderManager().restartLoader(LOADER_ID, null, this);
        }

		setContentView(R.layout.cart);

        // Use a custom cursor adapter to display an empty (null) cursor.
        bookAdapter = new BookAdapter(this, null);
        ListView lv = (ListView) findViewById(android.R.id.list);
        lv.setAdapter(bookAdapter);

        lv.setOnItemClickListener(this);
        lv.setChoiceMode(ListView.CHOICE_MODE_MULTIPLE_MODAL);
        lv.setMultiChoiceModeListener(this);

        LoaderManager lm = getLoaderManager();
        lm.initLoader(LOADER_ID, null, this);
    }

    private void updateVisibility() {
        TextView empty = (TextView) findViewById(R.id.empty_cart);
        ListView lv = (ListView) findViewById(android.R.id.list);
        if (lv.getCount() <= 0) {
            empty.setVisibility(View.VISIBLE);
        } else {
            empty.setVisibility(View.GONE);
        }
    }
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		super.onCreateOptionsMenu(menu);
		getMenuInflater().inflate(R.menu.bookstore_menu, menu);
        return true;
	}

	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		super.onOptionsItemSelected(item);
        switch(item.getItemId()) {

            case R.id.add:
                Intent addIntent = new Intent(this, AddBookActivity.class);
                startActivityForResult(addIntent, ADD_REQUEST);
                break;

            case R.id.checkout:
                Intent checkoutIntent = new Intent(this, CheckoutActivity.class);
                checkoutIntent.putExtra(CheckoutActivity.COUNT_KEY, this.bookAdapter.getCount());
                startActivityForResult(checkoutIntent, CHECKOUT_REQUEST);
                break;

            default:
                break;
        }
        return false;
    }

	@Override
	protected void onActivityResult(int requestCode, int resultCode,
			Intent intent) {
		super.onActivityResult(requestCode, resultCode, intent);

        // Use ADD_REQUEST and CHECKOUT_REQUEST codes to distinguish the cases.
        switch(requestCode) {
            case ADD_REQUEST:
                if (resultCode == RESULT_OK) {
                    Book b = intent.getParcelableExtra(AddBookActivity.BOOK_RESULT_KEY);
                    ContentValues cv = new ContentValues();
                    b.writeToProvider(cv);
                    getContentResolver().insert(BookContract.CONTENT_URI, cv);
                }
                break;
            case CHECKOUT_REQUEST:
                if (resultCode == RESULT_OK) {
                    getContentResolver().delete(BookContract.CONTENT_URI, null, null);
                }
                break;
        }

        this.updateVisibility();

	}

    /*
     * Loader callbacks
     */
	@Override
	public Loader onCreateLoader(int id, Bundle args) {
	    String[] projection = new String[]{ BookContract._ID, BookContract.TITLE, BookContract.AUTHORS };
        switch (id) {
            case LOADER_ID:
                return new CursorLoader(this, BookContract.CONTENT_URI, projection,
                        null, null, null);
            default:
                return null;
        }
	}

	@Override
	public void onLoadFinished(Loader loader, Object data) {
	    switch (loader.getId()) {
            case LOADER_ID:
                this.bookAdapter.swapCursor((Cursor) data);
                this.bookAdapter.notifyDataSetChanged();
                this.updateVisibility();
                break;
            default:
                break;
        }
	}

	@Override
	public void onLoaderReset(Loader loader) {
	    switch (loader.getId()) {
            case LOADER_ID:
                this.bookAdapter.swapCursor(null);
                this.bookAdapter.notifyDataSetChanged();
                this.updateVisibility();
                break;
            default:
                break;
        }
	}

    /*
     * Selection of a book from the list view
     */
    @Override
    public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
        Cursor c = getContentResolver().query(BookContract.CONTENT_URI(id), null, null, null, null);
        Book b = new Book(c);
        Intent i = new Intent(this, ViewBookActivity.class);
        i.putExtra(ViewBookActivity.BOOK_KEY, b);
        startActivity(i);
    }


    /*
     * Handle multi-choice action mode for deletion of several books at once
     */
    Set<Long> selected;

    @Override
    public boolean onCreateActionMode(ActionMode mode, Menu menu) {
        getMenuInflater().inflate(R.menu.books_cab, menu);
        selected = new HashSet<>();
        return true;
    }

    @Override
    public void onItemCheckedStateChanged(ActionMode mode, int position, long id, boolean checked) {
        if (checked) {
            selected.add(id);
        } else {
            selected.remove(id);
        }
    }

    @Override
    public boolean onActionItemClicked(ActionMode mode, MenuItem item) {
        switch(item.getItemId()) {
            case R.id.delete:
                for (Long id : selected) {
                    getContentResolver().delete(BookContract.CONTENT_URI(id), null, null);
                }
                selected.clear();
                this.updateVisibility();
                return true;
            default:
                return false;
        }
    }

    @Override
    public boolean onPrepareActionMode(ActionMode mode, Menu menu) {
        return false;
    }

    @Override
    public void onDestroyActionMode(ActionMode mode) { }
}