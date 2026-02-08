#include <criterion/criterion.h>

#include "glist/glist.h"

Test(glist_popback, one_element)
{
    glist_t *list = glist_new(sizeof(int));
    int val = 14352;
    glist_pushback(list, &val);
    gnode_t *node = glist_popback(list);
    cr_assert(node, "Node should not be NULL");
    cr_assert(node->data, "Data should not be NULL");
    int result = *(int *)node->data;
    cr_expect(result == val, "Expected: %d but got: %d", val, result);
    gnode_destroy(node);
    glist_destroy(list, NULL);
}

Test(glist_popback, entire_list)
{
    glist_t *list = glist_new(sizeof(int));
    int array[] = {45, 124, 546, 42, 78};
    size_t array_size = sizeof(array) / sizeof(*array);

    for (int i = 0; i < 5; i++) {
        glist_pushback(list, &array[i]);
    }
    int i = array_size - 1;
    while (glist_size(list)) {
        gnode_t *node = glist_popback(list);
        int result = *(int *)node->data;
        int ref = array[i--];
        cr_expect(result == ref, "Expected: %d but got: %d", ref, result);
    }
    glist_destroy(list, NULL);
}

Test(glist_popback, empty)
{
    glist_t *list = glist_new(sizeof(int));
    cr_assert(list, "List cannot be NULL");
    gnode_t *node = glist_popback(list);
    cr_assert(node == NULL, "Node should be NULL");
    glist_destroy(list, NULL);
}

Test(glist_popback, too_far)
{
    glist_t *list = glist_new(sizeof(int));
    int array[] = {45, 124, 546, 42, 78};

    for (int i = 0; i < 5; i++) {
        glist_pushback(list, &array[i]);
    }
    while (glist_size(list)) {
        cr_expect_(glist_popback(list) != NULL);
    }
    cr_expect_(glist_popback(list) == NULL);
    cr_expect_(glist_popback(list) == NULL);
    glist_destroy(list, NULL);
}
