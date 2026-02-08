/*
** EPITECH PROJECT, 2023
** gList
** File description:
** test
*/

#include "glist/glist.h"

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <sys/resource.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

void redirect_all()
{
    cr_redirect_stderr();
    cr_redirect_stdout();
}

Test(glist, create)
{
    glist_t* list = glist_new(sizeof(int));

    cr_assert(list != NULL, "Expected list to be not NULL");
    cr_expect(list->head != NULL, "Expected not NULL");
    cr_expect(list->tail != NULL, "Expected not NULL");
    cr_expect(list->head->next == list->tail, "Expected list.tail");
    cr_expect(list->head->prev == NULL, "Expected NULL");
    cr_expect(list->tail->next == NULL, "Expected NULL");
    cr_expect(list->tail->prev == list->head, "Expected list.head");
    cr_expect(list->chunk_size == sizeof(int), "Expected size: sizeof(int)");
    glist_destroy(list, NULL);
}

Test(glist, add_elems)
{
    glist_t* list = glist_new(sizeof(int));
    int nb = 45;

    glist_pushback(list, &nb);
    cr_expect(*(int*)list->head->next->data == 45);
    cr_expect(*(int*)list->tail->prev->data == 45);
    glist_destroy(list, NULL);
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
    struct test result = *(struct test *)glist_popback(list);
    cr_expect(result.a == 84);
    cr_expect_float_eq(result.b, 6.28f, 0.0001f);
    result = *(struct test *)glist_popback(list);
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

Test(glist, pop_front)
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
    glist_destroy(list, NULL);
}

Test(glist, pop_back)
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
    glist_destroy(list, NULL);
}

Test(glist, pop_back_too_far)
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
    glist_destroy(list, NULL);
}

Test(glist, pop_front_too_far)
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
    glist_destroy(list, NULL);
}

Test(glist, front_null)
{
    glist_t *list = glist_new(sizeof(int));

    cr_expect(glist_front(list) == NULL);
    glist_destroy(list, NULL);

}

Test(glist, back_null)
{
    glist_t *list = glist_new(sizeof(int));

    cr_expect(glist_back(list) == NULL);
    glist_destroy(list, NULL);
}

Test(glist, back_success)
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
    glist_destroy(list, NULL);
}

Test(glist, front_success)
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
    glist_destroy(list, NULL);
}

Test(glist, destroy)
{
    glist_t* list = glist_new(sizeof(float));

    float array[] = {32.56f, 57.25f, 5446.21f, 8921.8f};
    for (int i = 0; i < 4; i++) {
        glist_pushback(list, &array[i]);
    }
    glist_destroy(list, NULL);
}

Test(glist, destroy_no_list)
{
    glist_destroy(NULL, NULL);
}

// NOTE: Implement test where a destructor is used e.g:
//       - A list of structures containing shared memory.

static int _int_comparator(const void *lhs, const void *rhs)
{
    int int_lhs = *(int *)(lhs);
    int int_rhs = *(int *)rhs;
    return (int_lhs - int_rhs);
}

Test(glist, sort_int)
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
    glist_destroy(list, NULL);
}

static void print_integer(const void *integer)
{
    int value = *(int *)integer;

    printf("%d,", value);
}

Test(glist, print, .init=cr_redirect_stdout)
{
    glist_t *list = glist_new(sizeof(int));
    int array[5] = {45, 124, 546, 42, 78};
    int size = sizeof(array) / sizeof(array[0]);

    for (int i = 0; i < size; i++) {
        glist_pushback(list, &array[i]);
    }
    glist_print(list, print_integer);
    fflush(stdout);
    cr_assert_stdout_eq_str("45,124,546,42,78,");
    glist_destroy(list, NULL);
}

Test(glist, print_list_size_zero, .init=cr_redirect_stdout)
{
    glist_t *list = glist_new(sizeof(int));

    glist_print(list, print_integer);
    fflush(stdout);
    cr_assert_stdout_eq_str("");
    glist_destroy(list, NULL);
}

Test(glist, print_no_list, .init=cr_redirect_stdout)
{
    glist_print(NULL, print_integer);
    fflush(stdout);
    cr_assert_stdout_eq_str("");
}

