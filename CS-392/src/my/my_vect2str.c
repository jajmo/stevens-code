#include "my.h"

/*
 * my_vec2str()
 *
 * Convert a vector to a string
 *
 * Precondition: vec is a valid vector, with more than 0 elements
 * Postcondition: A string with all of vec elements is returned
 *
 * @param vec - A vector
 * @return char* - A new string containing the vector elements
 */
char*            my_vect2str(char** vec)
{
    unsigned int strlen;
    char*        str;
    char**       loc;

    if(*vec != NULL)
    {
        loc = vec;
        for(strlen = 0; *vec; strlen += (my_strlen(*vec) + 1), vec++) 
            ;
        strlen--;
        str = (char*) xmalloc(strlen * sizeof(char));
        for(vec = loc; *vec; vec++)
        {
            my_strcat(str, *vec);
            my_strcat(str, " ");
        }
        str[strlen] = '\0';
    }
    else
    {
        str = my_strdup(""); 
    }

    return str;
}
