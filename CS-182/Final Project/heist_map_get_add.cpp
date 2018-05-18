#include "heist_map.hh"

/*
	add_location(t_location l)
	Author: Dakota (dcrouche)
	
	Adds the given location to the next available vertex
	
	Precondition:
		The given location is valid
		The graph has not reached its capacity
	
	Postcondition:
		The given location will be added to the graph
		The index of the new location will be returned
		If the capacity has been reached, INVALID will be returned
*/
unsigned int HeistMap::add_location(t_location l)
{
	if (v < cap)
	{
		vertices[v++] = l;
		return v;
	}
	return INVALID;
}

/**
 * add_person(t_person p)
 * Author: Jason Ajmo (jajmo)
 *
 * Add a person to the people array
 *
 * Precondition:
 *		p != NULL
 *
 * Postcondition:
 * 		people[peopleCount++] is set to p
 */
void HeistMap::add_person(t_person p)
{
	if(peopleCount < cap)
		people[peopleCount++] = p;
}

/*
	vertex(unsigned int i)
	Author: Dakota (dcrouche)
	
	Returns a pointer to the specified location
	
	Precondition:
		i is a valid unsigned int
			greater than or equal to 0 and
			less than v
	
	Postcondition:
		A pointer to the location at index i will be returned
		If such a vertex does not exist, NULL will be returned
*/
t_location* HeistMap::get_location(unsigned int i)
{
	if (i<v) return vertices+i;
	else return NULL;
}

/*
	add_visibility(unsigned int i, unsigned int j, unsigned int vis)
	Author: Dakota (dcrouche)
	
	This is a method used to connect two locations with a particular visibility.
	
	Precondition:
		i is an unsigned int within the range of valid vertices
			it indicates the source of the edge
		j is an unsigned int within the range of valid vertices
			it indicates the destination of the edge
		vis is a valid int greater than 0
			it indicates the visibility of the edge
	
	Postcondition:
		The visibility for the edge indicated by the endpoints will be set to vis
		The count of edges will be increased by one, if this is not an overwrite
		False will be returned if the endpoints are invalid or if they are equal
		True will be returned otherwise
*/
bool HeistMap::add_visibility(unsigned int i, unsigned int j, unsigned int vis)
{
	if (i!=j && i<v && j<v)
	{
		if (get_visibility(i, j)==0) 
			e++;
		
		am[i][j] = vis;
		return true;
	}

	return false;
}

/*
	get_visibility(unsigned int i, unsigned int j)
	Author: Dakota (dcrouche)
	
	This method returns the visibility of the path that goes from location i to j
	
	Precondition
		i is an unsigned int within the range of valid vertices
			it indicates the source of the edge
		j is an unsigned int within the range of valid vertices
			it indicates the destination of the edge
	
	Postcondition
		The visibility of the given edge will be returned
		If there is no edge here, 0 will be returned
*/
unsigned int HeistMap::get_visibility(unsigned int i, unsigned int j)
{
	if (i < v && j < v && i != j)
		return am[i][j];

	return 0;
}