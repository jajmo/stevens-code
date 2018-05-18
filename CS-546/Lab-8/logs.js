var MongoClient = require('mongodb').MongoClient,
    settings = require('./config.js'),
    Guid = require('guid');

var fullMongoUrl = settings.mongoConfig.serverUrl + settings.mongoConfig.database;
var exports = module.exports = {};

MongoClient.connect(fullMongoUrl)
    .then(function(db) {
        return db.createCollection("logs");
    }).then(function (logs) {
        exports.getAllLogs = function() {
            return logs.find().toArray();
        };

        exports.createLogEntry = function (requestPath, requestMethod, cookies, timestamp)
        {
            // Replace periods in cookie keys with underscores
            for (var prop in cookies)
            {
                if (prop.indexOf(".") !== -1)
                {
                    cookies[prop.replace(/\./g, "_")] = cookies[prop];
                    delete cookies[prop];
                }
            }

            var log = {
                _id: Guid.create().toString(),
                requestPath: requestPath,
                requestMethod: requestMethod,
                cookies: cookies,
                timestamp: timestamp
            };

            return logs.insertOne(log);
        };
    });