var objectsModule = {};

/**
 * shallowClone()
 *
 * Shallow clone an object
 *
 * @param object baseObject The object to clone
 * @return object The cloned object
 */
objectsModule.shallowClone = function (baseObject) {
    var newObject = {};

    // Since typeof doesn't differentiate between objects and arrays, make sure
    // the argument isn't an array
    if (typeof baseObject != "object" || Array.isArray(baseObject)) {
        throw "Argument must be an object";
    }

    // Iterate over the top-level keys
    Object.keys(baseObject).forEach(function (key) {
        newObject[key] = baseObject[key];
    });

    return newObject;
};

/**
 * deepClone()
 *
 * Deep clone an object
 *
 * @param object baseObject The object to deep clone
 * @return object The cloned object
 */
objectsModule.deepClone = function (baseObject) {
    var newObject = {};

    // Since typeof doesn't differentiate between objects and arrays, make sure
    // the argument isn't an array
    if (typeof baseObject != "object" || Array.isArray(baseObject)) {
        throw "Argument must be an object";
    }

    // Iterate over the keys
    // If that property is an object, recurse a level deeper
    Object.keys(baseObject).forEach(function (key) {
        if (typeof baseObject[key] == "object") {
            newObject[key] = objectsModule.deepClone(baseObject[key]);
        } else {
            newObject[key] = baseObject[key];
        }
    });

    return newObject;
};

module.exports = objectsModule;