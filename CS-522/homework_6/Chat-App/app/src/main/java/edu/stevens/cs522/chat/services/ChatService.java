package edu.stevens.cs522.chat.services;

import android.app.Service;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Binder;
import android.os.Bundle;
import android.os.Handler;
import android.os.HandlerThread;
import android.os.IBinder;
import android.os.Process;
import android.os.Looper;
import android.os.Message;
import android.os.ResultReceiver;
import android.preference.PreferenceManager;
import android.util.Log;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.UnknownHostException;
import java.util.Date;

import edu.stevens.cs522.chat.activities.SettingsActivity;
import edu.stevens.cs522.chat.async.IContinue;
import edu.stevens.cs522.chat.entities.ChatMessage;
import edu.stevens.cs522.chat.entities.Peer;
import edu.stevens.cs522.chat.managers.MessageManager;
import edu.stevens.cs522.chat.managers.PeerManager;
import edu.stevens.cs522.chat.managers.TypedCursor;
import edu.stevens.cs522.chat.util.InetAddressUtils;

import static android.app.Activity.RESULT_OK;

public class ChatService extends Service implements IChatService, SharedPreferences.OnSharedPreferenceChangeListener {

    protected static final String TAG = ChatService.class.getCanonicalName();
    protected static final String SEND_TAG = "ChatSendThread";
    protected static final String RECEIVE_TAG = "ChatReceiveThread";

    protected IBinder binder = new ChatBinder();
    protected SendHandler sendHandler;
    protected HandlerThread sendHandlerThread;
    protected Thread receiveThread;
    protected DatagramSocket chatSocket;
    protected boolean socketOK = true;
    protected boolean finished = false;

    PeerManager peerManager;
    MessageManager messageManager;

    protected int chatPort;

    @Override
    public void onCreate() {
        SharedPreferences prefs = PreferenceManager.getDefaultSharedPreferences(this);
        chatPort = Integer.parseInt(prefs.getString(SettingsActivity.APP_PORT_KEY, SettingsActivity.DEFAULT_APP_PORT));
        prefs.registerOnSharedPreferenceChangeListener(this);

        peerManager = new PeerManager(this);
        messageManager = new MessageManager(this);

        try {
            chatSocket = new DatagramSocket(chatPort);
        } catch (Exception e) {
            IllegalStateException ex = new IllegalStateException("Unable to init client socket.");
            ex.initCause(e);
            throw ex;
        }

        this.sendHandlerThread = new HandlerThread(SEND_TAG, Process.THREAD_PRIORITY_BACKGROUND);
        this.sendHandlerThread.start();
        Looper sendLooper = this.sendHandlerThread.getLooper();
        this.sendHandler = new SendHandler(sendLooper);

        /*
         * This is the thread that receives messages.
         */
        receiveThread = new Thread(new ReceiverThread());
        receiveThread.start();
    }

    @Override
    public void onDestroy() {
        finished = true;
        sendHandler.getLooper().getThread().interrupt();  // No-op?
        sendHandler.getLooper().quit();
        receiveThread.interrupt();
        chatSocket.close();
        PreferenceManager.getDefaultSharedPreferences(this).unregisterOnSharedPreferenceChangeListener(this);
    }

    @Override
    public IBinder onBind(Intent intent) {
        return binder;
    }

    public final class ChatBinder extends Binder {
        public IChatService getService() {
            return ChatService.this;
        }
    }

    @Override
    public void onSharedPreferenceChanged(SharedPreferences prefs, String key) {
        if (key.equals(SettingsActivity.APP_PORT_KEY)) {
            try {
                chatSocket.close();
                chatPort = Integer.parseInt(prefs.getString(SettingsActivity.APP_PORT_KEY, SettingsActivity.DEFAULT_APP_PORT));
                chatSocket = new DatagramSocket(chatPort);
            } catch (IOException e) {
                IllegalStateException ex = new IllegalStateException("Unable to change client socket.");
                ex.initCause(e);
                throw ex;
            }
        }
    }

