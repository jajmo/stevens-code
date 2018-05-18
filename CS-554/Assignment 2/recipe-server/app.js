const express = require("express");
const bodyParser = require("body-parser");
const app = express();
const static = express.static(__dirname + '/public');
const recipeData = require("../recipe-data");
const userData = require("../recipe-users");
const uuid = require("node-uuid");
const Promise = require("bluebird");
const jwt = require("jsonwebtoken");

const rewriteUnsupportedBrowserMethods = (req, res, next) => {
    if (req.body && req.body._method) {
        req.method = req.body._method;
        delete req.body._method;
    }

    next();
};

// Verify a token
const verifyToken = (req) => {
    let token = req.get('Auth-Token');
    let decoded = undefined;

    try {
        decoded = jwt.verify(token, app.get('sessionSecret'));
    } catch (e) {
        return false;
    }

    return decoded.sub;
}

// Middleware to verify a request. Ensures a user is logged in
const verifyRequest = () => {
    return (req, res, next) => {
        let token = req.get('Auth-Token');
        let username = verifyToken(req);
    
        if (username === false) {
            res.status(401).send({ success: false, message: "Unauthorized" });
        } else {
            userData.getUserByUsername(username).then((user) => {
                if (!user || user.sessionID != token) {
                    res.status(401).send({ success: false, message: "Unauthorized" });
                } else {
                    res.locals.user = user;
                    next();
                }
            }).catch((err) => {
                res.status(401).send({ success: false, message: "Unauthorized" });
            });
        }
    }
};

// Send a request to the worker
const redisRequest = (eventEmit, successEmit, errorEmit, data, res) => {
    let redisConnection = app.get("redis");
    let messageId = uuid.v4();
    let timeout = null;

    data.requestId = messageId;

    redisConnection.on(successEmit + messageId, (data, channel) => {
        redisConnection.off(successEmit + messageId);
        redisConnection.off(errorEmit + messageId);
        clearTimeout(timeout);

        res.json({ success: true, message: data });
    });

    redisConnection.on(errorEmit + messageId, (data, channel) => {
        redisConnection.off(successEmit + messageId);
        redisConnection.off(errorEmit + messageId);
        clearTimeout(timeout);

        res.json({ success: false, message: data });
    });

    timeout = setTimeout(() => {
        redisConnection.off(successEmit + messageId);
        redisConnection.off(errorEmit + messageId);
        res.status(500).json({ success: false, message: "Connection timed out" });
    }, 5000);

    redisConnection.emit(eventEmit + messageId, data);
}

app.set('sessionSecret', uuid.v4());
app.set('redis', require("./redis-connection"));
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({extended: true}));
app.use(rewriteUnsupportedBrowserMethods);

/* Home route */
app.get("/", (req, res) => {
    res.redirect("/recipes");
});

/* User routes */
app.post("/users", (req, res) => {
    let username = req.body.username;
    let password = req.body.password;
    let profile  = req.body.profile;

    let data = {
        username: username,
        password: password,
        profile: profile
    };

    redisRequest("create-user:", "user-created:", "user-create-failed:", data, res);
});

app.post("/users/session", (req, res) => {
    let username = req.body.username;
    let password = req.body.password;

    if (!username || !password) {
        res.json({ success: false, message: "Invalid parameters" });
        return;
    }

    username = username.trim();
    password = password.trim();

    userData.getUserByUsername(username).then((user) => {
        if (!user) {
            return Promise.reject("Invalid username or password");
        }

        return jwt.sign({ sub: user.username }, app.get('sessionSecret'));
    }).then((token) => {
        return userData.authenticateUser(username, password, token);
    }).then((token) => {
        res.json({ success: true, token: token });
    }).catch((err) => {
        res.json({ success: false, message: err });
    });
});

app.get("/users/:id", (req, res) => {
    let userId = req.params.id.trim();
    
    redisRequest("get-user:", "user-data:", "get-user-failed:", { userId: userId }, res);
});

app.get("/users", (req, res) => {
    redisRequest("get-users:", "users-data:", "get-users-failed:", { }, res);
});

app.put("/users", verifyRequest(), (req, res) => {
    let username = req.body.username;
    let password = req.body.password;
    let profile  = req.body.profile;
    
    username = (!username) ? res.locals.user.username : username.trim();
    password = (!password) ? res.locals.user.password : password.trim();
    profile  = (!profile)  ? res.locals.user.profile  : profile.trim();

    let data = {
        username: username,
        password: password,
        profile:  profile,
        id: res.locals.user._id
    }

    redisRequest("update-user:", "user-updated:", "user-update-failed:", data, res);
});

app.delete("/users", verifyRequest(), (req, res) => {
    redisRequest("delete-user:", "user-deleted:", "user-delete-failed:", { userId: res.locals.user._id }, res);
});

/* Recipe routes */
app.post("/recipes", verifyRequest(), (req, res) => {
    let recipe = req.body.recipe;
    let userId = res.locals.user._id;
    let username = res.locals.user.username;

    let data = { 
        recipe: recipe,
        userId: userId,
        username: username
    }

    redisRequest("create-recipe:", "recipe-created:", "recipe-created-failed:", data, res);
});

app.get("/recipes/:id", (req, res) => {
    let recipeId = req.params.id;
    let username = verifyToken(req);
    let data = { 
        recipeId: recipeId, 
        loggedIn: username !== false,
        username: (username !== false) ? username : undefined
    }

    redisRequest("get-recipe:", "got-recipe:", "recipe-get-failed:", data, res);
});

app.get("/recipes", (req, res) => {
    redisRequest("get-recipes:", "got-recipes:", "recipes-get-failed:", { }, res);
});

app.put("/recipes/:id", verifyRequest(), (req, res) => {
    let recipeId = req.params.id;
    let userId = res.locals.user._id;
    let recipe = req.body.recipe;

    let data = {
        recipe: recipe,
        userId: userId,
        recipeId: recipeId
    }

    redisRequest("update-recipe:", "recipe-updated:", "recipe-update-failed:", data, res);
});

app.delete("/recipes/:id", verifyRequest(), (req, res) => {
    let recipeId = req.params.id;
    let userId = res.locals.user._id;

    let data = {
        recipeId: recipeId,
        userId: userId
    }

    redisRequest("delete-recipe:", "recipe-deleted:", "recipe-delete-failed:", data, res);
});

app.get("*", (req, res) => {
    res.redirect("/");
});

app.listen(3000, () => {
    console.log("We've now got a server!");
    console.log("Your routes will be running on http://localhost:3000");
});