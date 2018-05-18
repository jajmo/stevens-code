var numbersModule = require("../numbers.js");
var testBase = require("./functions.js");

// Area of triangle tests
testBase.assertEqual(numbersModule.triangleArea(10, 5), 25, "triangleArea", 1);
try {
    numbersModule.triangleArea(10, 0);
    console.log("triangleArea test 2 FAILED!");
} catch (err) {
    console.log("triangleArea test 2 passed");
}
try {
    numbersModule.triangleArea(null, 1);
    console.log("triangleArea test 3 FAILED!");
} catch (err) {
    console.log("triangleArea test 3 passed");
}
try {
    numbersModule.triangleArea(10, null);
    console.log("triangleArea test 4 FAILED!");
} catch (err) {
    console.log("triangleArea test 4 passed");
}

// Perimeter of triangle tests
testBase.assertEqual(numbersModule.perimeterOfTriangle(5, 5, 2), 12, "perimeterOfTriangle", 1);
try {
    numbersModule.perimeterOfTriangle(5, 5, 0);
    console.log("perimeterOfTriangle test 2 FAILED!");
} catch (err) {
    console.log("perimeterOfTriangle test 2 passed");
}
try {
    numbersModule.perimeterOfTriangle(null, 5, 5);
    console.log("perimeterOfTriangle test 3 FAILED!");
} catch (err) {
    console.log("perimeterOfTriangle test 3 passed");
}
try {
    numbersModule.perimeterOfTriangle(5, null, 5);
    console.log("perimeterOfTriangle test 4 FAILED!");
} catch (err) {
    console.log("perimeterOfTriangle test 4 passed");
}
try {
    numbersModule.perimeterOfTriangle(5, 5, null);
    console.log("perimeterOfTriangle test 5 FAILED!");
} catch (err) {
    console.log("perimeterOfTriangle test 5 passed");
}

// Area of square tests
testBase.assertEqual(numbersModule.areaOfSquare(2), 4, "areaOfSquare", 1);
try {
    numbersModule.areaOfSquare(0);
    console.log("areaOfSquare test 2 FAILED!");
} catch (err) {
    console.log("areaOfSquare test 2 passed");
}
try {
    numbersModule.areaOfSquare(null);
    console.log("areaOfSquare test 3 FAILED!");
} catch (err) {
    console.log("areaOfSquare test 3 passed");
}

// Perimeter of square tests
testBase.assertEqual(numbersModule.perimeterOfSquare(2), 8, "perimeterOfSquare", 1);
try {
    numbersModule.perimeterOfSquare(0);
    console.log("perimeterOfSquare test 2 FAILED!");
} catch (err) {
    console.log("perimeterOfSquare test 2 passed");
}
try {
    numbersModule.perimeterOfSquare(null);
    console.log("perimeterOfSquare test 3 FAILED!");
} catch (err) {
    console.log("perimeterOfSquare test 3 passed");
}

// Area of cube tests
testBase.assertEqual(numbersModule.areaOfCube(2), 8, "areaOfCube", 1);
try {
    numbersModule.areaOfCube(0);
    console.log("areaOfCube test 2 FAILED!");
} catch (err) {
    console.log("areaOfCube test 2 passed");
}
try {
    numbersModule.areaOfCube(null);
    console.log("areaOfCube test 3 FAILED!");
} catch (err) {
    console.log("areaOfCube test 3 passed");
}

// Surface area of cube tests
testBase.assertEqual(numbersModule.surfaceAreaOfCube(2), 24, "surfaceAreaOfCube", 1);
try {
    numbersModule.surfaceAreaOfCube(0);
    console.log("surfaceAreaOfCube test 2 FAILED!");
} catch (err) {
    console.log("surfaceAreaOfCube test 2 passed");
}
try {
    numbersModule.surfaceAreaOfCube(null);
    console.log("surfaceAreaOfCube test 3 FAILED!");
} catch (err) {
    console.log("surfaceAreaOfCube test 3 passed");
}

// Perimeter of cube tests
testBase.assertEqual(numbersModule.perimeterOfCube(2), 24, "perimeterOfCube", 1);
try {
    numbersModule.perimeterOfCube(0);
    console.log("perimeterOfCube test 2 FAILED!");
} catch (err) {
    console.log("perimeterOfCube test 2 passed");
}
try {
    numbersModule.surfaceAreaOfCube(null);
    console.log("perimeterOfCube test 3 FAILED!");
} catch (err) {
    console.log("perimeterOfCube test 3 passed");
}

// Circumferecnce of circle tests
testBase.assertEqual(numbersModule.circumferenceOfCircle(5), 31.41592653589793, "circumferenceOfCircle", 1);
try {
    numbersModule.circumferenceOfCircle(0);
    console.log("circumferenceOfCircle test 2 FAILED!");
} catch (err) {
    console.log("circumferenceOfCircle test 2 passed");
}
try {
    numbersModule.circumferenceOfCircle(null);
    console.log("circumferenceOfCircle test 3 FAILED!");
} catch (err) {
    console.log("circumferenceOfCircle test 3 passed");
}

// Area of circle tests
testBase.assertEqual(numbersModule.areaOfCircle(5), 78.53981633974483, "areaOfCircle", 1);
try {
    numbersModule.areaOfCircle(0);
    console.log("areaOfCircle test 2 FAILED!");
} catch (err) {
    console.log("areaOfCircle test 2 passed");
}
try {
    numbersModule.areaOfCircle(null);
    console.log("areaOfCircle test 3 FAILED!");
} catch (err) {
    console.log("areaOfCircle test 3 passed");
}