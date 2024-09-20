#include <iostream>  // preprocessor directive
#include <vector>

using std::cin;  // using declaration
using std::cout;

// function prototypes
template <typename T>
void printArray(const std::vector<T>&);
template <typename T>
void insertionSort(std::vector<T>&);

/*
Insertion sort is a simple sorting algorithm that builds the final sorted array
one element at a time. It is adaptive, meaning it performs well for already
substantially sorted data.

Key characteristics:
1. In-place algorithm: only requires a constant amount O(1) of additional memory
space.
2. Stable sort: maintains the relative order of equal elements.
3. Online algorithm: can sort a list as it receives it.

Time Complexity
 +------------------+--------+-----------------------------------------------+
 | Case             | Time   | Description                                   |
 +------------------+--------+-----------------------------------------------+
 | Best             | O(n)   | Array is already sorted                       |
 | Worst            | O(n^2) | Array is in reverse order                     |
 | Average          | O(n^2) | Random arrangement of elements                |
 +------------------+--------+-----------------------------------------------+

Space Complexity: O(1) - Sorts in-place, only uses a constant amount of extra
memory.

Comparison with other sorting algorithms:
- More efficient than bubble sort and selection sort for small data sets
- Less efficient than more advanced algorithms like quicksort, heapsort, or
merge sort for larger datasets

*/

int main() {
  // declaration
  std::vector<int> nums;
  int num;

  // input
  cout << "\nEnter numbers, or EOF to stop: ";
  while (cin >> num) {
    nums.push_back(num);
  }
  cout << "\n\nUnsorted array:\n";
  printArray(nums);

  // processing
  insertionSort(nums);

  // output
  cout << "Sorted array:\n";
  printArray(nums);
  cout << "\n";

  return 0;
}

// Output:
/*
Enter numbers, or EOF to stop: 5 4 3 2 1 ^D

Original array:
5 4 3 2 1
Sorted array:
1 2 3 4 5
*/

template <typename T>
void printArray(const std::vector<T>& nums) {
  if (!nums.size()) {
    cout << "(Empty)";
  }
  for (auto n : nums) {
    cout << n << " ";
  }
  cout << "\n";
}

// it requires two loops:
// the number of comparisons is: n * (n - 1)
// Complexity: O(n^2)
template <typename T>
void insertionSort(std::vector<T>& arr) {
  std::size_t size = arr.size();
  // arrays of size 0 or 1 are already sorted
  if (size <= 1) {
    return;
  }

  // iterate through the array, starting from the second element
  for (std::size_t next = 1; next < size; next++) {
    // store the current element as the key to be inserted
    T insertKey = arr[next];

    // initialize the index for insertion
    std::size_t indexToMove = next;

    // move elements that are greater than the key to one position ahead of
    // their current position
    while (indexToMove > 0 && insertKey < arr[indexToMove - 1]) {
      // Shift element to the right
      arr[indexToMove] = arr[indexToMove - 1];
      // update the indexToMove to the left
      --indexToMove;
    }

    // insert the key in its correct position
    arr[indexToMove] = insertKey;
  }
}

/*
Example:

arr = {3, 1, 4, 2}
size = 4
    0     1     2     3
 +-----+-----+-----+-----+
 |  3  |  1  |  4  |  2  |
 +-----+-----+-----+-----+

Let's start an insertion sort!
------------------------------------------------------------------
next = 1:
    0        1     2     3
 +-----+  +-----+-----+-----+
 |  3  |  |  1  |  4  |  2  |
 +-----+  +-----+-----+-----+
 Sorted        Unsorted

 insertKey = arr[1] = 1
 indexToMove = next = 1
 arr[indexToMove - 1] = arr[0] = 3

  Compare and shift:
  indexToMove = 1
                   0     1     2     3
    +-----+     +-----+-----+-----+-----+
    |  1  |     |  3  |  3  |  4  |  2  |
    +-----+     +-----+-----+-----+-----+
   insertKey             ^
                     indexToMove

  indexToMove = 0
                   0     1     2     3
    +-----+     +-----+-----+-----+-----+
    |  1  |     |  3  |  3  |  4  |  2  |
    +-----+     +-----+-----+-----+-----+
   insertKey       ^
              indexToMove

insert the key (1) in its correct position (0)
    0     1        2     3
 +-----+-----+  +-----+-----+
 |  1  |  3  |  |  4  |  2  |
 +-----+-----+  +-----+-----+
    Sorted         Unsorted

------------------------------------------------------------------
next = 2:
    0     1        2     3
 +-----+-----+  +-----+-----+
 |  1  |  3  |  |  4  |  2  |
 +-----+-----+  +-----+-----+
    Sorted         Unsorted

 insertKey = arr[2] = 4
 indexToMove = next = 2
 arr[indexToMove - 1] = arr[1] = 3

  Compare and shift:
  insertKey > arr[indexToMove - 1] => 4 > 3 => end the while loop

insert the key (4) in its correct position (2)
    0     1     2        3
 +-----+-----+-----+  +-----+
 |  1  |  3  |  4  |  |  2  |
 +-----+-----+-----+  +-----+
        Sorted        Unsorted
------------------------------------------------------------------
next = 3:
    0     1     2        3
 +-----+-----+-----+  +-----+
 |  1  |  3  |  4  |  |  2  |
 +-----+-----+-----+  +-----+
        Sorted        Unsorted

 insertKey = arr[3] = 2
 indexToMove = next = 3
 arr[indexToMove - 1] = arr[2] = 4

  Compare and shift:
  indexToMove = 3
                   0     1     2     3
    +-----+     +-----+-----+-----+-----+
    |  2  |     |  1  |  3  |  4  |  4  |
    +-----+     +-----+-----+-----+-----+
   insertKey                         ^
                                indexToMove

  indexToMove = 2
                   0     1     2     3
    +-----+     +-----+-----+-----+-----+
    |  2  |     |  1  |  3  |  3  |  4  |
    +-----+     +-----+-----+-----+-----+
   insertKey                   ^
                          indexToMove

  indexToMove = 1
                   0     1     2     3
    +-----+     +-----+-----+-----+-----+
    |  2  |     |  1  |  3  |  3  |  4  |
    +-----+     +-----+-----+-----+-----+
   insertKey             ^
                    indexToMove

  insertKey > arr[indexToMove - 1] => 2 > 1 => end the while loop

insert the key (2) in its correct position (1)
    0     1     2     3
 +-----+-----+-----+-----+
 |  1  |  2  |  3  |  4  |
 +-----+-----+-----+-----+
           Sorted
------------------------------------------------------------------

The sorted array:
arr = {1, 2, 3, 4}
 +-----+-----+-----+-----+
 |  1  |  2  |  3  |  4  |
 +-----+-----+-----+-----+

*/