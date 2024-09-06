#include <iostream>

using std::cin;  // using declaration
using std::cout;

/*
Array-based Stack Implementation

A stack is a fundamental data structure in computer science that follows the
Last-In-First-Out (LIFO) principle. This means that the last element added to
the stack is the first one to be removed.

A array-based stack provides efficient O(1) time complexity for both push and
pop operations, making it suitable for many applications where a fixed-size
stack is needed.
*/
template <typename T>
class ArrayStack {
 public:
  // constructor
  ArrayStack() : count(0) {}

  /*
  Initial:
      +-----+
   4  |     |
      +-----+
   3  |     |
      +-----+
   2  |     |
      +-----+
   1  |     |
      +-----+
   0  |     |  count = 0
      +-----+

  After 5 push:
      +-----+
   4  |  5  |  < top
      +-----+
   3  |  4  |
      +-----+
   2  |  3  |
      +-----+
   1  |  2  |
      +-----+
   0  |  1  |  count = 5
      +-----+

  After 2 pop:
      +-----+
   4  |     |
      +-----+
   3  |     |
      +-----+
   2  |  3  |  < top
      +-----+
   1  |  2  |
      +-----+
   0  |  1  |  count = 3
      +-----+
  */

  void push(T newVal) {
    /* Adds an element to the top of the stack. */
    if (isFull()) {
      throw std::runtime_error("Error! Stack is full.\n");
    } else {
      arr[count++] = newVal;
    }
  }

  T pop() {
    /* Removes and returns the top element from the stack. */
    if (isEmpty()) {
      throw std::runtime_error("Error! Stack is empty.\n");
    } else {
      T topNum = arr[--count];
      return topNum;
    }
  }

  bool isEmpty() { return count == 0; }

  bool isFull() { return count == MAX_SIZE; }

  std::size_t size() const { return count; }

  std::size_t maxSize() const { return MAX_SIZE; }

  void printStack() {
    if (isEmpty()) {
      cout << "(Empty)\n";
    } else {
      for (int i = 0; i < count; i++) {
        cout << arr[i] << " ";
      }
      cout << "\n";
    }
  }

 private:
  const static std::size_t MAX_SIZE = 5;
  T arr[MAX_SIZE];
  std::size_t count;
};

// function prototype
void printMenu();

int main() {
  // declaration
  ArrayStack<int> stack;
  int input, num;
  bool isRunning = true;

  // input, processing and output
  while (isRunning) {
    printMenu();
    cout << "Enter your choice: ";
    if (!(cin >> input)) {
      // clear the error flags on the input stream
      cin.clear();
      // clear the input buffer by ignoring characters
      cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      cout << "Invalid input. Please enter a number.\n";
      continue;
    }

    switch (input) {
      case 1:
        std::size_t size;
        cout << "Enter the amount of numbers to push: ";
        if (!(cin >> size)) {
          cin.clear();
          cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          cout << "Invalid input. Please enter a number.\n";
          break;
        }
        if (size + stack.size() > stack.maxSize()) {
          cout << "Error! The stack will be full.\n";
          break;
        }
        cout << "Enter number(s):\n";
        for (std::size_t i = 0; i < size; i++) {
          cout << "> ";
          if (cin >> num) {
            try {
              stack.push(num);
            } catch (std::exception& e) {
              cout << e.what();
              break;
            }
          } else {
            cout << "Invalid input. Stopping push operation.\n";
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
          }
        }
        cout << size << " number(s) is pushed.\n";
        break;
      case 2:
        try {
          num = stack.pop();
          cout << "Popped the number " << num << "\n";
        } catch (std::exception& e) {
          cout << e.what();
        }
        break;
      case 3:
        cout << "Print the stack: ";
        stack.printStack();
        break;
      case 4:
        cout << "Exit the program...\n\n";
        isRunning = false;
        break;
      default:
        cout << "Invalid input!\n";
    }
  }

  return 0;
}

void printMenu() {
  cout << "\n***** Menu *****\n";
  cout << "| 1. Push      |\n";
  cout << "| 2. Pop       |\n";
  cout << "| 3. Print     |\n";
  cout << "| 4. Exit      |\n";
  cout << "****************\n\n";
}

/*
An example of a real-world situation:

Let's think about the Undo Functionality in a Text Editor:
The Undo Functionality is an array-based stack that stores previous states of
the text. Each time text is added, the current state is pushed onto the stack.
The undo operation pops the last state off the stack, effectively reverting the
last change.
*/