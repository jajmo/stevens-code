/*
 * swap.cpp
 * Contains the method to swap two elements in an array
 */
#include "sorting.hh"

template void Sortings<int,intintCompare>::swap(int*, unsigned int, unsigned int);
template void Sortings<char*,strstrCompare>::swap(char**, unsigned int, unsigned int);

template <class Elem, class Comp>

/*
 * Method to swap two elements in arr
 * Precondition: arr is not null, i and j are both less than the length of the array
 * Postcondition: arr[i] and arr[j] are swapped
 */
void Sortings<Elem, Comp>::swap(Elem *arr, unsigned int i, unsigned int j)
{
	Elem tmp = arr[i];
	arr[i] = arr[j];
	arr[j] = tmp;
}
