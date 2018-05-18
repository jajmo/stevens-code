#include "heist_map.hh"

/**
 * Final Project
 * Main Class: HeistMap
 * Header: heist_map.hh
 * Authors: Jason Ajmo (jajmo), Dakota Crouchelli (dcrouche)
 */
int main(int argc, char** argv)
{
	HeistMap*    map = HeistMap::start();
	unsigned int input;

	if(map == NULL)
	{
		cout << "File sneaky cound not be found!" << endl;
		return 0;
	}
	
	do
	{
		cout << "1) Show Locations" << endl;
		cout << "2) Show Map" << endl;
		cout << "3) Show People" << endl;
		cout << "4) One Man Job" << endl;
		cout << "5) Escape Routes" << endl;
		cout << "6) Big Job Crew Selector" << endl;
		cout << "0) Exit" << endl;

		cin >> input;

		map->processInput(input);
		
		cout << endl;
	} while (input < 7 && input > 0);
	/**/

	delete map;
	return 0;
}