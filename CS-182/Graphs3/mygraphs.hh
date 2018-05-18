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

//Edge structure
typedef struct s_edge
{
  unsigned int src;
  unsigned int dst;
  int weight;
} t_edge;

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
  virtual int *dijkstra(unsigned int); // returns the distances array
  virtual int get_edge(unsigned int, unsigned int) = 0; //Used by Dijkstra
  MyGraph<Elem> *getMST(); //calls either Prims or Kruskal based on density
  void unvisitAll(); // will make your life easier
  void traverse(bool);
  void showMaxFlow(MyGraph<Elem>*); 
  int **floyd(); // return a 2D array of size V*V with the shortest distance from every source to every destination. You may use 0 or INF as "no such path", up to you
  MyGraph<Elem> *fordFulkerson(unsigned int source, unsigned int target); // Return the final residual network for the original graph FF algorithm from source to target
protected:
  const static int INF = 2147483647;
  Elem *vertices;
  bool *visited;
  bool directed;
  unsigned int v;
  unsigned int e;
  unsigned int cap;
  bool myunion(int[], unsigned int, unsigned int);
  unsigned int myfind(int P[], unsigned int);
  virtual MyGraph<Elem> *kruskal() = 0;
  virtual MyGraph<Elem> *prims() = 0;
  int findAugmentingPath(unsigned int w, unsigned int t, int flow);
private:
  void bfs(unsigned int);
  void dfs(unsigned int);
};

#endif
