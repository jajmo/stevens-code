#include "mygraphs.hh"

template int** MyGraph<string>::floyd();
template int** MyGraph<int>   ::floyd();

template <class Elem>

int** MyGraph<Elem>::floyd()
{
	int i, j, k;
	int **D;

	if(this->V() < 2)
		return NULL;

	D = new int*[this->V()];

	for(i = 0; i < this->V(); i++)
	{
		D[i] = new int[this->V()];

		for(j = 0; j < this->V(); j++)
		{
			if(i == j)
				D[i][j] = 0;
			else
				D[i][j] = this->get_edge(i, j);
		}
	}

	for(k = 0; k < this->V(); k++)
		for(i = 0; i < this->V(); i++)
			if(i != k && D[i][k] != this->INF)
				for(j = 0; j < this->V(); j++)
					if(j != k && j != i && D[k][i] != this->INF && (D[i][j] > (D[i][k] + D[k][j])))
						D[i][j] = D[i][k] + D[k][j];

	return D;
}