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
    public Date timestamp;
    public double longitude;
    public double latitude;

    public Peer() {
        // Use default values
        this.longitude = -74.023937;
        this.latitude = 40.744906;
    }

    public Peer(Parcel in) {
        this.id = in.readLong();
        this.name = in.readString();
        this.timestamp = (Date) in.readValue(Date.class.getClassLoader());
        this.longitude = in.readDouble();
        this.latitude = in.readDouble();
    }

    public Peer(Cursor in) {
        this.id = PeerContract.getId(in);
        this.name = PeerContract.getName(in);
        this.timestamp = PeerContract.getTimestamp(in);
        this.longitude = PeerContract.getLongitude(in);
        this.latitude = PeerContract.getLatitude(in);
    }

    public void writeToProvider(ContentValues out) {
        PeerContract.putName(out, this.name);
        PeerContract.putTimestamp(out, this.timestamp);
        PeerContract.putLongitude(out, this.longitude);
        PeerContract.putLatitude(out, this.latitude);
    }

    @Override
    public void writeToParcel(Parcel in, int flags) {
        in.writeLong(this.id);
        in.writeString(this.name);
        in.writeValue(this.timestamp);
        in.writeDouble(this.longitude);
        in.writeDouble(this.latitude);
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
