// We require the package, so we can use it later
var rp = require('request-promise');

var getPeopleDataConfig = {
    uri: 'http://localhost:3000/api/people',
    json: true
};

var apiRequest = rp(getPeopleDataConfig);

apiRequest.then(function (people) {
    // console.log(people);
    
    people.forEach(function (person) {
        console.log(person.name + " likes to eat " + person.favoriteFood);
    })

    return people;
}).catch(function (error) {
    console.log("We've encountered an error downloading the list of people!")
    console.error(error);
}).then(function (people) { 
    // people will be what we returned previously
    // we can actually chain promises by returning new promises inside of our .then methods; this allows
    // us to keep a synchronous appearance
    
    // you can also return a second promise and keep chaining it
    var querySecondPerson = {
        method: 'GET',
        uri: 'http://localhost:3000/api/people/',
        qs: { id: 2 },
        json: true
    };

    var examplePerson = rp(querySecondPerson);

    // the result of that request will be passed to the next .then call
    return examplePerson;
}).then(function (example) {
    console.log("We are continuing our chain are using the following person as an example:");
    console.log(example);

    console.log("we will now use the url param syntax to get the same data")

    var querySamePerson = {
        method: 'GET',
        uri: 'http://localhost:3000/api/people/2', // notice that 
        json: true
    };

    var samePerson = rp(querySamePerson);

    // the result of that request will be passed to the next .then call
    return samePerson;
}).then(function (samePerson) {
    console.log("You will notice that we got the same type of data, 2 ways")
    console.log(samePerson);
});

var createNewPersonConfig = {
    uri: 'http://localhost:3000/api/people',
    json: true,
    method: 'POST',
    body: {
        name: 'Dill',
        favoriteFood: 'Duck',
        interests: ['Pickling', 'Cooking']
    }
};

var makeNewPersonRequest = rp(createNewPersonConfig);

makeNewPersonRequest.then(function (newPerson) {
    console.log("Made a new person!");
    console.log(newPerson);
}).catch(function (error) {
    console.error("Error occurred making a new person:");
    console.error(error.message);
});