#include <iostream>  // preprocess directive

// using namespace std;  // using directive
using std::cin;  // using declaration
using std::cout;

int main() {
  // declaration
  int size, num;
  int *nums;

  // input and processing
  cout << "\nEnter the size of the array: ";
  cin >> size;

  nums = new int[size];  // to allocate memory
  cout << "Enter numbers (-1 to stop): \n";
  for (int i = 0; i < size; i++) {
    cout << "> ";
    cin >> num;
    if (num == -1) {
      break;
    }
    nums[i] = num;
  }

  // output
  cout << "\nResult: ";
  for (int i = 0; i < size; i++) {
    cout << nums[i] << " ";
  }
  cout << "\n\n";

  return 0;
}