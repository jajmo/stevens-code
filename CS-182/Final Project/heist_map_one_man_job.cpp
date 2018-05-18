#include "heist_map.hh"

/**
 * one_map_job()
 * Author: Jason Ajmo (jajmo)
 *
 * Processes the user input for one man job, and then calls the respective function with the user input
 *
 * Precondition:
 * 		v > 0
 *
 * Postcondition:
 * 		The one man job output is printed, or if failed an alternate message is printed
 */
void HeistMap::one_man_job()
{
	int 		 i;
	unsigned int start, dst, crew;
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
	} while(dst > v || dst == start); //Don't check for negatives, unsigned int

	cout << "Select an person to attempt job (index): " << endl;

	//Get person index
	do
	{
		for(i = 0; i < peopleCount; i++)
		{
			cout << i << ") " << people[i].name;
			cout << " vis " << people[i].vis << endl;
		}

		cin >> crew;
	} while(crew > peopleCount); //Don't check for negatives, unsigned int

	show_safest_path(start, dst, crew);
}