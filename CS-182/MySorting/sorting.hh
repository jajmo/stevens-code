#ifndef _SORTING_H_
#define _SORTING_H_

#include <iostream>
#include <cstring>
using namespace std;

template <class Elem, class Comp>

class Sortings
{
 public:
  static void merge(Elem *arr, unsigned int n);
  static void select(Elem *arr, unsigned int n);
  static void shell(Elem *arr, unsigned int n);
private:
  static const unsigned int THRESHOLD = 3; // used by shell
  static void insert2(Elem *arr, unsigned int incr, unsigned int n, unsigned int s);
  static void swap(Elem *arr, unsigned int, unsigned int);
  static void mergeRecurse(Elem *arr, Elem tmp[], unsigned int l, unsigned int r);
};

class intuival
{
public:
  static unsigned int uintVal(int);
};

class intintCompare
{
 public:
  static bool lt(int, int);
  static bool gt(int, int);
  static bool eq(int, int);
};

class strstrCompare
{
 public:
  static bool lt(char*, char*);
  static bool gt(char*, char*);
  static bool eq(char*, char*);  
};

#endif
