/*
** EPITECH PROJECT, 2023
** gencds
** File description:
** generic_list_actions
*/

#include "glist/glist.h"

#include <stdlib.h>

int glist_pushback(glist_t *list, void *elem)
{
    gnode_t *new_node = gnode_create(list->chunk_size, elem);

    new_node->next = list->tail;
    new_node->prev = list->tail->prev;
    list->tail->prev->next = new_node;
    list->tail->prev = new_node;
    list->size++;
    return 0;
}

gnode_t *glist_popback(glist_t *list)
{
    gnode_t *last_node = glist_back(list);

    if (!last_node) {
        return NULL;
    }
    if (list->size == 1) {
        list->head->next = list->tail;
        list->tail->prev = list->head;
    } else {
        last_node->prev->next = list->tail;
        list->tail->prev = last_node->prev;
    }
    list->size--;
    return last_node;
}

int glist_pushfront(glist_t *list, void *elem)
{
    gnode_t *new_node = gnode_create(list->chunk_size, elem);

    new_node->prev = list->head;
    new_node->next = list->head->next;
    list->head->next->prev = new_node;
    list->head->next = new_node;
    list->size++;
    return 0;
}

gnode_t *glist_popfront(glist_t *list)
{
    gnode_t *first_node = glist_front(list);

    if (!first_node) {
        return NULL;
    }
    if (list->size == 1) {
        list->head->next = list->tail;
        list->tail->prev = list->head;
    } else {
        first_node->next->prev = list->head;
        list->head->next = first_node->next;
    }
    list->size--;
    return first_node;
}
