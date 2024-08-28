#include <iostream>  // preprocess directive

using std::cin;  // using declaration
using std::cout;

/*
 A node object for a doubly linked list holds data and two pointers.
 One stores the previous node and another stores the next node.
             +---------+---------+---------+
 nullptr <---|- *prev  |  data1  |  *next -|---> +---------+---------+---------+
             +---------+---------+---------+ <---|- *prev  |  data2  |  *next -|---> nullptr
                                                 +---------+---------+---------+
*/
class Node {  // struct can do the same
 public:
  int data;
  Node* next;
  Node* prev;

  // constructor
  Node(int newData, Node* nextPtr = nullptr, Node* prevPtr = nullptr)
      : data(newData), next(nextPtr), prev(prevPtr) {}  // initializer list
};

/*
 A doubly-linked list object holds two pointers (head & tail), which storing
 the beginning and the end of the node, which connects to all other nodes.
                      +---------+
                      |  *head  |                          +---------+
                      +----|----+                          |  *tail  |
                           V                               +----|----+
             +---------+---------+---------+                    V
 nullptr <---|- *prev  |  data1  |  *next -|---> +---------+---------+---------+
             +---------+---------+---------+ <---|- *prev  |  data2  |  *next -|---> nullptr
                                                 +---------+---------+---------+

*/

class DoublyLinkedList {
 public:
  // constructor
  DoublyLinkedList() : head(nullptr), tail(nullptr), count(0) {}

  // deconstructor
  ~DoublyLinkedList() {
    // create a pointer and start deleting nodes from the head
    Node* curr = head;
    while (curr) {
      head = head->next;
      delete curr;
      curr = head;
    }
  }

  bool isEmpty() { return head == nullptr; }

  void addToHead(int data) {
    // create a new node
    Node* newNode = new Node(data);
    // if the list is not empty, connect the original first node to the new one.
    if (head) {
      head->prev = newNode;
    }
    // set the new node's next to the current head
    newNode->next = head;
    // set the new node as the new head
    head = newNode;

    // if it IS the first node, make it the tail as well
    if (!tail) {
      tail = newNode;
    }
    count++;  // update the count
  }

  void addToTail(int data) {
    // create a new node
    Node* newNode = new Node(data);
    // if the list is not empty
    if (tail) {
      // connect the original last node to the new one
      tail->next = newNode;
      // set the new node's prev to the current tail
      newNode->prev = tail;
      // move the tail to the new node
      tail = newNode;
    }
    // if it IS the first node, make it the tail and the head
    else {
      head = tail = newNode;
    }
    count++;  // update the count
  }

  int popFromHead() {
    if (!head) {
      throw std::runtime_error("The Doubly Linked List is empty.\n");
    }
    int HeadData = head->data;
    Node* temp = head;

    // if there's only one node in the list
    if (head == tail) {
      head = tail = nullptr;
    } else {
      // move the head to the original second node (the new head)
      head = head->next;
      // Set the new head's prev to point to nullptr since it's head right now
      head->prev = nullptr;
    }
    delete temp;  // delete the original head
    count--;      // update the count
    return HeadData;
  }

  int popFromTail() {
    if (!tail) {
      throw std::runtime_error("The Doubly Linked List is empty.\n");
    }
    int tailData = tail->data;
    Node* temp = tail;

    // if there's only one node in the list
    if (head == tail) {
      head = tail = nullptr;
    } else {
      // move the tail to the second-to-last node (the new tail)
      tail = tail->prev;
      // set the new tail's next to point to nullptr since it's tail right now
      tail->next = nullptr;
    }
    delete temp;  // delete the original tail
    count--;      // update the count
    return tailData;
  }

  void printDLLForward() {
    if (isEmpty()) {
      cout << "(Empty)";
      return;
    }
    cout << "NULL -> ";
    // create a cursor and print from the head to the end
    Node* curr = head;
    while (curr) {
      cout << curr->data << " -> ";
      curr = curr->next;
    }

    cout << "NULL" << std::endl;
  }

