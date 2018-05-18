/*********************************************************************

    Chat server: accept chat messages from clients.
    
    Sender chatName and GPS coordinates are encoded
    in the messages, and stripped off upon receipt.

    Copyright (c) 2017 Stevens Institute of Technology

**********************************************************************/
package edu.stevens.cs522.chat.activities;

import android.app.Activity;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.os.Handler;
import android.os.IBinder;
import android.os.ResultReceiver;
import android.preference.PreferenceManager;
import android.util.Log;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.SimpleCursorAdapter;
import android.widget.Toast;

import java.net.DatagramSocket;
import java.net.InetAddress;
import java.util.Date;

import edu.stevens.cs522.chat.R;
import edu.stevens.cs522.chat.async.QueryBuilder;
import edu.stevens.cs522.chat.contracts.MessageContract;
import edu.stevens.cs522.chat.entities.ChatMessage;
import edu.stevens.cs522.chat.managers.MessageManager;
import edu.stevens.cs522.chat.managers.PeerManager;
import edu.stevens.cs522.chat.managers.TypedCursor;
import edu.stevens.cs522.chat.rest.ChatHelper;
import edu.stevens.cs522.chat.settings.Settings;
import edu.stevens.cs522.chat.util.DateUtils;
import edu.stevens.cs522.chat.util.InetAddressUtils;
import edu.stevens.cs522.chat.util.ResultReceiverWrapper;

public class ChatActivity extends Activity implements OnClickListener, QueryBuilder.IQueryListener<ChatMessage>, ResultReceiverWrapper.IReceive {

	final static public String TAG = ChatActivity.class.getCanonicalName();
		
    /*
     * UI for displaying received messages
     */
	private SimpleCursorAdapter messages;
	private ListView messageList;
    private SimpleCursorAdapter messagesAdapter;
    private MessageManager messageManager;
    private PeerManager peerManager;

    /*
     * Widgets for dest address, message text, send button.
     */
    private EditText chatRoomName;
    private EditText messageText;
    private Button sendButton;


    /*
     * Helper for Web service
     */
    private ChatHelper helper;

    /*
     * For receiving ack when message is sent.
     */
    private ResultReceiverWrapper sendResultReceiver;
	
	/*
	 * Called when the activity is first created. 
	 */
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

        /**
         * Initialize settings to default values.
         */
		if (!Settings.isRegistered(this)) {
			Intent i = new Intent(this, RegisterActivity.class);
			startActivity(i);
		}

        setContentView(R.layout.messages);

        this.messageText = (EditText) findViewById(R.id.message_text);
        this.sendButton = (Button) findViewById(R.id.send_button);
        this.chatRoomName = (EditText) findViewById(R.id.chat_room);

        this.sendResultReceiver = new ResultReceiverWrapper(new Handler());

        this.messageList = (ListView) findViewById(R.id.message_list);
        String[] from = { MessageContract.MESSAGE_TEXT };
        int[] to = { R.id.message };
        this.messagesAdapter = new SimpleCursorAdapter(this, R.layout.message, null, from, to, 0);
        this.messageList.setAdapter(this.messagesAdapter);

        this.messageManager = new MessageManager(this);
        this.messageManager.getAllMessagesAsync(this);

        this.sendButton.setOnClickListener(this);

        this.helper = new ChatHelper(this, this.sendResultReceiver);
    }

	public void onResume() {
        super.onResume();
        sendResultReceiver.setReceiver(this);
    }

    public void onPause() {
        super.onPause();
        sendResultReceiver.setReceiver(null);
    }

    public void onDestroy() {
        super.onDestroy();
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        super.onCreateOptionsMenu(menu);
        getMenuInflater().inflate(R.menu.chatserver_menu, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        super.onOptionsItemSelected(item);
        switch(item.getItemId()) {

            case R.id.peers:
                Intent i = new Intent(this, ViewPeersActivity.class);
                startActivity(i);
                break;

            case R.id.settings:
                Intent intent = new Intent(this, SettingsActivity.class);
                startActivity(intent);
                break;

            case R.id.register:
                Intent j = new Intent(this, RegisterActivity.class);

                // requestCode doesn't matter here - we just want the result int to show a toast if
                // the user is already registered
                startActivityForResult(j, RegisterActivity.REGISTER_REQUEST);
                break;

            default:
        }

        return false;
    }

    /*
     * Callback for the SEND button.
     */
    public void onClick(View v) {
        if (helper != null) {

            String chatRoom;
            String message;

            chatRoom = this.chatRoomName.getText().toString().trim();
            chatRoom = (chatRoom.equals("")) ? ChatHelper.DEFAULT_CHAT_ROOM : chatRoom;
            message = this.messageText.getText().toString().trim();

            if (message.equals(""))
                return;

            this.helper.postMessage(chatRoom, message);

            Log.i(TAG, "Sent message: " + message);

            messageText.setText("");
        }
    }

    @Override
    protected void onActivityResult(int reqCode, int resCode, Intent data) {
        switch (resCode) {
            case RegisterActivity.ALREADY_REGISTERED:
                Toast.makeText(this, "You're already registered!", Toast.LENGTH_SHORT).show();
                break;
            default:
                break;
        }
    }

    @Override
    public void onReceiveResult(int resultCode, Bundle data) {
        switch (resultCode) {
            case RESULT_OK:
                Toast.makeText(this, "Message sent!", Toast.LENGTH_SHORT).show();
                break;
            default:
                Toast.makeText(this, "Uh oh, something went wrong", Toast.LENGTH_SHORT).show();
                break;
        }
    }

    @Override
    public void handleResults(TypedCursor<ChatMessage> results) {
        this.messagesAdapter.swapCursor(results.getCursor());
        this.messagesAdapter.notifyDataSetChanged();
    }

    @Override
    public void closeResults() {
        this.messagesAdapter.swapCursor(null);
        this.messagesAdapter.notifyDataSetChanged();
    }

}