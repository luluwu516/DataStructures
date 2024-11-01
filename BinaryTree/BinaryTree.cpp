#include <iostream>  // preprocessor directive

using std::cin;  // using declaration
using std::cout;

/*
A Binary Tree (BT) is a hierarchical data structure where each node has at most
two children (left and right child) with no specific ordering between nodes,
making it suitable for representing hierarchical relationships like file systems
or expression trees, with a time complexity of O(n) for basic operations.

                      +-----+
                      |  1  | <-- root                   Level 1
                      +-----+
                     /       \
              +-----+         +-----+
              |  2  |         |  3  | <-- internal       Level 2
              +-----+         +-----+       node
             /       \       /       \
      +-----+   +-----+     +-----+   +-----+
      |  4  |   |  5  |     |  6  |   |  7  | <-- leaf   Level 3
      +-----+   +-----+     +-----+   +-----+

 Characteristics:
 * Each node has at most two children (left and right)
 * Each node contains one data element
 * The left subtree contains values less than the parent node
 * The right subtree contains values greater than the parent node
 * Can be balanced or unbalanced

 Different Types (Source: https://www.programiz.com/dsa/binary-tree)
 * Perfect Binary Tree:
   Every internal node has exactly two child nodes and all the leaf nodes are at
   the same level.

                      +-----+
                      |  1  | (2 children)              Level 1
                      +-----+
                     /       \
              +-----+         +-----+
 (2 children) |  2  |         |  3  | (2 children)      Level 2
              +-----+         +-----+
             /       \       /       \
      +-----+   +-----+     +-----+   +-----+
      |  4  |   |  5  |     |  6  |   |  7  |           Level 3
      +-----+   +-----+     +-----+   +-----+

 * Full Binary Tree:
   Every node has 0 or 2 children

                      +-----+
                      |  1  | (2 children)              Level 1
                      +-----+
                     /       \
             +-----+         +-----+
   (0 child) |  2  |         |  3  | (2 children)       Level 2
             +-----+         +-----+
                            /       \
                           +-----+   +-----+
                 (0 child) |  4  |   |  5  | (0 child)  Level 3
                           +-----+   +-----+

 * Complete Binary Tree
   All levels are filled except possibly the last level

                      +-----+
                      |  1  | (2 children)              Level 1
                      +-----+
                     /       \
              +-----+         +-----+
    (1 child) |  2  |         |  3  | (0 children)      Level 2
              +-----+         +-----+
             /
      +-----+
      |  4  | (0 child)                                 Level 3
      +-----+

 * Balanced Binary Tree:
   Height difference between left and right subtrees is at most 1

                         +-----+
                         |  1  | (df = 1)          Level 1
                         +-----+
                        /       \
                 +-----+         +-----+
        (df = 0) |  2  |         |  3  | (df = 0)  Level 2
                 +-----+         +-----+
                /       \
         +-----+   +-----+
(df = 0) |  4  |   |  5  | (df = 0)                Level 3
         +-----+   +-----+

   df = difference between two subtree's heights

 * Unbalanced tree and Right-Skewed Binary Tree:
   Height difference between left and right subtrees is greater than 1.

                    +-----+
                    |  1  | (df = 3) <-- greater than 1
                    +-----+
                            \
                            +-----+
                            |  2  | (df = 2) <-- greater than 1
                            +-----+
                                    \
                                    +-----+
                                    |  3  | (df = 1)
                                    +-----+
                                           \
                                           +-----+
                                           |  4  | (df = 0)
                                           +-----+

 Time Complexity
 +------------+----------+-------------------------------+
 | Case       | Time     | Description                   |
 +------------+----------+-------------------------------+
 | Search     | O(n)     | If the tree is unbalanced.    |
 | Insertion  | O(n)     | If the tree is unbalanced.    |
 | Deletion   | O(n)     | If the tree is unbalanced.    |
 | Traversal  | O(n)     | If the tree is unbalanced.    |
 +------------+----------+-------------------------------+

 Space complexity: O(n)

 Pros:
 * Efficient organization of data
 * Fast search operations - O(log n) (when balanced)
 * Natural recursive structure
 * Supports ordered traversal
 * Memory efficient compared to arrays for dynamic data

 Cons:
 * Can become unbalanced, degrading performance
 * More complex to implement than linear data structures
 * No constant-time access to elements
 * Requires proper memory management
 * Not cache-friendly due to scattered memory allocation

*/

