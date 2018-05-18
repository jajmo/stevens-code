/*
 * intintCompare.cpp
 * Used for comparing integers
 * Used in conjunction with templates
 */
#include "sorting.hh"

/*
 * Method to compare if i is less than j
 * Precondition: i and j are not null, i and j are valid integers
 * Postcondition: i and j are compared and the boolean value is returned
 */
bool intintCompare::lt(int i, int j) { return i < j; }

/*
 * Method to compare if i is greater than j
 * Precondition: i and j are not null, i and j are valid integers
 * Postcondition: i and j are compared and the boolean value is returned
 */
bool intintCompare::gt(int i, int j) { return i > j; }

/*
 * Method to compare if i is equal to j
 * Precondition: i and j are not null, i and j are valid integers
 * Postcondition: i and j are compared and the boolean value is returned
 */
bool intintCompare::eq(int i, int j) { return i == j; }
