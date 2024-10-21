#include <algorithm>  // preprocessor directive
#include <iostream>
#include <vector>

using std::cin;  // using declaration
using std::cout;

/*
B-trees are self-balancing tree data structures that maintain sorted data and
allow searches, sequential access, insertions, and deletions in logarithmic
time. They are optimized for systems that read and write large blocks of data,
such as databases and file systems.

 Characteristics of B-trees:
 * They can have more than two children per node.
 * They maintain balance by design, ensuring all leaf nodes are at the same
   depth.
 * They minimize the number of disk accesses required for operations.
 * Nodes can contain a variable number of keys and children, within a predefined
   range.


A 2-3 tree is a specific type of B-tree and serves as a simpler example to
understand the general B-tree concept.

 Characteristics of B-trees:
 * Each internal node has either 2 or 3 children.
 * All leaves are at the same depth.
 * Data is stored in sorted order.
 * A 2-node has one data element and two children.
 * A 3-node has two data elements and three children.
 * The tree is always balanced.

 Time Complexity
 +------------+------------+--------------------------------------------+
 | Case       | Time       | Description                                |
 +------------+------------+--------------------------------------------+
 | Search     | O(log n)   | The tree is balanced, so search is always  |
 |            |            | logarithmic.                               |
 | Insertion  | O(log n)   | In the worst case, we might need to split  |
 |            |            | nodes up to the root.                      |
 | Deletion   | O(log n)   | Similar to insertion, we might need to     |
 |            |            | rebalance up to the root.                  |
 +------------+------------+--------------------------------------------+

 Space complexity: O(n) - The tree stores n elements across its nodes.

 Pros:
 * Guaranteed logarithmic performance for insertions, deletions, and searches.
 * Always balanced, which ensures consistent performance.
 * Good for databases and file systems where balance is critical.

 Cons:
 * More complex to implement compared to binary search trees.
 * Requires more memory per node due to the potential for 3 children.
 * Frequent splitting and merging of nodes can be computationally expensive.

*/

template <typename T>
class TwoTreeTree {
 private:
  struct Node {
    std::vector<T> keys;
    std::vector<Node*> children;
    Node* parent;

    // construct
    Node() : parent(nullptr) {}
  };

  // Data member
  Node* root;

  // utility function
  void insert(Node* node, const T& key) {
    if (node->children.empty()) {  // leaf
      node->keys.push_back(key);
      std::sort(node->keys.begin(), node->keys.end());
      if (node->keys.size() > 2) {
        split(node);
      }
    } else {  // internal node
      int i = 0;
      while (i < node->keys.size() && key > node->keys[i]) {
        i++;
      }
      insert(node->children[i], key);
    }
  }

  void split(Node* node) {
    T middle = node->keys[1];
    Node* left = new Node();
    Node* right = new Node();

    left->keys.push_back(node->keys[0]);
    right->keys.push_back(node->keys[2]);

    if (!node->children.empty()) {
      left->children = {node->children[0], node->children[1]};
      right->children = {node->children[2], node->children[3]};
      for (auto child : left->children) {
        child->parent = left;
      }
      for (auto child : right->children) {
        child->parent = right;
      }
    }

    if (node->parent == nullptr) {  // root
      Node* newRoot = new Node();
      newRoot->keys.push_back(middle);
      newRoot->children = {left, right};
      left->parent = newRoot;
      right->parent = newRoot;
      root = newRoot;
    } else {
      Node* parent = node->parent;
      int index =
          std::find(parent->children.begin(), parent->children.end(), node) -
          parent->children.begin();

      parent->keys.insert(parent->keys.begin() + index, middle);
      parent->children[index] = left;
      parent->children.insert(parent->children.begin() + index + 1, right);
      left->parent = parent;
      right->parent = parent;

      if (parent->keys.size() > 2) {
        split(parent);
      }
    }
    delete node;
  }

  void printHelper(Node* node, int depth) {
    if (node == nullptr) {
      return;
    }

    for (int i = 0; i < depth; i++) {
      cout << " ";
    }
    for (const auto& key : node->keys) {
      cout << key << " ";
    }
    cout << "\n";

    for (const auto& child : node->children) {
      printHelper(child, depth + 1);
    }
  }

 public:
  // constructor
  TwoTreeTree() : root(new Node()) {}

  void insert(const T& key) { insert(root, key); }

  void printTree() { printHelper(root, 0); }
};

int main() {
  // declaration
  TwoTreeTree<int> tree;
  int num;

  // input
  while (true) {
    cout << "Enter a number, or -1 to stop: ";
    cin >> num;
    if (num == -1) {
      break;
    }

    tree.insert(num);

    // displary current state of the tree
    cout << "Two-Three Tree: \n";
    tree.printTree();
  }

  // print final tree
  cout << "\n\nFinal Two-Three Tree:\n";
  tree.printTree();
  cout << "\n";

  return 0;
}