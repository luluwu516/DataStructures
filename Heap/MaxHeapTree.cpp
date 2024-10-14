#include <iostream>  // preprocessor directive
#include <queue>

using std::cin;  // using declaration
using std::cout;

/*
A Max Heap is a complete binary tree data structure where the parent node is
always greater than or equal to its children. The root of the tree is always the
maximum element in the heap.

                  +-----+
                  |  7  |  <-- the largest data
                  +-----+
                 /       \
          +-----+         +-----+
          |  6  |         |  5  |
          +-----+         +-----+
         /       \       /       \
  +-----+   +-----+     +-----+   +-----+
  |  4  |   |  3  |     |  2  |   |  1  |
  +-----+   +-----+     +-----+   +-----+

 Characteristics:
 * Complete Binary Tree: All levels are fully filled except possibly the last
   level, which is filled from left to right.
 * Heap Property: For every node i, the value of i is greater than or equal to
   its children.
 * Array Representation: Can be efficiently implemented using an array.


 Time Complexity
 +------------------+------------+--------------------------------------------+
 | Case             | Time       | Description                                |
 +------------------+------------+--------------------------------------------+
 | Find Minimum     | O(1)       | The minimum element is always at the root. |
 | Insertion        | O(log n)   | In the worst case, the new element might   |
 |                  |            | need to bubble up to the root.             |
 | Delete Minimum   | O(log n)   | Deleting the root involves replacing it    |
 |                  |            | with the last element, removing it, and    |
 |                  |            | then performing a heapify down operation.  |
 +------------------+------------+--------------------------------------------+

 Pros:
 * Efficient access to the minimum element (O(1))
 * Efficient insertion and deletion operations (O(log n))
 * Space-efficient (can be implemented as an array)
 * Useful for priority queue implementations

 Cons:
 * Not suitable for searching for arbitrary elements (O(n) in worst case)
 * Not efficient for in-order traversal
 * Balancing the heap after insertion or deletion can be complex

*/

template <typename T>
class MaxHeap {
 private:
  struct Node {
    T data;
    Node* left;
    Node* right;
    Node* parent;

    // constructor
    Node(T value)
        : data(value), left(nullptr), right(nullptr), parent(nullptr) {}
  };

  Node* root;
  // pointer to the last node (for efficient insertion/deletion)
  Node* lastNode;

  void swap(Node* a, Node* b) {
    // swap the data
    T temp = a->data;
    a->data = b->data;
    b->data = temp;
  }

  void heapifyUp(Node* node) {
    while (node->parent && node->data > node->parent->data) {
      swap(node, node->parent);
      node = node->parent;
    }
  }

  void heapifyDown(Node* node) {
    Node* maxNode = node;
    // check if left child is larger
    if (node->left && node->left->data > maxNode->data) {
      maxNode = node->left;
    }
    // check if right child is larger
    if (node->right && node->right->data > maxNode->data) {
      maxNode = node->right;
    }

    // if a child is larger, swap and continue heapifying
    if (maxNode != node) {
      swap(maxNode, node);
      heapifyDown(maxNode);
    }
  }

  Node* findLastParent() {
    // find the parent node where a new node should be inserted
    if (isEmpty()) {
      return nullptr;
    }

    std::queue<Node*> q;
    q.push(root);
    Node* lastParent = nullptr;

    while (!q.empty()) {
      Node* current = q.front();
      q.pop();

      // if we find a node with less than two children, it's our insertion point
      if (!current->left || !current->right) {
        lastParent = current;
        break;
      }

      q.push(current->left);
      q.push(current->right);
    }

    return lastParent;
  }

  void deleteAllNodes(Node* node) {
    if (node == nullptr) {
      return;
    }

    // post-order traversal
    deleteAllNodes(node->left);
    deleteAllNodes(node->right);

    // delete the current node
    delete node;
  }

 public:
  // constructor
  MaxHeap() : root(nullptr), lastNode(nullptr) {}

  // destructor
  ~MaxHeap() { deleteAllNodes(root); }

  void insert(T newData) {
    Node* newNode = new Node(newData);

    if (isEmpty()) {
      root = newNode;
    } else {
      Node* lastParent = findLastParent();

      if (!lastParent->left) {
        lastParent->left = newNode;
      } else {
        lastParent->right = newNode;
      }

      newNode->parent = lastParent;
      lastNode = newNode;
    }

    heapifyUp(newNode);
  }

