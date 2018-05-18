var exports = module.exports = {};

// for now, let's just send an array of data to the requester:
var listOfPeople = [];

exports.getPerson = function (id) {
    if (!id) throw "No id provided";
    if (typeof id === "string") id = parseInt(id);

    var match = listOfPeople.filter(function (p) { return p.id === id; });

    if (match.length > 0) return match[0];

    throw "Person with id of " + id + " could be found.";
};

exports.getPeople = function () { 
    // simple clone
    return listOfPeople.slice(0);
}

exports.addPerson = function (person) {
    person.id = listOfPeople.length;

    listOfPeople.push(person);

    return person;
}

exports.addPerson({ name: "Phil", favoriteFood: "Prosciutto", interests: ["Coffee", "Programming", "Writing"] });
exports.addPerson({ name: "Bill", favoriteFood: "Burgers", interests: ["League", "Red Bull"] });
exports.addPerson({ name: "Jill", favoriteFood: "Jello", interests: ["Programming", "Mystery Novels"] });
