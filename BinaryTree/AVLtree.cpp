#include <iostream>  // preprocesser directive
#define MAX(a, b) (a > b ? a : b)

using std::cin;  // using declaration
using std::cout;

/*

An AVL tree is a self-balancing binary search tree named after its inventors
Adelson-Velsky and Landis. In C++, it can be implemented as a template class for
flexibility with different data types.

 Characteristics:
 * Self-balancing: Maintains balance by ensuring the height difference between
   left and right subtrees is at most 1
 * Binary search tree properties: For each node, left child < node < right
   child.
 * Balance factor: Calculated as height(left subtree) - height(right subtree),
   must be -1, 0, or 1.
 * Rotation operations: Uses single and double rotations to maintain balance.

 Time Complexity
 +------------+----------+-------------------------------+
 | Case       | Time     | Description                   |
 +------------+----------+-------------------------------+
 | Search     | O(log n) | If the tree is unbalanced.    |
 | Insertion  | O(log n) | If the tree is unbalanced.    |
 | Deletion   | O(log n) | If the tree is unbalanced.    |
 | Traversal  | O(n)     | If the tree is unbalanced.    |
 +------------+----------+-------------------------------+
 Space complexity: O(n)

 Pros:
 * Guaranteed O(log n) time complexity for search, insert, and delete
   operations.
 * Faster lookups compared to regular binary search trees for larger datasets.
 * Automatic balancing ensures consistent performance.

 Cons:
 * More complex implementation compared to simple binary search trees.
 * Additional memory overhead for storing height or balance factor.
 * Slightly slower insertions and deletions due to rotation operations.


*/

template <typename T>
class AVLtree {
 private:
  struct Node {
    T data;
    Node* left;
    Node* right;
    int height;

    // constructor
    Node(T value) : data(value), left(nullptr), right(nullptr), height(1) {}
  };

  // data member
  Node* root;

  // member functions
  int getHeight(Node* node) { return node ? node->height : 0; }

  int balanceFactor(Node* node) {
    return getHeight(node->left) - getHeight(node->right);
  }

  void updateHeight(Node* node) {
    node->height = 1 + MAX(getHeight(node->left), getHeight(node->right));
  }

  Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    /*
                      parent
                         |
                      +-----+
                      |  x  |
                      +-----+
                     /       \
                    T1        +-----+
                              |  y  |
                              +-----+
                             /       \
                            T2       T3

    */

    x->right = T2;
    y->left = x;

    /*
                       parent
                          |
                       +-----+
                       |  y  |
                       +-----+
                      /       \
               +-----+        T3
               |  x  |
               +-----+
              /       \
             T1       T2

     */

    updateHeight(x);
    updateHeight(y);

