package edu.stevens.cs522.chatserver.activities;

import android.app.Activity;
import android.os.Bundle;
import android.widget.TextView;

import edu.stevens.cs522.chatserver.R;
import edu.stevens.cs522.chatserver.entities.Peer;

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
        TextView address = (TextView) findViewById(R.id.view_address);
        TextView port = (TextView) findViewById(R.id.view_port);

        username.setText(peer.name);
        last_seen.setText(peer.timestamp.toString());
        address.setText(peer.address.toString());
        port.setText(Integer.toString(peer.port));
    }

}
