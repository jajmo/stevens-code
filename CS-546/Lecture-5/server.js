// We first require our express package
var express = require('express');
var bodyParser = require('body-parser');
var questionAndAnswers = require('./data.js')

// This package exports the function to create an express instance:
var app = express();

// Here we change our view engine from Jade (default) to EJS
app.set('view engine', 'ejs');  

// This is called 'adding middleware', or things that will help parse your request
app.use(bodyParser.json()); // for parsing application/json
app.use(bodyParser.urlencoded({ extended: true })); // for parsing application/x-www-form-urlencoded

// This middleware will activate for every request we make to 
// any path starting with /assets;
// it will check the 'static' folder for matching files 
app.use('/assets', express.static('static'));

// check for hidden input with the tag _method
// browser sometimes cannot submit a PUT or DELETE request,
// so we can use middleware to change it before it hits our routes!
// I have programatically injected some code that will add a hidden input called _method
app.use(function (req, res, next) {
    if (req.body && req.body._method) {
        console.log(req.body);
        req.method = req.body._method;
        delete req.body._method;
    }

    // let the next middleware run:
    next();
});

// Setup your routes here!

app.get("/", function (request, response) {
    // This will redirect to a different route; the user will end up at /questions automatically
    response.redirect("/questions");
});

app.get("/all_the_forms", function (request, response) {
    response.render('pages/forms', { pageTitle: "Testing all the inputs" });
});

app.post("/all_the_forms", function (request, response) {
    var tableData = [];
    
    // our request.body will get populated as an object
    for (var key in request.body) {
        var data = request.body[key];
        var entry = {
            inputName: key,
            inputValue: JSON.stringify(data),
            inputType: typeof data
        };

        tableData.push(entry);
    }

    response.render('pages/forms', { pageTitle: "Testing all the inputs", tableData: tableData });
});

app.get("/questions/:id", function (request, response) {
    try {
        var question = questionAndAnswers.getQuestion(request.params.id);
        // we caught an exception! Let's show an error page!
        response.render('pages/question', { question: question, pageTitle: question.title });
    } catch (message) {
        // we caught an exception! Let's show an error page!
        response.status(500).render('pages/error', { errorType: "Issue loading question!", errorMessage: message });
    }
});

// Make a new question
app.post("/questions", function (request, response) {
    console.log("POSTING REQUEST WITH BODY OF:");
console.log(request.body);
    try {
        var question = questionAndAnswers.addQuestion(request.body.title, request.body.text);
        response.render('pages/question', { question: question, pageTitle: question.title });
    } catch (message) {
        // we caught an exception! Let's show an error page!
        response.status(500).render('pages/error', { errorType: "Issue creating question!", errorMessage: message });
    }
});

// let's add an answer!
app.post("/questions/:id/answer", function (request, response) {
    try {
        var question = questionAndAnswers.answerQuestion(request.params.id, request.body.answer);
        response.render('pages/question', { question: question, pageTitle: question.title });
    } catch (message) {
        // we caught an exception! Let's show an error page!
        response.status(500).render('pages/error', { errorType: "Cannot answer question!", errorMessage: message });
    }
});

// Update a question
app.put("/questions/:id", function (request, response) {
    console.log("PUTTING REQUEST WITH BODY OF:");
    console.log(request.body);

    try {
        var question = questionAndAnswers.updateQuestion(request.params.id, request.body.title, request.body.text);
        // we caught an exception! Let's show an error page!
        response.render('pages/question', { question: question, pageTitle: question.title });
    } catch (message) {
        // we caught an exception! Let's show an error page!
        response.status(500).render('pages/error', { errorType: "Issue updating question!", errorMessage: message });
    }
})

app.get("/questions", function (request, response) {
    // We have to pass a second parameter to specify the root directory
    // __dirname is a global variable representing the file directory you are currently in
    var questionType = request.query.type,
        displayType = "",
        questionsToShow = [];

    // First, we retrieve our data
    if (questionType === "answered") {
        displayType = "Answered Questions";
        questionsToShow = questionAndAnswers.getAnsweredQuestions();
    } else if (questionType === "all") {
        displayType = "All Questions";
        questionsToShow = questionAndAnswers.getAllQuestions();
    } else {
        displayType = "Unanswered Questions";
        questionsToShow = questionAndAnswers.getUnansweredQuestions();
    }

    // render will search your 'views' directory and follow the path you give it to get a template
    // it will compile the template with the model you provide in the second parameter and
    // send it to the user
    response.render('pages/index', { questions: questionsToShow, type: displayType, pageTitle: "Home" });
});

// We can now navigate to localhost:3000
app.listen(3000, function () {
    console.log('Your server is now listening on port 3000! Navigate to http://localhost:3000 to access it');
});
