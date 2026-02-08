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

    if (glist_size(list) == 0) {
        list->tail = new_node;
        list->head = new_node;
    } else {
        new_node->prev = list->tail;
        list->tail->next = new_node;
        list->tail = new_node;
    }
    list->size++;
    return 0;
}

gnode_t *glist_popback(glist_t *list)
{
    gnode_t *node = glist_back(list);

    if (!node) {
        return NULL;
    }
    if (list->size == 1) {
        list->head = NULL;
        list->tail = NULL;
    } else {
        list->tail = node->prev;
        list->tail->next = NULL;
    }
    list->size--;
    return node;
}

int glist_pushfront(glist_t *list, void *elem)
{
    gnode_t *new_node = gnode_create(list->chunk_size, elem);

    if (glist_size(list) == 0) {
        list->head = new_node;
        list->tail = new_node;
    } else {
        new_node->next = list->head;
        list->head->prev = new_node;
        list->head = new_node;
    }
    list->size++;
    return 0;
}

gnode_t *glist_popfront(glist_t *list)
{
    gnode_t *node = glist_front(list);

    if (!node) {
        return NULL;
    }
    if (list->size == 1) {
        list->head = NULL;
        list->tail = NULL;
    } else {
        list->head = node->next;
        list->head->prev = NULL;
    }
    list->size--;
    return node;
}
