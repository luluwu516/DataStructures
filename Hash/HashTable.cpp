#include "HashTable.hpp"

HashTable::HashTable(int tableSize) : size(tableSize), table(tableSize, -1) {}
/*

For example, tableSize = 5:

            0     1     2     3     4
         +-----+-----+-----+-----+-----+
  Table  |  U  |  U  |  U  |  U  |  U  |  (U: uninitialized)
         +-----+-----+-----+-----+-----+

*/

// calculate the hash value from the key, possibly also normailizing the result
int HashTable::hash(int key) { return key % size; }
/*

Division: Take the key, modulo that key by a value, and then we keep the
remainder as the hash value.

For example, key is 1:

  hashVal = key % 5 = 1 % 5 = 1

            0     1     2     3     4
         +-----+-----+-----+-----+-----+
  Table  |  U  |  1  |  U  |  U  |  U  |  (U: uninitialized)
         +-----+-----+-----+-----+-----+
                  ^

*/

// figures out where to drop the data in the event of a collision
bool HashTable::probe(int key) {
  int hashVal = hash(key);
  int probeVal = (hashVal + 1) % size;

  while (hashVal != probeVal) {
    if (table[probeVal] == UNINITIALIZED || table[probeVal] == DIRTY) {
      table[probeVal] = key;
      return true;
    }
    probeVal = ++probeVal % size;
  }

  return false;
}

// calculate the hash value from the key, possibly also normailizing the result
bool HashTable::add(int key) {
  int index = hash(key);

  if (table[index] == UNINITIALIZED) {
    table[index] = key;
    return true;
  }

  return probe(key);
}
/*

Here is the table:

            0     1     2     3     4
         +-----+-----+-----+-----+-----+
  Table  |  U  |  1  |  U  |  U  |  U  |  (U: uninitialized)
         +-----+-----+-----+-----+-----+

Add 2, 3, 4, 5:

            0     1     2     3     4
         +-----+-----+-----+-----+-----+
  Table  |  5  |  1  |  2  |  3  |  4  |
         +-----+-----+-----+-----+-----+

If we want to add 6...
            0     1     2     3     4
         +-----+-----+-----+-----+-----+
  Table  |  5  |  1  |  2  |  3  |  4  |
         +-----+-----+-----+-----+-----+
                  ^
                It's occupied

Then we will iterate the table until we find an empty slot or we back to the
first slot

            0     1     2     3     4
         +-----+-----+-----+-----+-----+
  Table  |  5  |  1  |  2  |  3  |  4  |
         +-----+-----+-----+-----+-----+
                        ^

            0     1     2     3     4
         +-----+-----+-----+-----+-----+
  Table  |  5  |  1  |  2  |  3  |  4  |
         +-----+-----+-----+-----+-----+
                              ^

            0     1     2     3     4
         +-----+-----+-----+-----+-----+
  Table  |  5  |  1  |  2  |  3  |  4  |
         +-----+-----+-----+-----+-----+
                                    ^

            0     1     2     3     4
         +-----+-----+-----+-----+-----+
  Table  |  5  |  1  |  2  |  3  |  4  |
         +-----+-----+-----+-----+-----+
            ^

            0     1     2     3     4
         +-----+-----+-----+-----+-----+
  Table  |  5  |  1  |  2  |  3  |  4  |
         +-----+-----+-----+-----+-----+
                  ^
                we back to the first slot!

The table is completely full. Return false.

*/

bool HashTable::removeHelper(int key, int index) {
  int start = index;
  index = (index + 1) % size;
  while (start != index) {
    if (table[index] == key) {
      table[index] = DIRTY;
      return index;
    }
    if (table[index] == UNINITIALIZED) {
      return false;
    }
    index = (index + 1) % size;
  }
  return false;
}

// remove the value, use hash function
bool HashTable::remove(int key) {
  int index = hash(key);

  if (table[index] == key) {
    table[index] = DIRTY;
    return true;
  }

  return removeHelper(key, index);
}
/*

Here is the table:

            0     1     2     3     4
         +-----+-----+-----+-----+-----+
  Table  |  5  |  1  |  2  |  3  |  4  |
         +-----+-----+-----+-----+-----+
                        ^

If we delete 2, we'll flag it with a value marking that cell as dirty

            0     1     2     3     4
         +-----+-----+-----+-----+-----+
  Table  |  5  |  1  |  D  |  3  |  4  |  (D: dirty)
         +-----+-----+-----+-----+-----+
                        ^
                    It was occupied before

Marking the cell as formerly occupied means that when we are resolving a
collision, we'll consider that cell as occupied and keep on digging.
When inserting a value, we'll treat the cell as empty and we can place a value
there.


*/

int HashTable::searchHelper(int key, int index) {
  int start = index;
  index = (index + 1) % size;
  while (start != index) {
    if (table[index] == key) {
      return index;
    }
    if (table[index] == UNINITIALIZED) {
      return -1;
    }
    index = (index + 1) % size;
  }
  return -1;
}

// return the data found associated with the key
int HashTable::search(int key) {
  int index = hash(key);

  if (table[index] == key) {
    return index;
  }

  return searchHelper(key, index);
}
/*

            0     1     2     3     4
         +-----+-----+-----+-----+-----+
  Table  |  5  |  1  |  D  |  3  |  4  |  (D: dirty)
         +-----+-----+-----+-----+-----+

Assume we add 10 and delete 5

            0     1     2     3     4
         +-----+-----+-----+-----+-----+
  Table  |  D  |  1  | 10  |  3  |  4  |  (D: dirty)
         +-----+-----+-----+-----+-----+

Now, we are looking for 10. The hash value is 10 % 5 = 0

            0     1     2     3     4
         +-----+-----+-----+-----+-----+
  Table  |  D  |  1  | 10  |  3  |  4  |  (D: dirty)
         +-----+-----+-----+-----+-----+
            ^
        It's not 10 but it's marked as dirty, so we will keep digging

            0     1     2     3     4
         +-----+-----+-----+-----+-----+
  Table  |  D  |  1  | 10  |  3  |  4  |  (D: dirty)
         +-----+-----+-----+-----+-----+
                  ^

            0     1     2     3     4
         +-----+-----+-----+-----+-----+
  Table  |  D  |  1  | 10  |  3  |  4  |  (D: dirty)
         +-----+-----+-----+-----+-----+
                        ^
                      found! Return true.

*/

void HashTable::printTable() {
  for (int i = 0; i < size; i++) {
    std::cout << "Index " << i << ": ";
    int val = table[i];
    if (val == UNINITIALIZED) {
      cout << "(Empty)";
    } else if (val == DIRTY) {
      cout << "(Dirty)";
    } else {
      cout << std::to_string(val);
    }
    cout << "\n";
  }
};