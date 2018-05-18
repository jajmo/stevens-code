#ifndef _MYAMGRAPH_HH_
#define _MYAMGRAPH_HH_

#include "mygraphs.hh"

template <class Elem>
class MyAmGraph : public MyGraph<Elem>
{
public:
  MyAmGraph(unsigned int cap, bool dir);
  ~MyAmGraph();
  int firstNeighbor(unsigned int);
  int nextNeighbor(unsigned int, unsigned int);
  bool add_edge(unsigned int, unsigned int, int);
  void show_edges();
  void show_am();
  int get_edge(unsigned int, unsigned int);
  MyGraph<Elem>* kruskal();
  MyGraph<Elem> *prims();
private:
  int **am;
};

#endif
