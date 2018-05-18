package edu.stevens.cs522.chatserver.activities;

import android.content.Intent;
import android.database.Cursor;
import android.os.Bundle;
import android.app.Activity;
import android.util.Log;
import android.view.View;
import android.widget.AdapterView;
import android.widget.Button;
import android.widget.ListView;
import android.widget.SimpleCursorAdapter;

import edu.stevens.cs522.chatserver.R;
import edu.stevens.cs522.chatserver.contracts.PeerContract;
import edu.stevens.cs522.chatserver.databases.MessagesDbAdapter;


public class ViewPeersActivity extends Activity implements AdapterView.OnItemClickListener {

    private ListView peerList;
    private SimpleCursorAdapter peerAdapter;
    private MessagesDbAdapter messagesDbAdapter;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.view_peers);
        this.messagesDbAdapter = new MessagesDbAdapter(getApplicationContext());
        this.messagesDbAdapter.open();
        fillData(this.messagesDbAdapter.fetchAllPeers());
        this.peerList.setOnItemClickListener(this);
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        this.messagesDbAdapter.close();
    }

    private void fillData(Cursor c) {
        String[] to = new String[] {PeerContract.NAME};
        int[] from = new int[] {R.id.name};
        this.peerAdapter = new SimpleCursorAdapter(this, R.layout.peer, c, to, from);
        this.peerList = (ListView) findViewById(R.id.peerList);
        this.peerList.setAdapter(this.peerAdapter);
    }

    @Override
    public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
        /*
         * Clicking on a peer brings up details
         */
        Intent intent = new Intent(this, ViewPeerActivity.class);
        intent.putExtra(ViewPeerActivity.PEER_ID_KEY, id);
        startActivity(intent);
    }
}
