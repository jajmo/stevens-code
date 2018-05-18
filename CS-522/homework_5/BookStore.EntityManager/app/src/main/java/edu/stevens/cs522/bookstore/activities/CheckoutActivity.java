package edu.stevens.cs522.bookstore.activities;

import android.app.Activity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.Toast;

import edu.stevens.cs522.bookstore.R;


public class CheckoutActivity extends Activity {

	// Key used for counting the number of checked out items
	public static final String COUNT_KEY = "COUNT_KEY";

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.checkout);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		super.onCreateOptionsMenu(menu);
		getMenuInflater().inflate(R.menu.default_menu, menu);
		return true;
	}

	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		super.onOptionsItemSelected(item);
		switch(item.getItemId()) {
			case R.id.ok:
				setResult(RESULT_OK);
				int count = getIntent().getIntExtra(COUNT_KEY, 0);
				String word = (count != 1) ? "books" : "book";
				Toast t = Toast.makeText(this, "Checked out " + count + " " + word, Toast.LENGTH_SHORT);
				t.show();
				break;
			case R.id.cancel:
				setResult(RESULT_CANCELED);
			default:
				break;
		}

		finish();
		return false;
	}

}