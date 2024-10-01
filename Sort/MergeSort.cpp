#include <iostream>  // preprocessor directive
#include <vector>

using std::cin;  // using declaration
using std::cout;

// function prototype
template <typename T>
void printArray(const std::vector<T>&);
template <typename T>
void mergeSort(std::vector<T>&, int, int);
template <typename T>
void merge(std::vector<T>&, int, int, int);

/*
Merge sort is a divide-and-conquer algorithm that was invented by John von
Neumann in 1945. It's an efficient, comparison-based sorting algorithm that
works on the principle of breaking down a list into smaller subarrays until each
subarray consists of a single element, and then merging those subarrays back
together to form a final sorted list.

Key characteristics:

1. Divide and Conquer: Merge sort uses the divide-and-conquer approach. It
divides the input array into two halves, recursively sorts them, and then merges
the two sorted halves.
2. Stable: Merge sort is a stable sorting algorithm, meaning it preserves the
relative order of equal elements.
3. Not in-place: Merge sort requires additional space to merge the sorted
subarrays.
4. Recursive: The algorithm is typically implemented recursively, although
iterative versions exist.

 Time Complexity
 +------------------+------------+-------------------------------------------+
 | Case             | Time       | Description                               |
 +------------------+------------+-------------------------------------------+
 | Best             | O(n log n) | Array is already sorted                   |
 | Worst            | O(n log n) | Array is in reverse order                 |
 | Average          | O(n log n) | Random arrangement of elements            |
 +------------------+------------+-------------------------------------------+

 Space Complexity: O(n) - Not sorts in-place.
 * It requires additional space to store the temporary arrays during the merging
process.
 * Merge sort requires additional space to merge the sorted subarrays.

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
  mergeSort(nums, 0, nums.size() - 1);

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

// Merge Sort Implementation
// Complexity: O(n log n)
template <typename T>
void mergeSort(std::vector<T>& arr, int lefint, int right) {
  // Base Case: if the subarray has more than one element
  if (left < right) {
    // calculate the middle index, avoiding potential overflow
    // it's equal to `(left + right) / 2`
    T mid = left + (right - left) / 2;

    // divide the left half array to half recursively
    mergeSort(arr, left, mid);
    // divide the right half array to half recursively
    mergeSort(arr, mid + 1, right);

    // merge the sorted halves
    merge(arr, left, mid, right);
  }
}

// utility function to merge two sorted subarrays
template <typename T>
void merge(std::vector<T>& arr, int left, int mid, int right) {
  // calculate sizes of two subarrays to be merged
  int n1 = mid - left + 1;
  int n2 = right - mid;

  // create temporary arrays
  std::vector<T> L(n1), R(n2);

  // Copy data to temporary arrays L[] and R[]
  for (std::size_t i = 0; i < n1; i++) {
    L[i] = arr[left + i];
  }
  for (int j = 0; j < n2; j++) {
    R[j] = arr[mid + 1 + j];
  }

  // merge the temporary arrays back into arr
  int i = 0, j = 0, k = left;

  // compare elements from L and R and place the smaller one in arr
  while (i < n1 && j < n2) {
    if (L[i] <= R[j]) {
      arr[k] = L[i];
      i++;
    } else {
      arr[k] = R[j];
      j++;
    }
    k++;
  }

  // copy remaining elements of L[], if any
  while (i < n1) {
    arr[k] = L[i];
    i++;
    k++;
  }

  // copy remaining elements of R[], if any
  while (j < n2) {
    arr[k] = R[j];
    j++;
    k++;
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

Let's start an merge sort!

First, divide the unsorted list into the one-element list, which is considered
sorted. We use the recursion function in the program to approach this.

             0     1     2     3
          +-----+-----+-----+-----+
          |  3  |  1  |  4  |  2  |
          +-----+-----+-----+-----+

       0     1                 2     3
    +-----+-----+           +-----+-----+
    |  3  |  1  |           |  4  |  2  |
    +-----+-----+           +-----+-----+

    0           1           2           3
 +-----+     +-----+     +-----+     +-----+
 |  3  |     |  1  |     |  4  |     |  2  |
 +-----+     +-----+     +-----+     +-----+

Second, repeatedly merge subarrays to produce new sorted subarrays until there
is only one subarray remaining. This will be the sorted list.

      0            0               0     1
   +-----+      +-----+         +-----+-----+
 L |  3  |    R |  1  |     arr |     |     |
   +-----+      +-----+         +-----+-----+
      ^            ^               ^
      i            j               k

      0            0               0     1
   +-----+      +-----+         +-----+-----+
 L |  3  |    R |  1  |     arr |  1  |     |
   +-----+      +-----+         +-----+-----+
      ^                                  ^
      i                                  k

      0            0               0     1
   +-----+      +-----+         +-----+-----+
 L |  3  |    R |  1  |     arr |  1  |  3  |
   +-----+      +-----+         +-----+-----+

+---------------------------------------------------------------------+
      0            0               2     3
   +-----+      +-----+         +-----+-----+
 L |  4  |    R |  2  |     arr |     |     |
   +-----+      +-----+         +-----+-----+
      ^            ^               ^
      i            j               k

      0            0               2     3
   +-----+      +-----+         +-----+-----+
 L |  4  |    R |  2  |     arr |  2  |     |
   +-----+      +-----+         +-----+-----+
      ^                                  ^
      i                                  k

      0            0               2     3
   +-----+      +-----+         +-----+-----+
 L |  4  |    R |  2  |     arr |  2  |  4  |
   +-----+      +-----+         +-----+-----+

+=====================================================================+
      0     1            0     1               0     1     2     3
   +-----+-----+      +-----+-----+         +-----+-----+-----+-----+
 L |  1  |  3  |    R |  2  |  4  |     arr |     |     |     |     |
   +-----+-----+      +-----+-----+         +-----+-----+-----+-----+
      ^                 ^                      ^
      i                 j                      k

      0     1            0     1               0     1     2     3
   +-----+-----+      +-----+-----+         +-----+-----+-----+-----+
 L |  1  |  3  |    R |  2  |  4  |     arr |  1  |     |     |     |
   +-----+-----+      +-----+-----+         +-----+-----+-----+-----+
            ^            ^                           ^
            i            j                           k

      0     1            0     1               0     1     2     3
   +-----+-----+      +-----+-----+         +-----+-----+-----+-----+
 L |  1  |  3  |    R |  2  |  4  |     arr |  1  |  2  |     |     |
   +-----+-----+      +-----+-----+         +-----+-----+-----+-----+
            ^                  ^                           ^
            i                  j                           k

      0     1            0     1               0     1     2     3
   +-----+-----+      +-----+-----+         +-----+-----+-----+-----+
 L |  1  |  3  |    R |  2  |  4  |     arr |  1  |  2  |  3  |     |
   +-----+-----+      +-----+-----+         +-----+-----+-----+-----+
                               ^                                 ^
                               j                                 k

      0     1            0     1               0     1     2     3
   +-----+-----+      +-----+-----+         +-----+-----+-----+-----+
 L |  1  |  3  |    R |  2  |  4  |     arr |  1  |  2  |  3  |  4  |
   +-----+-----+      +-----+-----+         +-----+-----+-----+-----+

+=====================================================================+
             0     1     2     3
          +-----+-----+-----+-----+
          |  3  |  1  |  4  |  2  |
          +-----+-----+-----+-----+

       0     1                 2     3
    +-----+-----+           +-----+-----+
    |  3  |  1  |           |  4  |  2  |
    +-----+-----+           +-----+-----+

    0           1           2           3
 +-----+     +-----+     +-----+     +-----+
 |  3  |     |  1  |     |  4  |     |  2  |
 +-----+     +-----+     +-----+     +-----+

       0     1                 2     3
    +-----+-----+           +-----+-----+
    |  1  |  3  |           |  2  |  4  |
    +-----+-----+           +-----+-----+

             0     1     2     3
          +-----+-----+-----+-----+
          |  1  |  2  |  3  |  4  |
          +-----+-----+-----+-----+

The sorted array:
arr = {1, 2, 3, 4}
 +-----+-----+-----+-----+
 |  1  |  2  |  3  |  4  |
 +-----+-----+-----+-----+

*/