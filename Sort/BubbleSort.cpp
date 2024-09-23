#include <iostream>  // preprocessor directive
#include <vector>

using std::cin;  // using declaration
using std::cout;

// function prototypes
template <typename T>
void printArray(const std::vector<T>&);
template <typename T>
void bubbleSort(std::vector<T>&);

/*
Bubble sort is a sorting algorithm that repeatedly steps through a list,
compares adjacent elements, and swaps them if they're in the wrong order. This
process is repeated until the entire list is sorted.

Key characteristics:


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
  bubbleSort(nums);

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

// Bubble Sort Implementation
// the number of comparisons is: (n-1) + (n-2) + (n-3) +.....+ 1 = n (n - 1) / 2
// Complexity: O(n^2)
template <typename T>
void bubbleSort(std::vector<T>& arr) {
  std::size_t size = arr.size();
  // arrays of size 0 or 1 are already sorted
  if (size <= 1) {
    return;
  }

  // for bubble sort, each iteration takes the largest (ascending order) to the
  // last position
  for (std::size_t step = 0; step < size - 1; step++) {
    // flag to optimize for already sorted arrays
    bool isSwapped = false;

    // in each iteration, the largest unsorted element "bubbles up" to its
    // correct position
    for (std::size_t i = 0; i < size - 1 - step; i++) {
      // compare adjacent elements and swap if they're in the wrong order
      if (arr[i] > arr[i + 1]) {
        // T temp = arr[i];
        // arr[i] = arr[i + 1];
        // arr[i + 1] = temp;
        std::swap(arr[i], arr[i + 1]);

        isSwapped = true;
      }
    }

    // if no swapping occurred in this pass, the array is already sorted
    if (!isSwapped) {
      // break the loop
      break;
    }
  }
}

/*
Example:

arr = {3, 1, 2}
size = 3
 +-----+-----+-----+
 |  3  |  1  |  2  |
 +-----+-----+-----+

Let's start a bubble sort!
+----------------------------------------------------------+
|                        step = 0                          |
+----------------------------------------------------------+
  i = 0
     0     1     2
  +-----+-----+-----+
  |  3  |  1  |  2  |
  +-----+-----+-----+
     ^     ^
  arr[0] arr[1]

  isSwapped = true
  +-----+-----+-----+
  |  1  |  3  |  2  |
  +-----+-----+-----+

+----------------------------------------------------------+
  i = 1
     0     1     2
  +-----+-----+-----+
  |  1  |  3  |  2  |
  +-----+-----+-----+
           ^     ^
         arr[1] arr[2]

  isSwapped = true
  +-----+-----+-----+
  |  1  |  2  |  3  |
  +-----+-----+-----+

+----------------------------------------------------------+
|                        step = 1                          |
+----------------------------------------------------------+
  i = 0
     0     1     2
  +-----+-----+-----+
  |  1  |  2  |  3  |
  +-----+-----+-----+
     ^     ^
  arr[0] arr[1]
  isSwapped = false

------------------------------------------------------------
The sorted array:
arr = {1, 2, 3}
 +-----+-----+-----+
 |  1  |  2  |  3  |
 +-----+-----+-----+

*/