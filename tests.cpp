#include <cassert>
#include "tests.h"

void Tests::run() {
    Allocator allocator = Allocator(100);

    CleverPtr ptr = allocator.alloc(10);
    vector<pair<int, int>> busy_blocks = vector<pair<int, int>>();
    int cnt = allocator.show_blocks(&(busy_blocks), OCCUPIED);

    assert(busy_blocks.size()==1);

    CleverPtr ptr1 = allocator.alloc(10);
    vector<pair<int, int>> busy_blocks1 = vector<pair<int, int>>();
    cnt = allocator.show_blocks(&(busy_blocks1), OCCUPIED);

    assert(busy_blocks1.size()==2);

    CleverPtr ptr2 = allocator.alloc(10);
    vector<pair<int, int>> busy_blocks2 = vector<pair<int, int>>();
    cnt = allocator.show_blocks(&(busy_blocks2), OCCUPIED);

    assert(busy_blocks2.size()==3);

    allocator.free(ptr1);
    vector<pair<int, int>> busy_blocks3 = vector<pair<int, int>>();
    cnt = allocator.show_blocks(&(busy_blocks3), OCCUPIED);

    assert(busy_blocks3.size()==2);

    allocator.free(ptr2);
    vector<pair<int, int>> free_blocks = vector<pair<int, int>>();
    cnt = allocator.show_blocks(&(free_blocks), FREE);

    assert(free_blocks.size()==3);

    allocator.defrag();
    vector<pair<int, int>> free_blocks1 = vector<pair<int, int>>();
    cnt = allocator.show_blocks(&(free_blocks1), FREE);
    assert(free_blocks1.size()==2);

    cout << "Well done!";
}
