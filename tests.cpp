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

	CleverPtr ptr3 = allocator.alloc(20);
	vector<pair<void*, int>>* busy_blocks5 = new vector<pair<void*, int>>();
	cnt = allocator.show_blocks(busy_blocks5, OCCUPIED);

	assert(cnt == 4);

	CleverPtr ptr4 = allocator.alloc(15);
	vector<pair<void*, int>>* busy_blocks6 = new vector<pair<void*, int>>();
	cnt = allocator.show_blocks(busy_blocks6, OCCUPIED);

	assert(cnt == 5);

	allocator.free(ptr3);

	allocator.free(ptr1);
	vector<pair<void*, int>>* busy_blocks3 = new vector<pair<void*, int>>();
	cnt = allocator.show_blocks(busy_blocks3, OCCUPIED);

	vector<pair<void*, int>>* free_blocks3 = new vector<pair<void*, int>>();
	cnt = allocator.show_blocks(free_blocks3, FREE);
	
	cout << " Free before defrag" << endl;
	for (auto v : *(free_blocks3)) {
		cout << v.first << " " << v.second << endl;
	}

	assert(cnt == 3);
	cout << "Busy before defrag" << endl;
	for (auto v : *(busy_blocks3)) {
		cout << v.first << " " << v.second << endl;
	}

	allocator.defrag();
	vector<pair<void*, int>>* free_blocks1 = new vector<pair<void*, int>>();
	cnt = allocator.show_blocks(free_blocks1, FREE);
	assert(cnt == 1);

	vector<pair<void*, int>>* busy_blocks4 = new vector<pair<void*, int>>();
	cnt = allocator.show_blocks(busy_blocks4, OCCUPIED);

	vector<pair<void*, int>>* free_blocks4 = new vector<pair<void*, int>>();
	cnt = allocator.show_blocks(free_blocks4, FREE);

	cout << " Free after defrag" << endl;
	for (auto v : *(free_blocks4)) {
		cout << v.first << " " << v.second << endl;
	}

	assert(cnt == 1);
	cout << "Busy after defrag" << endl;
	for (auto v : *(busy_blocks4)) {
		cout << v.first << " " << v.second << endl;
	}

	cout << "Done";
}