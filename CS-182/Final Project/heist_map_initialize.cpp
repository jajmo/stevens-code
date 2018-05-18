#include "heist_map.hh"
#include <fstream>
#include <sstream>

/**
 * static start()
 * Author: Jason Ajmo (jajmo)
 * 
 * Reads and populates a new object from the file
 *
 * Return HeistMap* - A new HeistMap populated and setup based on the data from the file
 *
 * Precondition:
 *		File sneaky exists
 *		File sneaky is in proper format
 *
 * Postcondition:
 *		The new HeistMap is returned and setup based on the information read from the file
 */
HeistMap* HeistMap::start()
{
	//All the variables except the istringstreams
	ifstream      file;
	unsigned int  l, p, e, itemVis, itemVal, from, to, weight, sneaky, count = 0;
	string		  line, token, itemName, name;
	int           i;
	HeistMap*	  tmp = NULL;
	t_location	  add;

	file.open("sneaky");

	//Ensure file exists
	if(file.is_open())
	{
		getline(file, line);

		istringstream out(line);
		out >> l >> e >> p;
		
		tmp = new HeistMap(l, p);

		//Add locations
		for(i = 0; i < l; i++)
		{
			count = 0;
			getline(file, line);
			istringstream out1(line);

			while(getline(out1, token, '|'))
			{
				switch(count)
				{
					case 0: 
						{	
							name = token;
							break;
						}
					case 1: 
						{
							itemName = token;
							break;
						}
					case 2: 
						{
							istringstream out2(token);
							out2 >> itemVis;
							break;
						}
					case 3: 
						{
							istringstream out3(token);
							out3 >> itemVal;
							break;
						}
					default: break;
				}

				count++;
			}

			add.name     = name;
			add.itemName = itemName;
			add.itemVis  = itemVis;
			add.itemVal  = itemVal;

			tmp->add_location(add);
		}

		//Add edges
		for(i = 0; i < e; i++)
		{
			getline(file, line);
			istringstream out4(line);
			out4 >> from >> to >> weight;
			tmp->add_visibility(from, to, weight);
		}

		//Add people
		for(i = 0; i < p; i++)
		{
			count = 0;

			getline(file, line);
			istringstream out5(line);

			while(getline(out5, token, '|'))
			{
				switch(count)
				{
					case 0: 
						{	
							name = token;
							break;
						}
					case 1: 
						{
							istringstream out6(token);
							out6 >> sneaky;
							break;
						}
					default: break;
				}

				count++;
			}

			t_person add2;
			add2.name = name;
			add2.vis  = sneaky;

			tmp->add_person(add2);		
		}

		file.close();
	}

	return tmp;
}