/*
 * mergeRecurse.cpp
 * Conatins the method that performs the merge sort
 */
#include "sorting.hh"

template void Sortings<int,intintCompare>::mergeRecurse(int *, int *, unsigned int, unsigned int);
template void Sortings<char*,strstrCompare>::mergeRecurse(char**, char **, unsigned int, unsigned int);

template <class Elem, class Comp>

/*
 * Private method to perform the recursive part of merge sort
 * Precondition: arr is not null, tmp is not null, l and r are both contained within the array
 * Postcondition: arr is sorted
 */
void Sortings<Elem, Comp>::mergeRecurse(Elem *arr, Elem tmp[], unsigned int l, unsigned int r)
{
	unsigned int m, i, j, k;
	if(l < r)
	{
		//m = l + (r - 1) / 2;
		m = (l + r) / 2;
		mergeRecurse(arr, tmp, l, m);	
		mergeRecurse(arr, tmp, m + 1, r);

		for(i = 0; i <= m; i++)
			tmp[i] = arr[i];

		for(j = r; j > m; j--, i++)
			tmp[i] = arr[j];

		for(i = l, j = l, k = r; i <= r; i++)
			if(Comp::gt(tmp[j], tmp[k]))
				arr[i] = tmp[k--];
			else
				arr[i] = tmp[j++];
	
	}
}
