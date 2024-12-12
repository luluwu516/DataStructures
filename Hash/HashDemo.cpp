#include "HashTable.cpp"

// function prototype
void printMenu();

int main() {
  // declaration
  HashTable hashTable(5);
  int num, res;
  bool isRunning = true;

  // adding elements
  cout << "\nEnter numbers, -1 to stop: \n> ";
  cin >> num;
  while (num != -1) {
    if (!hashTable.add(num)) {
      cout << "Error! Table is full!\n";
    }
    cin >> num;
  }

  // initial hash table
  cout << "\n\nInitial Table:\n";
  hashTable.printTable();

  while (isRunning) {
    printMenu();
    cout << "Enter your choice: ";
    cin >> num;

    switch (num) {
      case 1: {
        cout << "Enter a number to add: ";
        cin >> num;
        if (hashTable.add(num)) {
          cout << "\n...Added " << num << "\n";
        } else {
          cout << "\n...Table is full! Stop adding.\n";
        }
        break;
      }
      case 2: {
        cout << "Enter a number to search: ";
        cin >> num;
        res = hashTable.search(num);
        if (res != -1) {
          cout << "\n...Found " << num << " at index " << res << "\n";
        } else {
          cout << "\n...Number " << num << " not found!\n";
        }
        break;
      }
      case 3: {
        cout << "Enter a number to delete: ";
        cin >> num;
        if (hashTable.remove(num)) {
          cout << "\n...Number " << num << " is removed\n";
        } else {
          cout << "\n...Error! Number " << num << "doesn't exist!\n";
        }
        break;
      }
      case 4: {
        hashTable.printTable();
        break;
      }
      case 5: {
        cout << "Exit the program...\n";
        isRunning = false;
        break;
      }
      default: {
        cout << "Invalid input!\n";
        break;
      }
    }
  }

  // final hash table
  cout << "\nFinal Table:\n";
  hashTable.printTable();
  cout << "\n";

  return 0;
}

void printMenu() {
  cout << "\n**** Menu ****\n";
  cout << "| 1. Add     |\n";
  cout << "| 2. Lookup  |\n";
  cout << "| 3. Remove  |\n";
  cout << "| 4. Print   |\n";
  cout << "| 5. Exit    |\n";
  cout << "**************\n\n";
}

// Sample Output
/*

*/