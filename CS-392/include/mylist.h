/*
 * mylist.h library
 *
 * Full linked list implementation using pointers
 *
 * Last Modified: 9/22/14 11:08 PM
 */
#ifndef _MYLIST_H_
#define _MYLIST_H_

#include "my.h"

typedef struct     s_node
{
    void*          elem;
    struct s_node* next;
}                  t_node;

t_node*      new_node(void*, t_node*); //Allocate a new node and return a pointer to the node
void         add_node(t_node*, t_node**); //Add the node to the beginning of the list
void         add_elem(void*, t_node**); //Create a new node and add it to the list
void         append(t_node*, t_node**); //Add a node to the end of the list
void         add_node_at(t_node*, t_node**, unsigned int); //Add a node in a specific position
void*        remove_node(t_node**); //Remove the first node and return the data
void*        remove_node_at(t_node**, unsigned int); //Remove a node from a certain position and return the data
void*        remove_last(t_node**); //Remove the last node and return the data
unsigned int count_nodes(t_node*); //Count the nodes in the list, and return the count
void         empty_list(t_node**); //Empty the list
t_node*      node_at(t_node*, unsigned int); //Returns a pointer to a node at a specified position
void*        elem_at(t_node*, unsigned int); //Returns a pointer to an elem at a specified position
void         traverse_int(t_node*); //Prints the list, with elem evaluated as an int
void         traverse_char(t_node*); //Prints the list, with elem evaluated as a char
void         traverse_string(t_node*); //Prints the list, with elem evaluated as a char*

#endif
