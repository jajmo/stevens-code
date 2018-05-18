package edu.stevens.cs522.bookstoredatabase.activities;

import java.util.ArrayList;

import android.app.Activity;
import android.app.ListActivity;
import android.content.ContentValues;
import android.content.Intent;
import android.database.Cursor;
import android.os.Bundle;
import android.util.Log;
import android.view.ContextMenu;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ListView;
import android.widget.SimpleCursorAdapter;
import android.widget.TextView;

import edu.stevens.cs522.bookstoredatabase.R;
import edu.stevens.cs522.bookstoredatabase.contracts.BookContract;
import edu.stevens.cs522.bookstoredatabase.databases.CartDbAdapter;
import edu.stevens.cs522.bookstoredatabase.entities.Book;

public class MainActivity extends Activity {
	
	// Use this when logging errors and warnings.
	private static final String TAG = MainActivity.class.getCanonicalName();
	
	// These are request codes for subactivity request calls
	static final private int ADD_REQUEST = 1;
	static final private int CHECKOUT_REQUEST = ADD_REQUEST + 1;

	static final private int VIEW_DETAILS = 0;
	static final private int DELETE = 1;

	// The database adapter
	private CartDbAdapter dba;

	// Cursor adapter
	private SimpleCursorAdapter adapter;

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.cart);
		this.dba = new CartDbAdapter(getApplicationContext()).open();
		fillData(this.dba.fetchAllBooks());
		this.updateVisibility();
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

	private void fillData(Cursor c) {
		String[] to = new String[] {CartDbAdapter.TITLE, CartDbAdapter.AUTHORS};
		int[] from = new int[] {R.id.cart_row_title, R.id.cart_row_author};
		this.adapter = new SimpleCursorAdapter(this, R.layout.cart_row, c,
				to, from);
		ListView lv = (ListView) findViewById(android.R.id.list);
		lv.setAdapter(this.adapter);
		registerForContextMenu(lv);
	}

	@Override
	public void onCreateContextMenu(ContextMenu m, View v, ContextMenu.ContextMenuInfo menuInfo) {
		super.onCreateContextMenu(m, v, menuInfo);
		m.add(Menu.NONE, VIEW_DETAILS, Menu.NONE, "View Details");
		m.add(Menu.NONE, DELETE, Menu.NONE, "Delete Item");
	}

	@Override
	public boolean onContextItemSelected(MenuItem item) {
		AdapterView.AdapterContextMenuInfo info = (AdapterView.AdapterContextMenuInfo) item.getMenuInfo();
		switch (item.getItemId()) {
			case DELETE:
				this.dba.delete(info.id);
				this.adapter.swapCursor(this.dba.fetchAllBooks());
				this.adapter.notifyDataSetChanged();
				this.updateVisibility();
				break;
			case VIEW_DETAILS:
				Book b = this.dba.fetchBook(info.id);
				Intent i = new Intent(this, ViewBookActivity.class);
				i.putExtra(ViewBookActivity.BOOK_KEY, b);
				startActivity(i);
				break;
			default:
				return false;
		}

		return true;
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
            	checkoutIntent.putExtra(CheckoutActivity.COUNT_KEY, this.adapter.getCount());
            	startActivityForResult(checkoutIntent, CHECKOUT_REQUEST);
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
                	this.dba.persist(b);
                	this.adapter.swapCursor(this.dba.fetchAllBooks());
                	this.adapter.notifyDataSetChanged();
                	this.updateVisibility();
				}
                break;
            case CHECKOUT_REQUEST:
                if (resultCode == RESULT_OK) {
                	this.dba.deleteAll();
					this.adapter.swapCursor(this.dba.fetchAllBooks());
					this.adapter.notifyDataSetChanged();
                	this.updateVisibility();
				}
                break;
        }
	}
	
	@Override
	public void onSaveInstanceState(Bundle savedInstanceState) {
		super.onSaveInstanceState(savedInstanceState);
	}
}