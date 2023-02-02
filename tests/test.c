/*
** EPITECH PROJECT, 2023
** GenericC-DS
** File description:
** test
*/

#include <criterion/criterion.h>
#include <criterion/logging.h>
#include <criterion/redirect.h>
#include <sys/resource.h>
#include <stdio.h>
#include "generic.h"
#include <math.h>

void redirect_all()
{
    cr_redirect_stderr();
    cr_redirect_stdout();
}

Test(genericsTest, glist_create_test)
{
    GList_t* list = glist_new(sizeof(int));

    cr_expect(list->head != NULL, "Expected not NULL");
    cr_expect(list->tail != NULL, "Expected not NULL");
    cr_expect(list->head->next == list->tail, "Expected list.tail");
    cr_expect(list->head->prev == NULL, "Expected NULL");
    cr_expect(list->tail->next == NULL, "Expected NULL");
    cr_expect(list->tail->prev == list->head, "Expected list.head");
    cr_expect(list->chunk_size == sizeof(int), "Expected size: sizeof(int)");
}

Test(genericsTest, glist_add_elems_test)
{
    GList_t* list = glist_new(sizeof(int));

    int nb = 45;

    glist_pushback(list, &nb);

    cr_expect(*(int*)list->head->next->data == 45);
    cr_expect(*(int*)list->tail->prev->data == 45);
}

Test(genericsTest, glist_add_struct_elems_test)
{
    struct test {
        int a;
        float b;
    };

    GList_t* list = glist_new(sizeof(struct test));

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
    struct test result = *(struct test *)glist_popback(list);
    cr_expect(result.a == 84);
    cr_expect_float_eq(result.b, 6.28f, 0.0001f);

    result = *(struct test *)glist_popback(list);
    cr_expect(result.a == 42);
    cr_expect_float_eq(result.b, 3.14f, 0.0001f);
}

Test(genericsTest, glist_pop_front_test)
{
    GList_t *list = glist_new(sizeof(int));
    int array[5] = {45, 124, 546, 42, 78};

    for (int i = 0; i < 5; i++) {
        glist_pushback(list, &array[i]);
    }
    cr_expect(glist_size(list) == 5);
    for (size_t i = 0; i < 5; i++) {
        cr_expect(glist_size(list) == (5 - i));
        int result = *(int*)glist_popfront(list);
        cr_expect(result == array[i]);
    }
}

Test(genericsTest, glist_pop_back_test)
{
    GList_t *list = glist_new(sizeof(int));
    int array[5] = {45, 124, 546, 42, 78};

    for (int i = 0; i < 5; i++) {
        glist_pushback(list, &array[i]);
    }
    cr_expect(glist_size(list) == 5);
    for (size_t i = 0; i < 5; i++) {
        cr_expect(glist_size(list) == (5 - i));
        int result = *(int*)glist_popback(list);
        cr_expect(result == array[4 - i]);
    }
}

Test(genericsTest, glist_pop_back_too_far_test)
{
    GList_t *list = glist_new(sizeof(int));
    int array[5] = {45, 124, 546, 42, 78};

    for (int i = 0; i < 5; i++) {
        glist_pushback(list, &array[i]);
    }
    cr_expect(glist_size(list) == 5);
    for (size_t i = 0; i < 5; i++) {
        cr_expect(glist_size(list) == (5 - i));
        cr_expect_(glist_popback(list) != NULL);
    }
    cr_expect_(glist_popback(list) == NULL);
    cr_expect_(glist_popback(list) == NULL);
}

Test(genericsTest, glist_pop_front_too_far_test)
{
    GList_t *list = glist_new(sizeof(int));
    int array[5] = {45, 124, 546, 42, 78};

    for (int i = 0; i < 5; i++) {
        glist_pushback(list, &array[i]);
    }
    cr_expect(glist_size(list) == 5);
    for (size_t i = 0; i < 5; i++) {
        cr_expect(glist_size(list) == (5 - i));
        int result = *(int*)glist_popfront(list);
        cr_expect(result == array[i]);
    }
    cr_expect(glist_popfront(list) == NULL);
    cr_expect(glist_popfront(list) == NULL);
}

Test(genericsTest, glist_front_NULL)
{
    GList_t *list = glist_new(sizeof(int));

    cr_expect(glist_front(list) == NULL);
}

Test(genericsTest, glist_back_NULL)
{
    GList_t *list = glist_new(sizeof(int));

    cr_expect(glist_back(list) == NULL);
}

Test(genericsTest, glist_back_success)
{
    GList_t *list = glist_new(sizeof(int));
    int value = 76;

    glist_pushback(list, &value);
    cr_expect(*((int*)glist_back(list)) == 76);
}

Test(genericsTest, glist_front_success)
{
    GList_t *list = glist_new(sizeof(int));
    int value = 76;

    glist_pushback(list, &value);
    cr_expect(*((int*)glist_front(list)) == 76);
}

// void *my_malloc(size_t size)
// {
//     return NULL;
// }

// #define malloc(size) my_malloc(size)
// Test(genericsTest, glist_list_failed_creation)
// {
//     GList_t *list = glist_new(sizeof(int));

//     cr_expect(list == NULL);
// }
// #undef malloc
