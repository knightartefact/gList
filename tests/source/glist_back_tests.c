#include <criterion/criterion.h>

#include "glist/glist.h"

Test(glist_back, null)
{
    glist_t *list = glist_new(sizeof(int));

    cr_expect(glist_back(list) == NULL);
    glist_destroy(list, NULL);
}

Test(glist_back, success)
{
    glist_t *list = glist_new(sizeof(int));
    gnode_t *back_node = NULL;
    int value = 76;
    int result = 0;

    glist_pushback(list, &value);
    back_node = glist_back(list);
    cr_assert(back_node != NULL, "Expected node to be not NULL.");
    cr_assert(back_node->data != NULL, "Expected data to be not NULL.");
    result = *(int *)back_node->data;
    cr_expect(result == value, "Expected value: %d, but got %d", value, result);
    glist_destroy(list, NULL);
}
