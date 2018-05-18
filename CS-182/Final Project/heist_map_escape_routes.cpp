#include "heist_map.hh"


/*
	findEscapeRoutes()
	Author: Dakota (dcrouche)
	
	Precondition:
		v>=2
	
	Postcondition:
		Allocates a 2D array of unsigned ints
		For each path between every possible pair of nodes, the safest path will be determined
			This is defined to be the path where the lowest visibility edge in the path is as high as possible.
		For each arr[i][j] element in the array the lowest visibility in the path from i to j will be stored
		For this algorithm, the item visibility of each location will be ignored.
		
*/

unsigned int **HeistMap::findEscapeRoutes()
{
	unsigned int **H = NULL;
	unsigned int i, j, k, temp;
	
	if (v>=2)
	{
		H = new unsigned int*[v];
		for (i=0; i<v; i++)
		{
			H[i] = new unsigned int[v];
			for (j=0; j<v; j++)
				if (i==j) H[i][j] = 0;
				else H[i][j] = get_visibility(i, j);
		}
		
		for (k=0; k<v; k++)
			for (i=0; i<v; i++)
				if (i!=k && H[i][k]!=0)
					for (j=0; j<v; j++)
					{
						temp = H[i][k]<H[k][j]? H[i][k] : H[k][j];
						if (j!=k && j!=i && H[k][j]!=0 && H[i][j]<temp)
							H[i][j] = temp;
					}
	}
	
	return H;
}
