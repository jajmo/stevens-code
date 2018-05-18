#include "my.h"

int main()
{
    char str[] = "test";
    char* test;
    int res;

    /* my_str() tests */
    my_str("~~~ my_str() tests ~~~\n");
    my_str("-->");
    my_str("Test string"); //Prints "Test string"
    my_str("<--\n");
    my_str("-->");
    my_str(""); //Nothing is printed
    my_str("<--");
    my_str("\n-->");
    my_str(NULL); //Nothing is printed
    my_str("<--\n");

    /* my_int() tests */
    my_str("~~~ my_int() tests ~~~\n");
    my_int(0); //0 is printed
    my_char('\n');
    my_int(7); //7 is printed
    my_char('\n');
    my_int(123); //123 is printed
    my_char('\n');
    my_int(-456); //-456 is printed
    my_char('\n');
    my_int(100); //100 is printed
    my_char('\n');
    my_int(1003); //1001 is printed
    my_char('\n');
    my_int(-128); //-128 is printed
    my_char('\n');
    my_int(1 << (8 * sizeof(int) - 1)); //-2147483648 is printed
    my_char('\n');

    /* my_num_base() tests */
    my_str("~~~ my_num_base() tests ~~~\n");
    my_num_base(12, "0123456789"); //12 is printed
    my_char('\n');
    my_num_base(-7, "01"); //-111 is printed
    my_char('\n');
    my_num_base(12, NULL); //Error message: Base not valid
    my_char('\n');
    my_num_base(13, ""); //Error message: Base not valid
    my_char('\n');
    my_num_base(3, "$"); //$$$ is printed
    my_char('\n');
    my_num_base(0, "$"); //Nothing is printed
    my_char('\n');
    my_num_base(-4, "$"); //-$$$$ is printed
    my_char('\n');
    
    /* my_strlen() tests */
    my_str("~~~ my_strlen() tests ~~~\n");
    my_int(my_strlen(str)); //4 is printed
    my_char('\n');
    my_int(my_strlen(NULL)); //-1 is printed
    my_char('\n');
    my_int(my_strlen("")); //0 is printed
    my_char('\n');
    my_int(my_strlen("blah!")); //5 is printed
    my_char('\n');

    /* my_alpha() test */
    my_str("~~~ my_alpha() test ~~~\n");
    my_alpha(); //abcdefghijklmnopqrstuvwxyz is printed
    my_char('\n');

    /* my_digits() test */
    my_str("~~~ my_digits() test ~~~\n");
    my_digits(); //0123456789 is printed
    my_char('\n');

    /* my_revstr() tests */
    my_str("~~~ my_revstr() tests ~~~\n");
    my_int(my_revstr(str)); //4 is printed
    my_char('\n');
    my_str(str); //tset is printed
    my_char('\n');
    my_int(my_revstr(NULL)); //-1 is printed
    my_char('\n');
    my_int(my_revstr("")); //0 is printed
    my_char('\n');

    /* my_strpos() tests */
    my_str("~~~ my_strpos() tests ~~~\n");
    my_int(my_strpos("balloon", 'l')); //2 is printed
    my_char('\n');
    my_int(my_strpos("Balloon", 'z')); //-1 is printed
    my_char('\n');
    my_int(my_strpos(NULL, 5)); //-1 is printed
    my_char('\n');
    my_int(my_strpos("", '\0')); //-1 is printed
    my_char('\n');
    
    /* my_strrpos() tests */
    my_str("~~~ my_strrpos() tests ~~~\n");
    my_int(my_strrpos("balloon", 'l')); //3 is printed
    my_char('\n');
    my_int(my_strrpos("Balloon", 'z')); //-1 is printed
    my_char('\n');
    my_int(my_strrpos(NULL, 5)); //-1 is printed
    my_char('\n');
    my_int(my_strrpos("", '\0')); //-1 is printed
    my_char('\n');

    /*
     * Assignment 2
     */
    my_str("\n\n**** ASSIGNMENT 2 ****\n\n");

    /* my_strdup() tests */
    my_str("~~~ my_strdup() tests ~~~\n");
    test = my_strdup("Hello");
    my_str(test);//Hello is printed
    my_char('\n');
    free(test);
    test = my_strdup(NULL);
    my_str("-->");
    my_str(test);//Nothing is printed
    my_str("<--\n");
    //free(test);
    test = my_strdup("");
    my_str("-->");
    my_str(test); //"" is printed
    my_str("<--\n");
    free(test);

    /* my_strcmp() tests */
    my_str("~~~ my_strcmp() tests ~~~\n");
    my_int(my_strcmp("Hello", "Alpha")); //Prints a positive number
    my_char('\n');
    my_int(my_strcmp(NULL, NULL)); //0 is printed
    my_char('\n');
    my_int(my_strcmp(NULL, "")); //Prints a negative number
    my_char('\n');
    my_int(my_strcmp("", NULL)); //Prints a positive number
    my_char('\n');
    my_int(my_strcmp("Hello", NULL)); //Prints a positive number
    my_char('\n');
    my_int(my_strcmp("", "Hello")); //Prints a negative number
    my_char('\n');
    my_int(my_strcmp("Hello", "")); //Prints a positive number
    my_char('\n');
    my_int(my_strcmp("Hello", "Hello")); //0 is printed
    my_char('\n');
    my_int(my_strcmp("abc", "ab")); //Prints a positive number
    my_char('\n');

    /* my_strncmp() tests */
    my_str("~~~ my_strncmp() tests ~~~\n");
    my_int(my_strncmp("America", "Africa", 2)); //Prints a positive number
    my_char('\n');
    my_int(my_strncmp("Aardvark", "Aaz", 2)); //Prints 0
    my_char('\n');
    my_int(my_strncmp(NULL, "Hello", 4)); //Prints a negative number
    my_char('\n');
    my_int(my_strncmp("Hello", NULL, 4)); //Prints a negative number
    my_char('\n');
    my_int(my_strncmp(NULL, NULL, 4)); //Prints 0
    my_char('\n');
    my_int(my_strncmp("", "Hey", 4)); //Prints a negative number
    my_char('\n');
    my_int(my_strncmp("Hey", "", 4)); //Prints a positive number
    my_char('\n');
    my_int(my_strncmp("Aaab", "aaab", 4)); //Prints a negative number
    my_char('\n');
    my_int(my_strncmp("zzzz", "aaaa", 0)); //Prints 0
    my_char('\n');
    my_int(my_strncmp("Alpha", "Bravo", 50)); //Prints a positive number
    my_char('\n');

    /* my_strcpy() tests */
    my_str("~~~ my_strcpy() tests ~~~\n");
    test = my_strdup("$$$$$$$$$$$$$$$");
    my_str(my_strcpy(test, "Test")); //Test is printed
    my_char('\n');
    free(test);
    test = my_strdup("Test");
    my_str("-->");
    my_str(my_strcpy(test, "")); //Nothing is printed
    my_str("<--\n");
    my_str("-->");
    my_str(my_strcpy(test, NULL)); //Nothing is printed
    my_str("<--\n");
    free(test);
    my_str("-->");
    my_str(my_strcpy(NULL, "Hello")); //Nothing is printed
    my_str("<--\n");
    test = my_strdup("Hello");
    my_str(my_strcpy(test, "Tests")); //Tests is printed
    my_char('\n');
    free(test);

    /* my_strncpy() tests */
    my_str("~~~ my_strncpy() tests~~~\n");
    test = my_strdup("Hello");
    my_str(my_strncpy(test, "Bewchy", 3)); //Bew is printed
    my_char('\n');
    free(test);
    test = my_strdup("Blah");
    my_str(my_strncpy(test, "Poop", 100)); //Poop is printed
    my_char('\n');
    free(test);
    test = my_strdup("Jason");
    my_str("-->");
    my_str(my_strncpy(test, "", 5)); //Nothing is printed
    my_str("<--\n");
    free(test);
    test = my_strdup("Jason");
    my_str(my_strncpy(test, NULL, 100)); //Jason is printed
    my_char('\n');
    free(test);

    /* my_strconcat() tests */
    my_str("~~~ my_strconcat() tests ~~~\n");
    test = my_strconcat("Hello ", "World");
    my_str(test); //Hello World is printed
    my_char('\n');
    free(test);
    test = my_strconcat(NULL, "Hello");
    my_str(test); //Hello is printed
    my_char('\n');
    free(test);
    test = my_strconcat("Bewchy loves Java", NULL);
    my_str(test); //Bewchy loves Java is printed
    my_char('\n');
    free(test);
    test = my_strconcat("", "Test"); 
    my_str(test); //Test is printed
    my_char('\n');
    free(test);
    test = my_strconcat("World", "");
    my_str(test); //World is printed
    free(test);
    my_char('\n');

    /* my_strcat() tests */
    my_str("~~~ my_strcat() tests ~~~\n");
    test = (char*) xmalloc(20 * sizeof(char));
    my_strcpy(test, "Hello");
    my_str(my_strcat(test, " Jason")); //Hello Jason is printed
    my_char('\n');
    my_str(my_strcat(test, "")); //Hello Jason is printed
    my_char('\n');
    my_str(my_strcat(test, NULL)); //Hello Jason is printed
    my_char('\n');
    my_str("-->");
    my_str(my_strcat(NULL, "Test")); //Nothing is printed
    my_str("<--\n");
    my_str("-->");
    my_str(my_strcat(NULL, NULL)); //Nothing is printed
    my_str("<--\n");
    free(test);

    /* my_strnconcat() tests */
    my_str("~~~ my_strnconcat() tests ~~~\n");
    test = my_strnconcat("Hello ", "World", 3); 
    my_str(test); //Hello Wor is printed
    my_char('\n');
    free(test);
    test = my_strnconcat("Hello ", "World", 100);
    my_str(test); //Hello World is printed
    my_char('\n');
    free(test);
    test = my_strnconcat(NULL, "Test", 2); 
    my_str(test); //Te is printed
    my_char('\n');
    free(test);
    test = my_strnconcat("Jason", NULL, 3); 
    my_str(test); //Jason is printed
    my_char('\n');
    free(test);
    test = my_strnconcat("", "Linux", 1); 
    my_str(test); //L is printed
    my_char('\n');
    free(test);
    test = my_strnconcat("Nirvana", "", 5); 
    my_str(test); //Nirvana is printed
    my_char('\n');
    free(test);
    
    /* my_strfind() tests */
    my_str("~~~ my_strfind() tests ~~~\n");
    test = my_strfind("Hello", 'l');  
    my_str(test); //llo is printed
    my_char('\n');
    //free(test);
    test = my_strfind(NULL, 'x'); 
    my_str(test); //Nothing is printed
    my_char('\n');
    free(test);
    test = my_strfind("Test", 'z'); 
    my_str(test); //Nothing is printed
    my_char('\n');
    free(test);
    test = my_strfind("", 'x'); 
    my_str(test); //Nothing is printed
    my_char('\n');
    free(test);

    /* my_strrfind() tests */
    my_str("~~~ my_strrfind() tests ~~~\n");
    test = my_strrfind("Hello", 'l'); 
    my_str(test); //lo is printed
    my_char('\n');
    //free(test);
    test = my_strrfind(NULL, 'x'); 
    my_str(test); //Nothing is printed
    my_char('\n');
    test = my_strrfind("Test", 'z');
    my_str(test); //Nothing is printed
    my_char('\n');
    test = my_strrfind("", 'x');
    my_str(test); //Nothing is printed

    /* my_atoi() tests */
    my_str("~~~ my_atoi() tests~~~\n");
    res = my_atoi("10");
    if(res == 10)
        my_str("Regular test passed!\n");
    else
        my_str("Regular test FAILED!\n");

    res = my_atoi("-127");
    if(res == -127)
        my_str("Negative test passed!\n");
    else
        my_str("Negative test FAILED!\n");

    res = my_atoi("       15");
    if(res == 15)
        my_str("Leading spaces test passed!\n");
    else
        my_str("Leading spaces test FAILED!\n");

    res = my_atoi("  +++-+  -+   -25");
    if(res == -25)
        my_str("Spaces and signs test passed!\n");
    else
        my_str("Spaces and signs test FAILED!\n");

    res = my_atoi("18   ");
    if(res == 18)
        my_str("Trailing spaces test passed!\n");
    else
        my_str("Trailing spaces test FAILED!\n");

    res = my_atoi(NULL);
    if(res == 0)
        my_str("NULL test passed!\n");
    else
        my_str("NULL test FAILED!\n");

    res = my_atoi("");
    if(res == 0)
        my_str("Empty string test passed!\n");
    else
        my_str("Empty string test FAILED!\n");

    res = my_atoi("-5.12");
    if(res == -5)
        my_str("Decimal point test passed!\n");
    else
        my_str("Decimal point test FAILED!\n");

    res = my_atoi("121 is cool");
    if(res == 121)
        my_str("Trailing chars test passed!\n");
    else
        my_str("Trailing chars test FAILED!\n");

    res = my_atoi("is cool 107");
    if(res == 107)
        my_str("Leading chars test passed!\n");
    else
        my_str("Leading chars test FAILED!\n");
}
