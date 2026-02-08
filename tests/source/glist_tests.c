/*
** EPITECH PROJECT, 2023
** gList
** File description:
** test
*/

#include "glist/glist.h"

#include <criterion/criterion.h>
#include <sys/resource.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

Test(glist, create)
{
    glist_t* list = glist_new(sizeof(int));

    cr_assert(list != NULL, "Expected list to be not NULL");
    cr_expect(list->head == NULL, "Expected not NULL");
    cr_expect(list->tail == NULL, "Expected not NULL");
    cr_expect(list->chunk_size == sizeof(int), "Expected size: sizeof(int)");
    glist_destroy(list, NULL);
}

Test(glist, destroy_no_list)
{
    glist_destroy(NULL, NULL);
}

Test(glist, add_struct_elems)
{
    struct test {
        int a;
        float b;
    };

    glist_t* list = glist_new(sizeof(struct test));

    struct test test = {
        .a = 42,
        .b = 3.14f
    };

    struct test test2 = {
        .a = 84,
        .b = 6.28f
    };

    glist_pushback(list, &test);
    glist_pushback(list, &test2);
    gnode_t *node = glist_popback(list);
    cr_assert(node);
    struct test result = *(struct test *)node->data;
    cr_expect(result.a == 84);
    cr_expect_float_eq(result.b, 6.28f, 0.0001f);
    node = glist_popback(list);
    result = *(struct test *)node->data;
    cr_expect(result.a == 42);
    cr_expect_float_eq(result.b, 3.14f, 0.0001f);
    glist_destroy(list, NULL);
}

Test(glist, pointers_to_elems)
{
    int *numbers[15] = {0};
    glist_t *list = glist_new(sizeof(int *));
    for (int i = 0; i < 15; i++) {
        numbers[i] = malloc(sizeof(int));
        *(numbers[i]) = i;
        glist_pushback(list, &numbers[i]);
    }
    int i = 0;
    gnode_t *node = glist_front(list);
    for (; node && node->data; node = node->next) {
        int *num = *(int **)node->data;
        cr_expect(numbers[i] == num, "(PTR) Exepected: %d but got: %d", numbers[i], num);
        cr_expect(*numbers[i] == *num, "(VAL) Exepected: %d but got: %d", *numbers[i], *num);
        i++;
    }
    glist_destroy(list, NULL);
}
