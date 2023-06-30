/*
** EPITECH PROJECT, 2023
** GenericC-DS
** File description:
** generic_list_sort
*/

#include <stdbool.h>
#include "generic_list.h"

static void _glist_swap_data(gnode_t *lhs, gnode_t *rhs)
{
    void *temp_data = lhs->data;

    lhs->data = rhs->data;
    rhs->data = temp_data;
}

static bool _glist_sort_pass(glist_t *list, int(*comparator)(const void *lhs, const void *rhs))
{
    bool swapped = false;
    gnode_t* current = list->head->next;

    while (current && current->next && current->next != list->tail) {
        if (comparator(current->data, current->next->data) > 0) {
            _glist_swap_data(current, current->next);
            swapped = true;
        }
        current = current->next;
    }
    return swapped;
}

int glist_sort(glist_t *list, int(*comparator)(const void *, const void *))
{
    while (_glist_sort_pass(list, comparator));
    return 0;
}
