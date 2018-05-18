#include "myamgraph.hh"
#include "sorting.hh"

template MyGraph<int>*    MyAmGraph<int>   ::kruskal();
template MyGraph<string>* MyAmGraph<string>::kruskal();

template <class Elem>

/**
 * kruskal()
 * Returns the minimal cost spanning tree
 */
MyGraph<Elem>* MyAmGraph<Elem>::kruskal()
{
	//Declare initially as NULL for error checking
	MyAmGraph<Elem> *theMST = NULL;

	//Must be undirected for kruskal to work
	if(!this->directed && this->v > 0)
	{
		//Variable declarations
		int i, j, count = 0;
		theMST = new MyAmGraph<Elem>(this->V(), false);
		t_edge edges[this->e];
		int parents [this->v];
		
		for(i = 0; i < this->v; i++)
		{
			theMST->add_vertex(this->vertices[i]);
			parents[i] = i;
		}

		for(i = 0; i < theMST->V(); i++)
		{
			for(j = i; j < theMST->V(); j++)
			{
				//cout << "j: " << j << " i: " << i << endl;
				if(this->get_edge(i, j) != this->INF)
				{
					edges[count].src    = i;
					edges[count].dst    = j;
					edges[count++].weight = this->get_edge(i, j);
				}
			}
		}

		//cout << "Before sorting" << endl;
		Sortings::select(edges, count);

		i = 0;
		while(theMST->E() < (this->v - 1))
		{
			//cout << "i: " << i << endl;
			if(i >= count)
			{
				//cout << "Error" << endl;
				delete theMST;
				return NULL;
			}

			if(this->myunion(parents, edges[i].src, edges[i].dst))
				theMST->add_edge(edges[i].src, edges[i].dst, edges[i].weight);
			i++;
		}
	}

	return theMST; //Returns NULL if error checking fails
}