const usersCollection = require("./usersCollection");
const bcrypt = require("bcrypt-nodejs");
const uuid = require("node-uuid");
const Promise = require("bluebird");
const redis = require('promise-redis')((resolver) => {
	return new Promise(resolver);
});
const client = redis.createClient();

// Keys for redis lists and stuff
const redisKeys = {
	userInfo: "userInfoList",
    userRecipeCache: "userRecipeCache-"
}

let exportedMethods = {
	getAllUsers() {
        return client.hgetall(redisKeys.userInfo).then((users) => {
            if (users) {
                let ret = [];
                for (var key in users) {
                    ret.push(JSON.parse(users[key]));
                }
                return ret;
            }

            return usersCollection().then((users) => {
                return users.find({}).toArray();
            }).then((users) => {
                let returnUsers = users.map((e) => {
                    return {
                        _id: e._id,
                        username: e.username,
                        profile: e.profile
                    }
                });

                returnUsers.forEach((user, idx) => {
                    // We don't care about waiting for this to finish since we're returning the array, not anything
                    // from the cache
                    client.hset(redisKeys.userInfo, user._id, JSON.stringify(user));
                });

                client.expire(redisKeys.userInfo, 60 * 5);
        
                return users;
            });
        });
	},
	getUserByUsername(username) {
		return client.get(username).then((user) => {
			if (user) {
				return JSON.parse(user);
			}

			return usersCollection().then((users) => {
				return users.findOne({ username: username }).then((foundUser) => {
					if (!foundUser) {
						return null;
					}

                    let user = foundUser;

					return client.setex(user._id, 60 * 5, JSON.stringify(user)).then(() => {
						return client.setex(user.username, 60 * 5, JSON.stringify(user));
					}).then(() => {
                        return user;
                    });
				});
			});
		});
	},
	getUserById(id) {
		return client.get(id).then((user) => {
			if (user) {
				return JSON.parse(user);
			}

			return usersCollection().then((users) => {
				return users.findOne({ _id: id }).then((foundUser) => {
					if (!foundUser) {
						return null;
					}

                    let user = foundUser;
    
					return client.setex(user._id, 60 * 5, JSON.stringify(user)).then(() => {
                        return client.setex(user.username, 60 * 5, JSON.stringify(user));
                    }).then(() => {
                        return user;
                    });
				});
			});
		});
	},
	authenticateUser(username, password, token) {
		if (!username || !password) {
			return Promise.reject("Invalid parameters");
		}

		return usersCollection().then((users) => {
			return this.getUserByUsername(username).then((foundUser) => {
				if (foundUser && bcrypt.compareSync(password, foundUser.password)) {
                    let user = foundUser;

					return users.update({ username: username }, { $set: { sessionID: token }}).then(() => {
						user.sessionID = token;
        
                        return client.set(user._id, JSON.stringify(user)).then(() => {
                            return client.set(user.username, JSON.stringify(user));
                        }).then(() => {
                            return token;
                        });
					});
				} else {
					return Promise.reject("Invalid username or password");
				}
			});
		});
	},
	createUser(username, password, profile) {
        if (!username || !password) {
            return Promise.reject("Invalid parameters");
        }

        username = username.trim();
        password = password.trim();
        profile  = (profile) ? profile : '';

        if (!username || !password) {
            return Promise.reject("Invalid parameters");
        }

		return usersCollection().then((users) => {
			return this.getUserByUsername(username).then((user) => {
				if (user) {
					return Promise.reject("User already exists");
				} else {
					let user = {
						_id: uuid.v4(),
						username: username,
						password: bcrypt.hashSync(password),
						profile: profile,
						sessionID: null
					};

					return users.insertOne(user).then(() => {
                        let localUser = { _id: user._id, username: user.username, profile: user.profile };
                        return client.hset(redisKeys.userInfo, user._id, JSON.stringify(localUser));
                    }).then(() => {
                        return client.setex(user._id, 60 * 5, JSON.stringify(user));
                    }).then(() => {
                        return client.setex(user.username, 60 * 5, JSON.stringify(user));
                    });
				}
			});
		});
	},
	updateUser(id, username, password, profile) {
        return usersCollection().then((users) => {
			return this.getUserById(id).then((user) => {
                let oldUser = user;

                if (!profile) {
                    profile = user.profile;
                }

                return this.getUserByUsername(username).then((user) => {
                    if (user && username != oldUser.username) {
					    return Promise.reject("New username is already in use");
                    } else {
                        if (password != oldUser.password) {
                            password = bcrypt.hashSync(password);
                        }

                        let updateSet = {
                            _id:       oldUser._id,
                            username:  username,
                            password:  password,
                            profile:   profile,
                            sessionID: null
                        };

                        return users.update({ _id: id }, updateSet).then(() => {
                            return client.setex(oldUser._id, 60 * 5, JSON.stringify(updateSet));
                        }).then(() => {
                            return client.setex(username, 60 * 5, JSON.stringify(updateSet));
                        }).then(() => {
                            return (oldUser.username != username) ? client.del(oldUser.username) : 1;
                        }).then(() => {
                            let local = {
                                _id: updateSet._id,
                                username: updateSet.username,
                                profile: updateSet.profile
                            }
                            return client.hset(redisKeys.userInfo, id, JSON.stringify(local));
                        });
                    }
                });
			});
		});
	},
	deleteUser(id) {
        return this.getUserById(id).then((user) => {
            return usersCollection().then((users) => {
                return users.deleteOne({ _id: id });
            }).then(() => {
                return client.del(id);
            }).then(() => {
                return client.del(user.username);
            }).then(() => {
                return client.hdel(redisKeys.userInfo, id);
            }).then(() => {
                return client.del("userRecipes-" + id);
            });
        });
	}
}

module.exports = exportedMethods;
