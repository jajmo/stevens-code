/*
 * insert2.cpp
 * Contains the method used for shell sort
 *
 * It is a modified insertion sort
 */
#include "sorting.hh"

template void Sortings<int,intintCompare>::insert2(int *, unsigned int, unsigned int, unsigned int);
template void Sortings<char*,strstrCompare>::insert2(char**, unsigned int, unsigned int, unsigned int);

template <class Elem, class Comp>

/*
 * Private method method to perform the modified insertion sort, used by shell sort
 * Precondition: arr is not null
 * Postcondition: The specified elements (by incr, n, and s) are sorted
 */
void Sortings<Elem, Comp>::insert2(Elem *arr, unsigned int incr, unsigned int n, unsigned int s)
{
	int i, j;

	for(i = s + incr; i < n; i += incr)
		for(j = i; (j > s) && (Comp::lt(arr[j], arr[j - incr])); j -= incr)
			Sortings::swap(arr, j, j - incr);
}
