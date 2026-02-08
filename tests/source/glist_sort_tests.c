#include <criterion/criterion.h>

#include "glist/glist.h"

// NOTE: Implement test where a destructor is used e.g:
//       - A list of structures containing shared memory.

static int _int_comparator(const void *lhs, const void *rhs)
{
    int int_lhs = *(int *)(lhs);
    int int_rhs = *(int *)rhs;
    return (int_lhs - int_rhs);
}

Test(glist_sort, integer_list)
{
    glist_t *list = glist_new(sizeof(int));
    int array[] = {45,54,8,6,75,2,7446,42,75,24,54,4};
    int sorted_array[] = {2,4,6,8,24,42,45,54,54,75,75,7446};
    size_t length = 12;

    for (size_t i = 0; i < length; i++) {
        glist_pushback(list, &array[i]);
    }
    glist_sort(list, _int_comparator);

    gnode_t *node = glist_front(list);
    int i = 0;
    while (node && node->next != list->tail) {
        int value = *(int *)node->data;
        int ref = sorted_array[i];
        cr_expect(ref == value, "Expected: %d but got: %d", ref, value);
        node = node->next;
        i++;
    }
    glist_destroy(list, NULL);
}
