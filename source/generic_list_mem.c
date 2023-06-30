/*
** EPITECH PROJECT, 2023
** gencds
** File description:
** generic_list_mem
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "generic_list.h"

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
        return NULL;
    }
    memmove(node->data, data, chunk_size);
    node->next = NULL;
    node->prev = NULL;
    return node;
}

void gnode_destroy(gnode_t **node)
{
    free((*node)->data);
    free(*node);
}

glist_t* glist_new(size_t chunk_size)
{
    gnode_t* head = gnode_create(chunk_size, NULL);
    gnode_t* tail = gnode_create(chunk_size, NULL);
    glist_t* list = malloc(sizeof(glist_t));

    if (!list || !head || !tail) {
        perror("Failed creating list");
        gnode_destroy(&head);
        gnode_destroy(&tail);
        return NULL;
    }
    head->next = tail;
    tail->prev = head;
    list->head = head;
    list->tail = tail;
    list->size = 0;
    list->chunk_size = chunk_size;
    return list;
}

void glist_destroy(glist_t **list, void(*dtor)(void *))
{
    void *current_data = NULL;

    if (!(*list))
        return;
    while ((*list)->size) {
        current_data = glist_popback(*list);
        if (dtor)
            dtor(current_data);
        free(current_data);
    }
    free((*list)->head);
    free((*list)->tail);
    free(*list);
}
