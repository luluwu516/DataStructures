#include <iostream>  // preprocessor directive

using std::cin;  // using declaration
using std::cout;

/*
Array-based Queue Implementation with circular buffer

A queue is a fundamental data structure in computer science that follows the
First-In-First-Out (FIFO) principle. This means that the first element added to
the stack is the first one to be removed.

A array-based queue provides efficient O(1) time complexity for both enqueue and
dequeue operations, making it suitable for many applications where a fixed-size
queue is needed.
*/
template <typename T>
class ArrayQueue {
 public:
  // constructor
  ArrayQueue() : count(0), front(0), back(-1) {}

  /*
  A circular buffer, also known as a ring buffer, is a data structure that uses
  a single, fixed-size buffer as if it were connected end-to-end.

  Initial:
    -1     0     1     2     3     4        count = 0
        +-----+-----+-----+-----+-----+
        |     |     |     |     |     |
        +-----+-----+-----+-----+-----+
    ^      ^
   back  front

  After 5 enqueue:
    -1     0     1     2     3     4        count = 5
        +-----+-----+-----+-----+-----+
        |  1  |  2  |  3  |  4  |  5  |
        +-----+-----+-----+-----+-----+
           ^                       ^
         front                    back

  After 2 dequeue:
    -1     0     1     2     3     4        count = 3
        +-----+-----+-----+-----+-----+
        |     |     |  3  |  4  |  5  |
        +-----+-----+-----+-----+-----+
                       ^           ^
                     front        back

  After 2 enqueue:
    -1     0     1     2     3     4        count = 5
        +-----+-----+-----+-----+-----+
        |  6  |  7  |  3  |  4  |  5  |
        +-----+-----+-----+-----+-----+
                 ^     ^
                back front
  */
  void enqueue(T newVal) {
    /* Adds an element to the back of the queue. */
    if (isFull()) {
      throw std::runtime_error("Error! Queue is full.\n");
    } else {
      // When reaching the end of the physical array, "wrap around" to the
      // beginning using the modulo operator (%)
      back = (back + 1) % MAX_SIZE;
      arr[back] = newVal;
      count++;
    }
  }

  T dequeue() {
    /* Removes and returns the element from the front of the queue. */
    if (isEmpty()) {
      throw std::runtime_error("Error! Queue is empty.\n");
    } else {
      // When reaching the end of the physical array, "wrap around" to the
      // beginning using the modulo operator (%)
      T frontNum = arr[front];
      front = (front + 1) % MAX_SIZE;
      count--;
      return frontNum;
    }
  }

  bool isEmpty() const { return count == 0; }

  bool isFull() const { return count == MAX_SIZE; }

  size_t size() const { return count; }

  size_t maxSize() const { return MAX_SIZE; }

  void printQueue() {
    if (isEmpty()) {
      cout << "(Empty)\n";
    } else {
      int i = front;
      for (int counter = 0; counter < count; counter++) {
        cout << arr[i] << " ";
        i = (i + 1) % MAX_SIZE;
      }
      cout << "\n";
    }
  }

 private:
  const static size_t MAX_SIZE = 5;
  T arr[MAX_SIZE];
  std::size_t count;
  int front;
  int back;
};

// function prototype
void printMenu();

int main() {
  // declaration
  ArrayQueue<int> queue;
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
        cout << "Enter the amount of numbers to enqueue: ";
        if (!(cin >> size)) {
          cin.clear();
          cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          cout << "Invalid input. Please enter a number.\n";
          break;
        }
        if (size + queue.size() > queue.maxSize()) {
          cout << "Error! The stack will be full.\n";
          break;
        }
        cout << "Enter number(s): \n";
        for (std::size_t i = 0; i < size; i++) {
          cout << "> ";
          if (cin >> num) {
            try {
              queue.enqueue(num);
            } catch (std::exception& e) {
              cout << e.what();
              break;
            }
          } else {
            size = i;
            cout << "Invalid input. Stopping enqueue operation.\n";
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
          }
        }
        cout << size << " number(s) is enqueued.\n";
        break;
      case 2:
        try {
          num = queue.dequeue();
          cout << "Dequeued the number " << num << "\n";
        } catch (std::exception& e) {
          cout << e.what();
        }
        break;
      case 3:
        cout << "Print the queue: ";
        queue.printQueue();
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
  cout << "| 1. Enqueue   |\n";
  cout << "| 2. Dequeue   |\n";
  cout << "| 3. Print     |\n";
  cout << "| 4. Exit      |\n";
  cout << "****************\n\n";
}

/*
An example of a real-world situation:

Let's consider a scenario in the context of a print job management system for a
shared office printer:
1. First-In-First-Out (FIFO) Order: Print jobs should typically be processed in
the order they were submitted. A queue naturally enforces this FIFO behavior.

2. Fixed Capacity: Most printers have a limit on how many jobs they can queue.
Our array-based queue with a fixed size (50 in this example) reflects this
limitation.

3. Efficient Operations: Adding a new print job (enqueue) and processing the
next job (dequeue) are both O(1) operations, ensuring quick response times even
when the queue is nearly full.

4. Bounded Memory Usage: The fixed-size array ensures that the print job manager
doesn't consume an unbounded amount of memory, which is important for a
long-running system.
*/