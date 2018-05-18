var mod = require("../objects.js");
var testBase = require("./functions.js");

// Shallow clone tests
var obj = {'hey': 1, 'test': 'test2'};
console.log("shallowClone test 1:");
console.log(mod.shallowClone(obj));
console.log(obj);
obj = {'hey': {'heySubKey': 1}, 'test': 'test2'};
console.log("shallowClone test 2:");
var x = mod.shallowClone(obj);
obj['hey']['heySubKey'] = 2;
console.log(x); // This should also be 2
console.log(obj);
obj = {};
console.log("shallowClone test 3:");
console.log(mod.shallowClone(obj));
console.log(obj);
try {
    mod.shallowClone(null);
    console.log("shallowClone test 4 FAILED!");
} catch (err) {
    console.log("shallowClone test 4 passed");
}

// Deep clone tests
obj = {'hey': 1, 'test': 'test2'};
console.log("deepClone test 1:");
console.log(mod.deepClone(obj));
console.log(obj);
obj = {'hey': {'heySubKey': 1}, 'test': 'test2'};
console.log("deepClone test 2:");
x = mod.deepClone(obj);
obj['hey']['heySubKey'] = 2;
console.log(x); // This should be 1
console.log(obj); // This should be 2
obj = {};
console.log("deepClone test 3:");
console.log(mod.deepClone(obj));
console.log(obj);
try {
    mod.deepClone(null);
    console.log("deepClone test 1 FAILED!");
} catch (err) {
    console.log("deepClone test 1 passed");
}