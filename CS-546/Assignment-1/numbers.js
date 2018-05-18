var numbersModule = {};

/**
 * triangleArea()
 *
 * Calculate the area of a triangle
 *
 * @param number base The base length
 * @param number height The height of the triangle
 * @return number The area of the triangle
 */
numbersModule.triangleArea = function (base, height) {
    if (typeof base != "number" || typeof height != "number" || base <= 0 || height <= 0) {
        throw "Arguments must be positive numbers";
    }

    return .5 * base * height;
};

/**
 * perimeterOfTriangle()
 *
 * Calculate the perimeter of a triangle
 *
 * @param number side1 The length of side 1
 * @param number side2 The length of side 2
 * @param number side3 The length of side 3
 * @return number The perimeter of the triangle
 */
numbersModule.perimeterOfTriangle = function (side1, side2, side3) {
    if (typeof side1 != "number" || typeof side2 != "number" || typeof side3 != "number" ||
        side1 <= 0 || side2 <= 0 || side3 <= 0) {
        throw "Arguments must be positive numbers";
    }

    return side1 + side2 + side3;
};

/**
 * areaOfSquare()
 *
 * Calculate the area of a square
 *
 * @param number side The length of a side
 * @return number The area of the square
 */
numbersModule.areaOfSquare = function (side) {
    if (typeof side != "number" || side <= 0) {
        throw "Argument must be a positive number";
    }

    return side * side;
}

/**
 * perimeterOfSquare()
 *
 * Calculate the perimeter of a square
 *
 * @param number side The length of a side
 * @return number The perimeter of the square
 */
numbersModule.perimeterOfSquare = function (side) {
    if (typeof side != "number" || side <= 0) {
        throw "Argument must be a positive number";
    }

    return side * 4;
}

/**
 * areaOfCube()
 *
 * Calculate the volume of a cube
 *
 * @param number side The length of a side
 * @return number The volume of the cube
 */
numbersModule.areaOfCube = function (side) {
    if (typeof side != "number" || side <= 0) {
        throw "Argument must be a positive number";
    }

    return side * side * side;
}

/**
 * surfaceAreaOfCube()
 *
 * Calculate the surface area of a cube
 *
 * @param number side The length of one side
 * @return number The surface area of the cube
 */
numbersModule.surfaceAreaOfCube = function (side) {
    if (typeof side != "number" || side <= 0) {
        throw "Argument must be a positive number";
    }

    return 6 * side * side;
}

/**
 * perimeterOfCube()
 *
 * Calculate the perimeter of a cube
 *
 * @param number side The length of a side
 * @return number The perimeter of the cube
 */
numbersModule.perimeterOfCube = function (side) {
    if (typeof side != "number" || side <= 0) {
        throw "Argument must be a positive number";
    }

    return 12 * side;
}

/**
 * circumferenceOfCircle()
 *
 * Calculate the circumference of a circle
 *
 * @param number radius The radius of the circle
 * @return number The circumference of the circle
 */
numbersModule.circumferenceOfCircle = function (radius) {
    if (typeof radius != "number" || radius <= 0) {
        throw "Argument must be a positive number";
    }

    return Math.PI * 2 * radius
}

/**
 * areaOfCircle()
 *
 * Calculate the area of a circle
 *
 * @param number radius The radius of the circle
 * @return number The area of the circle
 */
numbersModule.areaOfCircle = function (radius) {
    if (typeof radius != "number" || radius <= 0) {
        throw "Argument must be a positive number";
    }

    return Math.PI * radius * radius;
}

module.exports = numbersModule;