package edu.stevens.cs522.chat.entities;

import android.content.ContentValues;
import android.database.Cursor;
import android.os.Parcel;
import android.os.Parcelable;

import java.net.InetAddress;
import java.util.Date;

import edu.stevens.cs522.chat.contracts.PeerContract;
import edu.stevens.cs522.chat.util.DateUtils;

/**
 * Created by dduggan.
 */

public class Peer implements Parcelable {

    public long id;

    public String name;

    // Last time we heard from this peer.
    public Date timestamp;
    public Double longitude;
    public Double latitude;

    public Peer() {}

    public Peer(Parcel in) {
        this.id = in.readLong();
        this.name = in.readString();
        this.timestamp = (Date) in.readValue(Date.class.getClassLoader());
    }

    public Peer(Cursor in) {
        this.id = PeerContract.getId(in);
        this.name = PeerContract.getName(in);
        this.timestamp = PeerContract.getTimestamp(in);
    }

    public void writeToProvider(ContentValues out) {
        PeerContract.putName(out, this.name);
        PeerContract.putTimestamp(out, this.timestamp);
    }

    @Override
    public void writeToParcel(Parcel in, int flags) {
        in.writeLong(this.id);
        in.writeString(this.name);
        in.writeValue(this.timestamp);
    }

    public void updateTimestamp() {
        this.timestamp = DateUtils.now();
    }

    public static final Creator<Peer> CREATOR =
            new Creator<Peer>() {
                @Override
                public Peer createFromParcel(Parcel in) {
                    return new Peer(in);
                }

                @Override
                public Peer[] newArray(int size) {
                    return new Peer[size];
                }
            };

    @Override
    public int describeContents() {
        return 0;
    }
}
