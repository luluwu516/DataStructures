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

 Time Complexity
 +------------------+--------+
 | Best             | O(n)   |
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
  if (!size) {
    return;
  }

  // assume the first element in the array is sorted, so start at index 1
  for (std::size_t next = 1; next < size; next++) {
    // save the value of the next element for insertion
    T insertKey = arr[next];

    // initialize the index for placing the element
    std::size_t indexToMove = next;

    // search for the location and move the elements
    while (indexToMove > 0 && insertKey < arr[indexToMove - 1]) {
      // if it is not in ascending order, shift the element one slot to the
      // right
      arr[indexToMove] = arr[indexToMove - 1];
      // update the indexToMove
      --indexToMove;
    }

    // place the insert key back to the correct position
    arr[indexToMove] = insertKey;
  }
}
