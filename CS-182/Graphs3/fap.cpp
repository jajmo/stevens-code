#include "mygraphs.hh"

template int MyGraph<string>::findAugmentingPath(unsigned int v, unsigned int s, int flow);
template int MyGraph<int>   ::findAugmentingPath(unsigned int v, unsigned int s, int flow);

template <class Elem>

int MyGraph<Elem>::findAugmentingPath(unsigned int v, unsigned int s, int flow)
{
	unsigned int w, minFlow;

	if(v < this->v && s < this->v && this->directed)
	{
		if(v == s)
			return flow;

		this->visited[v] = true;

		for(w = this->firstNeighbor(v); w < this->v; w = this->nextNeighbor(v, w))
		{
			if(!this->visited[w])
			{
				this->visited[w] = true;

				if(this->get_edge(v, w) < flow)
					minFlow = this->get_edge(v, w);
				else
					minFlow = flow;

				//minFlow = ((this->get_edge(s, w) < flow) ? this->get_edge(s, w) : flow);

				if((minFlow = findAugmentingPath(w, s, minFlow)) > 0 && minFlow != this->INF)
				{
					this->add_edge(w, v, this->get_edge(w, v) + minFlow);
					this->add_edge(v, w, this->get_edge(v, w) - minFlow);

					return minFlow;
				}
			}
		}
	}

	return 0;
}/**/