#ifndef _SORTING_HH
#define _SORTING_HH_

#include <iostream>
#include "myamgraph.hh"

using namespace std;

class Sortings
{
	public: static void select(t_edge *arr, unsigned int n)
	{
		int i, j, min;
		t_edge tmp;

		if(arr != NULL)
		{
			for(i = 0; i < n; i++)
			{
				for(min = i, j = i + 1; j < n; j++)
					if(arr[j].weight < arr[min].weight)
						min = j;

				if(i != min)
				{
					tmp      = arr[i];
					arr[i]   = arr[min];
					arr[min] = tmp;
				}
			}
		}	
	}
};

#endif