  void printDLLReverse() {
    if (isEmpty()) {
      cout << "(Empty)";
      return;
    }
    cout << "NULL -> ";
    // create a cursor and print from the head to the end
    Node* curr = tail;
    while (curr) {
      cout << curr->data << " -> ";
      curr = curr->prev;
    }

    cout << "NULL" << std::endl;
  }

 private:
  Node* head;
  Node* tail;
  int count;
};

int main() {
  // declaration
  DoublyLinkedList doublyLinkedList;
  int num, headData, tailData;

  // input
  cout << "\nEnter numbers (-1 to stop): \n> ";
  cin >> num;
  while (num != -1) {
    doublyLinkedList.addToTail(num);
    cout << "> ";
    cin >> num;
  }

  // processing and output
  cout << "\nNumbers in the linked list:\n";
  doublyLinkedList.printDLLForward();

  cout << "\nDoubly Linked List after deleting from the beginning:\n";
  try {
    num = doublyLinkedList.popFromHead();
    doublyLinkedList.printDLLForward();
    cout << "Deleted number: " << num << "\n";
  } catch (std::exception& e) {
    cout << "Error! " << e.what();
  }

  cout << "\nDoubly Linked List after deleting from the end:\n";
  try {
    num = doublyLinkedList.popFromTail();
    doublyLinkedList.printDLLForward();
    cout << "Deleted number: " << num << "\n";
  } catch (std::exception& e) {
    cout << "Error! " << e.what();
  }

  cout << "\nEnter the number to the beginning: ";
  cin >> num;
  cout << "Doubly Linked List after adding the number to the beginning:\n";
  doublyLinkedList.addToHead(num);
  doublyLinkedList.printDLLForward();

  cout << "\nEnter the number to the end: ";
  cin >> num;
  cout << "Doubly Linked List after adding the number to the end:\n";
  doublyLinkedList.addToTail(num);
  doublyLinkedList.printDLLForward();

  cout << "\nFinal Doubly Linked List: \n";
  doublyLinkedList.printDLLForward();
  cout << "Print reversed: \n";
  doublyLinkedList.printDLLReverse();
  cout << "\n";

  return 0;
}

// Sample Output 1:
/*

Enter numbers (-1 to stop):
> 10
> 15
> 5
> 2
> 4
> -1

Numbers in the linked list:
NULL -> 10 -> 15 -> 5 -> 2 -> 4 -> NULL

Doubly Linked List after deleting from the beginning:
NULL -> 15 -> 5 -> 2 -> 4 -> NULL
Deleted number: 10

Doubly Linked List after deleting from the end:
NULL -> 15 -> 5 -> 2 -> NULL
Deleted number: 4

Enter the number to the beginning: 7
Doubly Linked List after adding the number to the beginning:
NULL -> 7 -> 15 -> 5 -> 2 -> NULL

Enter the number to the end: 24
Doubly Linked List after adding the number to the end:
NULL -> 7 -> 15 -> 5 -> 2 -> 24 -> NULL

Final Doubly Linked List:
NULL -> 7 -> 15 -> 5 -> 2 -> 24 -> NULL
Print reversed:
NULL -> 24 -> 2 -> 5 -> 15 -> 7 -> NULL

*/

// Sample Output 2:
/*

Enter numbers (-1 to stop):
> -1

Numbers in the linked list:
(Empty)
Doubly Linked List after deleting from the beginning:
Error! The Doubly Linked List is empty.

Doubly Linked List after deleting from the end:
Error! The Doubly Linked List is empty.

Enter the number to the beginning: 4
Doubly Linked List after adding the number to the beginning:
NULL -> 4 -> NULL

Enter the number to the end: 12
Doubly Linked List after adding the number to the end:
NULL -> 4 -> 12 -> NULL

Final Doubly Linked List:
NULL -> 4 -> 12 -> NULL
Print reversed:
NULL -> 12 -> 4 -> NULL

*/