  T extractMax() {
    if (isEmpty()) {
      throw std::out_of_range("Error! Heap is empty.\n");
    }

    T maxValue = root->data;

    if (root == lastNode) {
      delete root;
      root = nullptr;
      lastNode = nullptr;
    } else {
      root->data = lastNode->data;

      Node* lastParent = lastNode->parent;
      // remove the last node
      // check the right node first
      if (lastParent->right == lastNode) {
        delete lastParent->right;
        lastParent->right = nullptr;
      } else {  // else, the node is left child
        delete lastParent->left;
        lastParent->left = nullptr;
      }

      lastNode = findLastNode();
      heapifyDown(root);
    }

    return maxValue;
  }

  // Get the maximum data (root's data) without removing it
  T getMax() {
    if (isEmpty()) {
      throw std::out_of_range("Error! Heap is empty.\n");
    }
    return root->data;
  }

  // find the last node in the heap (rightmost node in the last level)
  Node* findLastNode() {
    if (isEmpty()) {
      return nullptr;
    }

    std::queue<Node*> q;
    q.push(root);
    Node* last = nullptr;

    while (!q.empty()) {
      last = q.front();
      q.pop();

      if (last->left) {
        q.push(last->left);
      }
      if (last->right) {
        q.push(last->right);
      }
    }

    return last;
  }

  bool isEmpty() const { return root == nullptr; }

  // print the heap in level order
  void printHeap() const {
    if (isEmpty()) {
      cout << "(Empty)";
    }
    std::queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
      int levelSize = q.size();
      for (int i = 0; i < levelSize; i++) {
        Node* curr = q.front();
        q.pop();
        cout << curr->data << " ";

        if (curr->left) {
          q.push(curr->left);
        }
        if (curr->right) {
          q.push(curr->right);
        }
      }
    }
    cout << "\n";
  }
};

int main() {
  // declaration
  MaxHeap<int> heap;
  int num;

  // input
  cout << "\nEnter a number, or -1 to stop: ";
  cin >> num;
  while (num != -1) {
    heap.insert(num);

    // display current state of the heap
    cout << "Heap: ";
    heap.printHeap();

    cout << "\nEnter a number, or -1 to stop: ";
    cin >> num;
  }

  // print initial heap
  cout << "\n\nInitial Heap:\n";
  heap.printHeap();

  // extract and display two largest elements
  cout << "\nLet's extract two largest data from the root.";
  for (int i = 0; i < 2; i++) {
    try {
      num = heap.extractMax();
      cout << "\nThe largest data in the heap: " << num << "\n";
      cout << "Heap: ";
      heap.printHeap();
    } catch (std::exception& e) {
      cout << e.what();
    }
  }

  // print final heap
  cout << "\n\nFinal Heap: \n";
  heap.printHeap();
  cout << "\n";

  return 0;
}

// Sample output
/*

Enter a number, or -1 to stop: 6
Heap: 6

Enter a number, or -1 to stop: 7
Heap: 7 6

Enter a number, or -1 to stop: 3
Heap: 7 6 3

Enter a number, or -1 to stop: 1
Heap: 7 6 3 1

Enter a number, or -1 to stop: 5
Heap: 7 6 3 1 5

Enter a number, or -1 to stop: 4
Heap: 7 6 4 1 5 3

Enter a number, or -1 to stop: 2
Heap: 7 6 4 1 5 3 2

Enter a number, or -1 to stop: -1


Initial Heap:
7 6 4 1 5 3 2

Let's extract two largest data from the root.
The largest data in the heap: 7
Heap: 6 5 4 1 2 3

The largest data in the heap: 6
Heap: 5 3 4 1 2


Final Heap:
5 3 4 1 2

*/

