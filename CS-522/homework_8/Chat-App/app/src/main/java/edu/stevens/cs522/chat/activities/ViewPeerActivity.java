package edu.stevens.cs522.chat.activities;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

import edu.stevens.cs522.chat.R;
import edu.stevens.cs522.chat.entities.Peer;

/**
 * Created by dduggan.
 */

public class ViewPeerActivity extends Activity {

    public static final String PEER_KEY = "peer";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.view_peer);

        Peer peer = getIntent().getParcelableExtra(PEER_KEY);

        if (peer == null) {
            throw new IllegalArgumentException("Expected peer as intent extra");
        }

        TextView username = (TextView) findViewById(R.id.view_user_name);
        TextView last_seen = (TextView) findViewById(R.id.view_timestamp);
        TextView longitude = (TextView) findViewById(R.id.view_longitude);
        TextView latitude = (TextView) findViewById(R.id.view_latitude);

        username.setText(peer.name);
        last_seen.setText(peer.timestamp.toString());
        longitude.setText(Double.toString(peer.longitude));
        latitude.setText(Double.toString(peer.latitude));
    }

}
