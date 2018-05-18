Assignment 2 - Workers and APIs
==============================

**Author:** Jason Ajmo

**Email:** jajmo@stevens.edu

API Specification
-----------------
* All API endpoints return a JSON object of the form `{ success: true|false, message: "data" }`, except for `POST /users/session`, which will return `token: "token"` instead of `message: "data"`
* Auth tokens are granted via `POST /users/session`, and must be passed in the HTTP header as `Auth-Token: <token>`. They expire when the server is restarted.

**User Routes**
| Method | Path | Description | Parameters | Auth Required |
| ------ | ---- | ---------- | ------------ | ----------- |
| POST   | /users | Create a new user | username: required, password: required, *profile: optional* | No
| POST   | /users/session | Generate a session key | username: required, password: required | No
| GET    | /users/:id | Get a user's profile | id: required | No
| GET    | /users | Get a list of all user's profiles | *None* | No
| PUT    | /users | Update your account | *username: optional, password: optional, profile: optional* | Yes
| DELETE | /users | Delete your account | *None* | Yes

**Recipe Routes**
| Method | Path | Description | Parameters | Auth Required |
| ------ | ---- | ---------- | ------------ | ----------- |
| POST | /recipes | Create a recipe | A JSON object representing the recipe. Only a title is required. | Yes
| GET  | /recipes/:id | Get a recipe | id: required | No
| GET  | /recipes | Get information about all recipes | *None* | No
| PUT  | /recipes/:id | Update a recipe | id: required | Yes
| DELETE | /recipes/:id | Delete a recipe | id: required | Yes

Running the app
---------------
* Navigate into each of the directories (`recipe-data/`, `recipe-server/`, `recipe-users/`, and `recipe-worker/`), and run `npm install` in each.
* Run `recipe-worker` by navigating into `recipe-worker/` and running `npm start`.
* While `recipe-worker` is running, open a new terminal and navigate into `recipe-server` and run `npm start`.
* Send API requests via Postman, or your client of choice.