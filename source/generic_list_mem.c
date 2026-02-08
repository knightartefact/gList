/*
** EPITECH PROJECT, 2023
** gencds
** File description:
** generic_list_mem
*/

#include "glist/glist.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

gnode_t *gnode_create(size_t chunk_size, void *data)
{
    gnode_t *node = malloc(sizeof(gnode_t));

    if (!node) {
        perror("Couldn't allocate memory for new node");
        return NULL;
    }
    if (!data) {
        node->data = NULL;
        return node;
    }
    node->data = malloc(chunk_size);
    if (!node->data) {
        perror("Error allocating node data");
        free(node);
        return NULL;
    }
    memmove(node->data, data, chunk_size);
    node->next = NULL;
    node->prev = NULL;
    return node;
}

void gnode_destroy(gnode_t *node)
{
    free(node->data);
    free(node);
}

glist_t* glist_new(size_t chunk_size)
{
    glist_t* list = malloc(sizeof(glist_t));

    if (!list) {
        perror("Failed creating list");
        return NULL;
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    list->chunk_size = chunk_size;
    return list;
}

void glist_destroy(glist_t *list, void(*dtor)(void *))
{
    if (!list)
        return;
    while (glist_size(list)) {
        gnode_t *node = glist_popback(list);
        if (dtor)
            dtor(node->data);
        gnode_destroy(node);
    }
    free(list);
}
