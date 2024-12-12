#include "HashTable.hpp"

HashTable::HashTable(int tableSize) : size(tableSize), table(tableSize, -1) {}

// calculate the hash value from the key, possibly also normalizing the result
int HashTable::hash(int key) { return std::abs(key) % size; }

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