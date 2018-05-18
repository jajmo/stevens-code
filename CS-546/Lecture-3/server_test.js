// We first require our express package
var express = require('express');
var bodyParser = require('body-parser');
var people = require('./people_data.js')

// This package exports the function to create an express instance:
var app = express();

// This is called 'adding middleware', or things that will help parse your request
app.use(bodyParser.json()); // for parsing application/json
app.use(bodyParser.urlencoded({ extended: true })); // for parsing application/x-www-form-urlencoded

function respondWithOnePerson(response, id) {
    try {
        var person = people.getPerson(id);
        response.json(person);
    } catch (e) {
        response.status(500).json({ message: e });
    }
}

// You can now setup your routes!
// You can setup a route by calling a method corresponding to what HTTP verb you want to capture the route for
// you can use app.get, app.post, app.put, app.delete, and more (http://expressjs.com/en/4x/api.html#app.METHOD)

// Your first parameter is your route path (see: http://expressjs.com/en/guide/routing.html)
// Route paths can be strings, string patterns, or regular expressions

// Your second parameter is a callback that takes in a request object and a response object;
// This allows you to see request data (such as querystring data), and send response data (such as the response body, status, etc).

// Your routes will be defined in order; so the first matching route you list will be used
app.get("/api/people", function (request, response) {

    // If someone accesses our API such as: /api/people?id=2, return just the result of the person with that ID
    if (request.query.id) {
        // we will route our data to our respondWithOnePerson function; it will handle the rest.
        respondWithOnePerson(response, request.query.id);
    } else {
        var allPeople = people.getPeople();

        // response.json will send a 200 status code, and a JSON result
        response.json(allPeople);
    }

});

// We can set parameters for our routes by adding a colon in front of path components
app.get("/api/people/:id", function (request, response) {
    // we can access :id in request.params.id
    // let's pipe our response into a helper function, since we already do this logic
    // This is very DRY
    respondWithOnePerson(response, request.params.id);
});

// Notice, with different verbs you can have the same route path
app.post("/api/people", function (request, response) {
    // If you want to see an example of a failed request, swap false to true:
    if (false) {
        response.status(501).json({ message: "This route is not yet completed!" });
        return;
    }

    response.json(people.addPerson(request.body));
});

// By using a wildcard, we are saying that any request should be sent to this route
app.get('*', function (request, response) {
    // Your request contains a slew of useful information!
    // http://expressjs.com/en/4x/api.html#req
    
    // If you send data, you will automatically send headers such as the status code
    // http://expressjs.com/en/4x/api.html#res
    response.send('Hello World!');
});

// We can now navigate to localhost:3000
app.listen(3000, function () {
    console.log('Your simply API server is now listening on port 3000! Navigate to http://localhost:3000');
});