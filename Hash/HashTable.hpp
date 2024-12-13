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
 | Search     | O(n)     | O(1)     |
 | Insertion  | O(n)     | O(1)     |
 | Deletion   | O(n)     | O(1)     |
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


Collision Resolution Techniques:
1. Chaining
   * Each hash table slot is a linked list
   * Multiple items can exist at same index

2. Open Addressing
   * Probe for next available slot
   * Linear probing
   * Quadratic probing

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

/*

Hash Functions:
Hashing is a technique of converting input data of arbitrary size into a
fixed-size string of characters, which acts like a unique digital fingerprint of
the data.


Take 123456789 as an example:

1. MD5 and SHA
   * MD5 (Message Digest Algorithm 5):
     hashValue = 25f9e794323b453885f5181f1b624d0b

   * SHA (Secure Hash Algorithm):
     hashValue = f7c3bc1d808e04732adf679965ccc34ca7ae3441 (SHA1)

2. Division:
   Take the key, modulo that key by a value, and then we keep the remainder as
   the hash value.

   Assume the value is 10:
   hashValue = 123456789 % 10 = 9

3. Extraction:
   Take a part of the key and use that as our hash value.

   Assume we extract the first 3:
   hashValue = 123

4. Mid-Square:
   Square the key and take the middle 3 as our hash value.

   123456789 * 123456789 = 15241578750190521
   hashValue = 875

5. Folding:
   Folding will break the key into x parts and then combine those parts back
   together.

   * Shift Folding:
     Break the key into 3 parts, then add those parts together.

      hashValue = 123 + 456 + 789 = 1368

   * Boundary Folding:
     Like Shift folding, except we put the parts on separate parts of a piece of
     paper and fold that paper together. (Think about a Tri-fold Menu)

     hashValue = 123 + 654 + 789 = 1566

6. Radix Transformation:
   Take the number, change into a different base.

   hashValue = 123456789 -- Base64 --> MTIzNDU2Nzg5

*/