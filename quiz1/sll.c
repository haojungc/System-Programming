#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "sll.h"

static void *safe_malloc(size_t size) {
    void *ptr = malloc(size);
    if (ptr == NULL) {
        fprintf(stderr, "Error: failed to allocate memory.\n");
        exit(EXIT_FAILURE);
    }
    return ptr;
}

/* Appends a new node to the list */
void add_entry(node_t **head, int new_value)
{
    /* Creates a pointer to pointer called `indirect` 
     * and makes it point to the address of `head` 
     * in the list */
    node_t **indirect = head;

    node_t *new_node = safe_malloc(sizeof(node_t));

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

void fisher_yates_shuffle(node_t **head_address) {
    int count = 0;
    node_t **indirect = head_address;

    /* Counts the number of nodes in the list */
    while (*indirect) {
        indirect = &(*indirect)->next;
        count++;
    }

    node_t **node = safe_malloc(sizeof(node_t*) * (count + 1));
    indirect = head_address;
    count = 0;

    /* Stores the addresses of each node in the list */
    while (*indirect) {
        node[count++] = *indirect;
        indirect = &(*indirect)->next;
    }
    node[count] = NULL;

    /* Shuffles the addresses of each node */
    for (int i = count - 1; i >= 1; i--) {
        int target = rand() % (i + 1);
        node_t *tmp = node[i];
        node[i] = node[target];
        node[target] = tmp;
    }

    /* Reconnects each node */
    for (int i = 0; i < count; i++)
        node[i]->next = node[i + 1];
    
    /* Updates head */
    *head_address = node[0];

    free(node);
}

void print_list(node_t *head)
{
    for (node_t *current = head; current; current = current->next)
        printf("%d ", current->value);
    printf("\n");
}