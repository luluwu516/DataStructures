#include <iostream>  // preprocessor directive

using std::cin;  // using declaration
using std::cout;

// function prototype
template <typename T>
void printArray(const std::vector<T>&);
template <typename T>
void quickSort(std::vector<T>&, int, int);
template <typename T>
int partition(std::vector<T>&, int, int);

/*
Quicksort is a highly efficient and widely used sorting algorithm developed by
British computer scientist Tony Hoare in 1960. It's a comparison-based,
divide-and-conquer algorithm that works by selecting a 'pivot' element from the
array and partitioning the other elements into two sub-arrays, according to
whether they are less than or greater than the pivot. The sub-arrays are then
sorted recursively. Quicksort's efficiency comes from the fact that it doesn't
need to compare every element with every other element.

Key characteristics:

1. Basic principle: Quicksort works on the divide-and-conquer principle. It
divides the input array into smaller parts, sorts them independently, and then
combines them to get the final sorted array.
2. Pivot selection: The algorithm chooses an element as a pivot (often the last
or a random element) and partitions the array around this pivot.
3. Partitioning: All elements smaller than the pivot are moved before it, and
all greater elements are moved after it. This is the key process of quicksort.
4. Recursion: The algorithm then recursively applies the above steps to the
sub-array of elements with smaller values and the sub-array of elements with
greater values.
5. Efficiency: Quicksort is notable for its efficiency, with an average time
complexity of O(n log n), making it one of the fastest sorting algorithms in
practice.
6. In-place sorting: Quicksort is typically implemented as an in-place sorting
algorithm, which means it doesn't require much additional memory beyond the
original array.
7. Widespread use: Due to its efficiency and relatively simple implementation,
quicksort is a popular choice in real-world applications and is often used as a
default sorting algorithm in various programming languages and libraries.

 Time Complexity
 +------------------+------------+-------------------------------------------+
 | Case             | Time       | Description                               |
 +------------------+------------+-------------------------------------------+
 | Best             | O(n log n) | Array is already sorted                   |
 | Worst            | O(n log n) | Array is in reverse order                 |
 | Average          | O(n^2)     | Random arrangement of elements            |
 +------------------+------------+-------------------------------------------+

 Space Complexity:
 * O(log n) average case for the recursive call stack
 * O(n) worst case, when the recursion doesn't divide the array evenly (e.g.,
already sorted array)

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
  quickSort(nums, 0, nums.size() - 1);

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
// Number of comparisons is: (n-1) + (n-2) + (n-3) +.....+ 1 = n (n - 1) / 2
// Complexity: O(n log n)
template <typename T>
void quickSort(std::vector<T>& arr, int low, int high) {
  if (low < high) {
    // pi is partitioning index, arr[pi] is now at right place
    int pi = partition(arr, low, high);

    // recursively sort elements before and after partition
    quickSort(arr, low, pi - 1);
    quickSort(arr, pi + 1, high);
  }
}

// utility function to partition the array
template <typename T>
int partition(std::vector<T>& arr, int low, int high) {
  // choose the rightmost element as pivot
  int pivot = arr[high];
  // index of smaller element
  int i = (low - 1);

  for (int j = low; j < high; j++) {
    // if current element is smaller than or equal to pivot
    if (arr[j] <= pivot) {
      // increment index of smaller element
      i++;
      std::swap(arr[i], arr[j]);
    }
  }
  std::swap(arr[i + 1], arr[high]);
  return (i + 1);
}

/*
Example:

arr = {3, 1, 4, 2}
size = 4
    0     1     2     3
 +-----+-----+-----+-----+
 |  3  |  1  |  4  |  2  |
 +-----+-----+-----+-----+

Let's start an quick sort!

First, select the pivot.
There are different variations of quicksort in which the pivot element is
selected from different positions, such as the first, last, and middle elements.
In this case, we will use the last (rightmost) element as the pivot.

             -1     0     1     2     3
+-----+          +-----+-----+-----+-----+
|  2  |          |  3  |  1  |  4  |  2  |
+-----+          +-----+-----+-----+-----+
 pivot        ^
              i

+=====================================================================+
Secondly, rearrange the array (partitioning).

j = 0

             -1     0     1     2     3
+-----+          +-----+-----+-----+-----+
|  2  |          |  3  |  1  |  4  |  2  |
+-----+          +-----+-----+-----+-----+
 pivot        ^     ^
              i     j

+---------------------------------------------------------------------+
j = 1

             -1     0     1     2     3
+-----+          +-----+-----+-----+-----+
|  2  |          |  3  |  1  |  4  |  2  |
+-----+          +-----+-----+-----+-----+
 pivot        ^           ^
              i           j

1 <= 2
             -1     0     1     2     3
+-----+          +-----+-----+-----+-----+
|  2  |          |  1  |  3  |  4  |  2  |
+-----+          +-----+-----+-----+-----+
 pivot              ^     ^
                    i     j

+---------------------------------------------------------------------+
j = 2

             -1     0     1     2     3
+-----+          +-----+-----+-----+-----+
|  2  |          |  1  |  3  |  4  |  2  |
+-----+          +-----+-----+-----+-----+
 pivot              ^           ^
                    i           j

+---------------------------------------------------------------------+
swap(arr[i + 1], arr[high])
             -1     0     1     2     3
+-----+          +-----+-----+-----+-----+
|  2  |          |  1  |  3  |  4  |  2  |
+-----+          +-----+-----+-----+-----+
 pivot                    ^           ^
                        i + 1     arr[high]

             -1     0     1     2     3
+-----+          +-----+-----+-----+-----+
|  2  |          |  1  |  2  |  4  |  3  |
+-----+          +-----+-----+-----+-----+
 pivot                    ^
                        pivot

All elements smaller than the pivot are moved before it, and all greater
elements are moved after it.
+=====================================================================+
Thirdly, The algorithm then recursively applies the above steps to the subarray
of elements with smaller values and the subarray of elements with greater
values.
          0     1     2     3
       +-----+-----+-----+-----+
       |  1  |  2  |  4  |  3  |
       +-----+-----+-----+-----+
                ^
    0           1           2     3
 +-----+     +-----+     +-----+-----+
 |  1  |     |  2  |     |  4  |  3  |
 +-----+     +-----+     +-----+-----+

+=====================================================================+
For each subarray, back to the first step: select the pivot

               1     2     3
 +-----+          +-----+-----+
 |  3  |          |  4  |  3  |
 +-----+          +-----+-----+
  pivot        ^
               i

Again, rearrange the array (partitioning).
j = 0
              1     2     3
+-----+          +-----+-----+
|  3  |          |  4  |  3  |
+-----+          +-----+-----+
 pivot        ^     ^
              i     j

swap(arr[i + 1], arr[high])
              1     2     3
+-----+          +-----+-----+
|  3  |          |  4  |  3  |
+-----+          +-----+-----+
 pivot              ^     ^
                  i + 1 arr[high]

              1     2     3
+-----+          +-----+-----+
|  3  |          |  3  |  4  |
+-----+          +-----+-----+
 pivot              ^
                  pivot

+=====================================================================+
The subarrays are divided until each subarray is formed of a single element. At
this point, the array is already sorted.

             0     1     2     3
          +-----+-----+-----+-----+
          |  1  |  2  |  3  |  4  |
          +-----+-----+-----+-----+

    0           1           2           3
 +-----+     +-----+     +-----+     +-----+
 |  1  |     |  2  |     |  3  |     |  4  |
 +-----+     +-----+     +-----+     +-----+

+=====================================================================+
The sorted array:
arr = {1, 2, 3, 4}
 +-----+-----+-----+-----+
 |  1  |  2  |  3  |  4  |
 +-----+-----+-----+-----+

The efficiency of quicksort comes from the fact that it doesn't need to compare
every element with every other element!
*/