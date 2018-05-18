#include "heist_map.hh"
#include "sorting.hh"
#include <string>

/**
 * bigJobCrew()
 * Author: Jason Ajmo (jajmo)
 *
 * Method to print out the names of the crew members that can safely make it from a location
 * to another location, both specified by the user
 *
 * Precondition:
 *		Map is valid
 *		v > 0
 *
 * Postcondition:
 *  	The crew that can go is printed; else "Nobody can go!" is printed
 */
void HeistMap::bigJobCrew()
{
	bool 		 peopleSent = false;
	unsigned int start, dst, crew, i, j;
	HeistMap*    res;
	cout << "Select a starting location (index): " << endl;

	//Get starting index
	do
	{
		for(i = 0; i < v; i++)
			cout << i << ") " << vertices[i].name << endl;

		cin >> start;
	} while(start > v); //Don't check for negatives, unsigned int

	cout << "Select an ending location (index): " << endl;

	//Get dst index
	do
	{
		for(i = 0; i < v; i++)
			if(i != start)
				cout << i << ") " << vertices[i].name << endl;

		cin >> dst;
	} while(dst > v && dst == start); //Don't check for negatives, unsigned int

	res = HeistMap::start(); //Create copy so we don't modify the original

	Sortings::select(people, peopleCount);

	for(i = 0; i < peopleCount; i++)
	{
		res->unvisitAll();
		
		if(res->canSend(start, dst, people[i].vis))
		{
			cout << people[i].name << ", ";
			peopleSent = true;
		}
	}
	
	if(!peopleSent)
		cout << "Nobody can go!";

	delete res;
	cout << endl;
}