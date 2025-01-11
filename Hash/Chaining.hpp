#ifndef HASH_TABLE
#define HASH_TABLE

#include <iostream>  // preprocessor directive
#include <vector>

using std::cin;  // using declaration
using std::cout;

/*

What is Collision?

A Collision in data structures, specifically in hash tables or hash maps, occurs
when two different keys generate the same hash value or index in the underlying
array.

The factors affect the probability of a collision:
1. Table Size
2. Hash Function
3. Load Factor: Represents how full the table is. Represents how full the table
   is. The ranges from 0.0 to 1.0, where 0.0 is empty, and 1.0 is full.

   Load Factor = Number of Entries / Number of Buckets


How to handle Collisions?

There are two primary methods to resolve collisions:
1. Chaining / Separate Chaining (This example):
   * Each array index contains a linked list or another data structure
   * When a collision occurs, new elements are added to the list at that index
   * Allows multiple key-value pairs to coexist at the same location
   * Performance depends on the length of the chains

2. Open Addressing (Check the HashTable.cpp):
   Seeks the next empty slot in the array when a collision happens.
   Methods include:
   * Linear Probing: Checks next consecutive slots
   * Quadratic Probing: Uses a quadratic function to find next slot
   * Double Hashing: Uses a second hash function to determine probe sequence

Chaining is a collision resolution technique in hash tables where each bucket
(array index) contains a linked list (or another data structure) of key-value
pairs that hash to the same index.

 Key Characteristics
 * Each array index points to a head of a linked list
 * Multiple elements can be stored at the same array index
 * Elements with the same hash value are chained together in a list
 * Allows handling of hash collisions by storing multiple entries per bucket

 Time Complexity
 +------------+----------+----------+
 | Operation  | Worst*   | Average  |
 +------------+----------+----------+
 | Search     | O(n)     | O(1)     |
 | Insertion  | O(n)     | O(1)     |
 | Deletion   | O(n)     | O(1)     |
 +------------+----------+----------+
 * The worst-case scenario occurs when multiple keys hash to the same index,
   creating a long collision chain.

 Space complexity: O(n)

 Pros:
 * Simple to implement
 * Handles collisions effectively
 * No primary clustering problem
 * Works well with dynamic resizing
 * Allows unlimited number of entries per bucket

 Cons:
 * Requires extra memory for linked list pointers
 * Performance degrades with many collisions
 * Less cache-friendly due to non-contiguous memory
 * Potential for long chains if hash function is poor

*/

class Chaining {
  struct Node {
    int key;
    std::string val;
    Node* next;

    // constructor
    Node(int k, std::string v) : key(k), val(v), next(nullptr) {}
  };

 private:
  int size;
  int count;
  std::vector<Node*> table;

  int hash(int);

 public:
  // constructor
  Chaining(int);

  // destructor
  ~Chaining();

  bool add(int, std::string);
  std::string remove(int);
  std::string search(int);

  int getSize() const;
  int getCount() const;
  void printChaining() const;
};

#endif