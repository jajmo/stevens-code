/*********************************************************************

    Chat server: accept chat messages from clients.
    
    Sender name and GPS coordinates are encoded
    in the messages, and stripped off upon receipt.

    Copyright (c) 2017 Stevens Institute of Technology

**********************************************************************/
package edu.stevens.cs522.chat.activities;

import android.app.Activity;
import android.content.BroadcastReceiver;
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

import edu.stevens.cs522.chat.R;
import edu.stevens.cs522.chat.async.QueryBuilder;
import edu.stevens.cs522.chat.contracts.MessageContract;
import edu.stevens.cs522.chat.entities.ChatMessage;
import edu.stevens.cs522.chat.managers.MessageManager;
import edu.stevens.cs522.chat.managers.PeerManager;
import edu.stevens.cs522.chat.managers.TypedCursor;
import edu.stevens.cs522.chat.services.ChatService;
import edu.stevens.cs522.chat.services.IChatService;
import edu.stevens.cs522.chat.util.InetAddressUtils;
import edu.stevens.cs522.chat.util.ResultReceiverWrapper;

public class ChatActivity extends Activity implements OnClickListener, QueryBuilder.IQueryListener<ChatMessage>, ServiceConnection, ResultReceiverWrapper.IReceive {

	final static public String TAG = ChatActivity.class.getCanonicalName();
		
    /*
     * UI for displaying received messages
     */
	private ListView messageList;
    private SimpleCursorAdapter messagesAdapter;
    private MessageManager messageManager;

    /*
     * Widgets for dest address, message text, send button.
     */
    private EditText destinationHost;
    private EditText destinationPort;
    private EditText messageText;
    private Button sendButton;


    /*
     * Use to configure the app (user name and port)
     */
    private SharedPreferences settings;

    /*
     * Reference to the service, for sending a message
     */
    private IChatService chatService;

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
		if (savedInstanceState == null) {
			PreferenceManager.setDefaultValues(this, R.xml.settings, false);
		}

        settings = PreferenceManager.getDefaultSharedPreferences(this);

        setContentView(R.layout.messages);

        this.destinationHost = (EditText) findViewById(R.id.destination_host);
        this.destinationPort = (EditText) findViewById(R.id.destination_port);
        this.messageText = (EditText) findViewById(R.id.message_text);
        this.sendButton = (Button) findViewById(R.id.send_button);

        this.messageList = (ListView) findViewById(R.id.message_list);
        String[] from = { MessageContract.MESSAGE_TEXT };
        int[] to = { R.id.message_text_view };
        this.messagesAdapter = new SimpleCursorAdapter(this, R.layout.message, null, from, to, 0);
        this.messageList.setAdapter(this.messagesAdapter);

        this.messageManager = new MessageManager(this);
        this.messageManager.getAllMessagesAsync(this);

        Intent bindIntent = new Intent(this, ChatService.class);
        bindService(bindIntent, this, Context.BIND_AUTO_CREATE);

        this.sendButton.setOnClickListener(this);

        this.sendResultReceiver = new ResultReceiverWrapper(null);
        this.sendResultReceiver.setReceiver(this);
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

            default:
        }

        return false;
    }

    /*
     * Callback for the SEND button.
     */
    public void onClick(View v) {
        if (chatService != null) {
            /*
			 * On the emulator, which does not support WIFI stack, we'll send to
			 * (an AVD alias for) the host loopback interface, with the server
			 * port on the host redirected to the server port on the server AVD.
			 */
            InetAddress destAddr;
            int destPort;
            String username;
            String message;

            destAddr = InetAddressUtils.toIpAddress(this.destinationHost.getText().toString());
            destPort = Integer.parseInt(this.destinationPort.getText().toString());
            username = this.settings.getString(SettingsActivity.USERNAME_KEY, SettingsActivity.DEFAULT_USERNAME);
            message = this.messageText.getText().toString();

            this.chatService.send(destAddr, destPort, username, message, this.sendResultReceiver);

            Log.i(TAG, "Sent message: " + message);
            messageText.setText("");
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

    @Override
    public void onServiceConnected(ComponentName name, IBinder service) {
        chatService = ((ChatService.ChatBinder) service).getService();
    }

    @Override
    public void onServiceDisconnected(ComponentName name) {
        chatService = null;
    }
}