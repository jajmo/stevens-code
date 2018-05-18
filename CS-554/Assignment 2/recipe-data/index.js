const recipeCollection = require("./recipeCollection");
const userData = require("../recipe-users");
const Promise = require("bluebird");
const redis = require('promise-redis')((resolver) => {
	return new Promise(resolver);
});
const client = redis.createClient();
const uuid = require('node-uuid');

const recipeListKey = "recipeList";
const userViewedRecipes = "userRecipes-";

let exportedMethods = {
    getAllRecipes() {
        return client.hgetall(recipeListKey).then((recipes) => {
            if (!recipes) {
                return recipeCollection().then((recipes) => {
                    return recipes.find({ }, { title: 1, createdById: 1, createdBy: 1 }).toArray();
                }).then((recipes) => {
                    if (recipes) {
                        recipes.map((e) => {
                            client.hset(recipeListKey, e._id, JSON.stringify(e));
                        });
                        client.expire(recipeListKey, 60 * 60);
                    }
                    return recipes;
                });
            } else {
                let ret = [];
                for (var key in recipes) {
                    ret.push(JSON.parse(recipes[key]));
                }
                return ret;
            }
        });
    },
    getRecipe(id, loggedIn, username) {
        return client.get(id).then((recipe) => {
            if (recipe) {
                return JSON.parse(recipe);
            }

            return recipeCollection().then((recipes) => {
                return recipes.findOne({ _id: id }).then((foundRecipe) => {
                    if (!foundRecipe) {
                        return null;
                    }

                    return client.setex(id, 60 * 60, JSON.stringify(foundRecipe)).then(() => {
                        return foundRecipe;
                    });
                });
            })
        }).then((foundRecipe) => {
            if (loggedIn && username !== undefined && foundRecipe != null) {
                return userData.getUserByUsername(username).then((user) => {
                    let userKey = userViewedRecipes + user._id;
                    
                    return client.llen(userKey).then((length) => {
                        if (length == 10) {
                            // If length is 10, pop from the left and push to the right
                            return client.lpop(userKey).then(() => {
                                return client.rpush(userKey, JSON.stringify(foundRecipe));
                            });
                        } else {
                            // Otherwise, just push
                            return client.rpush(userKey, JSON.stringify(foundRecipe));
                        }
                    }).then(() => {
                        return foundRecipe;
                    });
                }).then(() => {
                    return foundRecipe;
                });
            } else {
                return foundRecipe;
            }
        });
    },
    addRecipe(origRecipe, userId, username) {
        if (!origRecipe) {
            return Promise.reject("Invalid parameters");
        }

        try {
            var recipe = JSON.parse(origRecipe);
        } catch (e) {
            return Promise.reject("Invalid JSON format");
        }

        if (!recipe.title) {
            return Promise.reject("A recipe title is required");
        }

        return recipeCollection().then((recipes) => {
            let id = uuid.v4();
            recipe._id = id;
            recipe.createdById = userId;
            recipe.createdBy = username;
            
            return recipes.insertOne(recipe).then(() => {
                return client.setex(id, 60 * 60, JSON.stringify(recipe)).then(() => {
                    return client.exists(recipeListKey);
                }).then((exists) => {
                    if (exists == 1) {
                        let insert = {
                            _id: recipe._id,
                            title: recipe.title,
                            createdBy: recipe.createdBy,
                            createdById: recipe.createdById
                        }
            
                        return client.hset(recipeListKey, id, JSON.stringify(insert));
                    }
    
                    return;
                });
            });
        });
    },
    editRecipe(recipe, recipeId, userId) {
        try {
            var newRecipe = JSON.parse(recipe);
        } catch (e) {
            return Promise.reject("Invalid JSON format");
        }

        return this.getRecipe(recipeId, false, undefined).then((recipe) => {
            if (!recipe) {
                return Promise.reject("Invalid recipe ID");
            } else if (recipe.createdById != userId) {
                return Promise.reject("Only the recipe creator can edit it");
            } else if (!newRecipe.title) {
                return Promise.reject("A recipe title is required");
            }

            newRecipe._id = recipe._id;
            newRecipe.createdBy = recipe.createdBy;
            newRecipe.createdById = recipe.createdById;

            return recipeCollection().then((recipes) => {
                return recipes.update({ _id: recipeId }, newRecipe);
            }).then(() => {
                return client.setex(recipeId, 60 * 60, JSON.stringify(newRecipe));
            }).then(() => {
                let insert = {
                    _id: newRecipe._id,
                    title: newRecipe.title,
                    createdBy: newRecipe.createdBy,
                    createdById: newRecipe.createdById
                }

                return client.hset(recipeListKey, recipeId, JSON.stringify(insert));
            });
        });
    },
    deleteRecipe(recipeId, userId) {
        return this.getRecipe(recipeId, false, undefined).then((recipe) => {
            if (!recipe) {
                return Promise.reject("Invalid recipe ID");
            } else if (recipe.createdById != userId) {
                return Promise.reject("Only the recipe creator can delete it");
            }

            return recipeCollection().then((recipes) => {
                return recipes.deleteOne({ _id: recipeId });
            }).then(() => {
                return client.del(recipeId);
            }).then(() => {
                return client.hdel(recipeListKey, recipeId);
            });
        })
    }
}

module.exports = exportedMethods;