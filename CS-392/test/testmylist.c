#include "mylist.h"

/*
 * GRADER NOTE:
 * This had to be heavily modified from my original test main to make it work
 * correctly
 */
int main()
{
    t_node* head = (t_node*) xmalloc(sizeof(t_node));
    t_node* node = (t_node*) xmalloc(sizeof(t_node));
    t_node* node1 = new_node("Data", NULL);
    t_node* node2 = new_node("TestPos1", NULL);
    t_node* node3 = new_node("MoreData", NULL);
    char* data = "Some test data";
    char* g = "Hello";
    char* h = "Professor";
    char* i = "Gabarro";
    char d, e, f;
    int a, b, c;

    /* new_node() tests */
    if((node = new_node(data, NULL)) != NULL)
        my_str("new_node NULL test passed!\n");
    else
        my_str("new_node NULL test FAILED!\n");

    if((node = new_node(NULL, NULL)) == NULL)
        my_str("new_node NULL, NULL test passed!\n");
    else
        my_str("new_node NULL, NULL test FAILED!\n");

    if((node = new_node(NULL, node)) == NULL)
        my_str("new_node NULL data test passed!\n");
    else
        my_str("new_node NULL data test FAILED!\n");
    free(node);

    if((node = new_node(data, node)) != NULL)
        my_str("new_node normal test passed!\n");
    else
        my_str("new_node normal test FAILED!\n");

    /* add_node() tests */
    add_node(NULL, &head);
    if(head->next == NULL)
        my_str("add_node NULL node test passed!\n");
    else
        my_str("add_node NULL node test FAILED!\n");

    add_node(node, NULL);
    if(head->next == NULL)
        my_str("add_node NULL head test passed!\n");
    else
        my_str("add_node NULL head test FAILED!\n");

    add_node(NULL, NULL);
    if(head->next == NULL)
        my_str("add_node NULL, NULL test passed!\n");
    else
        my_str("add_node NULL, NULL test FAILED!\n");

    add_node(node, &head);
    if(head->elem == data)
        my_str("add_node normal test passed!\n");
    else
        my_str("add_node normal test FAILED!\n");

    /* add_elem() tests */
    add_elem(data, NULL);
    if(head->next != NULL)
        my_str("add_elem NULL head test passed!\n");
    else
        my_str("add_elem NULL head test FAILED!\n");

    add_elem(NULL, NULL);
    if(head->next != NULL)
        my_str("add_elem NULL, NULL test passed!\n");
    else
        my_str("add_elem NULL, NULL test FAILED!\n");

    add_elem(data, &head);
    if(head->next->elem == data)
        my_str("add_elem normal test passed!\n");
    else
        my_str("add_elem normal test FAILED!\n");

    empty_list(&head);

    /* append() tests */
    data = "Some more test data";
    free(node);
    //node = new_node(data, NULL);
    node = (t_node*) xmalloc(sizeof(t_node));
    node->elem = data;
    node->next = NULL;

    append(NULL, &head);
    if(head == NULL)
        my_str("append NULL node test passed!\n");
    else
        my_str("append NULL node test FAILED!\n");

    append(node, NULL);
    if(head == NULL)
        my_str("append NULL head test passed!\n");
    else
        my_str("append NULL head test FAILED!\n");

    append(NULL, NULL);
    if(head == NULL)
        my_str("append NULL, NULL test passed!\n");
    else
        my_str("append NULL, NULL test FAILED!\n");

    add_elem("Test", &head);
    append(node, &head);
    if(head != NULL && head->next->elem == data)
        my_str("append normal test passed!\n");
    else
        my_str("append normal test FAILED!\n");

    /* empty_list() tests */
    empty_list(NULL);
    if(head->next != NULL)
        my_str("empty_list NULL test passed!\n");
    else
        my_str("empty_list NULL test FAILED!\n");

    empty_list(&head);
    if(head == NULL)
        my_str("empty_list normal test passed!\n");
    else
        my_str("empty_list normal test FAILED!\n");

    empty_list(&head);
    if(head == NULL)
        my_str("empty_list empty list test passed!\n");
    else
        my_str("empty_list empty list test FAILED!\n");

    add_elem("Data", &head);
    add_elem("More data", &head);

    /* remove_node() tests */
    if(remove_node(NULL) == NULL)
        my_str("remove_node NULL test passed!\n");
    else
        my_str("remove_node NULL test FAILED!\n");

    if(remove_node(&head) == "More data")
        my_str("remove_node normal test passed!\n");
    else
        my_str("remove_node normal test FAILED!\n");

    empty_list(&head);
    if(remove_node(&head) == NULL && head == NULL)
        my_str("remove_node empty list test passed!\n");
    else
        my_str("remove_node empty list test FAILED!\n");

    /* add_node_at() tests */
    empty_list(&head);
    node = new_node("Test", NULL);

    add_node_at(node, &head, 0);
    if(head->elem == "Test")
        my_str("add_node_at empty list pos 0 test passed!\n");
    else
        my_str("add_node_at empty list pos 0 test FAILED!\n");

    add_node_at(node1, &head, 100);
    if(head->next != NULL && head->next->elem == "Data" && head->next->next == NULL)
        my_str("add_node_at num > length(list) test passed!\n");
    else
        my_str("add_node_at num > length(list) test FAILED!\n");

    add_node_at(node2, &head, 1);
    if(head->next != NULL && head->next->elem == "TestPos1")
        my_str("add_node_at 0 < num < length(list) test passed!\n");
    else
        my_str("add_node_at 0 < num < length(list) test FAILED!\n");
    
    add_node_at(NULL, &head, 0);
    if(head->next->next->next == NULL)
        my_str("add_node_at NULL node test passed!\n");
    else
        my_str("add_node_at NULL node test FAILED!\n");

    add_node_at(node3, NULL, 0);
    if(head->next->elem == "TestPos1")
        my_str("add_node_at NULL head test passed!\n");
    else
        my_str("add_node_at NULL head test FAILED!\n");
    
    /* remove_node_at() tests */
    if(remove_node_at(&head, 0) == "Test")
        my_str("remove_node_at head test passed!\n");
    else
        my_str("remove_node_at head test FAILED!\n");

    if(remove_node_at(NULL, 100) == NULL)
        my_str("remove_node_at NULL test passed!\n");
    else
        my_str("remove_node_at NULL test FAILED!\n");

    if(remove_node_at(&head, 1) == "Data")
        my_str("remove_node_at 0 < pos < length(list) test passed!\n");
    else
        my_str("remove_node_at 0 < pos < length(list) test FAILED!\n");

    if(remove_node_at(&head, 100) == "Data")
        my_str("remove_node_at pos > length(list) test passed!\n");
    else
        my_str("remove_node_at pos > length(list) test FAILED!\n");

    empty_list(&head);
    
    //Fill list one last time
    add_elem("Hello", &head);
    add_elem("I Love Java", &head);
    add_elem("POINTERS ARE FUN!", &head);

    /* remove_last() tests */
    if(remove_last(&head) == "Hello")
        my_str("remove_last normal test passed!\n");
    else
        my_str("remove_last normal test FAILED!\n");

    if(remove_last(NULL) == NULL)
        my_str("remove_last NULL test passed!\n");
    else
        my_str("remove_last NULL test FAILED!\n");

    /* node_at() tests */
    if(node_at(NULL, 1) == NULL)
        my_str("node_at NULL test passed!\n");
    else
        my_str("node_at NULL test FAILED!\n");

    if(node_at(head, 100)->elem == "I Love Java")
        my_str("node_at num > length(list) test passed!\n");
    else
        my_str("node_at num > length(list) test FAILED!\n");

    if(node_at(head, 0)->elem == "POINTERS ARE FUN!")
        my_str("node_at head test passed!\n");
    else
        my_str(node_at(head, 0)->elem);

    if(node_at(head, 1)->elem == "I Love Java")
        my_str("node_at normal test passed!\n");
    else
        my_str("node_at normal test FAILED!\n");

    /* elem_at() tests */
    if(elem_at(NULL, 1) == NULL)
        my_str("elem_at NULL test passed!\n");
    else
        my_str("elem_at NULL test FAILED!\n");

    if(elem_at(head, 100) == "I Love Java")
        my_str("elem_at num > length(list) test passed!\n");
    else
        my_str("elem_at num > length(list) test FAILED!\n");

    if(elem_at(head, 0) == "POINTERS ARE FUN!")
        my_str("elem_at head test passed!\n");
    else
        my_str("elem_at head test FAILED!\n");

    if(elem_at(head, 1) == "I Love Java")
        my_str("elem_at normal test passed!\n");
    else
        my_str("elem_at normal test FAILED!\n");

    /* count_nodes() test */
    if(count_nodes(head) == 2)
        my_str("count_nodes normal test passed!\n");
    else
        my_str("count_nodes normal test FAILED!\n");

    if(count_nodes(NULL) == 0)
        my_str("count_nodes NULL test passed!\n");
    else
        my_str("count_nodes NULL test FAILED!\n");

    empty_list(&head);

    if(count_nodes(head) == 0)
        my_str("count_nodes empty list test passed!\n");
    else
        my_str("count_nodes empty list test FAILED!\n");

    /* traverse_int() tests */
    a = 4;
    b = 8;
    c = 10;
    add_elem(&a, &head);
    add_elem(&b, &head);
    add_elem(&c, &head);
    traverse_int(NULL); //Nothing is printed
    traverse_int(head); //10 8 4 is printed
    
    /* traverse_char() tests */
    d = 'f';
    e = 'a';
    f = 'r';
    empty_list(&head);
    add_elem(&d, &head);
    add_elem(&e, &head);
    add_elem(&f, &head);
    traverse_char(NULL); //Nothing is printed
    traverse_char(head); //r a f is printed

    /* traverse_string() tests */
    empty_list(&head);
    add_elem(g, &head);
    add_elem(h, &head);
    add_elem(i, &head);
    traverse_string(NULL); //Nothing is printed
    traverse_string(head); //Gabarro Professor Hello is printed

    empty_list(&head);
    free(node);
    free(node1);
    free(node2);
    free(node3);
    free(head);

    return 0;
}
