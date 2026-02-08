/*
** EPITECH PROJECT, 2023
** gList
** File description:
** gnode_tests
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <stdio.h>
#include "generic_list.h"

Test(gnode, create)
{
    int value = 135324;
    int result = 0;
    gnode_t *node = gnode_create(sizeof(int), &value);

    cr_expect(node != NULL, "Expected node not to be NULL.");
    cr_expect(node->data != NULL, "Expected data to be not NULL.");
    result = *(int *)node->data;
    cr_expect(result == value, "Expected value %d, but got %d.", value, result);
}

Test(gnode, create_null_data)
{
    int *result;
    gnode_t *node = gnode_create(sizeof(int), NULL);

    cr_expect(node != NULL, "Expected node not to be NULL.");
    result = node->data;
    cr_expect(result == NULL, "Expected value to be NULL.");
}

Test(gnode, create_data_fail)
{
    int data = 42;
    gnode_t *node = gnode_create(100000000000, &data);

    cr_assert(node == NULL, "Expected node to be NULL.");
}

Test(gnode, destroy)
{
    int data = 42;
    gnode_t *node = gnode_create(sizeof(int), &data);

    gnode_destroy(node);
}
