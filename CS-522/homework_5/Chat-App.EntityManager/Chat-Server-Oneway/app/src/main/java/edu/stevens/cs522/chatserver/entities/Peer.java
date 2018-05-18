package edu.stevens.cs522.chatserver.entities;

import android.content.ContentValues;
import android.database.Cursor;
import android.os.Parcel;
import android.os.Parcelable;

import com.google.common.net.InetAddresses;

import java.net.InetAddress;
import java.util.Date;

import edu.stevens.cs522.chatserver.contracts.PeerContract;
import edu.stevens.cs522.chatserver.util.DateUtils;

/**
 * Created by dduggan.
 */

public class Peer implements Parcelable {

    public long id;
    public String name;

    // Last time we heard from this peer.
    public Date timestamp;
    public InetAddress address;
    public int port;

    public Peer() {}

    public Peer(Parcel in) {
        this.id = in.readLong();
        this.name = in.readString();
        this.timestamp = (Date) in.readValue(Date.class.getClassLoader());
        this.address = (InetAddress) in.readValue(InetAddress.class.getClassLoader());
        this.port = in.readInt();
    }

    public Peer(Cursor in) {
        this.id = PeerContract.getId(in);
        this.name = PeerContract.getName(in);
        this.timestamp = PeerContract.getTimestamp(in);
        this.address = PeerContract.getAddress(in);
        this.port = PeerContract.getPort(in);
    }

    public void writeToProvider(ContentValues out) {
        PeerContract.putName(out, this.name);
        PeerContract.putTimestamp(out, this.timestamp);
        PeerContract.putAddress(out, this.address);
        PeerContract.putPort(out, this.port);
    }

    @Override
    public void writeToParcel(Parcel in, int flags) {
        in.writeLong(this.id);
        in.writeString(this.name);
        in.writeValue(this.timestamp);
        in.writeValue(this.address);
        in.writeInt(this.port);
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