    return y;
  }

  Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    /*
                      parent
                         |
                      +-----+
                      |  y  |
                      +-----+
                     /       \
              +-----+        T3
              |  x  |
              +-----+
             /       \
            T1       T2

    */

    x->right = y;
    y->left = T2;

    /*
                      parent
                         |
                      +-----+
                      |  x  |
                      +-----+
                     /       \
                    T1        +-----+
                              |  y  |
                              +-----+
                             /       \
                            T2       T3

    */

    updateHeight(y);
    updateHeight(x);

    return x;
  }

  Node* balance(Node* node) {
    if (!node) {
      return nullptr;
    }

    updateHeight(node);

    int bf = balanceFactor(node);

    // Left-Left Case
    if (bf > 1) {
      return rotateRight(node);
    }
    // Right-Right Case
    else if (bf < -1) {
      return rotateLeft(node);
    }
    // Left-Right Case
    else if (bf > 1 && balanceFactor(node->left) < 0) {
      node->left = rotateLeft(node->left);
      return rotateRight(node);
    }
    // Right-Left Case
    else if (bf < -1 && balanceFactor(node->right) > 0) {
      node->right = rotateRight(node->right);
      return rotateLeft(node);
    }

    return node;
  }

  Node* insertRecursive(Node* node, T value) {
    if (!node) {
      return new Node(value);
    }

    if (value < node->data) {
      node->left = insertRecursive(node->left, value);
    } else if (value > node->data) {
      node->right = insertRecursive(node->right, value);
    } else {
      return node;  // AVL doesn't allow to have dupes
    }

    return balance(node);
  }

  Node* findMinRecursive(Node* node) const {
    if (node->left) {
      return findMinRecursive(node->left);
    }
    return node;
  }

  Node* findMaxRecursive(Node* node) const {
    if (node->right) {
      return findMaxRecursive(node->right);
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
    // found the node
    else {
      // no child
      if (!node->left && !node->right) {
        Node* temp = node;
        node = nullptr;
        delete temp;
      }
      // one child
      else if (!node->right) {
        Node* temp = node;
        node = node->left;
        delete temp;
      } else if (!node->left) {
        Node* temp = node;
        node = node->right;
        delete temp;
      }
      // two children
      else {
        Node* temp = findMinRecursive(node->right);
        node->data = temp->data;
        node->right = deleteRecursive(node->right, node->data);
      }
    }

    if (!node) {
      return nullptr;
    }
    return balance(node);
  }

  Node* searchRecursive(Node* node, T value) {
    if (!node || node->data == value) {
      return node;
    }

    if (value < node->data) {
      return searchRecursive(node->left, value);
    } else {
      return searchRecursive(node->right, value);
    }
  }

  int countRecursive(Node* node) {
    if (!node) {
      return 0;
    }
    return 1 + countRecursive(node->left) + countRecursive(node->right);
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
  AVLtree() : root(nullptr) {}

  // destructor
  ~AVLtree() { destroyRecursive(root); }

  void add(T valueToInsert) { root = insertRecursive(root, valueToInsert); }

  void remove(T valueToDelete) { root = deleteRecursive(root, valueToDelete); }

  bool lookUp(T valueToSearch) {
    // Node* curr = root;
    // while (curr) {
    //   if (valueToSearch == curr->data) {
    //     return true;
    //   }
    //   if (valueToSearch < curr->data) {
    //     curr = curr->left;
    //   } else if (valueToSearch > curr->data) {
    //     curr = curr->right;
    //   }
    // }
    // return false;

    return searchRecursive(root, valueToSearch);
  }

  int getCount() { return countRecursive(root); }

  int getHeight() { return root->height; }

  T findMin() const {
    if (!root) {
      throw std::runtime_error("Tree is empty\n");
    }
    return findMinRecursive(root)->data;
  }

  T findMax() const {
    if (!root) {
      throw std::runtime_error("Tree is empty\n");
    }
    return findMaxRecursive(root)->data;
  }

  bool isEmpty() const { return root == nullptr; }

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
    for (int i = 1; i <= root->height; i++) {
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

int main() {
  AVLtree<int> avl;
  int input;
  bool isRunning = true;

  // input
  cout << "\nEnter numbers, -1 to stop: \n> ";
  cin >> input;
  while (input != -1) {
    avl.add(input);
    cin >> input;
  }

  // initial tree
  cout << "\nIntial Tree:\n";
  avl.printInfo();

  // output
  while (isRunning) {
    printMenu();
    cout << "Enter your choice: ";
    cin >> input;

    switch (input) {
      case 1: {
        cout << "Enter a number: ";
        cin >> input;

        avl.add(input);
        cout << "\n...Added " << input << "\n";
        cout << "\nCurrent Tree:\n";
        avl.printInfo();
        break;
      }
      case 2: {
        cout << "Enter a number to search: ";
        cin >> input;
        bool res = avl.lookUp(input);
        cout << "\nValue " << input << " is "
             << (res ? "found\n" : "not found\n");
        break;
      }
      case 3: {
        cout << "Enter a number to remove: ";
        cin >> input;

        cout << "\nOriginal Tree:\n";
        avl.printInfo();

        avl.remove(input);

        cout << "\nCurrent Tree:\n";
        avl.printInfo();
        break;
      }
      case 4: {
        cout << "\nCurrent Tree:\n";
        avl.printInfo();
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
  avl.printInfo();
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
> 3 2 1 4 5 -1

Adding 3:
                    +-----+
                    |  3  |
                 0  +-----+

Adding 2:
                    +-----+
                    |  3  |
                 1  +-----+
                   /
            +-----+
            |  2  |
         0  +-----+

Adding 3:
                    +-----+
                    |  3  |
                 2  +-----+
                   /
            +-----+
            |  2  |
         1  +-----+
           /
    +-----+
    |  2  |
 0  +-----+

 balance factor (bf) > 1, do "right rotate"

                    +-----+
                    |  2  |
                 0  +-----+
                   /       \
            +-----+         +-----+
            |  1  |         |  3  |
         0  +-----+      0  +-----+

Adding 4:
                    +-----+
                    |  2  |
                -1  +-----+
                   /       \
            +-----+         +-----+
            |  1  |         |  3  |
         0  +-----+     -1  +-----+
                                   \
                                    +-----+
                                    |  4  |
                                 0  +-----+

Adding 5:
                    +-----+
                    |  2  |
                -2  +-----+
                   /       \
            +-----+         +-----+
            |  1  |         |  3  |
         0  +-----+     -2  +-----+
                                   \
                                    +-----+
                                    |  4  |
                                -1  +-----+
                                           \
                                            +-----+
                                            |  5  |
                                         0  +-----+

 bf < -1, do "left rotate"

                    +-----+
                    |  2  |
                -2  +-----+
                   /       \
            +-----+         +-----+
            |  1  |         |  4  |
         0  +-----+     -2  +-----+
                           /       \
                    +-----+         +-----+
                    |  3  |         |  5  |
                    +-----+     -1  +-----+

Intial Tree:
                    +-----+
                    |  2  |
                -2  +-----+
                   /       \
            +-----+         +-----+
            |  1  |         |  4  |
         0  +-----+     -2  +-----+
                           /       \
                    +-----+         +-----+
                    |  3  |         |  5  |
                    +-----+     -1  +-----+

Height     : 3
Node Count : 5

Pre-Order  : 2 1 4 3 5
In-Order   : 1 2 3 4 5
Post-Order : 1 3 5 4 2
Level Order: 2 1 4 3 5

***** Menu *****
| 1. Add       |
| 2. Lookup    |
| 3. Delete    |
| 4. Print     |
| 5. Exit      |
****************

Enter your choice: 1
Enter a number: 6

...Added 6

                    +-----+
                    |  2  |
                -2  +-----+
                   /       \
            +-----+         +-----+
            |  1  |         |  4  |
         0  +-----+     -2  +-----+
                           /       \
                    +-----+         +-----+
                    |  3  |         |  5  |
                    +-----+     -1  +-----+

Adding 6:
                    +-----+
                    |  2  |
                -2  +-----+
                   /       \
            +-----+         +-----+
            |  1  |         |  4  |
         0  +-----+     -1  +-----+
                           /       \
                    +-----+         +-----+
                    |  3  |         |  5  |
                 0  +-----+     -1  +-----+
                                           \
                                            +-----+
                                            |  6  |
                                         0  +-----+

 bf < -1, do "left rotate"

                    +-----+
                    |  2  | < x
                -2  +-----+
                   /       \
            +-----+         +-----+
            |  1  |         |  4  | < y
         0  +-----+     -1  +-----+
                           /       \
                    +-----+         +-----+
                    |  3  | < T2    |  5  |
                 0  +-----+     -1  +-----+
                                           \
                                            +-----+
                                            |  6  |
                                         0  +-----+

            +-----+         +-----+
      T2 >  |  3  |         |  4  | < y
         0  +-----+     -1  +-----+
                           /       \
                    +-----+         +-----+
                    |  2  | < x     |  5  |
                 0  +-----+     -1  +-----+
                   /                       \
            +-----+                        +-----+
            |  1  |                        |  6  |
            +-----+                     0  +-----+

                            +-----+
                            |  4  | < y
                         0  +-----+
                           /       \
                    +-----+         +-----+
                    |  2  | < x     |  5  |
                 0  +-----+     -1  +-----+
                   /       \               \
            +-----+         +-----+         +-----+
            |  1  |         |  3  |         |  6  |
         0  +-----+      0  +-----+      0  +-----+

Current Tree:
                            +-----+
                            |  4  |
                         0  +-----+
                           /       \
                    +-----+         +-----+
                    |  2  |         |  5  |
                 0  +-----+     -1  +-----+
                   /       \               \
            +-----+         +-----+         +-----+
            |  1  |         |  3  |         |  6  |
         0  +-----+      0  +-----+      0  +-----+

Height     : 3
Node Count : 6

Pre-Order  : 4 2 1 3 5 6
In-Order   : 1 2 3 4 5 6
Post-Order : 1 3 2 6 5 4
Level Order: 4 2 5 1 3 6

***** Menu *****
| 1. Add       |
| 2. Lookup    |
| 3. Delete    |
| 4. Print     |
| 5. Exit      |
****************

Enter your choice: 3
Enter a number to remove: 5

Original Tree:

                            +-----+
                            |  4  |
                         0  +-----+
                           /       \
                    +-----+         +-----+
                    |  2  |         |  5  |
                 0  +-----+     -1  +-----+
                   /       \               \
            +-----+         +-----+         +-----+
            |  1  |         |  3  |         |  6  |
         0  +-----+      0  +-----+      0  +-----+

Height     : 3
Node Count : 6

Pre-Order  : 4 2 1 3 5 6
In-Order   : 1 2 3 4 5 6
Post-Order : 1 3 2 6 5 4
Level Order: 4 2 5 1 3 6

                            +-----+
                            |  4  |  < valueToDelete
                         0  +-----+
                           /       \
                    +-----+         +-----+
                    |  2  |         |  5  |  < temp
                 0  +-----+     -1  +-----+
                   /       \               \
            +-----+         +-----+         +-----+
            |  1  |         |  3  |         |  6  |
         0  +-----+      0  +-----+      0  +-----+

                            +-----+
                            |  5  |  < valueToDelete
                         0  +-----+
                           /       \
                    +-----+         +-----+
                    |  2  |         |  5  |  < temp
                 0  +-----+     -1  +-----+
                   /       \               \
            +-----+         +-----+         +-----+
            |  1  |         |  3  |         |  6  |
         0  +-----+      0  +-----+      0  +-----+

                            +-----+
                            |  5  |
                         1  +-----+
                           /       \
                    +-----+         +-----+
                    |  2  |         |  6  |  < temp
                 0  +-----+      0  +-----+
                   /       \
            +-----+         +-----+
            |  1  |         |  3  |
         0  +-----+      0  +-----+

Current Tree:
                            +-----+
                            |  5  |
                         1  +-----+
                           /       \
                    +-----+         +-----+
                    |  2  |         |  6  |
                 0  +-----+      0  +-----+
                   /       \
            +-----+         +-----+
            |  1  |         |  3  |
         0  +-----+      0  +-----+

Height     : 3
Node Count : 5

Pre-Order  : 5 2 1 3 6
In-Order   : 1 2 3 5 6
Post-Order : 1 3 2 6 5
Level Order: 5 2 6 1 3

***** Menu *****
| 1. Add       |
| 2. Lookup    |
| 3. Delete    |
| 4. Print     |
| 5. Exit      |
****************

Enter your choice: 2
Enter a number to search: 6

Value 6 is found

***** Menu *****
| 1. Add       |
| 2. Lookup    |
| 3. Delete    |
| 4. Print     |
| 5. Exit      |
****************

Enter your choice: 2
Enter a number to search: 4

Value 4 is not found

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
                            +-----+
                            |  5  |
                         1  +-----+
                           /       \
                    +-----+         +-----+
                    |  2  |         |  6  |
                 0  +-----+      0  +-----+
                   /       \
            +-----+         +-----+
            |  1  |         |  3  |
         0  +-----+      0  +-----+

Height     : 3
Node Count : 5

Pre-Order  : 5 2 1 3 6
In-Order   : 1 2 3 5 6
Post-Order : 1 3 2 6 5
Level Order: 5 2 6 1 3

*/