#include "heist_map.hh"

/**
 * dfs(unsigned int idx)
 * Author: Jason Ajmo (jajmo)
 *
 * Prints out all of the locations using a depth first search
 *
 * Parameter index - The index at which the dfs starts
 *
 * Precondition:
 *      idx < v
 *
 * Postcondition:
 *      The locations are printed out
 */
void HeistMap::dfs(unsigned int idx)
{
    int        n;
    t_location curr;
    visited[idx] = true;

    curr = get_location(idx)[0];
    cout << curr.name     << " has ";
    cout << curr.itemName << " worth $";
    cout << curr.itemVal  << "K" << endl;

    for(n = firstNeighbor(idx); n >= 0; n = nextNeighbor(idx, n))
       if(!visited[n])
           dfs(n);
}   

/**
 * canSend(unsigned int source, unsigned int target, unsigned int stealth)
 * Author: Jason Ajmo (jajmo)
 *
 * Checks to see if a person with visibility stealth can make it safely from
 * source to target
 *
 * Paremeter source  - the starting location index
 * Parameter target  - the ending location index
 * Parameter stealth - the visiblity of the person to send
 * Return bool       - whether the person is able to make it safely to target or not
 *
 * Precondition:
 *      source < v
 *      target < v
 *      source != target
 *
 * Postcondition:
 *      A bool is returned indicating if the person is able to make it
 */
bool HeistMap::canSend(unsigned int source, unsigned int target, unsigned int stealth)
{
    unsigned int w;

    if(source == target)
        return true;

    visited[source] = true;

    for(w = getSmallestEdge(source); w < v; w = getNextEdge(source, w))
    {
        if(!visited[w] && w != INVALID)
        {
            visited[w] = true;

            if(canSend(w, target, stealth) && get_visibility(source, w) >= stealth)
            {
                add_visibility(source, w, get_visibility(source, w) - stealth);
                return true;
            }
        }
    }

    return false;
}

/**
 * getSmallestEdge(unsigned int idx)
 * Author: Jason Ajmo (jajmo)
 *
 * Returns a neighbor of idx that has the smallest edge
 *
 * Parameter idx       - the index of the vertex to get the smallest edge of
 * Return unsigned int - the index of the neighbor of idx with the smallset edge
 *
 * Precondition:
 *      idx < v
 *
 * Postcondition:
 *      The index of the first neighbor of idx with the smallest edge is returned
 */
unsigned int HeistMap::getSmallestEdge(unsigned int idx)
{
    return getNextEdge(idx, -1);
}

/**
 * getNextEdge(unsigned int first, unsigned int second)
 * Author: Jason Ajmo (jajmo)
 *
 * Returns the next neighbor of first after second with the smallest edge
 *
 * Parameter first     - the index of the location to get the next neighbor of
 * Parameter second    - the index of previous neighbor of first
 * Return unsigned int - the index of the next neighbor of first after second with the smallest edge
 *
 * Precondition:
 *      first < v
 *      second < v
 *      first != second
 *
 * Postcondition:
 *      The index of the next neighbor of first after second with the smallest edge is returned
 */
unsigned int HeistMap::getNextEdge(unsigned int first, unsigned int second)
{
    unsigned int min, i;

    if(nextNeighbor(first, second) != INVALID && first != second)
        min = nextNeighbor(first, second);
    else
        return INVALID;

    for(i = ++second; i < v; i++)
        if(first != i && get_visibility(first, i) < get_visibility(first, min) && get_visibility(first, i) != 0 && get_visibility(first, i) != INVALID)
            min = i;

    return min;
}