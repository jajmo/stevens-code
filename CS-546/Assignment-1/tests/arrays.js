var mod = require("../arrays.js");

console.log("shallowClone() tests");
var arr = [1, 2, [3, 4], 4, 5];
var x = mod.shallowClone(arr);
arr[2][0] = 0;
console.log(arr); // [1, 2, [0, 4], 4, 5]
console.log(x); // [1, 2, [0, 4], 4, 5]
try {
    mod.shallowClone({'foo': 'bar'});
    console.log("shallowClone test 2 FAILED!");
} catch (err) {
    console.log("shallowClone test 2 passed");
}
try {
    mod.shallowClone(null);
    console.log("shallowClone test 3 FAILED!");
} catch (err) {
    console.log("shallowClone test 3 passed");
}

console.log("randomize() tests");
arr = [1, 2, [3, 4], 4, 5];
x = mod.randomized(arr);
console.log(arr); // [1, 2, [0, 4], 4, 5]
console.log(x); // [1, 2, [0, 4], 4, 5]
try {
    mod.randomized({'foo': 'bar'});
    console.log("randomized test 2 FAILED!");
} catch (err) {
    console.log("randomized test 2 passed");
}
try {
    mod.randomized(null);
    console.log("randomized test 3 FAILED!");
} catch (err) {
    console.log("randomized test 3 passed");
}