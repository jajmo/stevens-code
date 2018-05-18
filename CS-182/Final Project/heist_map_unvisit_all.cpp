#include "heist_map.hh"

/**
 * unvisitAll()
 * Author: Jason Ajmo (jajmo)
 *
 * Marks all of the vertices as unvisited
 *
 * Precondition:
 *		None
 *
 * Postcondition:
 *		All of the vertices are marked unvisited
 */
void HeistMap::unvisitAll()
{
	int i;

	for(i = 0; i < v; i++)
		visited[i] = false;
}