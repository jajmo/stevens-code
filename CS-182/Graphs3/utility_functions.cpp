#include "mygraphs.hh"
#include "myamgraph.hh"

template void MyGraph<int>   ::unvisitAll();
template void MyGraph<string>::unvisitAll();

template <class Elem>

/**
 * unvisitAll()
 *
 * Marks all of the vertices as unvisited
 */
void MyGraph<Elem>::unvisitAll()
{
	int i;

	for(i = 0; i < this->v; i++)
		this->visited[i] = false;
}

template MyGraph<int>*    MyGraph<int>   ::getMST();
template MyGraph<string>* MyGraph<string>::getMST();

template <class Elem>

/**
 * getMST()
 *
 * Returns either prims or kruscal, depending on the density
 */
MyGraph<Elem>* MyGraph<Elem>::getMST()
{
	if(this->e < ((this->v * (this-> v - 1)) / 3))
		return this->kruskal();
	else
		return this->prims();
}