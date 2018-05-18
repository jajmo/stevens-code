#include "mygraphs.hh"

template void MyGraph<string>::showMaxFlow(MyGraph<string>*);
template void MyGraph<int>   ::showMaxFlow(MyGraph<int>*);

template <class Elem>

void MyGraph<Elem>::showMaxFlow(MyGraph<Elem>* maxFlow)
{
	int i, j;

	for(i = 0; i < maxFlow->V(); i++)
	{
		for(j = 0; j < maxFlow->V(); j++)
		{
			//cout << "i: " << i << " j: " < <j << endl;
			if(maxFlow->get_edge(i, j) == this->INF || this->get_edge(i, j) == this->INF)
				cout << "0\t";
			else if(this->get_edge(j, i) == this->INF)
				cout << maxFlow->get_edge(i, j) << "/" << this->get_edge(i, j) << "\t";
			else if(maxFlow->get_edge(i, j) > this->get_edge(j, i))
			{
				cout << (maxFlow->get_edge(i, j) - this->get_edge(j, i));
				cout << "/" << this->get_edge(i, j) << "\t";
			}
			else
				cout << "0/" << this->get_edge(i, j) << "\t";
		}

		cout << endl;
	}
}