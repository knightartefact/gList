#include <criterion/criterion.h>

#include "glist/glist.h"

Test(glist_pushfront, one_element)
{
    glist_t* list = glist_new(sizeof(int));
    int nb = 45;

    glist_pushfront(list, &nb);
    gnode_t *front = glist_front(list);
    gnode_t *back = glist_back(list);
    cr_expect(front == back);
    cr_expect(*(int*)front->data == 45);
    cr_expect(*(int*)back->data == 45);
    glist_destroy(list, NULL);
}

Test(glist_pushfront, multiple_elements)
{
    glist_t* list = glist_new(sizeof(int));
    int nbs[] = {1, 23, 456, 7890};
    size_t array_size = sizeof(nbs) / sizeof(*nbs);

    for (size_t i = 0; i < array_size; i++) {
        glist_pushfront(list, &nbs[i]);
        gnode_t *front = glist_front(list);
        int data = *(int *)front->data;
        cr_expect(data == nbs[i]);
    }
    cr_expect(glist_size(list) == array_size);
    glist_destroy(list, NULL);
}

