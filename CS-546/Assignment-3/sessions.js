var config = require('./config.js');
var exports = module.exports = {};
var sessionData = { };

exports.getSessionData = function (sessionId, dataName) {
    if (!sessionId) {
        return;
    }

    if (sessionData[sessionId] === undefined) {
        exports.createSession(sessionId);
    }

    var data = sessionData[sessionId][dataName];

    if (data === undefined) {
        return null;
    } else {
        return data['value'];
    }
};

exports.setSessionData = function (sessionId, dataName, data) {
    if (!sessionId) {
        return;
    }

    sessionData[sessionId][dataName] = { };
    sessionData[sessionId][dataName]['value'] = data;
};

exports.clearSessionData = function (sessionId, dataName) {
    if (!sessionId) {
        return;
    }

    delete sessionData[sessionId][dataName];
};

exports.clearSession = function (sessionId, response) {
    if (!sessionId) {
        return;
    }

    var anHourAgo = new Date();
    anHourAgo.setHours(anHourAgo.getHours() - 1);
    response.cookie(config.tempSession, "", { expires: anHourAgo });
    response.clearCookie(config.tempSession);
    delete sessionData[sessionId];
};

exports.createSession = function (sessionId) {
    if (!sessionId) {
        return;
    }

    sessionData[sessionId] = { };
}