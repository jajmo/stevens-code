var mod = require("../dates.js");
var testBase = require("./functions.js");

try {
    mod.daysUntil(null);
    console.log("dates test 1 FAILED!");
} catch (err) {
    console.log("dates test 1 passed");
}

try {
    mod.daysUntil("2012-02-20");
    console.log("dates test 2 FAILED!");
} catch (err) {
    console.log("dates test 2 passed");
}

try {
    mod.daysUntil(new Date("2012-02-01"));
    console.log("dates test 3 FAILED!");
} catch (err) {
    console.log("dates test 3 passed");
}

console.log("Days until 2/15/2016: " + mod.daysUntil(new Date("2016-02-15")));

console.log("Days until the end of 2016: " + mod.daysLeftInYear());

console.log("Days since 2/8/16: " + mod.daysSince(new Date("2016-02-08")));
try {
    mod.daysSince(new Date("2016-08-31"));
    console.log("daysSince test 1 FAILED!");
} catch (err) {
    console.log("daysSince test 1 passed");
}
try {
    mod.daysSince("2016-02-01");
    console.log("daysSince test 2 FAILED!");
} catch (err) {
    console.log("daysSince test 2 passed");
}
try {
    mod.daysSince(null);
    console.log("daysSince test 3 FAILED!");
} catch (err) {
    console.log("daysSince test 3 passed");
}

console.log("Next friday the 13th: " + mod.nextFridayTheThirteenth());