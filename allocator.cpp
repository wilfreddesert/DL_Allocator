#include <iostream>
#include "allocator.h"

static LIST_INIT(head);

void* CleverPtr::get() const {
    return data;
}

Allocator::Allocator() {
    Allocator(100);//100 Bytes
}

Allocator::Allocator(int size) {
    this->memory = (char*)malloc(size);
    head.block = this->memory;
    head.size = size;
}

CleverPtr Allocator::alloc(int size) {
    dl_list *ptr = &(head);
    bool find = false;

    while (ptr) {
        if (ptr->state == FREE && ptr->size >= size) {
            find = true;
            break;
        }
        ptr = ptr->next;
    }

    if (find) {
        dl_list *new_block = new dl_list(size, ptr->block, OCCUPIED);

        ptr->block = (char*)((uintptr_t)(ptr->block) + size);
        ptr->size -= size;

        add_to_list(&(head), new_block);

        return CleverPtr{new_block->block};
    }

    return CleverPtr(nullptr);
}

void Allocator::free(CleverPtr &ptr) {
    char* block1 = (char *)ptr.get();
    dl_list* ptr1 = &(head);

    while(ptr1->next){
        if (ptr1->block == block1)
            break;

        ptr1 = ptr1->next;
    }

    ptr1->state = FREE;
}

void Allocator::defrag() {
    dl_list *ptr = &(head);

    while(ptr) {
        if (ptr->next) {
            if (ptr->state == FREE && ptr->next->state == FREE) {
                ptr->size += ptr->next->size;
                remove_from_list(ptr->next);
            }
        }
        ptr = ptr->next;
    }
}

int Allocator::show_blocks(vector<pair<int, int>> *blocks, STATES state) {
    int busy_blocks_cnt = 0;

    dl_list *ptr = &(head);

    while(ptr) {
        if (ptr->state == state) {
            pair<int, int> p = {head.block - ptr->block, ptr->size};
            blocks->emplace_back(p);
            busy_blocks_cnt++;
        }
        ptr = ptr->next;
    }

    return busy_blocks_cnt;
}
