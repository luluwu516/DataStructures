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

 Time Complexity
 +------------------+--------+
 | Best             | O(n)   |    // If the array is already sorted
 +------------------+--------+
 | Worst            | O(n^2) |
 +------------------+--------+
 | Average          | O(n^2) |
 +------------------+--------+

 +------------------+--------+
 | Space Complexity | O(1)   |
 +------------------+--------+

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

// it requires two loops:
// the number of comparisons is: (n-1) + (n-2) + (n-3) +.....+ 1 = n(n-1)/2
// Complexity: O(n^2)
template <typename T>
void bubbleSort(std::vector<T>& arr) {
  std::size_t size = arr.size();
  if (!size) {
    return;
  }

  // for bubble sort, each iteration takes the largest (ascending order) to the
  // last position
  for (std::size_t step = 0; step < size - 1; step++) {
    // check if swapping occurs in this step
    bool isSwapped = false;

    // loop to access each array element and compare it with the next element
    for (std::size_t i = 0; i < size - 1 - step; i++) {
      // sort in ascending order, so if arr[i] greater arr[i + 1], swap two
      // elements
      if (arr[i] > arr[i + 1]) {
        // T temp = arr[i];
        // arr[i] = arr[i + 1];
        // arr[i + 1] = temp;
        std::swap(arr[i], arr[i + 1]);

        isSwapped = true;
      }
    }

    // if no swapping occurs, which means the array is sorted, then break the
    // loop
    if (!isSwapped) {
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
step = 0:
 isSwapped == false
 i < size - 1 - step (3 - 1 - 0)
 i < 2
+---------------------+-------------+---------------------+
| i = 0               | i[0] > i[1] | isSwapped == true   |
| +-----+-----+-----+ |  3   >  1   | +-----+-----+-----+ |
| |  3  |  1  |  2  | +-------------+ |  1  |  3  |  2  | |
| +-----+-----+-----+ |    True     | +-----+-----+-----+ |
+---------------------+-------------+---------------------+
| i = 1               | i[0] > i[1] | isSwapped == true   |
| +-----+-----+-----+ |  3   >  2   | +-----+-----+-----+ |
| |  1  |  3  |  2  | +-------------+ |  1  |  2  |  3  | |
| +-----+-----+-----+ |    True     | +-----+-----+-----+ |
+---------------------+-------------+---------------------+

step = 1:
 isSwapped == false
 i < size - 1 - step (3 - 1 - 1)
 i < 1
+---------------------+--------------+---------------------+
| i = 0               | i[0] !> i[1] | no swapping!        |
| +-----+-----+-----+ |  1   !>  2   |                     |
| |  1  |  2  |  3  | +--------------+                     |
| +-----+-----+-----+ |    False     |                     |
+---------------------+--------------+---------------------+
 !isSwapped == true -> break the loop!

The sorted array:
arr = {1, 2, 3}
 +-----+-----+-----+
 |  1  |  2  |  3  |
 +-----+-----+-----+

*/