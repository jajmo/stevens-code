package edu.stevens.cs522.bookstore.activities;

import java.util.ArrayList;

import android.app.ListActivity;
import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.ActionBar;
import android.support.v7.app.AppCompatActivity;
import android.view.ContextMenu;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import edu.stevens.cs522.bookstore.entities.Author;
import edu.stevens.cs522.bookstore.entities.Book;
import edu.stevens.cs522.bookstore.R;
import edu.stevens.cs522.bookstore.util.BooksAdapter;

public class MainActivity extends AppCompatActivity {
	
	// Use this when logging errors and warnings.
	private static final String TAG = MainActivity.class.getCanonicalName();
	
	// These are request codes for subactivity request calls
	static final private int ADD_REQUEST = 1;
	static final private int CHECKOUT_REQUEST = ADD_REQUEST + 1;
	static final private int REMOVE_ID = 1;
	static final private int VIEW_DETAILS_ID = 0;
	static final private String STATE_KEY = "STATE_KEY";

	// There is a reason this must be an ArrayList instead of a List.
	private ArrayList<Book> shoppingCart;
	private BooksAdapter data;

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		// TODO check if there is saved UI state, and if so, restore it (i.e. the cart contents)
		if (savedInstanceState != null) {
			this.shoppingCart = savedInstanceState.getParcelableArrayList(STATE_KEY);
		} else {
			this.shoppingCart = new ArrayList<>();
		}

		// TODO Set the layout (use cart.xml layout)
		setContentView(R.layout.cart);
		this.updateVisibility();

		// TODO use an array adapter to display the cart contents.
		ListView list = findViewById(android.R.id.list);
		this.data = new BooksAdapter(this, this.shoppingCart);
		list.setAdapter(this.data);
		registerForContextMenu(list);

		// Give the user some helpful hints when they single quick tap on an item
		list.setOnItemClickListener(new AdapterView.OnItemClickListener() {
			@Override
			public void onItemClick(AdapterView<?> adapterView, View view, int i, long l) {
				Toast.makeText(getApplicationContext(), "Long press for options", Toast.LENGTH_SHORT).show();
			}
		});
	}

	@Override
	public void onCreateContextMenu(ContextMenu menu, View v, ContextMenu.ContextMenuInfo menuInfo) {
		super.onCreateContextMenu(menu, v, menuInfo);
		menu.add(Menu.NONE, VIEW_DETAILS_ID, Menu.NONE, "View Details");
		menu.add(Menu.NONE,REMOVE_ID, Menu.NONE, "Delete From Cart");
	}

	@Override
	public boolean onContextItemSelected(MenuItem item) {
		AdapterView.AdapterContextMenuInfo info = (AdapterView.AdapterContextMenuInfo) item.getMenuInfo();
		switch (item.getItemId()) {
			case REMOVE_ID:
				this.shoppingCart.remove(info.position);
				this.data.notifyDataSetChanged();
				this.updateVisibility();
				break;
			case VIEW_DETAILS_ID:
				Book b = this.shoppingCart.get(info.position);
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

		// TODO inflate a menu with ADD and CHECKOUT options
		getMenuInflater().inflate(R.menu.bookstore_menu, menu);
        return true;
	}

	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		super.onOptionsItemSelected(item);
        switch(item.getItemId()) {

            // TODO ADD provide the UI for adding a book
            case R.id.add:
                Intent addIntent = new Intent(this, AddBookActivity.class);
                startActivityForResult(addIntent, ADD_REQUEST);
                break;

            // TODO CHECKOUT provide the UI for checking out
            case R.id.checkout:
            	Intent checkoutIntent = new Intent(this, CheckoutActivity.class);
            	checkoutIntent.putExtra(CheckoutActivity.COUNT_KEY, this.shoppingCart.size());
            	startActivityForResult(checkoutIntent, CHECKOUT_REQUEST);
                break;

            default:
        }
        return false;
    }

	@Override
	protected void onActivityResult(int requestCode, int resultCode, Intent intent) {
		super.onActivityResult(requestCode, resultCode, intent);
		// TODO Handle results from the Search and Checkout activities.

        // Use ADD_REQUEST and CHECKOUT_REQUEST codes to distinguish the cases.
        switch(requestCode) {
            case ADD_REQUEST:
                // ADD: add the book that is returned to the shopping cart.
				if (resultCode == RESULT_OK) {
                	Book result = intent.getParcelableExtra(AddBookActivity.BOOK_RESULT_KEY);
                	this.shoppingCart.add(result);
                	this.data.notifyDataSetChanged();
                	this.updateVisibility();
				}
                break;
            case CHECKOUT_REQUEST:
                // CHECKOUT: empty the shopping cart.
				if (resultCode == RESULT_OK) {
                	this.shoppingCart.clear();
                	this.data.notifyDataSetChanged();
                	this.updateVisibility();
				}
                break;
        }
	}
	
	@Override
	public void onSaveInstanceState(Bundle savedInstanceState) {
		// TODO save the shopping cart contents (which should be a list of parcelables).
		savedInstanceState.putParcelableArrayList(STATE_KEY, this.shoppingCart);
		super.onSaveInstanceState(savedInstanceState);
	}

	/* Update visiblity of "THE CART IS EMPTY!" */
	private void updateVisibility() {
		TextView empty = findViewById(android.R.id.empty);
		if (this.shoppingCart.size() > 0) {
			empty.setVisibility(View.GONE);
		} else {
			empty.setVisibility(View.VISIBLE);
		}
	}
}