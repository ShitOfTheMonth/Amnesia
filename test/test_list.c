#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "amnesia_list.h"

int main(int argc, char **argv)
{
    int i;
    int *z;
    amnesia_list *list;
    amnesia_list_node *n;

    (void)argc;
    (void)argv;

    list = amnesia_list_new();
    for (i = 0; i < 10; i++)
    {
        z = malloc(sizeof(int));
        memcpy(z, &i, sizeof(int));
        amnesia_list_add(list, amnesia_list_new_node(z));
    }

    n = list->head;
    while (n != NULL)
    {
        printf("%d\n", *(int*)n->data);
        n = n->next;
    }
    /*while (n != NULL && n = n->next);*/
    /*while (n =  n->next && n != NULL);*/

}
