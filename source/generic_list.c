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
#include <stdbool.h>

GNode_t *gnode_create(size_t chunk_size, void *data)
{
    GNode_t *node = malloc(sizeof(GNode_t));

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

void gnode_destroy(GNode_t **node)
{
    free((*node)->data);
    free(*node);
}

GList_t* glist_new(size_t chunk_size)
{
    GNode_t* head = gnode_create(chunk_size, NULL);
    GNode_t* tail = gnode_create(chunk_size, NULL);
    GList_t* list = malloc(sizeof(GList_t));

    if (!list) {
        perror("Failed creating list");
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

void glist_destroy(GList_t **list, void(*dtor)(void *))
{
    void *current_data = NULL;

    if (!(*list))
        return;
    while ((*list)->size) {
        current_data = glist_popback(*list);
        dtor(current_data);
        free(current_data);
    }
    free((*list)->head);
    free((*list)->tail);
    free(*list);
}

size_t glist_size(GList_t *list)
{
    return list->size;
}

int glist_pushback(GList_t *list, void *elem)
{
    GNode_t *new_node = gnode_create(list->chunk_size, elem);

    new_node->prev = list->tail->prev;
    list->tail->prev->next = new_node;
    list->tail->prev = new_node;
    list->size++;
    return 0;
}

void *glist_popback(GList_t *list)
{
    GNode_t *last_node = list->tail->prev;
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
    GNode_t *first_node = list->head->next;
    void *data = first_node->data;;

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

void glist_print(GList_t *list, void (*print_function)(const void *))
{
    GNode_t *current = NULL;

    if (!list)
        return;
    current = list->head->next;
    while (current && current != list->tail) {
        print_function(current->data);
        current = current->next;
    }
}

static void _glist_swap_data(GNode_t *lhs, GNode_t *rhs)
{
    void *temp_data = lhs->data;

    lhs->data = rhs->data;
    rhs->data = temp_data;
}

static bool _glist_sort_pass(GList_t *list, int(*comparator)(const void *lhs, const void *rhs))
{
    bool swapped = false;
    GNode_t* current = list->head->next;

    while (current && current->next && current->next != list->tail) {
        if (comparator(current->data, current->next->data) > 0) {
            _glist_swap_data(current, current->next);
            swapped = true;
        }
        current = current->next;
    }
    return swapped;
}

int glist_sort(GList_t *list, int(*comparator)(const void *, const void *))
{
    while (_glist_sort_pass(list, comparator));
    return 0;
}