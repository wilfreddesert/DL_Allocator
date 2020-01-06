#include <cstdint>

#ifndef ALLOCATORLT_LIST_H
#define ALLOCATORLT_LIST_H

#endif //ALLOCATORLT_LIST_H

enum STATES {FREE, OCCUPIED};

class dl_list {
public:
    dl_list *next;
    dl_list *prev;
    int size;
    void * block;
    int state;
};

static dl_list* init_list_node(void* dl_list_memory, void* ptr, int size, STATES state){
    dl_list *node = static_cast<dl_list*>(dl_list_memory);
    node->block = ptr;
    node->state = state;
    node->size = size;
    node->next = nullptr;
    node->prev = nullptr;

    return node;
}

static void add_to_list(dl_list *next_node, dl_list *new_node) {
    if (next_node->prev){
        next_node->prev->next = new_node;
        new_node->prev = next_node->prev;
        new_node->next = next_node;
        next_node->prev = new_node;
    }
    else {
        new_node->next = next_node;
        next_node->prev = new_node;
    }
}

static void remove_from_list(dl_list *node) {
    if (node->prev)
        node->prev->next = node->next;
    if (node->next)
        node->next->prev = node->prev;
}

static void union_list_node(dl_list* node1, dl_list* node2) {
    node1->size += node2->size;
    remove_from_list(node2);
}
