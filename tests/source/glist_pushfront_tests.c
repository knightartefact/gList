#include <criterion/criterion.h>

#include "glist/glist.h"

Test(glist_pushfront, one_element)
{
    glist_t* list = glist_new(sizeof(int));
    int nb = 45;

    glist_pushfront(list, &nb);
    cr_expect(*(int*)list->head->next->data == 45);
    cr_expect(*(int*)list->tail->prev->data == 45);
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
    glist_destroy(list, NULL);
}

