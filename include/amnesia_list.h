#ifndef AMNESIA_LIST_H
#define AMNESIA_LIST_H

#include <stdbool.h>

typedef struct _list_node amnesia_list_node;
typedef struct _list amnesia_list;

struct _list_node {
    amnesia_list_node *next;
    void *data;
} _list_node;

struct _list {
    amnesia_list_node *head;
} _list;

extern amnesia_list *amnesia_list_new(void);
extern amnesia_list_node *amnesia_list_new_node(void *data);
extern bool amnesia_list_add(amnesia_list *list, amnesia_list_node *n);
extern bool amnesia_list_delete(amnesia_list *list, amnesia_list_node *n);
extern bool amnesia_list_delete_by_value(amnesia_list *list, void *data);
extern void amnesia_list_free(amnesia_list *list);

#endif /* AMNESIA_LIST_H */
