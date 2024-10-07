#include <iostream>  // preprocessor directive
#include <vector>

using std::cin;  // using declaration
using std::cout;

// function prototype
template <typename T>
void printArray(const std::vector<T>&);
template <typename T>
T binarySearch(const std::vector<T>, const T);

/*
Binary search is an efficient algorithm for finding a specific element in a
sorted array or list. It works by repeatedly dividing the search interval in
half, significantly reducing the number of elements that need to be checked
compared to a linear search.

 Characteristics:
 * Requires sorted data
 * Uses divide-and-conquer approach
 * Efficient for large datasets

 Space Complexity: O(1) - Linear search uses a constant amount of extra space
 regardless of the input size:
 * It only uses a few variables (loop counter, array reference, target value)
 * No additional data structures are created

 Time Complexity
 +---------------+----------+-------------------------------------------------+
 | Case          | Time     | Description                                     |
 +---------------+----------+-------------------------------------------------+
 | Best          | O(1)     | The target element is the middle element.       |
 | Worst/Average | O(log n) | In each step, the search space is divided by 2. |
 |               |          | The process continues until the search space is |
 |               |          | reduced to 1. The search ends when n = 2^k.     |
 +---------------+----------+-------------------------------------------------+

 Pros:
 * Very efficient for large sorted datasets
 * Logarithmic time complexity
 * Requires no additional memory

 Cons:
 * Only works on sorted arrays
 * Not efficient for small datasets compared to linear search
 * Requires the data to be stored in a structure allowing random access (like an
   array)

*/

int main() {
  // declaration
  std::vector<int> nums;
  int num, res;

  // input
  cout << "\nEnter numbers, or -1 to stop: ";
  cin >> num;
  while (num != -1) {
    nums.push_back(num);
    cin >> num;
  }

  cout << "\nEnter number to search: ";
  cin >> num;
  cout << "\n\nUnsorted array:\n";
  printArray(nums);

  // processing
  cout << "Sorted array:\n";
  std::sort(nums.begin(), nums.end());
  printArray(nums);
  res = binarySearch(nums, num);

  // output
  cout << "\nNumber " << num;
  if (res != -1) {
    cout << " is found in the sorted array at index " << res << "\n\n";
  } else {
    cout << " is not found\n\n";
  }

  return 0;
}

// Sample output:
/*

Enter numbers, or -1 to stop: 1 2 3 4 5 6 7 8 9 10 -1

Enter number to search: 4


Unsorted array:
1 2 3 4 5 6 7 8 9 10
Sorted array:
1 2 3 4 5 6 7 8 9 10

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
T binarySearch(const std::vector<T> arr, const T valToSearch) {
  std::size_t size = arr.size();
  int left = 0, right = size - 1, mid;

  while (left <= right) {
    // mid = (left + right) / 2;
    // avoid potential overflow
    mid = left + (right - left) / 2;
    if (arr[mid] == valToSearch) {
      return mid;  // value is found!
    } else if (arr[mid] < valToSearch) {
      left = mid + 1;  // value is in the right half
    } else {
      right = mid - 1;  // value is in the left half
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

Let's start a binary search!
+--------------------------------------------------------------+
 Step 1:

     0     1     2     3     4     5     6     7     8     9
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+------+
  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  10  |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+------+
     ^                       ^                              ^
   left                     mid                           right

  Value is in the left half. Move the right variable.
     0     1     2     3     4     5     6     7     8     9
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+------+
  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  10  |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+------+
     ^                 ^     ^
   left              right  mid

+--------------------------------------------------------------+
 Step 2:

     0     1     2     3     4     5     6     7     8     9
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+------+
  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  10  |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+------+
     ^     ^           ^
   left   mid        right

  Value is in the right half. Move the left variable.
     0     1     2     3     4     5     6     7     8     9
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+------+
  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  10  |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+------+
           ^     ^     ^
          mid  left   right

+--------------------------------------------------------------+
 Step 3:

     0     1     2     3     4     5     6     7     8     9
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+------+
  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  10  |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+------+
                 ^     ^
               left   right
                mid

  Value is in the right half. Move the left variable.
     0     1     2     3     4     5     6     7     8     9
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+------+
  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  10  |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+------+
                 ^     ^
                mid  right
                      left

+--------------------------------------------------------------+
 Step 4:

     0     1     2     3     4     5     6     7     8     9
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+------+
  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  10  |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+------+
                       ^
                     right
                      left
                      mid
  Value is found!
  nums[3] == valToSearch == 4
  Return index 3
+--------------------------------------------------------------+
Result:
 Number 4 is found in the sorted array at index 3

*/

/*

Comparison with Linear Search:
 +---------------------------------+--------+----------+
 | Aspect                          | Linear | Binary   |
 +---------------------------------+--------+----------+
 | Time Complexity (Worst/Average) | O(n)   | O(log n) |
 | Time Complexity (Best)          | O(1)   | O(1)     |
 | Space Complexity                | O(1)   | O(1)     |
 | Requires Sorted Data            | No     | Yes      |
 +---------------------------------+--------+----------+

*/