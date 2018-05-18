package edu.stevens.cs522.bookstore.activities;

import android.app.Activity;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.TextView;

import edu.stevens.cs522.bookstore.R;
import edu.stevens.cs522.bookstore.entities.Book;

public class ViewBookActivity extends AppCompatActivity {
	
	// Use this as the key to return the book details as a Parcelable extra in the result intent.
	public static final String BOOK_KEY = "book";
	
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.view_book);

		// TODO get book as parcelable intent extra and populate the UI with book details.
		Book b = (Book) getIntent().getExtras().get(BOOK_KEY);
		TextView title = findViewById(R.id.view_title);
		TextView author = findViewById(R.id.view_author);
		TextView isbn = findViewById(R.id.view_isbn);

		title.setText(b.title);
		author.setText(b.getAuthors());
		isbn.setText(b.isbn);
	}
}