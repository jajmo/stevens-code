package edu.stevens.cs522.chat.managers;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;

import edu.stevens.cs522.chat.async.AsyncContentResolver;
import edu.stevens.cs522.chat.async.IContinue;
import edu.stevens.cs522.chat.async.IEntityCreator;
import edu.stevens.cs522.chat.async.QueryBuilder.IQueryListener;
import edu.stevens.cs522.chat.contracts.MessageContract;
import edu.stevens.cs522.chat.entities.ChatMessage;


/**
 * Created by dduggan.
 */

public class MessageManager extends Manager<ChatMessage> {

    private static final int LOADER_ID = 1;

    private static final IEntityCreator<ChatMessage> creator = new IEntityCreator<ChatMessage>() {
        @Override
        public ChatMessage create(Cursor cursor) {
            return new ChatMessage(cursor);
        }
    };

    private AsyncContentResolver contentResolver;

    public MessageManager(Context context) {
        super(context, creator, LOADER_ID);
        contentResolver = new AsyncContentResolver(context.getContentResolver());
    }

    public void getAllMessagesAsync(IQueryListener<ChatMessage> listener) {
        executeQuery(MessageContract.CONTENT_URI, listener);
    }

    public void persistSync(ChatMessage message) {
        ContentValues cv = new ContentValues();
        message.writeToProvider(cv);

        getSyncResolver().insert(MessageContract.CONTENT_URI, cv);
    }

    public void persistAsync(final ChatMessage message) {
        ContentValues cv = new ContentValues();
        message.writeToProvider(cv);
        this.contentResolver.insertAsync(MessageContract.CONTENT_URI, cv, new IContinue<Long>() {
            @Override
            public void kontinue(Long id) {
                message.id = id;
            }
        });
    }

    public void updateAsync(final ChatMessage message) {
        ContentValues cv = new ContentValues();
        message.writeToProvider(cv);
        this.contentResolver.updateAsync(MessageContract.CONTENT_URI, cv, MessageContract.ID + " = ?", new String[]{ Long.toString(message.id) });
    }
}
