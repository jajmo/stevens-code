package edu.stevens.cs522.chatserver.managers;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.net.Uri;
import android.util.Log;
import android.widget.CursorAdapter;

import java.util.List;

import edu.stevens.cs522.chatserver.async.AsyncContentResolver;
import edu.stevens.cs522.chatserver.async.IContinue;
import edu.stevens.cs522.chatserver.async.IEntityCreator;
import edu.stevens.cs522.chatserver.async.QueryBuilder.IQueryListener;
import edu.stevens.cs522.chatserver.async.SimpleQueryBuilder;
import edu.stevens.cs522.chatserver.contracts.PeerContract;
import edu.stevens.cs522.chatserver.entities.Peer;


/**
 * Created by dduggan.
 */

public class PeerManager extends Manager<Peer> implements SimpleQueryBuilder.ISimpleQueryListener<Peer> {

    private static final int LOADER_ID = 2;
    private Peer peer;
    private IContinue<Uri> callback;

    private static final IEntityCreator<Peer> creator = new IEntityCreator<Peer>() {
        @Override
        public Peer create(Cursor cursor) {
            return new Peer(cursor);
        }
    };

    private AsyncContentResolver contentResolver;

    public PeerManager(Context context) {
        super(context, creator, LOADER_ID);
        contentResolver = new AsyncContentResolver(context.getContentResolver());
    }

    public void getAllPeersAsync(IQueryListener<Peer> listener) {
        executeQuery(PeerContract.CONTENT_URI, listener);
    }

    public void getPeerAsync(long id, final IContinue<Peer> callback) {
        executeSimpleQuery(PeerContract.CONTENT_URI(id), new SimpleQueryBuilder.ISimpleQueryListener<Peer>() {
            @Override
            public void handleResults(List<Peer> results) {
                callback.kontinue(results.get(0));
            }
        });
    }

    public void persistAsync(Peer peer, IContinue<Uri> callback) {
        this.peer = peer;
        this.callback = callback;

        String where = PeerContract.NAME + "=?";
        String[] args = { peer.name };
        executeSimpleQuery(PeerContract.CONTENT_URI, null, where, args, this);
    }

    public void handleResults(List<Peer> results) {
        ContentValues cv = new ContentValues();
        this.peer.writeToProvider(cv);

        if (results.size() == 0) {
            // New peer
            this.contentResolver.insertAsync(PeerContract.CONTENT_URI, cv, this.callback);
        } else {
            // Update peer
            String where = PeerContract.ID + "=?";
            String[] selectArgs = { Long.toString(peer.id) };
            this.contentResolver.updateAsync(PeerContract.CONTENT_URI(this.peer.id), cv, where, selectArgs);
            callback.kontinue(PeerContract.CONTENT_URI(this.peer.id));
        }
    }

}
