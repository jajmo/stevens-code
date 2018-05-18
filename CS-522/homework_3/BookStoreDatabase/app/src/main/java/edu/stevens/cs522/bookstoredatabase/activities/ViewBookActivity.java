package edu.stevens.cs522.bookstoredatabase.activities;

import android.app.Activity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.TextView;

import edu.stevens.cs522.bookstoredatabase.R;
import edu.stevens.cs522.bookstoredatabase.entities.Book;


public class ViewBookActivity extends Activity {
	
	// Use this as the key to return the book details as a Parcelable extra in the result intent.
	public static final String BOOK_KEY = "book";
	
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.view_book);

		Book b = getIntent().getParcelableExtra(BOOK_KEY);
		TextView title = (TextView) findViewById(R.id.view_title);
		TextView author = (TextView) findViewById(R.id.view_author);
		TextView isbn = (TextView) findViewById(R.id.view_isbn);
		TextView price = (TextView) findViewById(R.id.view_price);

		title.setText(b.title);
		author.setText(b.getAuthors());
		isbn.setText(b.isbn);
		price.setText(b.price);
	}
}