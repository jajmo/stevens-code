package edu.stevens.cs522.bookstore.entities;

import android.os.Parcel;
import android.os.Parcelable;

public class Book implements Parcelable {
	
	// TODO Modify this to implement the Parcelable interface.

	public int id;
	public String title;
	public Author[] authors;
	public String isbn;
	public String price;

	private static int id_counter = 0;

	public Book() {
		this.id = this.id_counter++;
	}

	public Book(Parcel in) {
		this.id = in.readInt();
		this.title = in.readString();
		this.authors = in.createTypedArray(Author.CREATOR);
		this.isbn = in.readString();
		this.price = in.readString();
	}

	public String getFirstAuthor() {
		if (authors != null && authors.length > 0) {
			return authors[0].toString();
		} else {
			return "";
		}
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
	public int describeContents() {
		return 0;
	}

	@Override
	public void writeToParcel(Parcel out, int var2) {
		out.writeInt(this.id);
		out.writeString(this.title);
		out.writeTypedArray(this.authors, var2);
		out.writeString(this.isbn);
		out.writeString(this.price);
	}
}