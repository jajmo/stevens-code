#include "myamgraph.hh"

/**
 * add_edge()
 * Adds an edge to the AM, from from to to with the weight weight
 *
 * Parameter from   - The index the edge will go from
 * Parameter to     - The index the edge will go to
 * Parameter weight - The weight of the edge
 * Return bool      - True if the edge was added successfully, false if not
 * Precondition     - None. Error checking is handled within the function
 * Postcondition    - The proper edge is added to the adjacency matrix with the correct weight
 */

template bool MyAmGraph<string>::add_edge(unsigned int, unsigned int, int);
template bool MyAmGraph<int>   ::add_edge(unsigned int, unsigned int, int);

template <class Elem>

bool MyAmGraph<Elem>::add_edge(unsigned int from, unsigned int to, int weight)
{
    if((from <= MyGraph<Elem>::v) && (to <= MyGraph<Elem>::v) && (from != to)) //Not complex, from != to
    {
        if(weight < 0)
        {
            weight = -1;

            if(get_edge(from, to) > -1)
                MyGraph<Elem>::e -= 2; //Subract 2 to compensate for adding 1 later on. The final result in this case needs to be e--
            else
                MyGraph<Elem>::e--;    //The weight is already -1, so subtract 1 to compensate for adding 1 later on. The final result needs to be e
        }

        if(MyGraph<Elem>::directed)
            am[from][to] = weight;
        else
        {
            if(from < to)
                am[from][to - from - 1] = weight; //swap(to, from)
            else
                am[to][from - to - 1]   = weight;
        }

        MyGraph<Elem>::e++; //Increment e no matter what, compensation for marking edges as -1 is done above
        return true;
    }

    return false;
}
