#ifndef _MYGRAPHS_HH_
#define _MYGRAPHS_HH_

#include <iostream>
using namespace std;

#ifndef TRUE
#define TRUE true
#endif

#ifndef FALSE
#define FALSE false
#endif


template <class Elem>
class MyGraph
{
public:
  MyGraph();
  ~MyGraph();
  MyGraph(bool dir);
  MyGraph(unsigned int cap, bool dir);
  MyGraph(unsigned int cap);
  unsigned int V();
  unsigned int E();
  virtual int firstNeighbor(unsigned int) = 0;
  virtual int nextNeighbor(unsigned int, unsigned int) = 0;
  int add_vertex(Elem);
  virtual bool add_edge(unsigned int, unsigned int, int) = 0;
  void show_vertices();
  Elem vertex(unsigned int);
  virtual void show_edges() = 0;
  void bfs();
  void dfs();
  void traverse(bool dfs);  //true for dfs, false for bfs
protected:
  const static int INF = 2147483647;
  Elem *vertices;
  bool *visited;
  bool directed;
  unsigned int v;
  unsigned int e;
  unsigned int cap;
private:
  void bfs(unsigned int);
  void dfs(unsigned int);
};

#endif/**/
