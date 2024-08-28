#include <iostream>  // preprocess directive

using std::cin;  // using declaration
using std::cout;

/*
 A node object holds a data and pointer to the next node.
 Nodes can be connected with the pointers.
 +---------+---------+      +---------+---------+
 |  data1  |  *next -|--->  |  data2  |  *next -|---> nullptr
 +---------+---------+      +---------+---------+
*/
struct Node {  // class with the public data member can do the same
  int data;
  Node* next;

  // constructor
  Node(int newData, Node* nextPtr = nullptr)
      : data(newData), next(nextPtr) {}  // initializer list
};

/*
 A linked list object holds a pointer (head) storing the beginning node, which
 connects to all other nodes.
 +--------+      +---------+---------+      +---------+---------+
 |  head -|--->  |  data1  |  *next -|--->  |  data2  |  *next -|---> nullptr
 +--------+      +---------+---------+      +---------+---------+
*/
class LinkedList {
 public:
  // constructor
  LinkedList() : head(nullptr), count(0) {}

  // destructor
  ~LinkedList() {
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
    // make the new node link to the head and make head link to the new node
    Node* newNode = new Node(data, head);
    head = newNode;
    count++;  // update the count
  }

  void addToTail(int data) {
    Node* newNode = new Node(data);
    if (isEmpty()) {
      head = newNode;
    } else {
      // use the pointer to iterate to the end of the list
      Node* curr = head;
      while (curr->next) {
        curr = curr->next;
      }
      // connect the last node to the new node
      curr->next = newNode;
    }
    count++;  // update the count
  }

  int popFromHead() {
    if (isEmpty()) {
      throw std::runtime_error("The Linked List is empty.\n");
    } else {
      int headData = head->data;
      Node* temp = head;
      // move the head to the original second node (the latest head)
      head = head->next;
      delete temp;  // delete the original head
      count--;      // update the count
      return headData;
    }
  }

  int popFromTail() {
    if (isEmpty()) {
      throw std::runtime_error("The Linked List is empty.\n");
    } else {
      Node* curr = head;
      // traverse to the second-to-last node
      while (curr->next->next) {
        curr = curr->next;
      }
      int tailData = curr->next->data;
      delete curr->next;     // delete the last node
      curr->next = nullptr;  // set the second-to-last node's next to nullptr
      count--;               // update the count
      return tailData;
    }
  }

  bool isInList(int dataToSearch) {
    // create a pointer and search from the head to the end
    Node* curr = head;
    while (curr->next) {
      if (curr->data == dataToSearch) {
        return true;
      }
      curr = curr->next;
    }
    return false;
  }

  void printLinkedList() {
    if (isEmpty()) {
      cout << "(Empty)";
      return;
    }
    // create a cursor and print from the head to the end
    Node* curr = head;
    while (curr) {
      cout << curr->data << " -> ";
      curr = curr->next;
    }

    cout << "NULL" << std::endl;
  }

 private:
  Node* head;
  int count;
};

int main() {
  // declaration
  LinkedList linkedlist;
  int num, headData, tailData;

  // input
  cout << "\nEnter numbers (-1 to stop): \n> ";
  cin >> num;
  while (num != -1) {
    linkedlist.addToTail(num);
    cout << "> ";
    cin >> num;
  }

  // processing and output
  cout << "\nNumbers in the linked list:\n";
  linkedlist.printLinkedList();

  cout << "\nLinked list after deleting from the beginning:\n";
  try {
    num = linkedlist.popFromHead();
    linkedlist.printLinkedList();
    cout << "Deleted number: " << num << "\n";
  } catch (std::exception& e) {
    cout << "Error! " << e.what();
  }

  cout << "\nLinked list after deleting from the end:\n";
  try {
    num = linkedlist.popFromTail();
    linkedlist.printLinkedList();
    cout << "Deleted number: " << num << "\n";
  } catch (std::exception& e) {
    cout << "Error! " << e.what();
  }

  cout << "\nEnter the number to the beginning: ";
  cin >> num;
  cout << "Linked list after adding the number to the beginning:\n";
  linkedlist.addToHead(num);
  linkedlist.printLinkedList();

  cout << "\nEnter the number to the end: ";
  cin >> num;
  cout << "Linked list after adding the number to the end:\n";
  linkedlist.addToTail(num);
  linkedlist.printLinkedList();
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
10 -> 15 -> 5 -> 2 -> 4 -> NULL

Linked list after deleting from the beginning:
15 -> 5 -> 2 -> 4 -> NULL
Deleted number: 10

Linked list after deleting from the end:
15 -> 5 -> 2 -> NULL
Deleted number: 4

Enter the number to the beginning: 7
Linked list after adding the number to the beginning:
7 -> 15 -> 5 -> 2 -> NULL

Enter the number to the end: 24
Linked list after adding the number to the end:
7 -> 15 -> 5 -> 2 -> 24 -> NULL

*/

// Sample Output 2:
/*

Enter numbers (-1 to stop):
> -1

Numbers in the linked list:
(Empty)
Linked list after deleting from the beginning:
Error! The Linked List is empty.

Linked list after deleting from the end:
Error! The Linked List is empty.

Enter the number to the beginning: 1
Linked list after adding the number to the beginning:
1 -> NULL

Enter the number to the end: 2
Linked list after adding the number to the end:
1 -> 2 -> NULL

*/