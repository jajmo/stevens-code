#include "heist_map.hh"
#include <sstream>

/**
 * show_locations()
 * Author: Jason Ajmo (jajmo)
 *
 * Prints all the locations in the vertices array
 *
 * Precondition:
 *		None
 *
 * Postcondition:
 *		All of the locations are printed using a depth first search
 */
void HeistMap::show_locations()
{
	int i, j;

    unvisitAll();

    for(j = 0; j < v; j++)
    {
        if(!visited[j])
            dfs(j);
    }
}

/**
 * show_crew()
 * Author: Jason Ajmo (jajmo)
 *
 * Prints out the crew members using a basic array traversal
 *
 * Precondition:
 *		None
 *
 * Postcondition:
 *		All of the crew is printed out
 */
void HeistMap::show_crew()
{
	int i;

	for(i = 0; i < peopleCount; i++)
	{
		cout << people[i].name << " has vis ";
		
		if(i !=  peopleCount - 1)
			cout << people[i].vis  << ", ";
		else
			cout << people[i].vis;
	}

	cout << endl;
}

/**
 * show_map()
 * Author: Jason Ajmo (jajmo)
 *
 * Prints out the adjacency matrix
 *
 * Precondition:
 *		None
 *
 * Postcondition:
 *		The adjacency matrix is printed
 */
void HeistMap::show_map()
{
	int i, j;

	for(i = 0; i < cap; i++)
	{
		for(j = 0; j < cap; j++)
			cout << get_visibility(i, j) << " ";
		cout << endl;
	}
}

/*
	show_safest_path(unsigned int s, unsigned int t, unsigned int p)
	Author: Dakota (dcrouche)
	
	PreCondition:
		s<v
		t<=v
		p<peopleCount
	
	PostCondition:
		Will print the safest path (if it exists) from s to t for person p
		If t==v, will print safest paths to all targets
		If there is no safe path, the person will be recommended not to steal this item.
*/
void HeistMap::show_safest_path(unsigned int s, unsigned int t, unsigned int p)
{
	unsigned int *there = NULL, *back = NULL;
	unsigned int times, i;
	
	stringstream temp;
	string path;
	
	if (s<v && t<=v && p<peopleCount)
	{
		there = findSafestPaths(s, people[p].vis);
		unsigned int times = t==v? t-- : 1;
		
		while (times>0)
		{
			path = people[p].name + " should not attempt to steal " + get_location(t)->itemName + ".";
			
			if (t!=s && there[t]!=INVALID)
			{
				back = findSafestPaths(t, people[p].vis + get_location(t)->itemVis);
				
				if (back[s]!=INVALID)
				{
					path = "";
					temp.str("");
					
					for (i=s; back[i]!=i; i=back[i])
						path = get_location(i)->name + ", " + path;
					
					temp<<"Pick up "<<get_location(t)->itemName<<" worth "<<get_location(t)->itemVal<<"K, ";
					path = temp.str() + path;
					
					for (i=t; there[i]!=i; i=there[i])
						path = get_location(i)->name + ", " + path;
					path = get_location(i)->name + ", " + path;
				}
				
				delete [] back;
			}
			
			cout<<path<<endl;
			times--;
			t--;
		}
		
		delete [] there;
	}
}

/*
	showEscapeRoutes()
	Author: Dakota (dcrouche)
	
	Precondition:
		findEscapeRoutes provides valid output
	
	Postcondition:
		The output of findEscapePaths will be adjusted to take the item visibility into account
		If this makes stealing the item impossible, the visibility output will be 0
		The matrix will be printed
*/
void HeistMap::showEscapeRoutes()
{
	unsigned int **Vis = findEscapeRoutes();
	unsigned int i, j;
	
	if (Vis!=NULL)
	{
		for (i=0; i<v; i++)
		{
			for(j=0; j<v; j++)
				if (Vis[i][j] <= (get_location(i)->itemVis))
					cout<<0<<" ";
				else cout<<Vis[i][j] - (get_location(i)->itemVis)<<" ";
			cout<<endl;
		}
	}
	
	else cout<<"No escape routes."<<endl;
	
	for (i=0; i<v; i++)
		delete [] Vis[i];
	
	delete [] Vis;
}