package edu.stevens.cs522.chatserver;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.TextView;

import java.util.ArrayList;

public class MessageAdapter extends ArrayAdapter {
    public MessageAdapter(Context context, ArrayList<Message> messages) {
        super(context, 0, messages);
    }

    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        Message message = (Message) getItem(position);
        if (convertView == null) {
            convertView = LayoutInflater.from(getContext()).inflate(R.layout.message, parent, false);
        }

        TextView message_sender = convertView.findViewById(R.id.message_sender);
        TextView message_text = convertView.findViewById(R.id.message_text);

        message_sender.setText(message.getSender());
        message_text.setText(message.getMessage());

        return convertView;
    }
}
