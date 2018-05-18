#include "myamgraph.hh"

/*
 * See comments within main() to explain what the tests do
 * If there are no comments, it is just a basic function call
 */
int main(int argc, char **argv)
{
    /** Undirected **/
    int i, j;

    cout << "----UNDIRECTED----" << endl;;

    MyAmGraph<string> *G = new MyAmGraph<string>(5, false);

    /* Vertices Test */
    //cout << G->vertex(5) << endl; //WILL CRASH PROGRAM. Gabarro said we don't have to worry about this

    G->add_vertex("A");
    G->add_vertex("B");
    G->add_vertex("C");
    G->add_vertex("D");
    G->add_vertex("E");
    G->add_vertex("F"); //Beyond cap, will not add

    cout << "Vertices: ";
    G->show_vertices(); //Will not print F
    cout << "------------------" << endl;

    G->show_am(); //Prints out the adjacency matrix from 0 to v
    cout << "------------------" << endl;

    /* Edges Test */
    G->add_edge(0, 1, 10);
    G->add_edge(0, 2, 15);
    G->add_edge(0, 3, 8);
    G->add_edge(1, 3, 20);
    G->add_edge(2, 2, 5);  //Self linking
    G->add_edge(2, 3, 10);
    G->add_edge(2, 4, 16);
    G->add_edge(2, 15, 6); //j is beyond v
    G->add_edge(2, 27, 8); //j is beyond cap
    G->add_edge(3, 2, 15); //i > j, function will swap. 15 will overwrite 10
    G->add_edge(3, 4, 8);
    G->add_edge(7, 7, 2);  //Self linking, greater than v & cap
    G->add_edge(12, 2, 8); //i is beyond cap
    G->add_edge(18, 3, 6); //i is beyond v;

    G->show_am();
    cout << "------------------" << endl;

    cout << "Edge weights: ";
    G->show_edges(); //Parses am[][] and prints out the weights
    cout << "------------------" << endl << "BFS: ";

    /* Search Tests */
    G->traverse(false);
    cout << "------------------" << endl << "DFS: ";

    G->traverse(true);
    cout << "------------------" << endl;

    /* Neighbors Test */
    for(i = 0; i < G->V(); i++)
    {
        cout << "Neighbors of " << i << ": ";

        for(j = G->firstNeighbor(i); j >= 0; j = G->nextNeighbor(i, j))
            cout << j << " ";

        cout << endl;
    }

    delete G;


    /** Directed **/

    cout << endl << "----DIRECTED----" << endl;

    G = new MyAmGraph<string>(5, true);

    /* Vertices Test */
    //cout << G->vertex(5) << endl; //WILL CRASH PROGRAM. Gabarro said we don't have to worry about this

    G->add_vertex("A");
    G->add_vertex("B");
    G->add_vertex("C");
    G->add_vertex("D");
    G->add_vertex("E");
    G->add_vertex("F"); //Beyond cap, will not add

    cout << "Vertices: ";
    G->show_vertices(); //Will not print F
    cout << "------------------" << endl;

    G->show_am(); //Prints out the adjacency matrix from 0 to v
    cout << "------------------" << endl;

    /* Edges Test */
    G->add_edge(0, 1, 10);
    G->add_edge(0, 2, 15);
    G->add_edge(0, 3, 8);
    G->add_edge(1, 3, 20);
    G->add_edge(1, 0, 4);
    G->add_edge(2, 0, 1);
    G->add_edge(2, 2, 5);  //Self linking
    G->add_edge(2, 3, 10);
    G->add_edge(2, 4, 16);
    G->add_edge(2, 15, 6); //j is beyond v
    G->add_edge(2, 27, 8); //j is eyond cap
    G->add_edge(3, 0, 4);
    G->add_edge(3, 1, 8);  //3 and 1 point to each other
    G->add_edge(3, 2, 15); //i > j, function will *not* swap for digraph
    G->add_edge(3, 4, 8);
    G->add_edge(4, 2, 5);
    G->add_edge(4, 3, 9);
    G->add_edge(7, 7, 2);  //Self linking, greater than v & cap
    G->add_edge(12, 2, 8); //i is beyond cap
    G->add_edge(18, 3, 6); //i is beyond v

    G->show_am();
    cout << "------------------" << endl;

    cout << "Edge weights: ";
    G->show_edges(); //Parses am[][] and prints out the weights
    cout << "------------------" << endl << "BFS: ";

    /* Search Tests */
    G->traverse(false);
    cout << "------------------" << endl << "DFS: ";

    G->traverse(true);
    cout << "------------------" << endl;

    /* Neighbors Test */
    for(i = 0; i < G->V(); i++)
    {
        cout << "Neighbors of " << i << ": ";

        for(j = G->firstNeighbor(i); j >= 0; j = G->nextNeighbor(i, j))
            cout << j << " ";

        cout << endl;
    }

    delete G;/**/
    return 0;
}
