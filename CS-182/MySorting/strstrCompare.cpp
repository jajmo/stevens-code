/*
 * strstrCompare.cpp
 * Contains methods to compare strings
 * Used with templates
 */
#include "sorting.hh"

/*
 * Method to see if str i is less than str j
 * Precondition: i and j are not null
 * Postcondition: i and j are compared, the boolean result returned
 */
bool strstrCompare::lt(char* i, char* j) 
{
	if(strcmp(i, j) > 0)
		return false;

	return true;
}

/*
 * Method to see if str i is greater than str j
 * Precondition: i and j are not null
 * Postcondition: i and j are compared, the boolean result returned
 */
bool strstrCompare::gt(char* i, char* j) 
{
	if(strcmp(i, j) < 0)
		return false;

	return true;
}

/*
 * Method to see if str i is eqal to str j
 * Precondition: i and j are not null
 * Postcondition: i and j are compared, the boolean result returned
 */
bool strstrCompare::eq(char* i, char* j) 
{
	if(strcmp(i, j) == 0)
		return false;

	return true;
}
