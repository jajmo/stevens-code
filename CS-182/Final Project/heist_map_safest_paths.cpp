#include "heist_map.hh"

/*
	findSafestPaths(unsigned int s, unsigned int vis)
	Author: Dakota (dcrouche)
	
	PreCondition:
		s<v
	
	PostCondition
		will return a previousStep[] signifying the safest paths from s to anywhere
			If there is no safe path to a given t, previousStep[t] == INVALID
			previousStep[s] = s
*/

unsigned int *HeistMap::findSafestPaths(unsigned int s, unsigned int vis)
{
	unsigned int *Vis = NULL;
	unsigned int *P   = NULL;
	unsigned int i, t, k, temp;
	
	if (s<v)
	{
		unsigned int todo[v-1];
		Vis = new unsigned int[v];
		P   = new unsigned int[v];
		
		for (i=0, t=0; i<v; i++)
		{
			Vis[i] = 0;
			P[i] = INVALID;
			todo[t++] = i;
		}
		
		Vis[s] = INVALID;
		P[s] = s;
		
		while (t>0)
		{
			for (k=0, i=1; i<t; i++)
				if (Vis[todo[i]]>Vis[todo[k]])
					k=i;
			
			if (Vis[todo[k]] == 0) break;
			
			for (i=firstNeighbor(todo[k]); i!=INVALID; i=nextNeighbor(todo[k], i))
			{
				temp = Vis[todo[k]] < get_visibility(todo[k], i)? Vis[todo[k]] : get_visibility(todo[k], i);
				
				if (temp > Vis[i])
				{
					Vis[i] = temp;
					P[i] = todo[k];
				}
			}
			
			todo[k] = todo[--t];
		}
		
		for (i=0; i<v; i++)
			if (i!=s && Vis[i] < vis)
				P[i] = INVALID;
	}
	
	delete [] Vis;
	return P;
}