#include "heist_map.hh"

/**
 * processInput(unsigned int i)
 * Author: Jason Ajmo (jajmo)
 *
 * Processes the user input from the main menu
 *
 * Precondition:
 *		i < 7
 *		i > 0
 *
 * Postcondition:
 *		The proper method is called based on the user's choice
 */
void HeistMap::processInput(unsigned int i)
{
	switch(i)
	{
		case 1: show_locations();
				break;
		case 2: show_map();
				break;
		case 3: show_crew();
				break;
		case 4: one_man_job();
				break;
		case 5: showEscapeRoutes();
				break;
		case 6: bigJobCrew();
		default: break;
	}
}