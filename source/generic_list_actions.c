/*
** EPITECH PROJECT, 2023
** gencds
** File description:
** generic_list_actions
*/

#include <stdlib.h>
#include "generic_list.h"

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

void *glist_popback(glist_t *list)
{
    gnode_t *last_node = list->tail->prev;
    void *data = last_node->data;;

    if (!list->size)
        return NULL;
    if (list->size == 1) {
        list->head->next = list->tail;
        list->tail->prev = list->head;
    } else {
        last_node->prev->next = list->tail;
        list->tail->prev = last_node->prev;
    }
    list->size--;
    free(last_node);
    return data;
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

void *glist_popfront(glist_t *list)
{
    gnode_t *first_node = list->head->next;
    void *data = first_node->data;

    if (!list->size)
        return NULL;
    if (list->size == 1) {
        list->head->next = list->tail;
        list->tail->prev = list->head;
    } else {
        first_node->next->prev = list->head;
        list->head->next = first_node->next;
    }
    list->size--;
    free(first_node);
    return data;
}
