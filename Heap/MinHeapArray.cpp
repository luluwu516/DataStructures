#include <iostream>  // preprocessor directive
#include <vector>

using std::cin;  // using declaration
using std::cout;

/*
A Min Heap is a complete binary tree data structure where the parent node is
always smaller than or equal to its children. The root of the tree is always the
minimum element in the heap.

                  +-----+
                  |  1  |  <-- the smallest data
                  +-----+
                 /       \
          +-----+         +-----+
          |  2  |         |  3  |
          +-----+         +-----+
         /       \       /       \
  +-----+   +-----+     +-----+   +-----+
  |  4  |   |  5  |     |  6  |   |  7  |
  +-----+   +-----+     +-----+   +-----+

 Characteristics:
 * Complete Binary Tree: All levels are fully filled except possibly the last
   level, which is filled from left to right.
 * Heap Property: For every node i, the value of i is less than or equal to its
   children.
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
 * Space-efficient (can be implemented as an array)  <-- we will apply it here
 * Useful for priority queue implementations

 Cons:
 * Not suitable for searching for arbitrary elements (O(n) in worst case)
 * Not efficient for in-order traversal
 * Balancing the heap after insertion or deletion can be complex

Trees can be represented using arrays, which is sometimes called an "implicit
data structure" representation. This method is particularly useful for certain
types of trees, like binary heaps or complete binary trees. The basic idea is to
store the tree nodes in an array using level-order traversal.

1. The root of the tree is stored at index 0.
2. For any node at index i:
   * Its left child is stored at index 2i + 1
   * Its right child is stored at index 2i + 2
3. Conversely, for any node at index i, its parent is at index (i - 1) / 2
   (integer division).

     0     1     2     3     4     5     6
  +-----+-----+-----+-----+-----+-----+-----+
  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |
  +-----+-----+-----+-----+-----+-----+-----+

*/

template <typename T>
class MinHeap {
 public:
  void insert(T newData) {
    heap.push_back(newData);
    // maintain heap property
    heapifyUp(size() - 1);
  }

  T extractMin() {
    if (isEmpty()) {
      throw std::out_of_range("Error! Heap is empty.\n");
    }

    T min = heap[0];

    // move last element to root
    heap[0] = heap.back();
    // remove last element
    heap.pop_back();

    if (!isEmpty()) {
      // maintain heap property
      heapifyDown(0);
    }

    return min;
  }

  T getMin() const {
    if (isEmpty()) {
      throw std::out_of_range("Error! Heap is empty.\n");
    }

    // root is always the minimum in a min heap
    return heap[0];
  }

  bool isEmpty() const { return heap.empty(); }

  size_t size() const { return heap.size(); }

  void printHeap() const {
    if (isEmpty()) {
      cout << "(Empty)";
    }
    for (T val : heap) {
      cout << val << " ";
    }
    cout << "\n";
  }

 private:
  std::vector<T> heap;

  // maintains heap property by moving an element up
  void heapifyUp(int index) {
    while (index > 0 && heap[(index - 1) / 2] > heap[index]) {
      std::swap(heap[index], heap[(index - 1) / 2]);
      index = (index - 1) / 2;
    }
  }

  // maintains heap property by moving an element down
  void heapifyDown(int index) {
    int minIndex = index;
    int left = 2 * index + 1;   // left child
    int right = 2 * index + 2;  // right child

    // check if left child is smaller
    if (left < heap.size() && heap[left] < heap[minIndex]) {
      minIndex = left;
    }

    // check if right child is smaller
    if (right < heap.size() && heap[right] < heap[minIndex]) {
      minIndex = right;
    }

    // if a child is smaller, swap and continue heapifying
    if (minIndex != index) {
      std::swap(heap[index], heap[minIndex]);

      // recursively heapify the affected subtree
      heapifyDown(minIndex);
    }
  }
};

