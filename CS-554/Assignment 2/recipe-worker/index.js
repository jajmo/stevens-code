const recipeData = require("../recipe-data");
const userData = require("../recipe-users");
const fetch = require('node-fetch');
const NRP = require('node-redis-pubsub');

const config = {
    port: 6379, // Port of your locally running Redis server
    scope: 'recipes' // Use a scope to prevent two NRPs from sharing messages
};

const redisConnection = new NRP(config); // This is the NRP client

/**
 * User channels
 */

/* Create a user */
redisConnection.on('create-user:*', (data, channel) => {
    let messageId = data.requestId;
    let username = data.username;
    let password = data.password;
    let profile = data.profile;

    userData.createUser(username, password, profile).then((data) => {
        redisConnection.emit(`user-created:${messageId}`, "User created");
    }).catch((err) => {
        redisConnection.emit(`user-create-failed:${messageId}`, err);
    });
});

/* Get a user's info */
redisConnection.on('get-user:*', (data, channel) => {
    let messageId = data.requestId;
    let userId = data.userId;

    userData.getUserById(userId).then((user) => {
        if (!user) {
            return Promise.reject("User does not exist");
        }
    
        redisConnection.emit(`user-data:${messageId}`, { _id: user._id, username: user.username, profile: user.profile });
    }).catch((err) => {
        redisConnection.emit(`get-user-failed:${messageId}`, err);
    });
});

/* Get info for all users */
redisConnection.on('get-users:*', (data, channel) => {
    let messageId = data.requestId;

    userData.getAllUsers().then((users) => {
        let data = users.map((a) => { return { _id: a._id, username: a.username, profile: a.profile }; });
        redisConnection.emit(`users-data:${messageId}`, data);
    }).catch((err) => {
        redisConnection.emit(`get-users-failed:${messageId}`, err);
    });
});

/* Update a user */
redisConnection.on('update-user:*', (data, channel) => {
    let messageId = data.requestId;
    let userId = data.id;
    let username = data.username;
    let password = data.password;
    let profile = data.profile;

    userData.updateUser(userId, username, password, profile).then((data) => {
        redisConnection.emit(`user-updated:${messageId}`, "Profile updated. Please re-authenticate");
    }).catch((err) => {
        redisConnection.emit(`user-update-failed:${messageId}`, err);
    });
});

/* Delete a user */
redisConnection.on('delete-user:*', (data, channel) => {
    let messageId = data.requestId;
    let userId = data.userId;

    userData.deleteUser(userId).then((data) => {
        redisConnection.emit(`user-deleted:${messageId}`, "User deleted");
    }).catch((err) => {
        redisConnection.emit(`user-delete-failed:${messageId}`, "Unable to delete user");
    });
}); 

/**
 * Recipe channels
 */

/* Create a recipe */
redisConnection.on('create-recipe:*', (data, channel) => {
    let messageId = data.requestId;
    let recipe = data.recipe;
    let userId = data.userId;
    let username = data.username;

    recipeData.addRecipe(recipe, userId, username).then(() => {
        redisConnection.emit(`recipe-created:${messageId}`, "Recipe created");
    }).catch((err) => {
        redisConnection.emit(`recipe-created-failed:${messageId}`, err);
    });
});

/* Get a recipe */
redisConnection.on('get-recipe:*', (data, channel) => {
    let messageId = data.requestId;

    recipeData.getRecipe(data.recipeId, data.loggedIn, data.username).then((recipe) => {
        if (!recipe) {
            return Promise.reject("Recipe does not exist");
        }
    
        redisConnection.emit(`got-recipe:${messageId}`, recipe);
    }).catch((err) => {
        redisConnection.emit(`recipe-get-failed:${messageId}`, err);
    });
});

/* Get all recipes */
redisConnection.on('get-recipes:*', (data, channel) => {
    let messageId = data.requestId;

    recipeData.getAllRecipes().then((recipes) => {
        redisConnection.emit(`got-recipes:${messageId}`, recipes);
    }).catch((err) => {
        redisConnection.emit(`recipes-get-failed:${messageId}`, err);
    });
});

/* Update a recipe */
redisConnection.on('update-recipe:*', (data, channel) => {
    let messageId = data.requestId;
    let userId = data.userId;
    let recipe = data.recipe;
    let recipeId = data.recipeId;

    recipeData.editRecipe(recipe, recipeId, userId).then(() => {
        redisConnection.emit(`recipe-updated:${messageId}`, "Recipe updated");
    }).catch((err) => {
        redisConnection.emit(`recipe-update-failed:${messageId}`, err);
    });
});

/* Delete a recipe */
redisConnection.on('delete-recipe:*', (data, channel) => {
    let messageId = data.requestId;
    let userId = data.userId;
    let recipeId = data.recipeId;

    recipeData.deleteRecipe(recipeId, userId).then(() => {
        redisConnection.emit(`recipe-deleted:${messageId}`, "Recipe deleted");
    }).catch((err) => {
        redisConnection.emit(`recipe-delete-failed:${messageId}`, err);
    });
});