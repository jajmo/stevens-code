package edu.stevens.cs522.bookstore.entities;

import android.os.Parcel;
import android.os.Parcelable;

public class Author implements Parcelable {
	
	// TODO Modify this to implement the Parcelable interface.

	// NOTE: middleInitial may be NULL!
	
	public String firstName;
	public String middleInitial;
	public String lastName;

	public Author(Parcel in) {
		this.firstName = in.readString();
		this.middleInitial = in.readString();
		this.lastName = in.readString();
	}

	public Author() { }

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
	public int describeContents() {
		return 0;
	}

	@Override
	public void writeToParcel(Parcel out, int var2) {
		out.writeString(this.firstName);
		out.writeString(this.middleInitial);
		out.writeString(this.lastName);
	}

}