/*
Let's start construct our max heap.
Insert 6, 7, 3, 1, 5, 4, and 2 one by one.
And then remove two of them from the root.
+=====================================================================+
Insert 6:
 root is empty now
 Create a new node and then assign it to root and lastNode

                  +-----+
                  |  6  | < root
                  +-----+ < lastNode

+---------------------------------------------------------------------+
Insert 7:
 root is the lastParent
 Assign the new node to its left and update the lastNode

                  +-----+
                  |  6  | < root
                  +-----+
                 /
          +-----+
          |  7  | < lastNode
          +-----+

 Oh no, 7 is greater than 6. Let's heapify it up!
 Swap value 7 and 6.

                  +-----+
                  |  7  | < root
                  +-----+
                 /
          +-----+
          |  6  | < lastNode
          +-----+

+---------------------------------------------------------------------+
Insert 3:
 root is the lastParent
 Assign the new node to its right and update the lastNode

                  +-----+
                  |  7  | < root
                  +-----+
                 /       \
          +-----+         +-----+
          |  6  |         |  3  | < lastNode
          +-----+         +-----+

+---------------------------------------------------------------------+
Insert 1:
 Now, 6 is the lastParent
 Assign the new node to its left and update the lastNode


                  +-----+
                  |  7  | < root
                  +-----+
                 /       \
          +-----+         +-----+
          |  6  |         |  3  |
          +-----+         +-----+
         /
  +-----+
  |  1  | < lastNode
  +-----+

+---------------------------------------------------------------------+
Insert 5:
 6 is the lastParent
 Assign the new node to its right and update the lastNode

                  +-----+
                  |  7  | < root
                  +-----+
                 /       \
          +-----+         +-----+
          |  6  |         |  3  |
          +-----+         +-----+
         /       \
  +-----+   +-----+
  |  1  |   |  5  | < lastNode
  +-----+   +-----+

+---------------------------------------------------------------------+
Insert 4:
 Now, 3 is the lastParent
 Assign the new node to its left and update the lastNode

                  +-----+
                  |  7  | < root
                  +-----+
                 /       \
          +-----+         +-----+
          |  6  |         |  3  |
          +-----+         +-----+
         /       \       /
  +-----+   +-----+     +-----+
  |  1  |   |  5  |     |  4  | < lastNode
  +-----+   +-----+     +-----+

 Oh no, 4 is greater than 3. Let's heapify it up!
 Swap value 7 and 6.

                  +-----+
                  |  7  | < root
                  +-----+
                 /       \
          +-----+         +-----+
          |  6  |         |  4  |
          +-----+         +-----+
         /       \       /
  +-----+   +-----+     +-----+
  |  1  |   |  5  |     |  3  | < lastNode
  +-----+   +-----+     +-----+

 Now, we have satisfied the heap property.

+---------------------------------------------------------------------+
Insert 2:
 4 is the lastParent
 Assign the new node to its left and update the lastNode

                  +-----+
                  |  7  | < root
                  +-----+
                 /       \
          +-----+         +-----+
          |  6  |         |  4  |
          +-----+         +-----+
         /       \       /       \
  +-----+   +-----+     +-----+   +-----+
  |  1  |   |  5  |     |  3  |   |  2  | < lastNode
  +-----+   +-----+     +-----+   +-----+

Everything satisfies the heap property. We done!

+=====================================================================+
Let's extract the max
Initial Heap:

                  +-----+
                  |  7  | < root
                  +-----+
                 /       \
          +-----+         +-----+
          |  6  |         |  4  |
          +-----+         +-----+
         /       \       /       \
  +-----+   +-----+     +-----+   +-----+
  |  1  |   |  5  |     |  3  |   |  2  | < lastNode
  +-----+   +-----+     +-----+   +-----+

Save root's value (the largest value) to maxValue
Replace root's value with the last node's value...

  +-----+         +-----+
  |  7  |         |  2  | <-- Hey, 2 is not the largest
  +-----+         +-----+
  maxValue       /       \
          +-----+         +-----+
          |  6  |         |  4  | < lastParent
          +-----+         +-----+
         /       \       /       \
  +-----+   +-----+     +-----+   +-----+
  |  1  |   |  5  |     |  3  |   |  2  | < lastNode
  +-----+   +-----+     +-----+   +-----+

Use lastParent to delete the lastNode

                  +-----+
                  |  2  | < root
                  +-----+
                 /       \
          +-----+         +-----+
          |  6  |         |  4  | < lastParent
          +-----+         +-----+
         /       \       /
  +-----+   +-----+     +-----+
  |  1  |   |  5  |     |  3  |         ? < lastNode
  +-----+   +-----+     +-----+

Update the lastNode using queue
+=====================================================================+
First, push root into the queue

                         0
      +-----+         +-----+
 last |     |   queue |  2  |
      +-----+         +-----+

Save queue's front into last (variable to store Node)
Pop the queue and push left and right nodes into queue

                         0     1
      +-----+         +-----+-----+
 last |  2  |   queue |  6  |  4  |
      +-----+         +-----+-----+

Again, save queue's front into last

                         0     1
      +-----+         +-----+-----+
 last |  6  |   queue |  6  |  4  |
      +-----+         +-----+-----+

Pop the front out and push its left and right nodes into queue

                         0     1     2
      +-----+         +-----+-----+-----+
 last |  6  |   queue |  4  |  1  |  5  |
      +-----+         +-----+-----+-----+

Do it repeatily...

                         0     1     2
      +-----+         +-----+-----+-----+
 last |  4  |   queue |  1  |  5  |  3  |
      +-----+         +-----+-----+-----+

4 only have one child. It's fine. Keep doing

                         0     1
      +-----+         +-----+-----+
 last |  1  |   queue |  5  |  3  |
      +-----+         +-----+-----+

1 doesn't have any child. We are closing!

                         0
      +-----+         +-----+
 last |  5  |   queue |  3  |
      +-----+         +-----+

5 doesn't have any child either. One more step!

                         0
      +-----+         +-----+
 last |  3  |   queue |     |
      +-----+         +-----+

queue is empty! We find 3 is the last node.

                  +-----+
                  |  2  | < root
                  +-----+
                 /       \
          +-----+         +-----+
          |  6  |         |  4  | < lastParent
          +-----+         +-----+
         /       \       /
  +-----+   +-----+     +-----+
  |  1  |   |  5  |     |  3  | < lastNode
  +-----+   +-----+     +-----+

+=====================================================================+
Now we find the lastNode. Let's fix the tree - Heapify Down.

Assume current node (root), 2, is the maxNode

                  +-----+
                  |  2  | < node
                  +-----+ < maxNode
                 /       \
          +-----+         +-----+
          |  6  |         |  4  |
          +-----+         +-----+
         /       \       /
  +-----+   +-----+     +-----+
  |  1  |   |  5  |     |  3  |
  +-----+   +-----+     +-----+

Compare it with its left child: 2 < 6
Update the maxNode to be the root's left child

                   +-----+
                   |  2  | < node
                   +-----+
                  /       \
           +-----+         +-----+
 maxNode > |  6  |         |  4  |
           +-----+         +-----+
          /       \       /
   +-----+   +-----+     +-----+
   |  1  |   |  5  |     |  3  |
   +-----+   +-----+     +-----+

Compare it with its root's right child: 6 > 4
Nothing needs to be updated

                   +-----+
                   |  2  | < node
                   +-----+
                  /       \
           +-----+         +-----+
 maxNode > |  6  |         |  4  |
           +-----+         +-----+
          /       \       /
   +-----+   +-----+     +-----+
   |  1  |   |  5  |     |  3  |
   +-----+   +-----+     +-----+

Since the maxNode is not the original node anymore. Let's swap!

                   +-----+
                   |  6  | < node
                   +-----+
                  /       \
           +-----+         +-----+
 maxNode > |  2  |         |  4  |
           +-----+         +-----+
          /       \       /
   +-----+   +-----+     +-----+
   |  1  |   |  5  |     |  3  |
   +-----+   +-----+     +-----+

After we update the heap, we have to heapify down again until we satisfy heap's
property. So, let's keep heapifing!
Assume current node (previous maxNode), 2, is the maxNode.

                   +-----+
                   |  6  |
                   +-----+
                  /       \
           +-----+         +-----+
    node > |  2  |         |  4  |
 maxNode > +-----+         +-----+
          /       \       /
   +-----+   +-----+     +-----+
   |  1  |   |  5  |     |  3  |
   +-----+   +-----+     +-----+

Compare it with its left child: 2 > 1
Nothing needs to be updated

                   +-----+
                   |  6  |
                   +-----+
                  /       \
           +-----+         +-----+
    node > |  2  |         |  4  |
 maxNode > +-----+         +-----+
          /       \       /
   +-----+   +-----+     +-----+
   |  1  |   |  5  |     |  3  |
   +-----+   +-----+     +-----+

Compare it with its right child: 2 < 5
Update the maxNode to be the root's right child

                   +-----+
                   |  6  |
                   +-----+
                  /       \
           +-----+         +-----+
    node > |  2  |         |  4  |
           +-----+         +-----+
          /       \       /
   +-----+   +-----+     +-----+
   |  1  |   |  5  |     |  3  |
   +-----+   +-----+     +-----+
                ^
             maxNode

Since the maxNode is not the original node anymore. Let's swap!

                   +-----+
                   |  6  |
                   +-----+
                  /       \
           +-----+         +-----+
    node > |  5  |         |  4  |
           +-----+         +-----+
          /       \       /
   +-----+   +-----+     +-----+
   |  1  |   |  2  |     |  3  |
   +-----+   +-----+     +-----+
                ^
             maxNode

Everything satisfies the heap property. Return the maxValue and we done!

                   +-----+
                   |  6  | < root
                   +-----+
                  /       \
           +-----+         +-----+
           |  5  |         |  4  |
           +-----+         +-----+
          /       \       /
   +-----+   +-----+     +-----+
   |  1  |   |  2  |     |  3  | < lastNode
   +-----+   +-----+     +-----+

+---------------------------------------------------------------------+
Let's remove one more data.

                   +-----+
                   |  6  | < root
                   +-----+
                  /       \
           +-----+         +-----+
           |  5  |         |  4  |
           +-----+         +-----+
          /       \       /
   +-----+   +-----+     +-----+
   |  1  |   |  2  |     |  3  | < lastNode
   +-----+   +-----+     +-----+

Save root's value to maxValue and replace its value with the lastNode's

  +-----+         +-----+
  |  6  |         |  3  | < root
  +-----+         +-----+
  maxValue       /       \
           +-----+         +-----+
           |  5  |         |  4  | < lastParent
           +-----+         +-----+
          /       \       /
   +-----+   +-----+     +-----+
   |  1  |   |  2  |     |  3  | < lastNode
   +-----+   +-----+     +-----+

Find lastParent. Use it to delete the original lastNode

  +-----+         +-----+
  |  6  |         |  3  | < root
  +-----+         +-----+
  maxValue       /       \
           +-----+         +-----+
           |  5  |         |  4  | < lastParent
           +-----+         +-----+
          /       \
   +-----+   +-----+
   |  1  |   |  2  |
   +-----+   +-----+

Find the new lastNode

                  +-----+
                  |  3  | < root
                  +-----+
                 /       \
           +-----+         +-----+
           |  5  |         |  4  | < lastParent
           +-----+         +-----+
          /       \
   +-----+   +-----+
   |  1  |   |  2  | < lastNode
   +-----+   +-----+

Heapify Down

                  +-----+
                  |  3  | < node
                  +-----+ < maxNode
                 /       \
           +-----+         +-----+
           |  5  |         |  4  |
           +-----+         +-----+
          /       \
   +-----+   +-----+
   |  1  |   |  2  |
   +-----+   +-----+

                  +-----+
                  |  3  | < node
                  +-----+
                 /       \
           +-----+         +-----+
 maxNode > |  5  |         |  4  |
           +-----+         +-----+
          /       \
   +-----+   +-----+
   |  1  |   |  2  |
   +-----+   +-----+

                  +-----+
                  |  5  | < node
                  +-----+
                 /       \
           +-----+         +-----+
 maxNode > |  3  |         |  4  |
           +-----+         +-----+
          /       \
   +-----+   +-----+
   |  1  |   |  2  |
   +-----+   +-----+

                  +-----+
                  |  5  |
                  +-----+
                 /       \
           +-----+         +-----+
    node > |  3  |         |  4  |
 maxNode > +-----+         +-----+
          /       \
   +-----+   +-----+
   |  1  |   |  2  |
   +-----+   +-----+

                  +-----+
                  |  5  |
                  +-----+
                 /       \
           +-----+         +-----+
    node > |  3  |         |  4  |
 maxNode > +-----+         +-----+
          /       \
   +-----+   +-----+
   |  1  |   |  2  |
   +-----+   +-----+

3 is greater than 1 and 2. Nothing needs to be updated
Everything satisfies the heap property. Return the maxValue. Well done!
+=====================================================================+
Final Heap:

                  +-----+
                  |  5  |
                  +-----+
                 /       \
          +-----+         +-----+
          |  3  |         |  4  |
          +-----+         +-----+
         /       \
  +-----+   +-----+
  |  1  |   |  2  |
  +-----+   +-----+

*/