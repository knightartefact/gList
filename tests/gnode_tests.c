/*
** EPITECH PROJECT, 2023
** GenericC-DS
** File description:
** gnode_tests
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <stdio.h>
#include "generic_list.h"

Test(genericNode, gnode_create)
{
    int value = 135324;
    int result = 0;
    gnode_t *node = gnode_create(sizeof(int), &value);

    cr_expect(node != NULL, "Expected node not to be NULL.");
    cr_expect(node->data != NULL, "Expected data to be not NULL.");
    result = *(int *)node->data;
    cr_expect(result == value, "Expected value %d, but got %d.", value, result);
}

Test(genericNode, gnode_create_null_data)
{
    int *result;
    gnode_t *node = gnode_create(sizeof(int), NULL);

    cr_expect(node != NULL, "Expected node not to be NULL.");
    result = node->data;
    cr_expect(result == NULL, "Expected value to be NULL.");
}
