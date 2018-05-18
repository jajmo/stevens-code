#ifndef _HEIST_MAP_HH
#define _HEIST_MAP_HH

#include <string>
#include <iostream>
using namespace std;

typedef struct	 s_person
{
	unsigned int vis;
	string		 name;
}				 t_person;

typedef struct	 s_location
{
	string		 name;
	string		 itemName;
	unsigned int itemVis;
	unsigned int itemVal;
}				 t_location;

class HeistMap
{
	public:
		
		HeistMap();
		~HeistMap();
		HeistMap(unsigned int cap, unsigned int p);

		static HeistMap* start();

		void processInput(unsigned int i);
		
		unsigned int firstNeighbor(unsigned int);
		unsigned int nextNeighbor(unsigned int, unsigned int);
		
		unsigned int add_location(t_location);
		bool add_visibility(unsigned int, unsigned int, unsigned int);
		t_location* get_location(unsigned int);
		unsigned int get_visibility(unsigned int, unsigned int);
		
		void show_locations();
		void show_crew();
		void show_map();
		void show_safest_path(unsigned int source, unsigned int target, unsigned int person);
		void showEscapeRoutes();
		void one_man_job();
		void bigJobCrew();
		void unvisitAll();
		
		unsigned int *findSafestPaths(unsigned int source, unsigned int visibility);
		unsigned int **findEscapeRoutes();
		bool canSend(unsigned int source, unsigned int target, unsigned int stealth);
		
	private:
		
		const static unsigned int INVALID = -1;
		
		t_location *vertices;
		t_person   *people;
		bool *visited;
		
		unsigned int v;
		unsigned int e;
		unsigned int cap;
		unsigned int peopleCount;
		
		unsigned int **am;
		
		int findAugmentingPath(unsigned int v, unsigned int s, unsigned int flow);
		void dfs(unsigned int);
		void add_person(t_person);
		unsigned int getSmallestEdge(unsigned int);
		unsigned int getNextEdge(unsigned int, unsigned int);
};

#endif
