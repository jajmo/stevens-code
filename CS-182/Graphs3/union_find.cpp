#include "mygraphs.hh"

template bool MyGraph<int>   ::myunion(int[], unsigned int, unsigned int);
template bool MyGraph<string>::myunion(int[], unsigned int, unsigned int);

template <class Elem>

/**
 * myunion()
 * Returns true or false
 */
bool MyGraph<Elem>::myunion(int parents[], unsigned int i, unsigned int j)
{
	i = this->myfind(parents, i);
	j = this->myfind(parents, j);

	if(i == j)
		return false;

	parents[j] = i;

	return true;
}

template unsigned int MyGraph<int>   ::myfind(int P[], unsigned int);
template unsigned int MyGraph<string>::myfind(int P[], unsigned int);

template <class Elem>

/*
 * myfind()
 * Returns an unsigned int
 */
unsigned int MyGraph<Elem>::myfind(int P[], unsigned int i)
{
	while(P[i] != i)
		i = P[i];

	return i;
}