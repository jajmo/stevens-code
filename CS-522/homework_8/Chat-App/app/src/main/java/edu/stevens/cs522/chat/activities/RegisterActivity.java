/*********************************************************************

 Chat server: accept chat messages from clients.

 Sender chatName and GPS coordinates are encoded
 in the messages, and stripped off upon receipt.

 Copyright (c) 2017 Stevens Institute of Technology

 **********************************************************************/
package edu.stevens.cs522.chat.activities;

import android.app.Activity;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import edu.stevens.cs522.chat.R;
import edu.stevens.cs522.chat.entities.ChatMessage;
import edu.stevens.cs522.chat.managers.TypedCursor;
import edu.stevens.cs522.chat.rest.ChatHelper;
import edu.stevens.cs522.chat.settings.Settings;
import edu.stevens.cs522.chat.util.ResultReceiverWrapper;

public class RegisterActivity extends Activity implements OnClickListener, ResultReceiverWrapper.IReceive {

    final static public String TAG = RegisterActivity.class.getCanonicalName();

    final static public int ALREADY_REGISTERED = RESULT_OK - 1;
    final static public int USERNAME_TAKEN = ALREADY_REGISTERED - 1;
    final static public int REGISTER_REQUEST = 1; // This is never used

    /*
     * Widgets for dest address, message text, send button.
     */
    private EditText userNameText;
    private Button registerButton;

    /*
     * Helper for Web service
     */
    private ChatHelper helper;

    /*
     * For receiving ack when registered.
     */
    private ResultReceiverWrapper registerResultReceiver;

    /*
     * Called when the activity is first created.
     */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        /**
         * Initialize settings to default values.
         */
        if (Settings.isRegistered(this)) {
            setResult(ALREADY_REGISTERED, null);
            finish();
            return;
        }

        setContentView(R.layout.register);

        this.registerResultReceiver = new ResultReceiverWrapper(new Handler());
        this.helper = new ChatHelper(this, this.registerResultReceiver);

        userNameText = (EditText) findViewById(R.id.chat_name_text);
        registerButton = (Button) findViewById(R.id.register_button);
        registerButton.setOnClickListener(this);
    }

    public void onResume() {
        super.onResume();
        this.registerResultReceiver.setReceiver(this);
    }

    public void onPause() {
        super.onPause();
        this.registerResultReceiver.setReceiver(null);
    }

    public void onDestroy() {
        super.onDestroy();
    }

    /*
     * Callback for the REGISTER button.
     */
    public void onClick(View v) {
        if (helper != null) {
            String userName;

            userName = userNameText.getText().toString().trim();

            if (userName.equals(""))
                return;

            helper.register(userName);

            Log.i(TAG, "Registered: " + userName);
        }
    }

    @Override
    public void onReceiveResult(int resultCode, Bundle data) {
        switch (resultCode) {
            case RESULT_OK:
                Toast.makeText(this, "Successfully registered!", Toast.LENGTH_SHORT).show();
                finish();
                break;
            case RESULT_CANCELED:
                Toast.makeText(this, "You're already registered!", Toast.LENGTH_SHORT).show();
                finish();
                break;
            default:
                Toast.makeText(this, "Unable to register", Toast.LENGTH_SHORT).show();
                break;
        }
    }

}