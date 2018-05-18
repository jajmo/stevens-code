#ifndef _SORTING_HH
#define _SORTING_HH_

#include <iostream>

using namespace std;

class Sortings
{
	public: static void select(t_person *arr, unsigned int n)
	{
		int i, j, min;
		t_person tmp;

		if(arr != NULL)
		{
			for(i = 0; i < n; i++)
			{
				for(min = i, j = i + 1; j < n; j++)
					if(arr[j].vis < arr[min].vis)
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