#include <iostream>  // preprocessor directive

using std::cin;  // using declaration
using std::cout;

// function prototype
template <typename T>
void printArray(const std::vector<T>&);
template <typename T>
int linearSearch(const std::vector<T>, const T);

/*
Linear search, also known as sequential search, is a simple searching algorithm
that checks each element in a list or array one by one until the target element
is found or the end of the list is reached.

 Characteristics:
 * Sequential access: It checks elements one by one.
 * Unordered data: It can work on both sorted and unsorted data.
 * Simple implementation: Easy to understand and code.

 Space Complexity: O(1) - Linear search uses a constant amount of extra space
 regardless of the input size:
 * It only uses a few variables (loop counter, array reference, target value)
 * No additional data structures are created

 Time Complexity
 +------------------+------+--------------------------------------------------+
 | Case             | Time | Description                                      |
 +------------------+------+--------------------------------------------------+
 | Best             | O(1) | The target element is the first element          |
 | Worst            | O(n) | The target element is at the end of the array,   |
 |                  |      | or the target element is not in the array at all |
 | Average          | O(n) | Expected number of operations = n/2              |
 +------------------+------+--------------------------------------------------+

 Pros:
 * Works on unsorted data
 * Simple to implement
 * Efficient for small datasets
 * No additional memory required

 Cons:
 * Slow for large datasets
 * Time complexity of O(n) in the worst and average cases
 * Less efficient compared to other algorithms for sorted data

*/

int main() {
  // declaration
  std::vector<int> nums;
  int num, res;

  // input
  cout << "\nEnter numbers, or -1 to stop: ";
  while (cin >> num) {
    if (num == -1) {
      break;
    }
    nums.push_back(num);
  }
  cout << "\nOriginal array:\n";
  printArray(nums);

  cout << "\nEnter number to search: ";
  cin >> num;

  // processing
  res = linearSearch(nums, num);

  // output
  cout << "\n\nResult:\nNumber " << num;
  if (res != -1) {
    cout << " is found in the sorted array at index " << res << "\n\n";
  } else {
    cout << " is not found\n\n";
  }

  return 0;
}

// Output
/*

Enter numbers, or -1 to stop: 1 2 3 4 5 6 7 8 9 10 -1

Original array:
1 2 3 4 5 6 7 8 9 10

Enter number to search: 4


Result:
Number 4 is found in the sorted array at index 3

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

template <typename T>
int linearSearch(const std::vector<T> arr, const T valToSearch) {
  std::size_t size = arr.size();
  for (int i = 0; i < size; i++) {
    if (arr[i] == valToSearch) {
      return i;
    }
  }
  return -1;  // value not found
}

/*

arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
size = 10

    0     1     2     3     4     5     6     7     8     9
 +-----+-----+-----+-----+-----+-----+-----+-----+-----+------+
 |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  10  |
 +-----+-----+-----+-----+-----+-----+-----+-----+-----+------+

valToSearch = 4

Let's start a linear search!
+--------------------------------------------------------------+
 i = 0

     0     1     2     3     4     5     6     7     8     9
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+------+
  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  10  |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+------+
     ^
     i
+--------------------------------------------------------------+
 i = 1

     0     1     2     3     4     5     6     7     8     9
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+------+
  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  10  |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+------+
           ^
           i
+--------------------------------------------------------------+
 i = 2

     0     1     2     3     4     5     6     7     8     9
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+------+
  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  10  |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+------+
                 ^
                 i
+--------------------------------------------------------------+
 i = 3

     0     1     2     3     4     5     6     7     8     9
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+------+
  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  10  |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+------+
                       ^
                       i

 nums[3] == valToSearch == 4
 We found the number!
+--------------------------------------------------------------+
Result:
 Number 4 is found in the sorted array at index 3

*/

/*

Comparison with Binary Search:
 +---------------------------------+--------+----------+
 | Aspect                          | Linear | Binary   |
 +---------------------------------+--------+----------+
 | Time Complexity (Worst/Average) | O(n)   | O(log n) |
 | Time Complexity (Best)          | O(1)   | O(1)     |
 | Space Complexity                | O(1)   | O(1)     |
 | Requires Sorted Data            | No     | Yes      |
 +---------------------------------+--------+----------+

*/