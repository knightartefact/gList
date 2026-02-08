/*
** EPITECH PROJECT, 2023
** gList
** File description:
** generic_list
*/

#include "glist/glist.h"

#include <stdio.h>

size_t glist_size(glist_t *list)
{
    return list->size;
}

gnode_t *glist_back(glist_t *list)
{
    return list->size ? list->tail->prev : NULL;
}

gnode_t *glist_front(glist_t *list)
{
    return list->size ? list->head->next : NULL;
}

void glist_print(glist_t *list, void (*print_function)(const void *))
{
    if (!list || !print_function)
       return;
    gnode_t *current = glist_front(list);
    printf("[");
    while (current && current != list->tail) {
        print_function(current->data);
        if (current->next != list->tail) {
            printf(", ");
        }
        current = current->next;
    }
    printf("]\n");
}