/*

Tree Traversal is the process of visiting each node in a tree data structure
exactly once in a specific order.

Pre-order Traversal:
* Process: Node -> Left subtree -> Right subtree (NLR)
* Uses:
  * Creating a copy of the tree
  * Serializing/Deserializing a tree structure
  * Prefix expression notation

In-order Traversal:
* Process: Left subtree -> Node -> Right subtree (LNR)
* Uses:
  * Produces sorted output for binary search trees (BST)
  * Used in expression tree evaluation
  * Helpful in creating a copy of a binary tree

Post-order Traversal:
* Process: Left subtree -> Right subtree -> Node (LRN)
* Uses:
  * Deleting nodes in a tree (bottom-up approach)
  * Evaluating postfix expressions
  * Computing space used by a directory and its subdirectories

Traversal Example:
                      +-----+
                      |  1  |
                      +-----+
                     /       \
              +-----+         +-----+
              |  2  |         |  3  |
              +-----+         +-----+
             /       \               \
      +-----+   +-----+               +-----+
      |  4  |   |  5  |               |  6  |
      +-----+   +-----+               +-----+

Preorder  (N -> L -> R): 1 -> 2 -> 4 -> 5 -> 3 -> 6
Inorder   (L -> N -> R): 4 -> 2 -> 5 -> 1 -> 3 -> 6
Postorder (L -> R -> N): 4 -> 5 -> 2 -> 6 -> 3 -> 1

*/

template <typename T>
class BinaryTree {
 private:
  // data member
  T* data;
  int rootIndex;
  int count;

  void preorderTraversal(int index) {
    if (index >= count) {
      return;
    }
    cout << data[index] << " ";
    preorderTraversal(2 * index + 1);
    preorderTraversal(2 * index + 2);
  }

  void inorderTraversal(int index) {
    if (index >= count) {
      return;
    }
    inorderTraversal(2 * index + 1);
    cout << data[index] << " ";
    inorderTraversal(2 * index + 2);
  }

  void postorderTraversal(int index) {
    if (index >= count) {
      return;
    }
    postorderTraversal(2 * index + 1);
    postorderTraversal(2 * index + 2);
    cout << data[index] << " ";
  }

 public:
  // constructor
  BinaryTree() : data(nullptr), rootIndex(0), count(0) {}

  // destructor
  ~BinaryTree() {}

  int getCount() { return count; }

  void add(T value) {
    T* temp = new T[++count];
    for (int i = 0; i < count - 1; i++) {
      temp[i] = data[i];
    }
    temp[count - 1] = value;
    data = temp;
  }

  T pop() {
    T lastValue = data[--count];
    T* temp = new T[count];
    for (int i = 0; i < count; i++) {
      temp[i] = data[i];
    }
    return lastValue;
  }

  void printArray() {
    for (int i = 0; i < count; i++) {
      cout << data[i] << " ";
    }
    cout << "\n";
  }

  void printPreOrder() {
    preorderTraversal(rootIndex);
    cout << "\n";
  }

  void printInorder() {
    inorderTraversal(rootIndex);
    cout << "\n";
  }

  void printPostorder() {
    postorderTraversal(rootIndex);
    cout << "\n";
  }
};

int main() {
  // declaration
  BinaryTree<int> bt;
  int num;

  // inpput
  cout << "Enter numbers, EOF to stop: \n> ";
  while (cin >> num) {
    bt.add(num);
  }

  // initial tree
  cout << "\n\nIntial Tree:\n";
  cout << "Array Tree: ";
  bt.printArray();
  cout << "Pre-Order : ";
  bt.printPreOrder();
  cout << "In-Order  : ";
  bt.printInorder();
  cout << "Post-Order: ";
  bt.printPostorder();

  // remove element
  num = bt.pop();

  cout << "\n\nAfter removing " << num << " from the end:\n";
  cout << "Array Tree: ";
  bt.printArray();
  cout << "Pre-Order : ";
  bt.printPreOrder();
  cout << "In-Order  : ";
  bt.printInorder();
  cout << "Post-Order: ";
  bt.printPostorder();

  cout << "\n";

  return 0;
}

// Sample Output:
/*

Enter numbers, EOF to stop:
> 1 2 3 4 5
^D

Intial Tree:
Array Tree: 1 2 3 4 5
Pre-Order : 1 2 4 5 3
In-Order  : 4 2 5 1 3
Post-Order: 4 5 2 3 1


After removing 5 from the end:
Array Tree: 1 2 3 4
Pre-Order : 1 2 4 3
In-Order  : 4 2 1 3
Post-Order: 4 2 3 1

*/