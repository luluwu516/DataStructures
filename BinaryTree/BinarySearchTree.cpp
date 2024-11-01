#include <iostream>  // preprocessor directive
#define MAX(a, b) (a > b ? a : b)

using std::cin;  // using declaration
using std::cout;

/*

A Binary Search Tree (BST) is a specialized binary tree that maintains a strict
ordering property where all nodes in the left subtree must be less than the
parent node, and all nodes in the right subtree must be greater than the parent
node, resulting in an ordered structure that allows for efficient searching
(O(log n) when balanced) and inorder traversal produces sorted output, making it
ideal for applications requiring fast search, insertion, and deletion operations
while maintaining ordered data.

 Characteristics:
 * All nodes follow BST property: left subtree contains smaller values, right
   subtree contains larger values
 * No duplicate values (in this implementation)
 * Inorder traversal gives sorted output
 * Each node has at most two children
 * Maintains a specific ordering of elements

 Time Complexity
 +------------+----------+-------------------------------+
 | Case       | Time     | Description                   |
 +------------+----------+-------------------------------+
 | Search     | O(n)     | If the tree is unbalanced.    |
 | Insertion  | O(n)     | If the tree is unbalanced.    |
 | Deletion   | O(n)     | If the tree is unbalanced.    |
 | Traversal  | O(n)     | If the tree is unbalanced.    |
 +------------+----------+-------------------------------+
 Worst case:
        +-----+
        |  1  |
        +-----+
                \
                +-----+
                |  2  |
                +-----+
                        \
                        +-----+
                        |  3  |
                        +-----+
                                \
                                +-----+
                                |  4  |
                                +-----+

 However, if the tree is balanced:
 +------------+----------+-------------------------------+
 | Case       | Time     | Description                   |
 +------------+----------+-------------------------------+
 | Search     | O(log n) | If the tree is balanced.      |
 | Insertion  | O(log n) | If the tree is balanced.      |
 | Deletion   | O(log n) | If the tree is balanced.      |
 | Traversal  | O(n)     | If the tree is balanced.      |
 +------------+----------+-------------------------------+
 Best case:
                      +-----+
                      |  1  |
                      +-----+
                     /       \
              +-----+         +-----+
              |  2  |         |  3  |
              +-----+         +-----+
             /
      +-----+
      |  4  |
      +-----+

 Space complexity: O(n)

 Pros:
 * Efficient searching, insertion, and deletion operations (O(log n) when
   balanced)
 * Naturally maintains sorted order
 * Flexible size - can grow and shrink dynamically
 * Supports range queries efficiently
 * Easy to implement basic operations

 Cons:
 * Performance degrades if tree becomes unbalanced
 * No constant-time access to elements (unlike arrays)
 * Extra memory for storing node pointers
 * Rebalancing might be needed (not implemented in basic BST)
 * Not cache-friendly due to pointer-based structure

*/

template <typename T>
class BinarySearchTree {
 private:
  struct Node {
    T data;
    Node* left;
    Node* right;

    // constructor
    Node(T value) : data(value), left(nullptr), right(nullptr) {}
  };

  // data members
  Node* root;
  int count;

  // member functions
  Node* findMin(Node* node) {
    while (node->left) {
      node = node->left;
    }
    return node;
  }

  Node* findMax(Node* node) {
    while (node->right) {
      node = node->right;
    }
    return node;
  }

  Node* deleteRecursive(Node* node, T value) {
    if (!node) {
      return nullptr;
    }

    if (value < node->data) {
      node->left = deleteRecursive(node->left, value);
    } else if (value > node->data) {
      node->right = deleteRecursive(node->right, value);
    }
    // found the value
    else {
      // no child
      if (!node->left && !node->right) {
        delete node;
        count--;
        return nullptr;
      }
      // one child
      else if (!node->right) {
        Node* temp = node->left;
        delete node;
        count--;
        return temp;
      } else if (!node->left) {
        Node* temp = node->right;
        delete node;
        count--;
        return temp;
      }
      // two children
      else {
        Node* temp = findMin(node->right);
        node->data = temp->data;
        node->right = deleteRecursive(node->right, node->data);
      }
    }
    return node;
  }

  int getHeightRecursive(Node* node) {
    if (!node) {
      return 0;
    }
    int leftHeight = getHeightRecursive(node->left);
    int rightHeight = getHeightRecursive(node->right);

    return MAX(leftHeight, rightHeight) + 1;
  }

  void destroyRecursive(Node* node) {
    if (!node) {
      return;
    }
    // post-order
    destroyRecursive(node->left);
    destroyRecursive(node->right);
    delete node;
  }

  // traversals helpers
  void preOrderTraversal(Node* node) {
    if (!node) {
      return;
    }
    cout << node->data << " ";
    preOrderTraversal(node->left);
    preOrderTraversal(node->right);
  }

  void inOrderTraversal(Node* node) {
    if (!node) {
      return;
    }
    inOrderTraversal(node->left);
    cout << node->data << " ";
    inOrderTraversal(node->right);
  }

