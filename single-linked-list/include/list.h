#ifndef _LIST_H_
#define _LIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef void *data_t;

/* Opaque data structure */
typedef struct list list_t;

typedef void (*PRINT)(void *);
typedef int (*DELETE)(void *);

/**
 * @return 0 on success , -1 on fail
 */
typedef int (*COMPARE)(void *, void *);

/**
 * @brief Set of an user-defined callbacks.
 *
 * User can define custom functions on how to
 *  handle the data(print/compare/delete)
 *
 * If the user's data works with allocated memory so
 *  define DELETE callback helps to avoid a memory leak
 */
void libslist_register_print_callback(PRINT);
void libslist_register_compare_callback(COMPARE);
void libslist_register_delete_callback(DELETE);

/**
 * @brief Creates new single-linked list instance
 *
 * @return on success: pointer to new list , on error: NULL
 */
list_t *libslist_create_list();

/**
 * @brief Removes the whole single-linked list
 *
 * @note Uses DELETE callback to deallocate user's data
 *
 * @param list_t Pointer to the list
 */
void libslist_remove_list(list_t *);

/**
 * @brief Adds a new node to the head of a list
 *
 * @param list_t Pointer to a list to add
 * @param data_t Data to add
 */
void libslist_push(list_t *, data_t);

/**
 * @brief Removes a node from a list's head
 *
 * @param list_t Pointer to a list to remove
 *
 * @return A data of removed node
 */
data_t libslist_pop(list_t *);

/**
 * @brief Delete specific node
 *
 * @note Uses COMPARE callback to handle user's data
 * @note Uses DELETE callback to deallocate the user's data
 *
 * @param list_t Pointer to a list
 * @param data_t Data to determine which node to delete
 */
void libslist_delete_node(list_t *, data_t);

/**
 */
data_t libslist_get_node(list_t *, data_t);

/**
 * @brief Prints a list
 *
 * @note Uses PRINT callback to print user's data
 *
 * @param list_t Pointer to a list
 */
void libslist_print_list(list_t *);

#endif