// We require the package, so we can use it later
var rp = require('request-promise');

// If no further configuration is needed, you can just call rp('url')
// Using the request-promise library allows us to make requests, and get promises in return
var result = rp('http://www.google.com');

// The Promise object is used for deferred and asynchronous computations. 
// A Promise represents an operation that hasn't completed yet, but is expected in the future.
// https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Promise

// A promise will allow you to write asynchronous code, syntactically as if it were synchronous
// In our case, our `result` variable will store a promise object, that has the following methods:
// result.then(onFulfilled, onRejected)
// result.catch(onRejected)

// Each promise has two methods, 
var tmp = result.then(function (htmlString) {
    console.log(htmlString);
    
    // throw "TemporaryError";
 
    return htmlString;
}).catch(function (err) {
    // Crawling failed...
    console.log("An error occurred");
    console.error(err);

    return "Recovered from an error; no HTML"
}).then(function (result) {
    console.log("We're done with this promise chain!")
    console.log(result);
});

