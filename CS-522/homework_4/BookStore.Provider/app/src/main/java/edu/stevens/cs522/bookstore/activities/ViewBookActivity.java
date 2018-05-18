package edu.stevens.cs522.bookstore.activities;

import android.app.Activity;
import android.os.Bundle;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.TextView;
import edu.stevens.cs522.bookstore.entities.Author;
import edu.stevens.cs522.bookstore.entities.Book;
import edu.stevens.cs522.bookstore.R;


public class ViewBookActivity extends Activity {
	
	// Use this as the key to return the book details as a Parcelable extra in the result intent.
	public static final String BOOK_KEY = "book";

	private ArrayAdapter<String> authorsAdapter;
	
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.view_book);

		Book b = getIntent().getParcelableExtra(BOOK_KEY);
		ListView lv = (ListView) findViewById(R.id.view_authors);
		TextView title = (TextView) findViewById(R.id.view_title);
		TextView isbn = (TextView) findViewById(R.id.view_isbn);
		TextView price = (TextView) findViewById(R.id.view_price);

		Author[] authors = b.authors;
		String[] authors2 = new String[authors.length];
		for (int i = 0; i < authors.length; i++)
			authors2[i] = authors[i].toString();

		authorsAdapter = new ArrayAdapter<>(this, android.R.layout.simple_list_item_1, authors2);
		lv.setAdapter(authorsAdapter);

		title.setText(b.title);
		isbn.setText(b.isbn);
		price.setText(b.price);
	}

}