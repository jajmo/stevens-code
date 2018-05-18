#include "mygraphs.hh"
#include "myamgraph.cpp"

template MyGraph<string>* MyGraph<string>::fordFulkerson(unsigned int source, unsigned int target);
template MyGraph<int>*    MyGraph<int>   ::fordFulkerson(unsigned int source, unsigned int target);

template <class Elem>

MyGraph<Elem> *MyGraph<Elem>::fordFulkerson(unsigned int source, unsigned int target)
{
	MyAmGraph<Elem> *resNet = NULL;
	int i, j;

	if(source < this->v && target < this->v && source != target && this->directed)
	{
		resNet = new MyAmGraph<Elem>(this->v, true);

		for(i = 0; i < this->v; i++)
			resNet->add_vertex(this->vertices[i]);

		for(i = 0; i < this->v; i++)
		{
			for(j = 0; j < this->v; j++)
			{
				if(i != j && this->get_edge(i, j) != this->INF && this->get_edge(i, j) != -1)
					resNet->add_edge(j, i, this->get_edge(i, j));
				else
					resNet->add_edge(j, i, 0);
			}
		}

		do
		{
			resNet->unvisitAll();
		}   while(resNet->findAugmentingPath(target, source, this->INF) > 0);
	}

	//resNet->show_am();
	return resNet;
}
