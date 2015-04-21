#include <stdlib.h>
#include <stdio.h>

#include "amnesia_list.h"

amnesia_list *amnesia_list_new(void)
{
  amnesia_list *list = (amnesia_list *) malloc(sizeof(amnesia_list));
  list->head = NULL;

  return list;
}

amnesia_list_node *amnesia_list_new_node(void *data)
{
  amnesia_list_node *node;
  node = (amnesia_list_node *) malloc(sizeof(amnesia_list_node));

  node->next = NULL;
  node->data = data;

  return node;
}

bool amnesia_list_add(amnesia_list *list, amnesia_list_node *n)
{
  if(list == NULL || n == NULL) {
    return false;
  }

  if(list->head == NULL) {
    list->head = n;

    return true;
  } else {
    amnesia_list_node *a = list->head;

    while(a->next != NULL) {
      a = a->next;
    }

    a->next = n;
    return true;
  }
}

bool amnesia_list_delete(amnesia_list *list, amnesia_list_node *n)
{
  amnesia_list_node *a = list->head;

  while(a->next != NULL) {
    if(a->next != n) {
      a = a->next;
    } else {
      if(a->next->next != NULL) {
        /* Delete and save its children */
        amnesia_list_node *child = a->next->next;

        free(a->next);
        a->next = child;

        return true;
      } else {
        /* It has no children, just free() it. */
        free(a->next);

        return true;
      }
    }
  }

  return false;
}

bool amnesia_list_delete_by_value(amnesia_list *list, void *data)
{
  amnesia_list_node *a, *b, *next;

  /* Start at the list head */
  a = list->head;

  while(a->next != NULL) {
    if(a->data == data) {
      /*
       * If it has children, save them (think of the children).
       *
       * Example: A->B->C->D->E, delete C,
       * Output: A->B->D->E
       */
      if(a->next->next != NULL) {
        amnesia_list_node *child = a->next->next;

        next = child;
      } else {
        next = NULL;
      }

      a->next = next;
      return true;
    }
  }

  return false;
}

void amnesia_list_free(amnesia_list *list)
{
  if(list == NULL)
    return;

  amnesia_list_node *a, *b;

  a = list->head;

  while(a != NULL)
  {
    b = a->next;

    free(a->data);
    free(a);

    a = b;
  }

  free(list);
}
