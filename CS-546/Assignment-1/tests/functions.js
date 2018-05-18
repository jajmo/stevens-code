var mod = {};

mod.assertEqual = function (actual, expected, testName, testNumber) {
    if (actual === expected) {
        console.log(testName + " test " + testNumber + " passed");
    } else {
        console.log(testName + " test " + testNumber + " FAILED!");
        console.log("Expected: " + expected + " | Actual: " + actual);
    }
}

module.exports = mod;