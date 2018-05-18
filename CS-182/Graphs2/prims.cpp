#include "myamgraph.hh"

template MyGraph<string>* MyAmGraph<string>::prims();
template MyGraph<int>*    MyAmGraph<int>   ::prims();

template <class Elem>

/**
 * prims()
 * Returns the minimal cost spanning tree
 */
MyGraph<Elem>* MyAmGraph<Elem>::prims()
{
	MyAmGraph<Elem> *theMST = NULL;

	if(!this->directed && this->v > 0)
	{
		t_edge arr[this->v -1];
		int i, minIdx;
		int size = this->v - 1;

		for(i = 1; i < this->v; i++)
		{
			arr[i - 1].src    = 0;
			arr[i - 1].dst    = i;
			arr[i - 1].weight = this->get_edge(0, i);
		}

		theMST = new MyAmGraph<Elem>(this->v, false);

		for(i = 0; i < this->v; i++)
			theMST->add_vertex(this->vertices[i]);

		t_edge tmp, swp;

		while(size > 0)
		{
			tmp    = arr[0];
			minIdx = 0;

			for(i = 0; i < size; i++)
			{
				if(arr[i].weight < tmp.weight)
				{
					tmp    = arr[i];
					minIdx = i;
				}
			}

			swp         = arr[minIdx];
			arr[minIdx] = arr[--size];
			arr[size]   = swp;

			if(tmp.weight == this->INF)
			{
				delete theMST;
				return NULL;
			}

			theMST->add_edge(tmp.src, tmp.dst, tmp.weight);

			for(i = 0; i < size; i++)
			{
				if(arr[i].weight > this->get_edge(tmp.dst, arr[i].dst))
				{
					arr[i].weight = this->get_edge(tmp.dst, arr[i].dst);
					arr[i].src    = tmp.dst;
				}
			}
		}
	}

	return theMST;
}