int main() {
  // declaration
  MinHeap<int> heap;
  int num;

  // input
  cout << "Enter a number, or -1 to stop: ";
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

  // extract and display two smallest elements
  cout << "\nLet's extract two smallest data from the root.";
  for (int i = 0; i < 2; i++) {
    try {
      num = heap.extractMin();
      cout << "\nThe smallest data in the heap: " << num << "\n";
      cout << "Heap: ";
      heap.printHeap();
    } catch (std::exception &e) {
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
Heap: 6 7

Enter a number, or -1 to stop: 3
Heap: 3 7 6

Enter a number, or -1 to stop: 1
Heap: 1 3 6 7

Enter a number, or -1 to stop: 5
Heap: 1 3 6 7 5

Enter a number, or -1 to stop: 4
Heap: 1 3 4 7 5 6

Enter a number, or -1 to stop: 2
Heap: 1 3 2 7 5 6 4

Enter a number, or -1 to stop: -1


Initial Heap:
1 3 2 7 5 6 4

Let's extract two smallest data from the root.
The smallest data in the heap: 1
Heap: 2 3 4 7 5 6

The smallest data in the heap: 2
Heap: 3 5 4 7 6


Final Heap: 3 5 4 7 6

*/

/*
Let's start construct our min heap.
Insert 6, 7, 3, 1, 5, 4, and 2 one by one.
And then remove two of them from the root.

+=====================================================================+
Insert 6:
 Tree diagram:
                  +-----+
                  |  6  |
                  +-----+

 How we store the value(s) in arr:

         0
      +-----+
 heap |  6  |
      +-----+

 index = 0
 0 is NOT greater than 0

+---------------------------------------------------------------------+
Insert 7:
 Tree diagram:
                  +-----+
                  |  6  |
                  +-----+
                 /
          +-----+
          |  7  |
          +-----+

 How we store the value(s) in arr:

         0     1
      +-----+-----+
 heap |  6  |  7  |
      +-----+-----+

 index = 1

         0     1
      +-----+-----+
 heap |  6  |  7  |
      +-----+-----+
         ^     ^
      parent  child

 parent is the smallest in the heap.

+---------------------------------------------------------------------+
Insert 3:

                  +-----+
                  |  6  |
                  +-----+
                 /       \
          +-----+         +-----+
          |  7  |         |  3  |
          +-----+         +-----+

 How we store the value(s) in arr:

         0     1     2
      +-----+-----+-----+
 heap |  6  |  7  |  3  |
      +-----+-----+-----+
                     ^
                   index

 index is greater than 0

         0     1     2
      +-----+-----+-----+
 heap |  6  |  7  |  3  |
      +-----+-----+-----+
         ^           ^
      parent       child

 parent is greater than child, so let's swap them!
 Then, update the index to its parent.

         0     1     2
      +-----+-----+-----+
 heap |  3  |  7  |  6  |
      +-----+-----+-----+
         ^
       index

 index = 0 and end the while loop

                  +-----+
                  |  3  |
                  +-----+
                 /       \
          +-----+         +-----+
          |  7  |         |  6  |
          +-----+         +-----+

+---------------------------------------------------------------------+
Insert 1:

                  +-----+
                  |  3  |
                  +-----+
                 /       \
          +-----+         +-----+
          |  7  |         |  6  |
          +-----+         +-----+
         /
  +-----+
  |  1  |
  +-----+

         0     1     2     3
      +-----+-----+-----+-----+
 heap |  3  |  7  |  6  |  1  |
      +-----+-----+-----+-----+
                           ^
                         index

         0     1     2     3
      +-----+-----+-----+-----+
 heap |  3  |  7  |  6  |  1  |
      +-----+-----+-----+-----+
               ^           ^
             parent      child

 parent is greater than child, so let's swap them!
 Then, update the index to its parent.

         0     1     2     3
      +-----+-----+-----+-----+
 heap |  3  |  1  |  6  |  7  |
      +-----+-----+-----+-----+
               ^
             index

         0     1     2     3
      +-----+-----+-----+-----+
 heap |  3  |  1  |  6  |  7  |
      +-----+-----+-----+-----+
         ^     ^
      parent child

 Again, parent is greater than child

         0     1     2     3
      +-----+-----+-----+-----+
 heap |  1  |  3  |  6  |  7  |
      +-----+-----+-----+-----+
         ^
       index

 Now, index is equal to 0. Stop the loop.

                  +-----+
                  |  1  |
                  +-----+
                 /       \
          +-----+         +-----+
          |  3  |         |  6  |
          +-----+         +-----+
         /
  +-----+
  |  7  |
  +-----+

+---------------------------------------------------------------------+
Insert 5:

                  +-----+
                  |  1  |
                  +-----+
                 /       \
          +-----+         +-----+
          |  3  |         |  6  |
          +-----+         +-----+
         /       \
  +-----+   +-----+
  |  7  |   |  5  |
  +-----+   +-----+

         0     1     2     3     4
      +-----+-----+-----+-----+-----+
 heap |  1  |  3  |  6  |  7  |  5  |
      +-----+-----+-----+-----+-----+
                                 ^
                               index

         0     1     2     3     4
      +-----+-----+-----+-----+-----+
 heap |  1  |  3  |  6  |  7  |  5  |
      +-----+-----+-----+-----+-----+
               ^                 ^
             parent            child

 parent is smaller than child, so nothing will happen.

                  +-----+
                  |  1  |
                  +-----+
                 /       \
          +-----+         +-----+
          |  3  |         |  6  |
          +-----+         +-----+
         /       \
  +-----+   +-----+
  |  7  |   |  5  |
  +-----+   +-----+

+---------------------------------------------------------------------+
Insert 4:

                  +-----+
                  |  1  |
                  +-----+
                 /       \
          +-----+         +-----+
          |  3  |         |  6  |
          +-----+         +-----+
         /       \       /
  +-----+   +-----+     +-----+
  |  7  |   |  5  |     |  4  |
  +-----+   +-----+     +-----+

         0     1     2     3     4     5
      +-----+-----+-----+-----+-----+-----+
 heap |  1  |  3  |  6  |  7  |  5  |  4  |
      +-----+-----+-----+-----+-----+-----+
                                       ^
                                     index

         0     1     2     3     4     5
      +-----+-----+-----+-----+-----+-----+
 heap |  1  |  3  |  6  |  7  |  5  |  4  |
      +-----+-----+-----+-----+-----+-----+
                     ^                 ^
                   parent            child

 parent is greater than child, so let's swap and update the index

         0     1     2     3     4     5
      +-----+-----+-----+-----+-----+-----+
 heap |  1  |  3  |  4  |  7  |  5  |  6  |
      +-----+-----+-----+-----+-----+-----+
                     ^
                   index

         0     1     2     3     4     5
      +-----+-----+-----+-----+-----+-----+
 heap |  1  |  3  |  4  |  7  |  5  |  6  |
      +-----+-----+-----+-----+-----+-----+
         ^           ^
       parent      child

 parent is the smaller than child, so no swap and end the loop.

                  +-----+
                  |  1  |
                  +-----+
                 /       \
          +-----+         +-----+
          |  3  |         |  4  |
          +-----+         +-----+
         /       \       /
  +-----+   +-----+     +-----+
  |  7  |   |  5  |     |  6  |
  +-----+   +-----+     +-----+

+---------------------------------------------------------------------+
Insert 2:

                  +-----+
                  |  1  |
                  +-----+
                 /       \
          +-----+         +-----+
          |  3  |         |  4  |
          +-----+         +-----+
         /       \       /       \
  +-----+   +-----+     +-----+   +-----+
  |  7  |   |  5  |     |  6  |   |  2  |
  +-----+   +-----+     +-----+   +-----+

         0     1     2     3     4     5     6
      +-----+-----+-----+-----+-----+-----+-----+
 heap |  1  |  3  |  4  |  7  |  5  |  6  |  2  |
      +-----+-----+-----+-----+-----+-----+-----+


                  +-----+
                  |  1  |
                  +-----+
                 /       \
          +-----+         +-----+
          |  3  |         |  2  |
          +-----+         +-----+
         /       \       /       \
  +-----+   +-----+     +-----+   +-----+
  |  7  |   |  5  |     |  6  |   |  4  |
  +-----+   +-----+     +-----+   +-----+

+=====================================================================+
Let's extract the min
Initial Tree:
                  +-----+
                  |  1  |
                  +-----+
                 /       \
          +-----+         +-----+
          |  3  |         |  2  |
          +-----+         +-----+
         /       \       /       \
  +-----+   +-----+     +-----+   +-----+
  |  7  |   |  5  |     |  6  |   |  4  |
  +-----+   +-----+     +-----+   +-----+


         0     1     2     3     4     5     6
      +-----+-----+-----+-----+-----+-----+-----+
 heap |  1  |  3  |  2  |  7  |  5  |  6  |  4  |
      +-----+-----+-----+-----+-----+-----+-----+



                  0     1     2     3     4     5
 +-----+       +-----+-----+-----+-----+-----+-----+
 |  1  |  heap |  4  |  3  |  2  |  7  |  5  |  6  |
 +-----+       +-----+-----+-----+-----+-----+-----+
   min            ^
                index

                  +-----+
                  |  4  | <-- Hey, 4 is not the smallest
                  +-----+
                 /       \
          +-----+         +-----+
          |  3  |         |  2  |
          +-----+         +-----+
         /       \       /
  +-----+   +-----+     +-----+
  |  7  |   |  5  |     |  6  |
  +-----+   +-----+     +-----+

Assume index is the minIndex and let's compare with its children

         0     1     2     3     4     5
      +-----+-----+-----+-----+-----+-----+
 heap |  4  |  3  |  2  |  7  |  5  |  6  |
      +-----+-----+-----+-----+-----+-----+
         ^     ^     ^
       index left  right
      minIndex

Compare with left child first. The left child is smaller, so it should be
minIndex

         0     1     2     3     4     5
      +-----+-----+-----+-----+-----+-----+
 heap |  4  |  3  |  2  |  7  |  5  |  6  |
      +-----+-----+-----+-----+-----+-----+
         ^     ^     ^
       index left  right
           minIndex

Compare with right child next. The right child is smaller, so it should be
minIndex

         0     1     2     3     4     5
      +-----+-----+-----+-----+-----+-----+
 heap |  4  |  3  |  2  |  7  |  5  |  6  |
      +-----+-----+-----+-----+-----+-----+
         ^     ^     ^
       index left  right
                  minIndex

Now, let's check if index and minIndex are the same

         0     1     2     3     4     5
      +-----+-----+-----+-----+-----+-----+
 heap |  4  |  3  |  2  |  7  |  5  |  6  |
      +-----+-----+-----+-----+-----+-----+
         ^           ^
       index      minIndex

minIndex != index, so let's swap

         0     1     2     3     4     5
      +-----+-----+-----+-----+-----+-----+
 heap |  2  |  3  |  4  |  7  |  5  |  6  |
      +-----+-----+-----+-----+-----+-----+
         ^           ^
       index      minIndex

                  +-----+
                  |  2  |
                  +-----+
                 /       \
          +-----+         +-----+
          |  3  |         |  4  |
          +-----+         +-----+
         /       \       /
  +-----+   +-----+     +-----+
  |  7  |   |  5  |     |  6  |
  +-----+   +-----+     +-----+

+---------------------------------------------------------------------+
Let's remove one more data.

         0     1     2     3     4     5
      +-----+-----+-----+-----+-----+-----+
 heap |  2  |  3  |  4  |  7  |  5  |  6  |
      +-----+-----+-----+-----+-----+-----+


                  0     1     2     3     4
 +-----+       +-----+-----+-----+-----+-----+
 |  2  |  heap |  6  |  3  |  4  |  7  |  5  |
 +-----+       +-----+-----+-----+-----+-----+
   min            ^
                index

                  +-----+
                  |  6  | <-- Hey, 6 is not the smallest
                  +-----+
                 /       \
          +-----+         +-----+
          |  3  |         |  4  |
          +-----+         +-----+
         /       \
  +-----+   +-----+
  |  7  |   |  5  |
  +-----+   +-----+

Assume index is the minIndex and let's compare with its children

         0     1     2     3     4
      +-----+-----+-----+-----+-----+
 heap |  6  |  3  |  4  |  7  |  5  |
      +-----+-----+-----+-----+-----+
         ^     ^     ^
       index left  right
      minIndex

Compare with left child first. The left child is smaller, so it should be
minIndex

         0     1     2     3     4
      +-----+-----+-----+-----+-----+
 heap |  6  |  3  |  4  |  7  |  5  |
      +-----+-----+-----+-----+-----+
         ^     ^     ^
       index left  right
            minIndex

Compare with right child next. The left child is still smaller.

         0     1     2     3     4
      +-----+-----+-----+-----+-----+
 heap |  6  |  3  |  4  |  7  |  5  |
      +-----+-----+-----+-----+-----+
         ^     ^     ^
       index left  right
            minIndex

Now, let's check if index and minIndex are the same

         0     1     2     3     4
      +-----+-----+-----+-----+-----+
 heap |  6  |  3  |  4  |  7  |  5  |
      +-----+-----+-----+-----+-----+
         ^     ^
       index minIndex

minIndex != index, so let's swap

         0     1     2     3     4
      +-----+-----+-----+-----+-----+
 heap |  3  |  6  |  4  |  7  |  5  |
      +-----+-----+-----+-----+-----+
         ^     ^
       index minIndex

                  +-----+
                  |  3  |
                  +-----+
                 /       \
          +-----+         +-----+
          |  6  |         |  4  |
          +-----+         +-----+
         /       \
  +-----+   +-----+
  |  7  |   |  5  |  <-- 5 is smaller than 6!
  +-----+   +-----+

We haven't finished yet. now index = 1

         0     1     2     3     4
      +-----+-----+-----+-----+-----+
 heap |  3  |  6  |  4  |  7  |  5  |
      +-----+-----+-----+-----+-----+
               ^           ^     ^
             index        left right
            minIndex


Compare with left and right child

         0     1     2     3     4
      +-----+-----+-----+-----+-----+
 heap |  3  |  6  |  4  |  7  |  5  |
      +-----+-----+-----+-----+-----+
               ^           ^     ^
             index        left right
                              minIndex

Since index != minIndex, let's swap!

         0     1     2     3     4
      +-----+-----+-----+-----+-----+
 heap |  3  |  5  |  4  |  7  |  6  |
      +-----+-----+-----+-----+-----+
               ^                 ^
             index            minIndex

Now, index = 4

         0     1     2     3     4
      +-----+-----+-----+-----+-----+
 heap |  3  |  5  |  4  |  7  |  6  |
      +-----+-----+-----+-----+-----+
                                 ^
                               index

Everything satisfies the heap property. We done!

+=====================================================================+
Final Tree:

                  +-----+
                  |  3  |
                  +-----+
                 /       \
          +-----+         +-----+
          |  5  |         |  4  |
          +-----+         +-----+
         /       \
  +-----+   +-----+
  |  7  |   |  6  |
  +-----+   +-----+

         0     1     2     3     4
      +-----+-----+-----+-----+-----+
 heap |  3  |  5  |  4  |  7  |  6  |
      +-----+-----+-----+-----+-----+

*/