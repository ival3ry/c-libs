#include "../include/list.h"

#include <string.h>

/* User defined structure */
typedef struct port
{
    char if_name[30];
    char *mem_leak;
    int port_number;
} port_t;

/* User defined callbacks */
void print_port_t(port_t *port)
{
    printf("PORT: %s | %d\n", port->if_name, port->port_number);
}

int delete_port_t(port_t *port)
{
    if (port == NULL)
    {
        return -1;
    }
    if (port->mem_leak != NULL)
    {
        free(port->mem_leak);
    }
    return 1;
}

int compare_port_t(port_t *lhs_port, port_t *rhs_port)
{
    if (lhs_port != NULL && rhs_port != NULL)
    {
        return (strcmp(lhs_port->if_name, rhs_port->if_name));
    }

    return 3;
}

int main(void)
{
    /* STEP 1: Register the callbacks */
    libslist_register_print_callback((PRINT)print_port_t);
    libslist_register_compare_callback((COMPARE)compare_port_t);
    libslist_register_delete_callback((DELETE)delete_port_t);

    /* STEP 2: Create new list */
    list_t *list = libslist_create_list();

    /* STEP 3: Create user's data to add */
    port_t *port_1 = malloc(sizeof(port_t));
    strcpy(port_1->if_name, "if_nane: port 11");
    port_1->mem_leak = strdup("mem: if_name: 1");
    port_1->port_number = 1;

    port_t *port_2 = malloc(sizeof(port_t));
    strcpy(port_2->if_name, "if_nane: port 22");
    port_2->mem_leak = strdup("mem: if_name: 2");
    port_2->port_number = 2;

    port_t *port_3 = malloc(sizeof(port_t));
    strcpy(port_3->if_name, "if_nane: port 33");
    port_3->mem_leak = strdup("mem: if_name: 3");
    port_3->port_number = 3;

    port_t *port_4 = malloc(sizeof(port_t));
    strcpy(port_4->if_name, "if_nane: port 44");
    port_4->mem_leak = strdup("mem: if_name: 4");
    port_4->port_number = 4;

    port_t *port_5 = malloc(sizeof(port_t));
    strcpy(port_5->if_name, "if_nane: port 55");
    port_5->mem_leak = strdup("mem: if_name: 5");
    port_5->port_number = 5;

    libslist_push(list, port_1);
    libslist_push(list, port_2);
    libslist_push(list, port_3);
    libslist_push(list, port_4);
    libslist_push(list, port_5);

    libslist_print_list(list);

    /* delete first element */
    libslist_delete_node(list, &(port_t){.if_name = "if_nane: port 55"});
    libslist_print_list(list);

    /* delete middle element */
    libslist_delete_node(list, &(port_t){.if_name = "if_nane: port 33"});
    libslist_print_list(list);

    /* delete last element */
    libslist_delete_node(list, &(port_t){.if_name = "if_nane: port 11"});
    libslist_print_list(list);

    /* there is not element to delete */
    libslist_delete_node(list, &(port_t){.if_name = "if_nane: port 5555"});
    libslist_print_list(list);

    libslist_remove_list(list);

    return 0;
}