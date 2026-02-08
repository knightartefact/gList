#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "glist/glist.h"

static void print_integer(const void *integer)
{
    int value = *(int *)integer;
    printf("%d", value);
}

static void print_string(const void *string)
{
    char *str = *(char **)string;
    printf("%s", str);
}

Test(glist_print, simple, .init=cr_redirect_stdout)
{
    glist_t *list = glist_new(sizeof(int));
    int array[] = {45, 124, 546, 42, 78};
    int size = sizeof(array) / sizeof(array[0]);

    for (int i = 0; i < size; i++) {
        glist_pushback(list, &array[i]);
    }
    glist_print(list, print_integer);
    fflush(stdout);
    cr_assert_stdout_eq_str("[45, 124, 546, 42, 78]\n");
    glist_destroy(list, NULL);
}

Test(glist_print, no_print_function)
{
    glist_t *list = glist_new(sizeof(int));
    int array[] = {45, 124, 546, 42, 78};
    int size = sizeof(array) / sizeof(array[0]);

    for (int i = 0; i < size; i++) {
        glist_pushback(list, &array[i]);
    }
    glist_print(list, NULL);
    glist_destroy(list, NULL);
}

Test(glist_print, empty_list, .init=cr_redirect_stdout)
{
    glist_t *list = glist_new(sizeof(int));

    glist_print(list, print_integer);
    fflush(stdout);
    cr_assert_stdout_eq_str("[]\n");
    glist_destroy(list, NULL);
}

Test(glist_print, no_list)
{
    glist_print(NULL, NULL);
}

Test(glist_print, names, .init=cr_redirect_stdout)
{
    glist_t *list = glist_new(sizeof(int));
    char *array[] = {"Bob", "Alice", "Gepetto", "Pinnochio", "Bruce Banner", "Bruce Wayne"};
    int size = sizeof(array) / sizeof(array[0]);

    for (int i = 0; i < size; i++) {
        glist_pushback(list, &array[i]);
    }
    glist_print(list, print_string);
    fflush(stdout);
    cr_assert_stdout_eq_str("[Bob, Alice, Gepetto, Pinnochio, Bruce Banner, Bruce Wayne]\n");
    glist_destroy(list, NULL);
}
