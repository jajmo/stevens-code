package edu.stevens.cs522.bookstoredatabase.entities;

import android.content.ContentValues;
import android.database.Cursor;
import android.os.Parcel;
import android.os.Parcelable;

import edu.stevens.cs522.bookstoredatabase.contracts.BookContract;
import edu.stevens.cs522.bookstoredatabase.databases.CartDbAdapter;

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

	public Book(Parcel in) {
		this.id = in.readLong();
		this.title = in.readString();
		this.authors = in.createTypedArray(Author.CREATOR);
		this.isbn = in.readString();
		this.price = in.readString();
	}

	public static final Parcelable.Creator<Book> CREATOR =
			new Parcelable.Creator<Book>() {
				public Book createFromParcel(Parcel in) {
					return new Book(in);
				}

				public Book[] newArray(int s) {
					return new Book[s];
				}
			};

	@Override
	public void writeToParcel(Parcel out, int flags) {
		out.writeLong(this.id);
		out.writeString(this.title);
		out.writeTypedArray(this.authors, flags);
		out.writeString(this.isbn);
		out.writeString(this.price);
	}

	public Book(Cursor cursor) {
		this.title = BookContract.getTitle(cursor);
		this.isbn = BookContract.getIsbn(cursor);
		this.price = BookContract.getPrice(cursor);
		this.authors = Author.fromArray(BookContract.getAuthors(cursor));
	}

	public String getAuthors() {
		String out = "";

		for (int i = 0; i < authors.length; i++) {
			out += authors[i].toString();
			if (i != authors.length - 1)
				out += ", ";
		}

		return out;
	}


	public void writeToProvider(ContentValues out) {
		BookContract.putTitle(out, this.title);
		BookContract.putIsbn(out, this.isbn);
		BookContract.putPrice(out, this.price);
	}

	@Override
	public int describeContents() {
    	return 0;
	}
}