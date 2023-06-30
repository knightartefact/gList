/*
** EPITECH PROJECT, 2023
** GenericC-DS
** File description:
** generic_list
*/

#include "generic_list.h"

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
    gnode_t *current = NULL;

    if (!list || list->size <= 0)
        return;
    current = list->head->next;
    while (current && current != list->tail) {
        print_function(current->data);
        current = current->next;
    }
}
