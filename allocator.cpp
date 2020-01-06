#include <iostream>
#include "allocator.h"


void* CleverPtr::get() const {
    return data;
}

Allocator::Allocator() {
    Allocator(100);//100 Bytes
}

Allocator::Allocator(int size) {
    this->memory = (void*)malloc(size + MEMORY_DELIMETR + (size + MEMORY_DELIMETR)*sizeof(dl_list));
    this->list_memory = (void*)((uintptr_t)this->memory + (size + MEMORY_DELIMETR));
    this->list_memory_flag = this->list_memory;
	head = static_cast<dl_list*>(list_alloc());
    head->block = this->memory;
    head->size = size;
    head->state = FREE;
    head->next = nullptr;
    head->prev = nullptr;
}

CleverPtr Allocator::alloc(int size) {
    dl_list *ptr = head;
    bool find = false;
    while (ptr) {
        if (ptr->state == FREE && ptr->size >= size) {
            find = true;
            break;
        }
        ptr = ptr->next;
    }
    if (find) {
        void * list_mem = list_alloc();
        dl_list *new_block = init_list_node(list_mem, ptr->block, size, OCCUPIED);
        ptr->block = (void*)((uintptr_t)(ptr->block) + size);
        ptr->size -= size;
        if (!ptr->prev) {
            head = new_block;
        }
        add_to_list(ptr, new_block);
        return CleverPtr{new_block->block};
    }
    return CleverPtr(nullptr);
}

void* Allocator::list_alloc() {
    void* ptr = this->list_memory_flag;
    this->list_memory_flag = (void*)((uintptr_t)this->list_memory_flag + sizeof(dl_list) + MEMORY_DELIMETR);
    return (ptr);
}

void Allocator::free(CleverPtr &ptr) {
    void* block = ptr.get();
    dl_list* cont = head;
    while(cont->next){
        if (cont->block == block)
            break;
        cont = cont->next;
    }
    cont->state = FREE;
    if (cont->prev && cont->prev->state == FREE)
        union_list_node(cont->prev, cont);
    if (cont->next && cont->next->state == FREE)
        union_list_node(cont, cont->next);
}

void Allocator::defrag() {
    dl_list* tail = head;
    while (tail->next) tail = tail->next;

    dl_list * ptr = tail;
    while (ptr){
        if (ptr->state == FREE){
            if (ptr->prev) {
                if (ptr->prev->state == OCCUPIED) {
                    dl_list *prev_elem = ptr->prev;
                    void *source = prev_elem->block;
                    void *destination = (void *) ((uintptr_t) ptr->block + (ptr->size - prev_elem->size));
                    memmove(destination, source, prev_elem->size);

                    int prev_elem_size = prev_elem->size;
                    prev_elem->size = ptr->size;
                    prev_elem->state = FREE;

                    ptr->block = destination;
                    ptr->state = OCCUPIED;
                    ptr->size = prev_elem_size;
                }
                else{
                    union_list_node(ptr->prev, ptr);
                }
            }
        }

        ptr = ptr->prev;
    }
}

int Allocator::show_blocks(vector<pair<void*, int>>* blocks, STATES state) {
	int blocks_cnt = 0;
	dl_list *ptr = head;
	while (ptr) {
		if (ptr->state == state) {
			pair<void*, int> p = { (ptr->block), ptr->size };
			blocks->emplace_back(p);
			blocks_cnt++;
		}
		ptr = ptr->next;
	}

	return blocks_cnt;
}
