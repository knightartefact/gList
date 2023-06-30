/*
** EPITECH PROJECT, 2023
** GenericC-DS
** File description:
** generic_list
*/

#ifndef GENERIC_LIST_H_
    #define GENERIC_LIST_H_
    #include <stddef.h>

typedef struct gnode_s {
    void *data;
    struct gnode_s *next;
    struct gnode_s *prev;
} gnode_t;

typedef struct glist_s {
    gnode_t *head;
    gnode_t *tail;
    size_t chunk_size;
    size_t size;
} glist_t;

/**
 * @brief Create a new node
 * @param chunk_size Size (in bytes) of the data contained by the node.
 * @param data Data that is to be copied in the node.
 * @return A newly created node or NULL if an error occurs.
*/
gnode_t* gnode_create(size_t chunk_size, void *data);

/**
 * @brief Destroy a node.
 * @param node The node you want to destroy.
*/
void gnode_destroy(gnode_t **node);

/**
 * @brief Create a new generic list based on chunk size.
 * @param chunk_size The size (in bytes) of an element in the list.
 * @return Returns a newly allocated list or NULL if an error occurs.
*/
glist_t* glist_new(size_t chunk_size);

/**
 * @brief Destroy a generic list, using a destructor for
 *        each element (if not NULL).
 * @param list The list you want to destroy.
 * @param dtor The destructor used on each element of the list.
 *             If this parameter is NULL, no destructor is used.
*/
void glist_destroy(glist_t **list, void(*dtor)(void *));

/**
 * @brief Get the size of the list.
 * @param list The list you want to get the size of.
 * @return Returns the size of the list (in number of elements).
*/
size_t glist_size(glist_t *list);

/**
 * @brief Get the last element of the list.
 * @param list The list you want to get the last element from.
 * @return Returns the last node of the list or NULL if list is empty.
*/
gnode_t *glist_back(glist_t *list);

/**
 * @brief Push an element at the back of the list.
 * @param list The list you want to add the element to.
 * @param elem The element you want to add to the list.
 * @return Returns 0 if the element was added successfully
*/
int glist_pushback(glist_t *list, void *elem);

/**
 * @brief Pop an element at the back of the list
 * @param list The list you want to popback from.
 * @return Returns the data contained in the list node or NULL if list is empty.
*/
void *glist_popback(glist_t *list);

/**
 * @brief Get the first element of the list.
 * @param list The list you want to get the first element from.
 * @return Returns the first node of the list or NULL if list is empty.
*/
gnode_t *glist_front(glist_t *list);

/**
 * @brief Push an element at the front of the list.
 * @param list The list you want to add the element to.
 * @param elem The element you want to add to the list.
 * @return Returns 0 if the element was added successfully
*/
int glist_pushfront(glist_t *list, void *elem);

/**
 * @brief Pop an element at the back of the list
 * @param list The list you want to popfront from.
 * @return Returns the data contained in the list node or NULL if list is empty.
*/
void *glist_popfront(glist_t *list);

/**
 * @brief Print the list.
 * @param list The list you want to print.
 * @param print_function The function used to print one element
 *                       (used for each element in the list)
*/
void glist_print(glist_t *list, void(*print_function)(const void *));

/**
 * @brief Sort the list.
 * @param list The list you want to sort
 * @param comparator The function used to compare two elements of the list.
 * The function must return an integer > 0 if the
 * comparison is true, else it must return 0 or less.
 * @return Returns 0 if the sorting of the list was successful.
*/
int glist_sort(glist_t *list, int(*comparator)(const void *, const void*));

/**
 * @brief Pop a node in the middle of the list
 * @param list The list you want to remove the element from.
 * @param node The element you want to remove.
 * @return Returns the data contained in the popped node or NULL if an error occurs.
*/
void *glist_popmid(glist_t *list, gnode_t *node);

#endif /* !GENERIC_LIST_H_ */
