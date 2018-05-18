package edu.stevens.cs522.bookstore.activities;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.widget.EditText;

import edu.stevens.cs522.bookstore.R;
import edu.stevens.cs522.bookstore.entities.Book;
import edu.stevens.cs522.bookstore.util.Utils;

public class AddBookActivity extends AppCompatActivity {
	
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

		// TODO provide ADD and CANCEL options
		getMenuInflater().inflate(R.menu.add_book_menu, menu);
		return true;
	}

	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		super.onOptionsItemSelected(item);
		// TODO
		
		// ADD: return the book details to the BookStore activity
		switch(item.getItemId()) {
			case R.id.add:
				Intent res = new Intent();
				res.putExtra(BOOK_RESULT_KEY, addBook());
				setResult(RESULT_OK, res);
				break;

			case R.id.cancel:
				setResult(RESULT_CANCELED, null);
				break;
		}

		finish();
		
		// CANCEL: cancel the request
		return false;
	}
	
	public Book addBook(){
		// TODO Just build a Book object with the search criteria and return that.
		Book b = new Book();
		EditText title = findViewById(R.id.search_title);
		EditText authors = findViewById(R.id.search_author);
		EditText isbn = findViewById(R.id.search_isbn);
		b.authors = Utils.parseAuthors(authors.getText().toString());
		b.title = title.getText().toString();
		b.isbn = isbn.getText().toString();
		return b;
	}

}