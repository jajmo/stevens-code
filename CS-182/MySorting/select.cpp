/*
 * select.cpp
 * Contains the method to perform selection sort
 */
#include "sorting.hh"

template void Sortings<int,intintCompare>::select(int *, unsigned int);
template void Sortings<char*,strstrCompare>::select(char**, unsigned int);

template <class Elem, class Comp>

/*
 * Method to perform selection sort
 * Precondition: arr is not null, n is less than the length of arr
 * Postcondition: n elements in arr are sorted
 */
void Sortings<Elem, Comp>::select(Elem *arr, unsigned int n)
{
	int i, j, min;

	if(arr != NULL)
	{
		for(i = 0; i < n; i++)
		{
			for(min = i, j = i + 1; j < n; j++)
				if(Comp::lt(arr[j], arr[min]))
					min = j;

			if(i != min)
				Sortings::swap(arr, intuival::uintVal(i), min);
		}
	}	
}
