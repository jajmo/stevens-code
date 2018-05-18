/*********************************************************************

    Chat server: accept chat messages from clients.
    
    Sender name and GPS coordinates are encoded
    in the messages, and stripped off upon receipt.

    Copyright (c) 2017 Stevens Institute of Technology

**********************************************************************/
package edu.stevens.cs522.chatserver;

import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.util.ArrayList;

import android.app.Activity;
import android.os.Bundle;
import android.os.StrictMode;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ListView;

public class ChatServer extends AppCompatActivity implements OnClickListener {

	final static public String TAG = ChatServer.class.getCanonicalName();
		
	/*
	 * Socket used both for sending and receiving
	 */
	private DatagramSocket serverSocket; 

	/*
	 * True as long as we don't get socket errors
	 */
	private boolean socketOK = true; 

	/*
	 * TODO: Declare a listview for messages, and an adapter for displaying messages.
	 */
	private ListView messages_view;
	private MessageAdapter messages_adapter;
	private ArrayList<Message> messages;

	private Button next;

	/*
	 * Called when the activity is first created. 
	 */
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main);
		this.next = findViewById(R.id.next);
		
		/**
		 * Let's be clear, this is a HACK to allow you to do network communication on the main thread.
		 * This WILL cause an ANR, and is only provided to simplify the pedagogy.  We will see how to do
		 * this right in a future assignment (using a Service managing background threads).
		 */
		StrictMode.ThreadPolicy policy = new StrictMode.ThreadPolicy.Builder().permitAll().build(); 
		StrictMode.setThreadPolicy(policy);

		try {
			/*
			 * Get port information from the resources.
			 */
			int port = Integer.parseInt(this.getString(R.string.app_port));
			Log.i(TAG, "Listening on port " + port);
			this.serverSocket = new DatagramSocket(port);
		} catch (Exception e) {
			this.socketOK = false;
			Log.e(TAG, "Cannot open socket: " + e.getMessage());
			return;
		}

		/*
		 * TODO: Initialize the UI.
		 */
		this.messages = new ArrayList<>();
		this.messages_adapter = new MessageAdapter(this, this.messages);
		this.messages_view = findViewById(R.id.msgList);
		this.messages_view.setAdapter(this.messages_adapter);
		this.next.setOnClickListener(this);
	}

	@Override
	public void onClick(View v) {
		Log.i(TAG, "beginning of handler");

		if (!this.socketOK) {
			Log.e(TAG, "Socket isn't okay - exiting handler");
			return;
		}

		byte[] receiveData = new byte[1024];
		DatagramPacket receivePacket = new DatagramPacket(receiveData, receiveData.length);

		try {
			this.serverSocket.receive(receivePacket);

			InetAddress sourceIPAddress = receivePacket.getAddress();
			Log.i(TAG, "Source IP Address: " + sourceIPAddress);

			/*
			 * TODO: Extract sender and receiver from message and display.
			 */
			String[] data = new String(receivePacket.getData()).split(":");
			Message m = new Message(data[0], data[1]);
			this.messages.add(m);
			this.messages_adapter.notifyDataSetChanged();

		} catch (Exception e) {
			Log.e(TAG, "Problems receiving packet: " + e.getMessage());
			socketOK = false;
		}
	}

	/*
	 * Close the socket before exiting application
	 */
	public void closeSocket() {
		this.serverSocket.close();
	}

	/*
	 * If the socket is OK, then it's running
	 */
	boolean socketIsOK() {
		return this.socketOK;
	}
	
}