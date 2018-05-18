# CS-546 Assignment 1
## An Introduction to Node

For this assignment, you will be making five modules in order to learn the basics of JavaScript syntax. I have provided an initial test driver that will require each module, but the implementation is entirely up to you!

You can test your code by running `node test.js`.

## String Module (string.js)
You can find a lot of information and useful functions related to strings on the [MDN String](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/String) documentation.

* occurrencesOfSubstring(main, substr); Count and return how many times a substring occurs in a main string; this function is case sensitive
* occurrencesOfSubstringInsensivie(main, substr); Count  and return how many times a substring occurs in a main string; this function is case insensitive
* randomizeSentences(paragraph); Given a string representing a paragraph, reorder the sentences. Return a new string representing a paragraph where the sentences are randomly ordered.

## Basic Numerical Operations (numbers.js)

You can find a lot of information and useful functions related to Math and numbers on the [MDN Math](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Math) documentation.

* triangleArea(base, height): Return the area of a triangle
* perimeterOfTriangle(side1, side2, side3); Return the perimeter of the triangle given 3 sides
* areaOfSquare(side); Return the area of a square given the length of one side
* perimeterOfSquare(side); Return the perimeter of a square given one square.
* areaOfCube(side); Return the area of a cube, given one side
* surfaceAreaOfCube(side); Return the surface area of a cube, given one side.
* perimeterOfCube(side): Return the permiter of a cube, given one side
* circumferenceOfCircle(radius): Return the circumference of a circle given a radius
* areaOfCircle(radius): Return the area of a circle given the radius.

## Objects (objects.js)

You can find a lot of information and useful functions related to objects on the [MDN Objects](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Object) documentation.

* shallowClone(baseObject): Return a 'shallow clone' of the baseObject A shallow clone is one where objects in
* deepClone(baseObject): Return a 'deep clone' of the baseObject. A deep clone is one where each object that you encounter nested in baseObject is also deeply cloned. For example, when cloning `{foo: {bar: 2}}` in a deep clone, you would set 

## Arrays (arrays.js)

You can find a lot of information and useful functions related to objects on the [MDN Array](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Array) documentation.

* shallowClone(baseArr): Given a base array, return a shallow copy of that array.
* randomized(baseArr): Given a base array, return a shallow copy of the array and return the elements in a randomized order

## Dates (dates.js)

You can find a lot of information and useful functions related to objects on the [MDN Date](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Date) documentation.

* daysUntil(someDate): Return the number of days between the current date and someDate.
* daysLeftInYear(): Return the number of days left in the year
* daysSince(someDate): Return the number of days that have passed since someDate.
* nextFridayTheThirteenth(): Return the date that is both a Friday and the 13th. 


## Things to Remember

1. Commit your code often; it helps the CAs and myself to help you if you need, and will help you organize your code into working components.
2. Expect bad input, and handle it accordingly! You can `throw "A string describing an error"` when given bad input. You can read about throwing [on the MDN](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Statements/throw)