  void postOrderTraversal(Node* node) {
    if (!node) {
      return;
    }
    postOrderTraversal(node->left);
    postOrderTraversal(node->right);
    cout << node->data << " ";
  }

  void printGivenLevel(Node* node, int level) {
    if (!node) {
      return;
    }
    if (level == 1) {
      cout << node->data << " ";
    } else if (level > 1) {
      printGivenLevel(node->left, level - 1);
      printGivenLevel(node->right, level - 1);
    }
  }

 public:
  // constructor
  BinarySearchTree() : root(nullptr), count(0) {}

  // destructor
  ~BinarySearchTree() { destroyRecursive(root); }

  bool add(T value) {
    Node* newNode = new Node(value);

    if (!root) {
      root = newNode;
    } else {
      Node* curr = root;
      while (curr) {
        if (value == curr->data) {
          // BST doesn't allow to have dupes
          cout << "Error! Duplicates are not allowed!!\n";
          return false;
        } else if (value < curr->data) {
          // check if there is a left node
          if (!curr->left) {
            curr->left = newNode;
            curr = curr->left;  // move curr to the newNode
          }
          curr = curr->left;
        } else if (value > curr->data) {
          // check if there is a right node
          if (!curr->right) {
            curr->right = newNode;
            curr = curr->right;  // move curr to the newNode
          }
          curr = curr->right;
        }
      }
    }
    count++;
    return true;
  }

  void remove(T valueToRemoved) {
    root = deleteRecursive(root, valueToRemoved);
  }

  bool lookUp(T valueToSearch) {
    Node* curr = root;
    while (curr) {
      if (valueToSearch == curr->data) {
        return true;
      }
      if (valueToSearch < curr->data) {
        curr = curr->left;
      } else if (valueToSearch > curr->data) {
        curr = curr->right;
      }
    }
    return false;
  }

  int getCount() { return count; }

  int getHeight() { return getHeightRecursive(root); }

  T findMinimum() {
    if (!root) {
      throw std::runtime_error("Tree is empty");
    }
    return findMin(root)->data;
  }

  T findMaximum() {
    if (!root) {
      throw std::runtime_error("Tree is empty");
    }
    return findMax(root)->data;
  }

  bool isEmpty() { return count == 0; }

  void printInfo() {
    cout << "Height     : " << getHeight() << "\n";
    cout << "Node Count : " << getCount() << "\n";
    cout << "\nPre-Order  : ";
    printPreOrder();
    cout << "In-Order   : ";
    printInorder();
    cout << "Post-Order : ";
    printPostorder();
    cout << "Level Order: ";
    printLevelOrder();
  }

  void printLevelOrder() {
    int height = getHeight();
    for (int i = 1; i <= height; i++) {
      printGivenLevel(root, i);
    }
    cout << "\n";
  }

  void printPreOrder() {
    preOrderTraversal(root);
    cout << "\n";
  }
  void printInorder() {
    inOrderTraversal(root);
    cout << "\n";
  }
  void printPostorder() {
    postOrderTraversal(root);
    cout << "\n";
  }
};

// function prototype
void printMenu();

int main() {  // declaration
  BinarySearchTree<int> bst;
  int input;
  bool isRunning = true;
  char buffer[10];

  // input
  cout << "\nEnter numbers, -1 to stop: \n> ";
  cin >> input;
  while (input != -1) {
    bst.add(input);
    cin >> input;
  }

  // initial tree
  cout << "\nIntial Tree:\n";
  bst.printInfo();

  // output
  while (isRunning) {
    printMenu();
    cout << "Enter your choice: ";
    cin >> input;

    switch (input) {
      case 1: {
        cout << "Enter a number: ";
        cin >> input;

        bst.add(input);
        cout << "\n...Added " << input << "\n";
        break;
      }
      case 2: {
        cout << "Enter a number to search: ";
        cin >> input;
        bool res = bst.lookUp(input);
        cout << "\nValue " << input << " is "
             << (res ? "found\n" : "not found\n");
        break;
      }
      case 3: {
        cout << "Enter a number to remove: ";
        cin >> input;

        cout << "\nOriginal Tree:\n";
        bst.printInfo();

        bst.remove(input);

        cout << "\nCurrent Tree:\n";
        bst.printInfo();
        break;
      }
      case 4: {
        cout << "\nCurrent Tree:\n";
        bst.printInfo();
        break;
      }
      case 5: {
        cout << "Exit the program...\n";
        isRunning = false;
        break;
      }
      default: {
        cout << "Invalid input!\n";
        break;
      }
    }
  }

  // Final Tree
  cout << "\nFinal Tree:\n";
  bst.printInfo();
  cout << "\n";

  return 0;
}

void printMenu() {
  cout << "\n***** Menu *****\n";
  cout << "| 1. Add       |\n";
  cout << "| 2. Lookup    |\n";
  cout << "| 3. Delete    |\n";
  cout << "| 4. Print     |\n";
  cout << "| 5. Exit      |\n";
  cout << "****************\n\n";
}

