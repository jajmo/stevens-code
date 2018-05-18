var express = require('express');
var bodyParser = require('body-parser');
var cookieParser = require('cookie-parser');
var uuid = require('node-uuid');
var userData = require('./data.js');
var config = require('./config.js');
var session = require('./sessions.js');
bcrypt = require('bcrypt-nodejs');

var app = express();

/* View setup */
app.set('view engine', 'ejs');

/* Server setup */
app.use(cookieParser());
app.use(bodyParser.json()); // for parsing application/json
app.use(bodyParser.urlencoded({ extended: true }));
app.use('/assets', express.static('static'));

/* Middleware */
app.use(function (request, response, next) {
    var cookieVal = request.cookies[config.cookieName];
    userData.isLoggedIn(cookieVal, response).then(function (res) {
        if (res !== null && cookieVal !== undefined) {
            response.locals.user = res;
        } else {
            response.locals.user = null;
        }

        next();
    });
});

var tempSessionId = null;

// Temporary sessions (used while logged out)
app.use(function (request, response, next) {
    if (response.locals.user === null) {
        if (!request.cookies[config.tempSession]) {
            var sessId = uuid.v4();
            session.createSession(sessId);
            var oneHour = new Date();
            oneHour.setHours(oneHour.getHours() + 1);
            response.cookie(config.tempSession, sessId, { expires: oneHour });
            tempSessionId = sessId;
        } else {
            tempSessionId = request.cookies[config.tempSession];
        }
    } else {
        tempSessionId = null;
    }

    next();
});

/* Routes */
app.get("/", function (request, response) {
    if (response.locals.user !== null) {
        response.redirect("/profile");
    } else {
        var err = session.getSessionData(tempSessionId, "error");
        var inf = session.getSessionData(tempSessionId, "info");
        session.clearSessionData(tempSessionId, "error");
        session.clearSessionData(tempSessionId, "info");

        response.render("pages/index", { title: "Login", error: err, info: inf });
    }
});

app.post("/login", function (request, response) {
    if (response.locals.user !== null) {
        response.redirect("/profile");
    }

    userData.getPassHash(request.body.username).then(function (passHash) {
        userData.login(request.body.username, bcrypt.compareSync(request.body.password, passHash), response).then(function (valid) {
            session.clearSession(tempSessionId, response);
            response.redirect("/");
        }).catch(function (err) {
            session.clearSessionData(tempSessionId, "info");
            session.setSessionData(tempSessionId, "error", "Invalid username or password");
            response.redirect("/");
        });
    }).catch(function (err) {
        session.clearSessionData(tempSessionId, "info");
        session.setSessionData(tempSessionId, "error", "Invalid username or password");
        response.redirect("/");
    });
});

app.post("/register", function (request, response) {
    if (response.locals.user !== null) {
        response.redirect("/profile");
    }

    if (request.body.username.trim() === "" || request.body.password.trim() === "") {
        session.setSessionData(tempSessionId, "error", "You must enter a username and a password");
        session.clearSessionData(tempSessionId, "info");
        response.redirect("/");
        return;
    }

    userData.createUser(request.body.username.trim(), bcrypt.hashSync(request.body.password.trim())).then(function (data) {
        session.setSessionData(tempSessionId, "info", data);
        session.clearSessionData(tempSessionId, "error");
        response.redirect("/");
    }).catch(function (err) {
        session.setSessionData(tempSessionId, "error", err);
        session.clearSessionData(tempSessionId, "info");
        response.redirect("/");
    });
});

app.get("/profile", function (request, response) {
    if (response.locals.user === null) {
        response.redirect("/");
    } else {
        response.render("pages/profile", { title: "Profile", user: response.locals.user })
    }
});

app.post("/profile", function (request, response) {
    if (response.locals.user === null) {
        response.redirect("/");
    }

    userData.updateProfile(request.body.fname, request.body.lname, request.body.hobby, request.body.petname, request.cookies[config.cookieName]).then(function (res) {
        response.redirect("/profile");
    }).catch(function (err) {
        response.render("pages/profile", { title: "Profile", user: response.locals.user, error: err })
    });
});

app.post("/logout", function (request, response) {
    if (response.locals.user === null) {
        response.redirect("/");
    }

    userData.logout(request.cookies[config.cookieName], response).then(function (res) {
        response.locals.user = null;
        response.redirect("/");
    });
});

// Default route for all non-existent routes
app.get("*", function (request, response) {
    response.redirect("/");
});


/* Start server */
app.listen(3000, function() {
    console.log('Your server is now listening on port 3000! Navigate to http://localhost:3000 to access it');
});
