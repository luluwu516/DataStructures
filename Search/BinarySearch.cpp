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

 +------------------+----------+
 | Time Complexity  | O(log n) |
 +------------------+----------+

Limitations:
1. The data must be sorted before searching.
2. It's only applicable to data structures that allow random access, like
arrays.
3. For small datasets, simpler algorithms like linear search might be faster due
to less overhead.

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
      return mid;       // value is found!
    } else if (arr[mid] < valToSearch) {
      left = mid + 1;   // value is in the right half
    } else {
      right = mid - 1;  // value is in the left half
    }
  }

  return -1;  // value not found
}

/*
Example:

valToSearch = 4
arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, size = 10
left = 0, right = 9

    0     1     2     3     4     5     6     7     8     9
 +-----+-----+-----+-----+-----+-----+-----+-----+-----+------+
 |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  10  |
 +-----+-----+-----+-----+-----+-----+-----+-----+-----+------+
    ^                                                      ^
  left                                                   right

Let's start a binary search!
 Loop 1:
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

 Loop 2:
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

 Loop 3:
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

Loop 4:
     0     1     2     3     4     5     6     7     8     9
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+------+
  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  10  |
  +-----+-----+-----+-----+-----+-----+-----+-----+-----+------+
                       ^
                     right
                      left
                      mid
  Value is found!
  Return index 3

*/