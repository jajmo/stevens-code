// We first require our express package
var express = require('express');
var bodyParser = require('body-parser');
var myData = require('./data.js');

// This package exports the function to create an express instance:
var app = express();

app.set('view engine', 'ejs'); 

// This is called 'adding middleware', or things that will help parse your request
app.use(bodyParser.json()); // for parsing application/json
app.use(bodyParser.urlencoded({ extended: true })); // for parsing application/x-www-form-urlencoded

// This middleware will activate for every request we make to 
// any path starting with /assets;
// it will check the 'static' folder for matching files 
app.use('/assets', express.static('static'));

// Setup your routes here!

app.get("/", function (request, response) { 
    // We have to pass a second parameter to specify the root directory
    // __dirname is a global variable representing the file directory you are currently in
    response.render('pages/index');
});

// Route to calculate the amount money saved after some years
app.get("/api/perMonthRetirementSavings", function (request, response) {
    try {
        // Calculate result and send success JSON if no error is thrown
        var result = myData.retirementAmountIfSavingPerMonth(parseInt(request.query.years), parseInt(request.query.perMonth), parseInt(request.query.interestRate));
        response.render('pages/result', { resultType: 'Retirement Savings', result: "$" + result });
    } catch (err) {
        response.render('pages/error', { errorType: 'Invalid arguments', errorMessage: err });
    }
});

// Route to calculate amount invested after some years
app.get("/api/investedAmount", function (request, response) {
    try {
        // Calculate result and send success JSON if no error is thrown
        var result = myData.investedAmountAfterSomeYears(parseInt(request.query.years), parseInt(request.query.initial), parseInt(request.query.interestRate));
        response.render('pages/result', { resultType: 'Amount Invested', result: "$" + result });
    } catch (err) {
        response.render('pages/error', { errorType: 'Invalid arguments', errorMessage: err });
    }
});

// Route to calculate months to pay off loan
app.get("/api/loanPayoff", function (request, response) {
    try {
        // Calculate result and send success JSON if no error is thrown
        var result = myData.monthsToPayOffLoan(parseInt(request.query.monthlyAmount), parseInt(request.query.loanAmount), parseInt(request.query.interestRate));
        response.render('pages/result', { resultType: 'Loan Payoff', result: result + ' months' });
    } catch (err) {
        response.render('pages/error', { errorType: 'Invalid arguments', errorMessage: err });
    }
});

// Renders results of the calculation for per month retirement savings
app.post("/results/perMonthRetirementSavings", function (request, response) {
    try {
        var result = myData.retirementAmountIfSavingPerMonth(parseInt(request.body.years), parseInt(request.body.perMonth), parseInt(request.body.interestRate));
        response.render('pages/result', { resultType: 'Retirement Savings', result: "$" + result });
    } catch (err) {
        response.render('pages/error', { errorType: 'Invalid arguments', errorMessage: err });
    }
});

// Renders the result of the calculation of invested amount
app.post("/results/investedAmount", function (request, response) {
    try {
        // Calculate result and send success JSON if no error is thrown
        var result = myData.investedAmountAfterSomeYears(parseInt(request.body.investYears), parseInt(request.body.initial), parseInt(request.body.investedInterestRate));
        response.render('pages/result', { resultType: 'Amount Invested', result: "$" + result });
    } catch (err) {
        response.render('pages/error', { errorType: 'Invalid arguments', errorMessage: err });
    }
});

// Renders the result of the calculation of loan payoff
app.post("/results/loanPayoff", function (request, response) {
    try {
        var result = myData.monthsToPayOffLoan(parseInt(request.body.monthlyAmount), parseInt(request.body.loanAmount), parseInt(request.body.loanInterestRate));
        response.render('pages/result', { resultType: 'Loan Payoff', result: result + ' months' });
    } catch (err) {
        response.render('pages/error', { errorType: 'Invalid arguments', errorMessage: err });
    }
});


// We can now navigate to localhost:3000
app.listen(3000, function () {
    console.log('Your server is now listening on port 3000! Navigate to http://localhost:3000 to access it');
});
