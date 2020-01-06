#include <cassert>
#include "tests.h"

void Tests::run() {
	Allocator allocator = Allocator(100);

	CleverPtr ptr = allocator.alloc(10);
	vector<pair<void*, int>>* busy_blocks = new vector<pair<void*, int>>();
	int cnt = allocator.show_blocks(busy_blocks, OCCUPIED);

	assert(cnt == 1);

	CleverPtr ptr1 = allocator.alloc(10);
	vector<pair<void*, int>>* busy_blocks1 = new vector<pair<void*, int>>();
	cnt = allocator.show_blocks(busy_blocks1, OCCUPIED);

	assert(cnt == 2);

	CleverPtr ptr2 = allocator.alloc(10);
	vector<pair<void*, int>>* busy_blocks2 = new vector<pair<void*, int>>();
	cnt = allocator.show_blocks(busy_blocks2, OCCUPIED);

	assert(cnt == 3);

	allocator.free(ptr1);
	vector<pair<void*, int>>* busy_blocks3 = new vector<pair<void*, int>>();
	cnt = allocator.show_blocks(busy_blocks3, OCCUPIED);

	assert(cnt == 2);

	allocator.defrag();
	vector<pair<void*, int>>* free_blocks1 = new vector<pair<void*, int>>();
	cnt = allocator.show_blocks(free_blocks1, FREE);
	assert(cnt == 1);

	cout << "Done\n";
}