    @Override
    public void send(InetAddress destAddress, int destPort, String sender, String messageText, ResultReceiver receiver) {
        Bundle data = new Bundle();
        data.putString(SendHandler.CHAT_NAME, sender);
        data.putString(SendHandler.CHAT_MESSAGE, messageText);
        data.putString(SendHandler.DEST_ADDRESS, destAddress.getHostAddress());
        data.putInt(SendHandler.DEST_PORT, destPort);
        data.putParcelable(SendHandler.RECEIVER, receiver);
        Message message = sendHandler.obtainMessage();
        message.setData(data);
        message.sendToTarget();
    }


    private final class SendHandler extends Handler {

        private static final String CHAT_NAME = "edu.stevens.cs522.chat.services.extra.CHAT_NAME";
        private static final String CHAT_MESSAGE = "edu.stevens.cs522.chat.services.extra.CHAT_MESSAGE";
        private static final String DEST_ADDRESS = "edu.stevens.cs522.chat.services.extra.DEST_ADDRESS";
        private static final String DEST_PORT = "edu.stevens.cs522.chat.services.extra.DEST_PORT";
        private static final String RECEIVER = "edu.stevens.cs522.chat.services.extra.RECEIVER";

        private SendHandler(Looper looper) {
            super(looper);
        }

        @Override
        public void handleMessage(Message message) {

            try {
                InetAddress destAddr;
                int destPort;
                byte[] sendData;  // Combine sender and message text; default encoding is UTF-8
                ResultReceiver receiver;

                Bundle data = message.getData();
                destAddr = InetAddressUtils.toIpAddress(data.getString(DEST_ADDRESS));
                destPort = data.getInt(DEST_PORT);
                sendData = (data.getString(CHAT_NAME) + ":" + new Date(System.currentTimeMillis()).getTime() + ":" + data.getString(CHAT_MESSAGE)).getBytes();
                receiver = data.getParcelable(RECEIVER);

                DatagramPacket sendPacket = new DatagramPacket(sendData, sendData.length, destAddr, destPort);

                chatSocket.send(sendPacket);

                Log.i(TAG, "Sent packet: " + new String(sendData));

                receiver.send(RESULT_OK, null);
            } catch (UnknownHostException e) {
                Log.e(TAG, "Unknown host exception: " + e.getMessage());
            } catch (IOException e) {
                Log.e(TAG, "IO exception: " + e.getMessage());
            }

        }
    }

    private final class ReceiverThread implements Runnable {

        public void run() {
            Looper.prepare();
            byte[] receiveData = new byte[1024];
            DatagramPacket receivePacket = new DatagramPacket(receiveData, receiveData.length);

            while (!finished && socketOK) {
                try {
                    chatSocket.receive(receivePacket);
                    Log.i(TAG, "Received a packet");

                    InetAddress sourceIPAddress = receivePacket.getAddress();
                    Log.i(TAG, "Source IP Address: " + sourceIPAddress);

                    String msgContents[] = new String(receivePacket.getData(), 0, receivePacket.getLength()).split(":");

                    final ChatMessage message = new ChatMessage();
                    message.sender = msgContents[0];
                    message.timestamp = new Date(Long.parseLong(msgContents[1]));
                    message.messageText = msgContents[2];

                    Log.i(TAG, "Received from " + message.sender + ": " + message.messageText);

                    Peer sender = new Peer();
                    sender.name = message.sender;
                    sender.timestamp = message.timestamp;
                    sender.address = receivePacket.getAddress();
                    sender.port = receivePacket.getPort();

                    Peer res = peerManager.persistSync(sender);
                    message.senderId = res.id;
                    messageManager.persistSync(message);

                } catch (Exception e) {
                    Log.e(TAG, "Problems receiving packet.", e);
                    socketOK = false;
                }

            }

        }

    }

}
