var MongoClient = require('mongodb').MongoClient,
    settings = require('./config.js'),
    uuid = require('node-uuid');

var fullMongoUrl = settings.mongoConfig.serverUrl + settings.mongoConfig.database;
var exports = module.exports = {};

MongoClient.connect(fullMongoUrl)
    .then(function(db) {
        var myCollection = db.collection("comments");

        // setup your body
        exports.createComment = function(comment) {
            if (!comment) {
                return Promise.reject("A comment must be provided.");
            }

            comment = comment.trim();

            if (comment === "") {
                return Promise.reject("A comment must be provided.");
            }
            // you may return Promise.reject("error message"); if there is an error, such as a comment not being provided;
	       // this will result in a rejected promise immediately being returned

            // return a promise that resolves the new comment
            return myCollection.insertOne({ _id: uuid.v4(), comment: comment }).then(function(newDoc) {
                return newDoc.insertedId;
            });
        };

        exports.getAllComments = function() {
            return myCollection.find().toArray();
        }
    });
