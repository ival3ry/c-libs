#include "../include/list.h"

typedef struct node
{
    data_t *data;
    struct node *next;
} node_t;

struct list
{
    node_t *head;
};

PRINT print_callback = NULL;
COMPARE compare_callback = NULL;
DELETE delete_callback = NULL;

void libslist_register_print_callback(PRINT print_fn)
{
    if (print_fn == NULL)
    {
        fprintf(stderr, "Incorrect print callback!\n");
        exit(EXIT_FAILURE);
    }
    print_callback = print_fn;
}

void libslist_register_compare_callback(COMPARE compare_fn)
{
    if (compare_fn == NULL)
    {
        fprintf(stderr, "Incorrect compare callback!\n");
        exit(EXIT_FAILURE);
    }
    compare_callback = compare_fn;
}

void libslist_register_delete_callback(DELETE delete_fn)
{
    if (delete_fn == NULL)
    {
        fprintf(stderr, "Incorrect delete callback!\n");
        exit(EXIT_FAILURE);
    }
    delete_callback = delete_fn;
}

list_t *libslist_create_list()
{
    list_t *list = malloc(sizeof(list_t));
    if (list == NULL)
    {
        fprintf(stderr, "Failed to allocate a memory for list\n");
        return NULL;
    }

    list->head = NULL;

    return list;
}

void libslist_remove_list(list_t *list)
{
    node_t *temp_node = list->head;
    while (temp_node != NULL)
    {
        delete_callback(temp_node->data);
        free(temp_node->data);

        node_t *current = temp_node;
        temp_node = temp_node->next;

        free(current);
    }
    free(list);
}

void libslist_push(list_t *list, data_t data)
{
    node_t *node = malloc(sizeof(node_t));
    if (node == NULL)
    {
        fprintf(stderr, "Failed to allocate a memory for new node\n");
        return;
    }

    node->data = data;

    if (list->head == NULL)
    {
        list->head = node;
        node->next = NULL;
    }
    else
    {
        node->next = list->head;
        list->head = node;
    }
}

data_t libslist_pop(list_t *list)
{
    if (list->head == NULL)
    {
        return NULL;
    }
    else
    {
        node_t *ret_node = list->head;
        list->head = list->head->next;

        data_t data = ret_node->data;
        free(ret_node);

        return data;
    }
}

void libslist_delete_node(list_t *list, data_t data_to_delete)
{
    if (compare_callback(list->head->data, data_to_delete) == 0)
    {
        if (list->head->next == NULL)
        {
            delete_callback(list->head->data);
            free(list->head);
        }
        else
        {
            node_t *current_node = list->head;
            list->head = list->head->next;

            delete_callback(current_node->data);
            free(current_node->data);
            free(current_node);
        }
    }
    else /* Case for delete last element */
    {
        node_t *temp = list->head;
        while (temp != NULL &&
               temp->next != NULL &&
               (compare_callback(temp->next->data, data_to_delete) != 0))
        {
            temp = temp->next;
        }
        if (temp != NULL && temp->next != NULL)
        {
            node_t *remove = NULL;
            remove = temp->next;
            temp->next = remove->next;

            delete_callback(remove->data);
            free(remove->data);
            free(remove);
        }
    }
}

data_t libslist_get_node(list_t *list, data_t data)
{
    assert(list != NULL);

    node_t *current_node = list->head;
    while (current_node != NULL)
    {
        assert(current_node->data != NULL);
        if (compare_callback(current_node->data, data) == 0)
        {
            return current_node->data;
        }

        current_node = current_node->next;
    }
    return NULL;
}

void libslist_print_list(list_t *list)
{
    printf("\nList Info:\n");
    node_t *current_node = list->head;
    while (current_node != NULL)
    {
        print_callback(current_node->data);

        current_node = current_node->next;
    }
}

data_t libslist_top(list_t *list)
{
    if (!list)
    {
        fprintf(stderr, "[%s]: ERROR: List is empty!\n", __func__);
        return NULL;
    }

    if (!list->head)
    {
        fprintf(stderr, "[%s]: ERROR: List head is NULL!\n", __func__);
        return NULL;
    }

    return list->head->data;
}