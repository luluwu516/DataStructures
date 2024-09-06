#include <iostream>

using std::cin;  // using declaration
using std::cout;

template <typename T>
class ArrayStack {
 public:
  // constructor
  ArrayStack() : count(0) {}

  void push(T newVal) {
    if (isFull()) {
      throw std::runtime_error("Error! Stack is full.\n");
    } else {
      data[count++] = newVal;
    }
  }

  T pop() {
    if (isEmpty()) {
      throw std::runtime_error("Error! Stack is empty.\n");
    } else {
      T topNum = data[--count];
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
        cout << data[i] << " ";
      }
      cout << "\n";
    }
  }

 private:
  const static std::size_t MAX_SIZE = 10;
  T data[MAX_SIZE];
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
      cin.clear();  // clear the error flags on the input stream
      cin.ignore(std::numeric_limits<std::streamsize>::max(),
                 '\n');  // clear the input buffer by ignoring characters
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
            } catch (std::runtime_error& e) {
              cout << e.what();
              break;
            }
          } else {
            std::cout << "Invalid input. Stopping push operation.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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