#include "myamgraph.hh"

int main(int argc, char **argv)
{
  int v, i;
  MyAmGraph<string> *G = new MyAmGraph<string>(5,false);

  G->add_vertex("A");
  G->add_vertex("B");
  G->add_vertex("C");
  G->add_vertex("D");
  G->show_vertices();
  G->show_am();
  G->add_edge(0, 1, 10);
  G->add_edge(0, 2, 15);
  G->add_edge(1, 3, 20);
  G->add_edge(2, 3, 10);
  G->show_am();
  G->show_edges();
  for (i = 0; i < G->V(); i++)
    {
      cout << "Neighbor of " << i << ": ";
      for (v = G->firstNeighbor(i); v >= 0; v = G->nextNeighbor(i, v))
	cout << v << " ";
      cout << endl;
    }
  G->bfs();
  cout << endl;
  G->dfs();
  return 0;
}
