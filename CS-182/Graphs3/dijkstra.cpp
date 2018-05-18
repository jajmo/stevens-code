#include "myamgraph.hh"

template int* MyGraph<int>   ::dijkstra(unsigned int);
template int* MyGraph<string>::dijkstra(unsigned int);

template <class Elem>

/**
 * dijkstra()
 * Returns an array of distances from node s to the rest of the nodes in the graph
 * Value is INF if the node cannot be reached from the starting point
 */
int* MyGraph<Elem>::dijkstra(unsigned int s)
{
	//Declare as null for returning sake, in case EC fails
	int * D = NULL;
	int i, t, k, z; //z = am[todo[t]][todo[i]]
	unsigned int temp; //Used for swapping

	if(s < this->v)
	{
		//Create variables
		unsigned int todo[this->v - 1];
		D = new int[this->v];

		for(i = 0, t = 0; i < this->v; i++)
		{
			if(i != s)
			{
				todo[t++] = i;
				D[i]      = this->get_edge(s, i);
			} else
				D[i] = 0;
		}

		while(t > 1)
		{
			for(k = 0, i = 1; i < t; i++)
				if(D[todo[k]] > D[todo[i]])
					k = i;

			if(D[todo[k]] == this->INF)
					break;

			//swap(todo, k, --t);
			temp      = todo[k];
			todo[k]   = todo[--t];
			todo[t]   = temp; //Don't decrement t again, !important!

			for(i = 0; i < t; i++)
			{
				z = this->get_edge(todo[t], todo[i]); //To avoid code repetititon

				if((z != this->INF) && (D[todo[i]] > (D[todo[t]] + z)))
					D[todo[i]] = D[todo[t]] + z;
			}
		}
	}

	return D;
}