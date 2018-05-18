#include "heist_map.hh"

/**
 * HeistMap()
 * Author: Jason Ajmo (jajmo)
 * 
 * Calls the second constructor to create a heist map
 * This method should never be called
 *
 * Precondition:
 *		None
 *
 * Postcondition:
 *		A new heist map is created
 */
HeistMap::HeistMap()
{
	HeistMap(10, 10);
}

/**
 * HeistMap(unsigned int cap, unsigned int p)
 * Author: Jason Ajmo (jajmo)
 *
 * Creates a blank heist map based on cap and p
 *
 * Parameter cap - the capacity of the new heist map
 * Parameter p   - The max amount of people in the map
 *
 * Precondition:
 *		None
 * Postcondition:
 *		A new heist map is created with cap capacity and p max people
 */ 
HeistMap::HeistMap(unsigned int cap, unsigned int p)
{
	int i, j;
	
	this->cap   = cap;
	vertices    = new t_location[cap];
	v           = 0;
	e           = 0;
	visited     = new bool[cap];
	am          = new unsigned int*[cap];
	peopleCount = 0;
	people      = new t_person[p];

	for(i = 0; i < cap; i++)
	{
		am[i] = new unsigned int[cap];
		
		for(j = 0; j < cap; j++)
			am[i][j] = 0;
	}
}

/**
 * ~HeistMap()
 * Author: Jason Ajmo (jajmo)
 *
 * Destructor for heist map class
 *
 * Precondition:
 *		None
 * Postcondition:
 * 		The heist map arrays are deleted
 */
HeistMap::~HeistMap()
{
	int i;
	
	delete [] vertices;
	delete [] visited;
	delete [] people;
	for(i = 0; i < cap; i++)
		delete [] am[i];
	delete [] am;
}
