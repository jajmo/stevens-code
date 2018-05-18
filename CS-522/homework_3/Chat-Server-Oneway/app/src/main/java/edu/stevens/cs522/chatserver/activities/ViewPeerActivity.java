package edu.stevens.cs522.chatserver.activities;

import android.app.Activity;
import android.content.Intent;
import android.database.Cursor;
import android.os.Bundle;
import android.widget.TextView;

import org.w3c.dom.Text;

import edu.stevens.cs522.chatserver.R;
import edu.stevens.cs522.chatserver.databases.MessagesDbAdapter;
import edu.stevens.cs522.chatserver.entities.Peer;

/**
 * Created by dduggan.
 */

public class ViewPeerActivity extends Activity {

    public static final String PEER_ID_KEY = "peer_id";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.view_peer);
        populateContent();
    }

    private void populateContent() {
        MessagesDbAdapter db = new MessagesDbAdapter(this);
        db.open();
        long id = getIntent().getLongExtra(PEER_ID_KEY, -1);
        Peer p = db.fetchPeer(id);
        db.close();

        TextView username = (TextView) findViewById(R.id.view_user_name);
        TextView timestamp = (TextView) findViewById(R.id.view_timestamp);
        TextView address = (TextView) findViewById(R.id.view_address);
        TextView port = (TextView) findViewById(R.id.view_port);

        username.setText(p.name);
        timestamp.setText(p.timestamp.toString());
        address.setText(p.address.getHostAddress());
        port.setText(Integer.toString(p.port));
    }

}
