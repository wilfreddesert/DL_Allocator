# Doubly-Linked List Allocator

This is a simple memory allocator used to allocate memory of a specified size following the first-fit principle, manage the allocated memory and perform simple optimization. 

## Getting started

### Requirements

С++11 or higher
cmake 3.11 or higher

### Usage

#### Include the following header:
```
#include "allocator.h"
```
#### Create an instance of the Allocator class:
```
Allocator allocator = Allocator(size);
```
where size — is an integer variable that sets the total amount of memory for the allocator.  

#### You can also use the default constructor:
```
Allocator allocator = Allocator();
```
In this default scenario 100 bytes will be allocated.

To allocate a specified amount of memory from the total amount, you need to call the `alloc` method of the Allocator class:
```
CleverPtr alloc(size_t size);
```
This method will return a CleverPtr object linking to the allocated memory. 

To delete the object from memory, you need to use the `free` method of the Allocator class:

```
void free(CleverPtr&);
```
You need to pass the reference to the CleverPtr object you want to delete as an argument.

To solve the issue related to memory fragmentation, you can use the `defrag` method:

```
void defrag();
```

## Running tests

To run the tests, you need to:

#### Include the following header

``` 
#include "tests.h" 
```
#### Create an instance of the Test class

```
Tests tests = Tests();
```
#### Call the `run` method:

```
tests.run();
```

## Authors
### Valeria Rakhmatova
### Timur Sharapov
##### Merry Christmas!