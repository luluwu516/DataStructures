#include "Chaining.hpp"

int Chaining::hash(int key) { return key % size; }

int Chaining::getSize() const { return size; }

int Chaining::getCount() const { return count; }

Chaining::Chaining(int tableSize)
    : size(tableSize), count(0), table(tableSize, nullptr) {}
/*
if tableSize = 2

Two-bucket chaining hashtable is created...

+=====+
|  0  |-(Empty)
+=====+
+=====+
|  1  |-(Empty)
+=====+

*/

Chaining::~Chaining() {
  for (int i = 0; i < size; i++) {
    // access to each node in the menu
    Node* curr = table[i];
    // clear the linked list
    while (curr) {
      Node* temp = curr;
      curr = curr->next;
      delete temp;
    }
  }
}
/*
It is a linked-list hashtable. To prevent memory leak, we have to free the node
one by one.

  +=====+ +-----+------+
> |  0  |-|  1  + Alan |
  +=====+ +-----+------+
  +=====+ +-----+------+ +------+------+
  |  1  |-|  1  + Andy |-|  11  + Judy |
  +=====+ +-----+------+ +------+------+

  +=====+
> |  0  |-(Empty)
  +=====+
  +=====+ +-----+------+ +------+------+
  |  1  |-|  1  + Andy |-|  11  + Judy |
  +=====+ +-----+------+ +------+------+

  +=====+
  |  0  |-(Empty)
  +=====+
  +=====+ +-----+------+ +------+------+
> |  1  |-|  1  + Andy |-|  11  + Judy |
  +=====+ +-----+------+ +------+------+

  +=====+
  |  0  |-(Empty)
  +=====+
  +=====+ +-----+------+
> |  1  |-|  1  + Andy |
  +=====+ +-----+------+

  +=====+
  |  0  |-(Empty)
  +=====+
  +=====+
> |  1  |-(Empty)
  +=====+

*/

bool Chaining::add(int key, std::string val) {
  Node* newNode = new Node(key, val);

  // use modulo to find the correct index
  int index = hash(key);

  if (table[index]) {  // if the bucket is not empty
    Node* curr = table[index];
    Node* prev = nullptr;

    // iterate to the end of the linked list
    while (curr && key >= curr->key) {
      // if find the node with the same data, replace it with the new data and
      // then return false
      if (curr->key == key) {
        curr->val = val;
        delete newNode;
        return false;
      }
      // if not, move to the next node
      prev = curr;
      curr = curr->next;
    }
    if (prev) {
      prev->next = newNode;
    } else {
      table[index] = newNode;
    }
    newNode->next = curr;
    count++;
    return true;
  } else {  // if the bucket is empty
    // assign the new node to it
    table[index] = newNode;
    count++;
    return true;
  }
}
/*

Adding 11 as key and "Judy" as value:

+=====+
|  0  |-(Empty)
+=====+
+=====+ +------+------+
|  1  |-|  11  + Judy |
+=====+ +------+------+

============================================================
Adding 1 as key and "Andy" as value:

+=====+
|  0  |-(Empty)
+=====+
+=====+ +-----+------+ +------+------+
|  1  |-|  1  + Andy |-|  11  + Judy |
+=====+ +-----+------+ +------+------+

============================================================
Adding 6 as key and "Candy" as value:

+=====+
|  0  |-(Empty)
+=====+
+=====+ +-----+------+ +-----+-------+ +------+------+
|  1  |-|  1  + Andy |-|  6  + Candy |-|  11  + Judy |
+=====+ +-----+------+ +-----+-------+ +------+------+

============================================================
Adding 6 as key and "Mandy" as value:

+=====+
|  0  |-(Empty)
+=====+
+=====+ +-----+------+ +-----+-------+ +------+------+
|  1  |-|  1  + Andy |-|  6  + Candy |-|  11  + Judy |
+=====+ +-----+------+ +-----+-------+ +------+------+
                          ^
                     duplicated!

Old value is replaced...

+=====+
|  0  |-(Empty)
+=====+
+=====+ +-----+------+ +-----+-------+ +------+------+
|  1  |-|  1  + Andy |-|  6  + Mandy |-|  11  + Judy |
+=====+ +-----+------+ +-----+-------+ +------+------+

*/

std::string Chaining::remove(int key) {
  // use modulo to find the correct index
  int index = hash(key);

  // access to the correct bucket
  Node* curr = table[index];
  Node* prev = nullptr;  // for keeping the linked list structure
  while (curr && key >= curr->key) {
    // if found the data
    if (curr->key == key) {
      // store the data value (we will return it later)
      std::string deletedData = curr->val;
      // first, skip the current data
      if (prev) {
        // if prev is not nullptr, connect the previous node's next to the
        // current node's next
        prev->next = curr->next;
      } else {
        // else, which means the data is in the first node, assign the current
        // node's next to the bucket
        table[index] = curr->next;
      }
      // store the node to be deleted
      Node* temp = curr;

      // move curr to the next node
      curr = curr->next;

      // delete the node
      delete temp;
      count--;

      return deletedData + " is removed";
    }
    prev = curr;
    curr = curr->next;
  }

  // after iterating to the end, if nothing found, return false
  return "No data found";
}
/*

Removing 6...

First, find the node

+=====+
|  0  |-(Empty)
+=====+
+=====+ +-----+------+ +-----+-------+ +------+------+
|  1  |-|  1  + Andy |-|  6  + Mandy |-|  11  + Judy |
+=====+ +-----+------+ +-----+-------+ +------+------+
                          ^
                        found!

Removing the node with that key

+=====+
|  0  |-(Empty)
+=====+
+=====+ +-----+------+ +------+------+
|  1  |-|  1  + Andy |-|  11  + Judy |
+=====+ +-----+------+ +------+------+

============================================================
Removing 7...

First, find the node

+=====+
|  0  |-(Empty)
+=====+
+=====+ +-----+------+ +-----+-------+ +------+------+
|  1  |-|  1  + Andy |-|  6  + Mandy |-|  11  + Judy |
+=====+ +-----+------+ +-----+-------+ +------+------+
                                      ^
                               No data found!

Return "No data found"

*/

std::string Chaining::search(int key) {
  int index = hash(key);
  Node* curr = table[index];
  // iterate the linked list
  while (curr) {
    // if find the data, return true
    if (curr->key == key) {
      return curr->val + " is found";
    }
    curr = curr->next;
  }

  // after iterating to the end, if nothing found, return false
  return "No data found";
}
/*

Searching 6...

+=====+
|  0  |-(Empty)
+=====+
+=====+ +-----+------+ +-----+-------+ +------+------+
|  1  |-|  1  + Andy |-|  6  + Mandy |-|  11  + Judy |
+=====+ +-----+------+ +-----+-------+ +------+------+
                          ^
                        found!

Return the value, "Mandy"

============================================================
Searching 7...

+=====+
|  0  |-(Empty)
+=====+
+=====+ +-----+------+ +-----+-------+ +------+------+
|  1  |-|  1  + Andy |-|  6  + Mandy |-|  11  + Judy |
+=====+ +-----+------+ +-----+-------+ +------+------+
                                      ^
                               No data found!

Return "No data found"

*/

void Chaining::printChaining() const {
  for (int i = 0; i < size; i++) {
    if (table[i]) {
      cout << "[" << i << "]: ";
      Node* curr = table[i];
      while (curr) {
        cout << curr->key << "-" << curr->val << " ";
        curr = curr->next;
      }
    } else {
      cout << "[" << i << "]: (Empty)";
    }
    cout << "\n";
  }
}