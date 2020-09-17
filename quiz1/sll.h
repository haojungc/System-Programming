#ifndef SLL_H
#define SLL_H

typedef struct __node {
    int value;
    struct __node *next;
} node_t;

void add_entry(node_t **head, int new_value);
node_t *find_entry(node_t *head, int value);
void remove_entry(node_t **head, node_t *entry);
void swap_pair(node_t **indirect);
node_t *reverse(node_t *head);
node_t *rev_recursive(node_t *current, node_t *prev);
void print_list(node_t *head);

#endif