// Sample Output
/*

Enter numbers, -1 to stop:
> 3 1 2 4 -1

Intial Tree:
Height     : 3
Node Count : 4

Pre-Order  : 3 1 2 4
In-Order   : 1 2 3 4
Post-Order : 2 1 4 3
Level Order: 3 1 4 2

                    +-----+
                    |  3  |
                    +-----+
                   /       \
            +-----+         +-----+
            |  1  |         |  4  |
            +-----+         +-----+
                   \
                    +-----+
                    |  2  |
                    +-----+

***** Menu *****
| 1. Add       |
| 2. Lookup    |
| 3. Delete    |
| 4. Print     |
| 5. Exit      |
****************

Enter your choice: 1
Enter a number: 5

...Added 5

                    +-----+
                    |  3  |
                    +-----+
                   /       \
            +-----+         +-----+
            |  1  |         |  4  |
            +-----+         +-----+
                   \               \
                    +-----+         +-----+
                    |  2  |         |  5  |
                    +-----+         +-----+

***** Menu *****
| 1. Add       |
| 2. Lookup    |
| 3. Delete    |
| 4. Print     |
| 5. Exit      |
****************

Enter your choice: 2
Enter a number to search: 6

Value 6 is not found

***** Menu *****
| 1. Add       |
| 2. Lookup    |
| 3. Delete    |
| 4. Print     |
| 5. Exit      |
****************

Enter your choice: 2
Enter a number to search: 2

Value 2 is found

                    +-----+
                    |  3  |
                    +-----+
                   /       \
            +-----+         +-----+
            |  1  |         |  4  |
            +-----+         +-----+
                   \               \
                    +-----+         +-----+
            found > |  2  |         |  5  |
                    +-----+         +-----+

***** Menu *****
| 1. Add       |
| 2. Lookup    |
| 3. Delete    |
| 4. Print     |
| 5. Exit      |
****************

Enter your choice: 3
Enter a number to remove: 3

Original Tree:
Height     : 3
Node Count : 5

 call deleteRecursive function
                    +-----+
                    |  3  | // found
                    +-----+
                   /       \
            +-----+         +-----+
            |  1  |         |  4  |
            +-----+         +-----+
                   \               \
                    +-----+         +-----+
                    |  2  |         |  5  |
                    +-----+         +-----+


                    +-----+
                    |  4  |  // change to temp's value
                    +-----+
                   /       \
            +-----+         +-----+
            |  1  |         |  4  | < temp
            +-----+         +-----+
                   \               \
                    +-----+         +-----+
                    |  2  |         |  5  |
                    +-----+         +-----+

 call the recursive function again
                    +-----+
                    |  4  |
                    +-----+
                   /       \
            +-----+         +-----+
            |  1  |         |  4  | // found
            +-----+         +-----+
                   \               \
                    +-----+         +-----+
                    |  2  |         |  5  | // only right child
                    +-----+         +-----+

                    +-----+
                    |  4  |
                    +-----+
                   /       \
            +-----+         +-----+
            |  1  |         |  5  |  // change to temp's value
            +-----+         +-----+
                   \               \
                    +-----+         +-----+
                    |  2  |         |  5  | < temp
                    +-----+         +-----+

                    +-----+
                    |  4  |
                    +-----+
                   /
            +-----+
            |  1  |
            +-----+
                   \
                    +-----+         +-----+
                    |  2  |         |  5  | < temp  // return
                    +-----+         +-----+

 Done!
                    +-----+
                    |  4  |
                    +-----+
                   /       \
            +-----+         +-----+
            |  1  |         |  5  |
            +-----+         +-----+
                   \
                    +-----+
                    |  2  |
                    +-----+

Pre-Order  : 3 1 2 4 5
In-Order   : 1 2 3 4 5
Post-Order : 2 1 5 4 3
Level Order: 3 1 4 2 5

Current Tree:
Height     : 3
Node Count : 4

Pre-Order  : 4 1 2 5
In-Order   : 1 2 4 5
Post-Order : 2 1 5 4
Level Order: 4 1 5 2

                    +-----+
                    |  4  |
                    +-----+
                   /       \
            +-----+         +-----+
            |  1  |         |  5  |
            +-----+         +-----+
                   \
                    +-----+
                    |  2  |
                    +-----+

***** Menu *****
| 1. Add       |
| 2. Lookup    |
| 3. Delete    |
| 4. Print     |
| 5. Exit      |
****************

Enter your choice: 4

Current Tree:
Height     : 3
Node Count : 4

Pre-Order  : 4 1 2 5
In-Order   : 1 2 4 5
Post-Order : 2 1 5 4
Level Order: 4 1 5 2

***** Menu *****
| 1. Add       |
| 2. Lookup    |
| 3. Delete    |
| 4. Print     |
| 5. Exit      |
****************

Enter your choice: 5
Exit the program...

Final Tree:
Height     : 3
Node Count : 4

Pre-Order  : 4 1 2 5
In-Order   : 1 2 4 5
Post-Order : 2 1 5 4
Level Order: 4 1 5 2

*/