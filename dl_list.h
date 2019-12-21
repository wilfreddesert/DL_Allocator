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
    char * block;
    int state;

    dl_list(){
        this->next = nullptr;
        this->prev = nullptr;
        this->size = 0;
        this->block = nullptr;
        this->state = FREE;
    }
    explicit dl_list(char* block){
        this->next = nullptr;
        this->prev = nullptr;
        this->size = 0;
        this->block = block;
        this->state = FREE;
    }

    dl_list(size_t size, char* block, STATES state){
        this->next = nullptr;
        this->prev = nullptr;
        this->size = size;
        this->block = block;
        this->state = state;
    }
};


static void add_to_list(dl_list *head_of_list, dl_list *new_node) {
    dl_list* ptr = head_of_list;

    while(ptr->next) ptr = ptr->next;

    ptr->next = new_node;
    new_node->prev = ptr;
}

static void remove_from_list(dl_list *node) {
    if (node->prev)
        node->prev->next = node->next;

    if (node->next)
        node->next->prev = node->prev;
}


#define dl_head_INIT(name)	{ dl_list() }
#define LIST_INIT(name)		dl_list name = dl_head_INIT(name)
