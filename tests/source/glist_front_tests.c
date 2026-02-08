#include <criterion/criterion.h>

#include "glist/glist.h"

Test(glist_front, null)
{
    glist_t *list = glist_new(sizeof(int));

    cr_expect(glist_front(list) == NULL);
    glist_destroy(list, NULL);
}

Test(glist_front, success)
{
    glist_t *list = glist_new(sizeof(int));
    gnode_t *front_node = NULL;
    int value = 76;
    int result = 0;

    glist_pushback(list, &value);
    front_node = glist_front(list);
    cr_assert(front_node != NULL, "Expected node to be not NULL.");
    cr_assert(front_node->data != NULL, "Expected data to be not NULL.");
    result = *(int *)front_node->data;
    cr_expect(result == value, "Expected value: %d, but got %d", value, result);
    glist_destroy(list, NULL);
}

