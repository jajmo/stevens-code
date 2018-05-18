// We first require our express package
var express = require('express');
var bodyParser = require('body-parser');
var todos = require('./toDoEntries.js');

// This package exports the function to create an express instance:
var app = express();

// The base URL of the API, use this for versioning or something in the future
const API_BASE = "/api";

// This is called 'adding middleware', or things that will help parse your request
app.use(bodyParser.json()); // for parsing application/json
app.use(bodyParser.urlencoded({ extended: true })); // for parsing application/x-www-form-urlencoded

app.use('/assets', express.static('static'));

// Default route
app.get("/", function (request, response) {
    response.sendFile("./pages/index.html", { root: __dirname });
});

// GET /api/todo
app.get(API_BASE + "/todo", function (request, response) {
    response.json(todos.getEntries(null));
});

// GET /api/todo/open
app.get(API_BASE + "/todo/open", function (request, response) {
    response.json(todos.getEntries('open'));
});

// GET /api/todo/completed
app.get(API_BASE + "/todo/completed", function (request, response) {
    response.json(todos.getEntries('completed'));
});

// GET /api/todo/:id
app.get(API_BASE + "/todo/:id", function (request, response) {
    var id = parseInt(request.params.id);
    var result = todos.getTodoByID(id);

    if (result === undefined) {
        response.status(404).json({ "error": "An entry with the ID of " + request.params.id + " could not be found" });
    } else {
        response.json(result);
    }
});

// POST /api/todo
app.post(API_BASE + "/todo", function (request, response) {
    var author = request.body.author;
    var title = request.body.taskTitle;
    var description = request.body.taskDescription;

    try {
        var newTask = todos.createTask(author, title, description);
        response.json(newTask);
    } catch (err) {
        response.status(500).json({ "error": err });
    }
});

// PUT /api/todo/:id
app.put(API_BASE + "/todo/:id", function (request, response) {
    var id = parseInt(request.params.id);
    var title = request.body.taskTitle;
    var description = request.body.taskDescription;
    var status = request.body.status;

    var result = todos.updateTask(id, title, description, status);

    if (result === -1) {
        // Invalid parameters
        response.status(500).json({ "error": "You must provide valid information in the request body to create an entry." });
    } else if (result === -2) {
        // Task ID not found
        response.status(404).json({ "error": "An entry with the ID of " + request.params.id + " cound not be found" });
    } else {
        response.json(result);
    }
});

// POST /api/todo/:id/notes
app.post(API_BASE + "/todo/:id/notes", function (request, response) {
    var id = parseInt(request.params.id);
    var note = request.body.note;

    var result = todos.addNote(id, note);

    if (result === -1) {
        // Invalid parameters
        response.status(500).json({ "error": "You must provide valid information in the request body to create an entry." });
    } else if (result === -2) {
        // Task ID not found
        response.status(404).json({ "error": "An entry with the ID of " + request.params.id + " cound not be found" });
    } else {
        response.json(result);
    }
});

// DELETE /api/todo/:id
app.delete(API_BASE + "/todo/:id", function (request, response) {
    var id = parseInt(request.params.id);

    try {
        todos.deleteTask(id);
        response.json({ "success": "true" });
    } catch (err) {
        console.log(err);
        response.status(404).json({ "error": err });
    }
});

// We can now navigate to localhost:3000
app.listen(3000, function () {
    console.log('Your server is now listening on port 3000! Navigate to http://localhost:3000 to access it');
});
