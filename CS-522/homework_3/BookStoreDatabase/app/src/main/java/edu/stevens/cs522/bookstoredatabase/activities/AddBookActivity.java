package edu.stevens.cs522.bookstoredatabase.activities;

import android.app.Activity;
import android.content.ContentValues;
import android.content.Intent;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.EditText;

import edu.stevens.cs522.bookstoredatabase.R;
import edu.stevens.cs522.bookstoredatabase.entities.Author;
import edu.stevens.cs522.bookstoredatabase.entities.Book;


public class AddBookActivity extends Activity {
	
	// Use this as the key to return the book details as a Parcelable extra in the result intent.
	public static final String BOOK_RESULT_KEY = "book_result";
	
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.add_book);
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
				Intent res = new Intent();
				res.putExtra(BOOK_RESULT_KEY, addBook());
				setResult(RESULT_OK, res);
				break;
			case R.id.cancel:
			default:
				setResult(RESULT_CANCELED);
				break;
		}
		finish();
		return false;
	}
	
	public Book addBook(){
		Book b = new Book();
		EditText title = (EditText) findViewById(R.id.search_title);
		EditText authors = (EditText) findViewById(R.id.search_author);
		EditText isbn = (EditText) findViewById(R.id.search_isbn);
		EditText price = (EditText) findViewById(R.id.search_price);

		b.title = title.getText().toString();
		b.authors = Author.parseAuthors(authors.getText().toString());
		b.isbn = isbn.getText().toString();
		b.price = price.getText().toString();
		return b;
	}
}