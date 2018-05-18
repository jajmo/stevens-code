package edu.stevens.cs522.bookstoredatabase.entities;

import android.content.ContentValues;
import android.os.Parcel;
import android.os.Parcelable;

import edu.stevens.cs522.bookstoredatabase.contracts.AuthorContract;

import static android.R.attr.author;

public class Author implements Parcelable {

	// NOTE: middleInitial may be NULL!

	public long id;
	public String firstName;
	public String middleInitial;
	public String lastName;

	public Author() {}

	public Author(String authorText) {
		String[] name = authorText.split(" ");
		switch (name.length) {
			case 0:
				firstName = lastName = "";
				break;
			case 1:
				firstName = "";
				lastName = name[0];
				break;
			case 2:
				firstName = name[0];
				lastName = name[1];
				break;
			default:
				firstName = name[0];
				middleInitial = name[1];
				lastName = name[2];
		}
	}

	public Author(Parcel in) {
		this.id = in.readLong();
		this.firstName = in.readString();
		this.middleInitial = in.readString();
		this.lastName = in.readString();
	}

	public static Author[] fromArray(String[] arr) {
		int i;
		Author[] ret = new Author[arr.length];

		for (i = 0; i < arr.length; i++) {
			ret[i] = new Author(arr[i]);
		}

		return ret;
	}

	public String toString() {
		StringBuffer sb = new StringBuffer();
		if (firstName != null && !"".equals(firstName)) {
			sb.append(firstName);
			sb.append(' ');
		}
		if (middleInitial != null && !"".equals(middleInitial)) {
			sb.append(middleInitial);
			sb.append(' ');
		}
		if (lastName != null && !"".equals(lastName)) {
			sb.append(lastName);
		}
		return sb.toString();
	}

	public static final Parcelable.Creator<Author> CREATOR =
			new Parcelable.Creator<Author>() {
				public Author createFromParcel(Parcel in) {
					return new Author(in);
				}

				public Author[] newArray(int s) {
					return new Author[s];
				}
			};

	@Override
	public void writeToParcel(Parcel in, int flags) {
		in.writeLong(this.id);
		in.writeString(this.firstName);
		in.writeString(this.middleInitial);
		in.writeString(this.lastName);
	}

	public void writeToProvder(ContentValues cv) {
		AuthorContract.putFirstName(cv, this.firstName);
		AuthorContract.putMiddleName(cv, this.middleInitial);
		AuthorContract.putLastName(cv, this.lastName);
	}

	@Override
	public int describeContents() {
		return 0;
	}

	public static Author[] parseAuthors(String text) {
		String[] names = text.split(",");
		Author[] authors = new Author[names.length];
		for (int ix=0; ix<names.length; ix++) {
			Author author = new Author();
			String[] name = names[ix].split(" ");

			switch (name.length) {
				case 0:
					author.firstName = author.lastName = "";
					break;
				case 1:
					author.firstName = "";
					author.lastName = name[0];
					break;
				case 2:
					author.firstName = name[0];
					author.lastName = name[1];
					break;
				default:
					author.firstName = name[0];
					author.middleInitial = name[1];
					author.lastName = name[2];
					break;
			}

			authors[ix] = author;
		}

		return authors;
	}
}
