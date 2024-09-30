#include <iostream>  // preprocessor directive

using std::cin;  // using declaration
using std::cout;

// function prototypes
template <typename T>
void printArray(const std::vector<T>&);
template <typename T>
void selectionSort(std::vector<T>&);

/*
Selection Sort
Selection sort is a simple and intuitive sorting algorithm that works by
repeatedly finding the minimum element from the unsorted part of the list and
placing it at the beginning of the sorted part.

Key characteristics:

1. It performs well on small lists but becomes inefficient for large lists.
2. It makes the minimum number of swaps (O(n)) compared to other algorithms like
bubble sort.
3. Its performance is consistent regardless of the initial order of elements.
4. It's not adaptive, meaning its time complexity doesn't improve for partially
sorted arrays.

 Time Complexity
 +------------------+--------+-----------------------------------------------+
 | Case             | Time   | Description                                   |
 +------------------+--------+-----------------------------------------------+
 | Best             | O(n^2) | Array is already sorted                       |
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
  selectionSort(nums);

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

// Selection Sort Implementation
// the number of comparisons is: (n-1) + (n-2) + (n-3) +.....+ 1 = n (n - 1) / 2
// Complexity: O(n^2)
template <typename T>
void selectionSort(std::vector<T>& arr) {
  std::size_t size = arr.size();
  // arrays of size 0 or 1 are already sorted
  if (size <= 1) {
    return;
  }

  // iterate through the array
  for (std::size_t i = 0; i < size - 1; i++) {
    // assume the current index has the minimum value
    int minIndex = i;
    // find the minimum element in the unsorted portion
    for (std::size_t j = i + 1; j < size; j++) {
      // if find a smaller element, update minIndex
      if (arr[minIndex] > arr[j]) {
        minIndex = j;
      }
    }

    // swap the found minimum element with the minIndex element
    if (minIndex != i) {
      std::swap(arr[i], arr[minIndex]);
    } else {
      // if no swapping occurred in this pass, the array is already sorted
      break;
    }
  }
}