#include "heist_map.hh"

/*
	firstNeighbor(unsigned int i)
	Author: Dakota (dcrouche)
	
	A method that returns the first connected neighbor of the location at the given index
	
	Precondition:
		i is a valid integer greater than or equal to 0 and less than the current v
	
	Postcondition:
		The adjacency matrix will be linearly parsed
		If the given location has at least one neighbor, the index of the first one found will be returned
		If the given location has no neighbors, INVALID will be returned
*/
unsigned int HeistMap::firstNeighbor(unsigned int i)
{
	return nextNeighbor(i, -1);
}

/*
	nextNeighbor(unsigned int i, unsigned int last)
	Author: Dakota (dcrouche)
	
	A method that returns the next connected neighbor of the location at the given index after the other location at the given index
	
	Precondition:
		i is a valid integer greater than or equal to 0 and less than the current v
		j is a valid integer greater than or equal to 0 and less than the current v
	
	Postcondition:
		The adjacency matrix will be linearly parsed
		If the given location has at least one neighbor after the last one, the index of the first one found will be returned
		If the given location has no more neighbors, INVALID will be returned
*/
unsigned int HeistMap::nextNeighbor(unsigned int i, unsigned int j)
{
	for(j = ++j; j < v; j++)
        if(get_visibility(i, j) != 0 && get_visibility(i, j) != INVALID && i != j)
            return j;

	return INVALID;
}