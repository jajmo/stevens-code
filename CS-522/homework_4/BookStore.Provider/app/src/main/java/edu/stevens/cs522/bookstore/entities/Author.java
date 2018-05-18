package edu.stevens.cs522.bookstore.entities;

import android.content.ContentValues;
import android.database.Cursor;
import android.os.Parcel;
import android.os.Parcelable;
import edu.stevens.cs522.bookstore.contracts.AuthorContract;

public class Author implements Parcelable {
	public long id;
	public String name;

	public Author(String authorText) {
		this.name = authorText;
	}

	public Author(Parcel in) {
		this.id = in.readLong();
		this.name = in.readString();
	}

	public Author(Cursor c) {
		this.id = AuthorContract.getId(c);
		this.name = AuthorContract.getFirstName(c);
	}

	public void writeToProvider(ContentValues out, long book_fk) {
		AuthorContract.putFirstName(out, this.name);
		AuthorContract.putBookId(out, book_fk);
	}

	public static Author[] parseAuthors(String authors) {
		String[] names = authors.split(",");
		Author[] ret = new Author[names.length];

		for (int i = 0; i < names.length; i++) {
			ret[i] = new Author(names[i]);
		}

		return ret;
	}

	public static Author[] fromStringArray(String[] authors) {
		Author[] a = new Author[authors.length];

		for (int i = 0; i < authors.length; i++)
			a[i] = new Author(authors[i]);
		return a;
	}

	@Override
	public String toString() {
		return name;
	}

	@Override
	public int describeContents() {
		return 0;
	}

	@Override
	public void writeToParcel(Parcel out, int flags) {
		out.writeLong(this.id);
		out.writeString(this.name);
	}

	public static final Creator<Author> CREATOR =
			new Creator<Author>() {
				@Override
				public Author createFromParcel(Parcel source) {
					return new Author(source);
				}

				@Override
				public Author[] newArray(int size) {
					return new Author[size];
				}
			};
}
