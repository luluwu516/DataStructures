#ifndef HASH_TABLE
#define HASH_TABLE

#include <iostream>  // preprocessor directive
#include <vector>

using std::cin;  // using declaration
using std::cout;

/*

A Hashtable is a data structure that implements an associative array or
dictionary, which maps keys to values using a hash function. It provides
efficient data retrieval, insertion, and deletion operations.

 Key Characteristics
 * Key-Value Storage: Stores data in key-value pairs, allowing quick access to
   values based on their unique keys.
 * Hash Function: Uses a hash function to convert keys into array indices,
   enabling fast lookups.
 * Dynamic Sizing: Can dynamically resize to maintain performance as the number
   of elements changes.
 * Unique Keys: Each key in a hashtable must be unique.

 Time Complexity
 +------------+----------+----------+
 | Operation  | Worst*   | Average  |
 +------------+----------+----------+
 | Search     | O(1)     | O(n)     |
 | Insertion  | O(1)     | O(n)     |
 | Deletion   | O(1)     | O(n)     |
 +------------+----------+----------+
 * The worst-case scenario occurs when multiple keys hash to the same index,
   creating a long collision chain.

 Space complexity: O(n)

 Pros:
 * Fast Lookups: O(1) average-case time complexity for insert, delete, and
   search operations
 * Flexible Key Types: Can use various data types as keys
 * Efficient Memory Usage: Provides good space efficiency
 * Dynamic Sizing: Can grow or shrink as needed
 Cons:
 * Potential Collisions: Multiple keys can hash to the same index
 * Worst-Case Performance: Can degrade to O(n) if many collisions occur
 * Higher Memory Overhead: Requires additional space for the hash table
   structure
 * No Guaranteed Order: Elements are not stored in a predictable sequence

*/

const int UNINITIALIZED = -1;
const int DIRTY = -2;

class HashTable {
 private:
  int size;
  std::vector<int> table;
  bool probe(int);
  int searchHelper(int, int);
  bool removeHelper(int, int);

 public:
  HashTable(int);
  
  int hash(int);

  bool add(int);
  bool remove(int);
  int search(int);

  void printTable();
};

#endif