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

Test(genericsTest, glist_create)
{
    glist_t* list = glist_new(sizeof(int));

    cr_expect(list->head != NULL, "Expected not NULL");
    cr_expect(list->tail != NULL, "Expected not NULL");
    cr_expect(list->head->next == list->tail, "Expected list.tail");
    cr_expect(list->head->prev == NULL, "Expected NULL");
    cr_expect(list->tail->next == NULL, "Expected NULL");
    cr_expect(list->tail->prev == list->head, "Expected list.head");
    cr_expect(list->chunk_size == sizeof(int), "Expected size: sizeof(int)");
}

Test(genericsTest, glist_add_elems)
{
    glist_t* list = glist_new(sizeof(int));
    int nb = 45;

    glist_pushback(list, &nb);
    cr_expect(*(int*)list->head->next->data == 45);
    cr_expect(*(int*)list->tail->prev->data == 45);
}

Test(genericsTest, glist_add_struct_elems)
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
    struct test result = *(struct test *)glist_popback(list);
    cr_expect(result.a == 84);
    cr_expect_float_eq(result.b, 6.28f, 0.0001f);
    result = *(struct test *)glist_popback(list);
    cr_expect(result.a == 42);
    cr_expect_float_eq(result.b, 3.14f, 0.0001f);
}

Test(genericsTest, glist_pop_front)
{
    glist_t *list = glist_new(sizeof(int));
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

Test(genericsTest, glist_pop_back)
{
    glist_t *list = glist_new(sizeof(int));
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

Test(genericsTest, glist_pop_back_too_far)
{
    glist_t *list = glist_new(sizeof(int));
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

Test(genericsTest, glist_pop_front_too_far)
{
    glist_t *list = glist_new(sizeof(int));
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

Test(genericsTest, glist_front_null)
{
    glist_t *list = glist_new(sizeof(int));

    cr_expect(glist_front(list) == NULL);
}

Test(genericsTest, glist_back_null)
{
    glist_t *list = glist_new(sizeof(int));

    cr_expect(glist_back(list) == NULL);
}

Test(genericsTest, glist_back_success)
{
    glist_t *list = glist_new(sizeof(int));
    gnode_t *back_node = NULL;
    int value = 76;
    int result = 0;

    glist_pushback(list, &value);
    back_node = glist_back(list);
    cr_expect(back_node != NULL, "Expected node to be not NULL.");
    cr_expect(back_node->data != NULL, "Expected data to be not NULL.");
    result = *(int *)back_node->data;
    cr_expect(*(int *)back_node->data == value, "Expected value: %d, but got %d", value, result);
}

Test(genericsTest, glist_front_success)
{
    glist_t *list = glist_new(sizeof(int));
    gnode_t *front_node = NULL;
    int value = 76;
    int result = 0;

    glist_pushback(list, &value);
    front_node = glist_front(list);
    cr_expect(front_node != NULL, "Expected node to be not NULL.");
    cr_expect(front_node->data != NULL, "Expected data to be not NULL.");
    result = *(int *)front_node->data;
    cr_expect(*(int *)front_node->data == value, "Expected value: %d, but got %d", value, result);
}

static void float_dtor(void *f)
{
    printf("used dtor: %f\n", *(float *)f);
}

Test(genericsTest, glist_destroy)
{
    glist_t* list = glist_new(sizeof(float));

    float array[] = {32.56f, 57.25f, 5446.21f, 8921.8f};
    for (int i = 0; i < 4; i++) {
        glist_pushback(list, &array[i]);
    }
    glist_destroy(&list, float_dtor);
}

Test(genericsTest, glist_destroy_no_destructor)
{
    glist_t* list = glist_new(sizeof(float));

    float array[] = {32.56f, 57.25f, 5446.21f, 8921.8f};
    for (int i = 0; i < 4; i++) {
        glist_pushback(list, &array[i]);
    }
    glist_destroy(&list, NULL);
}

static int _int_comparator(const void *lhs, const void *rhs)
{
    int int_lhs = *(int *)(lhs);
    int int_rhs = *(int *)rhs;
    return (int_lhs - int_rhs);
}

Test(genericsTest, glist_sort_int)
{
    glist_t *list = glist_new(sizeof(int));
    int array[] = {45,54,8,6,75,2,7446,42,75,24,54,4};
    int sorted_array[] = {2,4,6,8,24,42,45,54,54,75,75,7446};
    size_t length = 12;

    for (size_t i = 0; i < length; i++)
    {
        glist_pushback(list, &array[i]);
    }
    glist_sort(list, _int_comparator);

    void *current = NULL;
    while (list->size) {
        current = glist_popback(list);
        cr_expect(sorted_array[length - 1] == *(int *)current);
        length--;
    }
}

