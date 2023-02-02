/*
** EPITECH PROJECT, 2023
** GenericC-DS
** File description:
** generic_list
*/

#include "generic_list.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

GNode_t *create_node(size_t chunk_size, void *data)
{
    GNode_t *node = malloc(sizeof(GNode_t));

    if (!node) {
        printf("Couldn't allocate memory for new node\n");
        return NULL;
    }
    if (!data) {
        node->data = NULL;
        return node;
    }
    node->data = malloc(chunk_size);
    memmove(node->data, data, chunk_size);
    node->next = NULL;
    node->prev = NULL;
    return node;
}

GList_t* glist_new(size_t chunk_size)
{
    GNode_t* head = create_node(chunk_size, NULL);
    GNode_t* tail = create_node(chunk_size, NULL);
    GList_t* list = malloc(sizeof(GList_t));

    if (!list) {
        free(head);
        free(tail);
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

size_t glist_size(GList_t *list)
{
    return list->size;
}

int glist_pushback(GList_t *list, void *elem)
{
    GNode_t *new_node = create_node(list->chunk_size, elem);

    new_node->prev = list->tail->prev;
    list->tail->prev->next = new_node;
    list->tail->prev = new_node;
    list->size++;
    return 0;
}

void *glist_popback(GList_t *list)
{
    void *data = NULL;
    GNode_t *last_node = NULL;

    if (!list->size) {
        return NULL;
    }
    if (list->size == 1) {
        last_node = list->tail->prev;
        data = last_node->data;
        list->head->next = list->tail;
        list->tail->prev = list->head;
        list->size--;
        return data;
    }
    last_node = list->tail->prev;
    data = last_node->data;
    last_node->prev->next = list->tail;
    list->tail->prev = last_node->prev;
    list->size--;
    return data;
}

void *glist_back(GList_t *list)
{
    return list->tail->prev->data;
}

void *glist_front(GList_t *list)
{
    return list->head->next->data;
}

void *glist_popfront(GList_t *list)
{
    void *data = NULL;
    GNode_t *first_node = NULL;

    if (!list->size) {
        return NULL;
    }
    if (list->size == 1) {
        first_node = list->head->next;
        data = first_node->data;
        list->head->next = list->tail;
        list->tail->prev = list->head;
        list->size--;
        return data;
    }
    first_node = list->head->next;
    data = first_node->data;
    first_node->next->prev = list->head;
    list->head->next = first_node->next;
    list->size--;
    return data;
}