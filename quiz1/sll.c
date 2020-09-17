#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "sll.h"

/* Appends a new node to the list */
void add_entry(node_t **head, int new_value)
{
    /* Creates a pointer to pointer called `indirect` 
     * and makes it point to the address of `head` 
     * in the list */
    node_t **indirect = head;

    node_t *new_node = malloc(sizeof(node_t));

    /* Checks if the memory is successfully allocated */
    assert(new_node); /* AA1 */
    new_node->value = new_value;
    new_node->next = NULL;

    /* (*indirect) is the value (address of a node) 
     * of the pointer that indirect points to */
    while (*indirect)
        /* indirect points to the pointer 
         * which points to the next node */
        indirect = &(*indirect)->next;
    
    /* Lets node_t pointer in the last node (*indirect) 
     * point to new_node */
    *indirect = new_node; /* AA2 */
}

node_t *find_entry(node_t *head, int value)
{
    node_t *current = head;
    for (; current && current->value != value; current = current->next)
        /* iterate */;
    return current;
}

void remove_entry(node_t **head, node_t *entry)
{
    node_t **indirect = head;

    while ((*indirect) != entry)
        indirect = &(*indirect)->next;

    *indirect = entry->next;
    free(entry);
}

void swap_pair(node_t **indirect)
{
    for (node_t **node = indirect; *node && (*node)->next; node = &(*node)->next->next) {
        node_t *tmp = *node;
        *node = (*node)->next;
        tmp->next = (*node)->next;
        (*node)->next = tmp;
    }
}

void reverse(node_t **indirect)
{
    *indirect = rev_recursive(*indirect, NULL);
}

node_t *rev_recursive(node_t *current, node_t *prev) {
    node_t *next = current->next;
    
    current->next = prev;
    if (!next) 
        return current;

    return rev_recursive(next, current);
}

void print_list(node_t *head)
{
    for (node_t *current = head; current; current = current->next)
        printf("%d ", current->value);
    printf("\n");
}