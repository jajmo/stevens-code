var arraysModule = {};

/**
 * shallowClone()
 *
 * Shallow clone an array
 *
 * @param object baseArr The base array to clone
 * @return object The cloned array
 */
arraysModule.shallowClone = function (baseArr) {
    var newArray = [];

    // typeof will return "object" for array, so use Array.isArray() instead
    if (!Array.isArray(baseArr)) {
        throw "Argument must be an array";
    }

    // Iterate over the keys, pushing each to the new array
    baseArr.forEach(function (elem) {
        newArray.push(elem);
    });

    return newArray;
};

/**
 * randomized()
 *
 * Shallow copy an array and return it in a random order
 *
 * @param object baseArr The base array to clone and shuffle
 * @return object The cloned and shuffled array
 */
arraysModule.randomized = function (baseArr) {
    // Shallow clone the array
    var copiedArr = arraysModule.shallowClone(baseArr);

    // Randomize the elements
    copiedArr = copiedArr.sort(function (elem) {
        return Math.round(Math.random()) - 0.5;
    });

    return copiedArr;
};

module.exports = arraysModule;