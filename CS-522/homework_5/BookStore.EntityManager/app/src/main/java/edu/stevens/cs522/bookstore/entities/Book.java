package edu.stevens.cs522.bookstore.entities;

import android.content.ContentValues;
import android.database.Cursor;
import android.os.Parcel;
import android.os.Parcelable;

import edu.stevens.cs522.bookstore.contracts.BookContract;

public class Book implements Parcelable {

	public long id;
	public String title;
	public Author[] authors;
	public String isbn;
	public String price;

	public Book() { }

	public String getFirstAuthor() {
		if (authors != null && authors.length > 0) {
			return authors[0].toString();
		} else {
			return "";
		}
	}

	private String getAuthors() {
		String authors = "";

		for (int i = 0; i < this.authors.length; i++) {
			authors += this.authors[i].toString();
			if (i < this.authors.length - 1)
				authors += BookContract.SEPARATOR_CHAR;
		}

		return authors;
	}

	public Book(Parcel in) {
		this.id = in.readLong();
		this.title = in.readString();
		this.authors = in.createTypedArray(Author.CREATOR);
		this.isbn = in.readString();
		this.price = in.readString();
	}

	@Override
	public void writeToParcel(Parcel out, int flags) {
		out.writeLong(this.id);
		out.writeString(title);
		out.writeTypedArray(this.authors, flags);
		out.writeString(this.isbn);
		out.writeString(this.price);
	}

	public Book(Cursor cursor) {
		this.id = BookContract.getId(cursor);
		this.title = BookContract.getTitle(cursor);
		this.isbn = BookContract.getIsbn(cursor);
		this.price = BookContract.getPrice(cursor);
		this.authors = Author.fromStringArray(BookContract.getAuthors(cursor));
	}

	public void writeToProvider(ContentValues out) {
		BookContract.putAuthors(out, this.getAuthors());
		BookContract.putTitle(out, this.title);
		BookContract.putIsbn(out, this.isbn);
		BookContract.putPrice(out, this.price);
	}

	@Override
	public int describeContents() {
		return 0;
	}

	public static final Creator<Book> CREATOR =
			new Creator<Book>() {
				@Override
				public Book createFromParcel(Parcel source) {
					return new Book(source);
				}

				@Override
				public Book[] newArray(int size) {
					return new Book[size];
				}
			};

}