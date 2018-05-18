#include "greet.h"

static const char *greeting = "Hello!";

void greet()
{
    printf("%s\n", greeting);
}

void hello(const char *friend, const char *greeting)
{
    printf("%s: %s\n", friend, greeting);
}

const char *getgreeting()
{
    return greeting;
}

int setgreeting(const char *new)
{
    if (new == NULL)
        return -1;

    greeting = new;
    return 0;
}