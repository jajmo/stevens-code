/*
 * merge.cpp
 * Contains the method that performs error checking and instantiates a new array to pass to mergeRecurse()
 */
#include "sorting.hh"

template void Sortings<int,intintCompare>::merge(int *, unsigned int);
template void Sortings<char*,strstrCompare>::merge(char**, unsigned int);

template <class Elem, class Comp>

/*
 * Method used for error checking and passing proper values to mergeRecurse()
 * Precondition: arr is not null, n is less than the length of arr
 * Postcondition: n elements in arr are sorted
 */
void Sortings<Elem, Comp>::merge(Elem *arr, unsigned int n)
{
	Elem tmp[n];
	Sortings::mergeRecurse(arr, tmp, 0, intuival::uintVal(n));
}
