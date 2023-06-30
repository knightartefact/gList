/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** generic_list_mid
*/

#include <stdlib.h>
#include "generic_list.h"

void *glist_popmid(glist_t *list, gnode_t *node)
{
    void *data = node->data;

    if (list == NULL || list->size == 0)
        return NULL;
    if (node->prev == list->head)
        return glist_popfront(list);
    if (node->next == list->tail)
        return glist_popback(list);
    node->next->prev = node->prev;
    node->prev->next = node->next;
    list->size--;
    free(node);
    return data;
}
