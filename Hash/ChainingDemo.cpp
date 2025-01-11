#include "Chaining.cpp"

// function prototype
void printMenu();

int main() {
  // declaration
  Chaining chaining(5);
  int choice, key;
  std::string value, res;
  bool isRunning = true;

  while (isRunning) {
    printMenu();
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
      case 1: {
        cout << "Enter a key to add: ";
        cin >> key;
        cout << "Enter a string: ";
        cin >> value;

        if (chaining.add(key, value)) {
          cout << "\n...Added " << key << ", " << value
               << ", to the hash table\n";
        } else {
          cout << "\n...Key duplicated. Old value is replaced\n";
        }
        break;
      }
      case 2: {
        cout << "Enter a key to search: ";
        cin >> key;
        res = chaining.search(key);

        cout << "\nResult: ";
        cout << res << "\n";
        break;
      }
      case 3: {
        cout << "Enter a key to delete: ";
        cin >> key;
        res = chaining.remove(key);

        cout << "\nResult: ";
        cout << res << "\n";
        break;
      }
      case 4: {
        chaining.printChaining();
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
  cout << "\nFinal Chaining:\n";
  chaining.printChaining();
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

Five-bucket chaining hashtable is created...

+=====+
|  0  |-(Empty)
+=====+
+=====+
|  1  |-(Empty)
+=====+
+=====+
|  2  |-(Empty)
+=====+
+=====+
|  3  |-(Empty)
+=====+
+=====+
|  4  |-(Empty)
+=====+

**** Menu ****
| 1. Add     |
| 2. Lookup  |
| 3. Remove  |
| 4. Print   |
| 5. Exit    |
**************

Enter your choice: 1
Enter a key to add: 11
Enter a string: Judy

...Added 11, Judy, to the hash table

+=====+
|  0  |-(Empty)
+=====+
+=====+ +------+------+
|  1  |-|  11  + Judy |
+=====+ +------+------+
+=====+
|  2  |-(Empty)
+=====+
+=====+
|  3  |-(Empty)
+=====+
+=====+
|  4  |-(Empty)
+=====+

**** Menu ****
| 1. Add     |
| 2. Lookup  |
| 3. Remove  |
| 4. Print   |
| 5. Exit    |
**************

Enter your choice: 1
Enter a key to add: 1
Enter a string: Andy

...Added 1, Andy, to the hash table

+=====+
|  0  |-(Empty)
+=====+
+=====+ +-----+------+ +------+------+
|  1  |-|  1  + Andy |-|  11  + Judy |
+=====+ +-----+------+ +------+------+
+=====+
|  2  |-(Empty)
+=====+
+=====+
|  3  |-(Empty)
+=====+
+=====+
|  4  |-(Empty)
+=====+

**** Menu ****
| 1. Add     |
| 2. Lookup  |
| 3. Remove  |
| 4. Print   |
| 5. Exit    |
**************

Enter your choice: 1
Enter a key to add: 6
Enter a string: Candy

...Added 6, Candy, to the hash table

+=====+
|  0  |-(Empty)
+=====+
+=====+ +-----+------+ +-----+-------+ +------+------+
|  1  |-|  1  + Andy |-|  6  + Candy |-|  11  + Judy |
+=====+ +-----+------+ +-----+-------+ +------+------+
+=====+
|  2  |-(Empty)
+=====+
+=====+
|  3  |-(Empty)
+=====+
+=====+
|  4  |-(Empty)
+=====+

**** Menu ****
| 1. Add     |
| 2. Lookup  |
| 3. Remove  |
| 4. Print   |
| 5. Exit    |
**************

Enter your choice: 4
[0]: (Empty)
[1]: 1-Andy 6-Candy 11-Judy
[2]: (Empty)
[3]: (Empty)
[4]: (Empty)

+=====+
|  0  |-(Empty)
+=====+
+=====+ +-----+------+ +-----+-------+ +------+------+
|  1  |-|  1  + Andy |-|  6  + Candy |-|  11  + Judy |
+=====+ +-----+------+ +-----+-------+ +------+------+
+=====+
|  2  |-(Empty)
+=====+
+=====+
|  3  |-(Empty)
+=====+
+=====+
|  4  |-(Empty)
+=====+

**** Menu ****
| 1. Add     |
| 2. Lookup  |
| 3. Remove  |
| 4. Print   |
| 5. Exit    |
**************

Enter your choice: 1
Enter a key to add: 6
Enter a string: Mandy

...Key duplicated. Old value is replaced

+=====+
|  0  |-(Empty)
+=====+
+=====+ +-----+------+ +-----+-------+ +------+------+
|  1  |-|  1  + Andy |-|  6  + Mandy |-|  11  + Judy |
+=====+ +-----+------+ +-----+-------+ +------+------+
+=====+
|  2  |-(Empty)
+=====+
+=====+
|  3  |-(Empty)
+=====+
+=====+
|  4  |-(Empty)
+=====+

**** Menu ****
| 1. Add     |
| 2. Lookup  |
| 3. Remove  |
| 4. Print   |
| 5. Exit    |
**************

Enter your choice: 1
Enter a key to add: 4
Enter a string: Lulu

...Added 4, Lulu, to the hash table

+=====+
|  0  |-(Empty)
+=====+
+=====+ +-----+------+ +-----+-------+ +------+------+
|  1  |-|  1  + Andy |-|  6  + Mandy |-|  11  + Judy |
+=====+ +-----+------+ +-----+-------+ +------+------+
+=====+
|  2  |-(Empty)
+=====+
+=====+
|  3  |-(Empty)
+=====+
+=====+ +-----+------+
|  4  |-|  4  + Lulu |
+=====+ +-----+------+

**** Menu ****
| 1. Add     |
| 2. Lookup  |
| 3. Remove  |
| 4. Print   |
| 5. Exit    |
**************

Enter your choice: 4
[0]: (Empty)
[1]: 1-Andy 6-Mandy 11-Judy
[2]: (Empty)
[3]: (Empty)
[4]: 4-Lulu

+=====+
|  0  |-(Empty)
+=====+
+=====+ +-----+------+ +-----+-------+ +------+------+
|  1  |-|  1  + Andy |-|  6  + Mandy |-|  11  + Judy |
+=====+ +-----+------+ +-----+-------+ +------+------+
+=====+
|  2  |-(Empty)
+=====+
+=====+
|  3  |-(Empty)
+=====+
+=====+ +-----+------+
|  4  |-|  4  + Lulu |
+=====+ +-----+------+

**** Menu ****
| 1. Add     |
| 2. Lookup  |
| 3. Remove  |
| 4. Print   |
| 5. Exit    |
**************

Enter your choice: 2
Enter a key to search: 6

Result: Mandy is found

+=====+
|  0  |-(Empty)
+=====+
+=====+ +-----+------+ +-----+-------+ +------+------+
|  1  |-|  1  + Andy |-|  6  + Mandy |-|  11  + Judy |
+=====+ +-----+------+ +-----+-------+ +------+------+
+=====+                          ^
|  2  |-(Empty)
+=====+
+=====+
|  3  |-(Empty)
+=====+
+=====+ +-----+------+
|  4  |-|  4  + Lulu |
+=====+ +-----+------+

**** Menu ****
| 1. Add     |
| 2. Lookup  |
| 3. Remove  |
| 4. Print   |
| 5. Exit    |
**************

Enter your choice: 2
Enter a key to search: 7

Result: No data found

+=====+
|  0  |-(Empty)
+=====+
+=====+ +-----+------+ +-----+-------+ +------+------+
|  1  |-|  1  + Andy |-|  6  + Mandy |-|  11  + Judy |
+=====+ +-----+------+ +-----+-------+ +------+------+
+=====+                               ^
|  2  |-(Empty)                No data found!
+=====+
+=====+
|  3  |-(Empty)
+=====+
+=====+ +-----+------+
|  4  |-|  4  + Lulu |
+=====+ +-----+------+

**** Menu ****
| 1. Add     |
| 2. Lookup  |
| 3. Remove  |
| 4. Print   |
| 5. Exit    |
**************

Enter your choice: 3
Enter a key to delete: 7

Result: No data found

+=====+
|  0  |-(Empty)
+=====+
+=====+ +-----+------+ +-----+-------+ +------+------+
|  1  |-|  1  + Andy |-|  6  + Mandy |-|  11  + Judy |
+=====+ +-----+------+ +-----+-------+ +------+------+
+=====+                               ^
|  2  |-(Empty)                 No data found!
+=====+
+=====+
|  3  |-(Empty)
+=====+
+=====+ +-----+------+
|  4  |-|  4  + Lulu |
+=====+ +-----+------+

**** Menu ****
| 1. Add     |
| 2. Lookup  |
| 3. Remove  |
| 4. Print   |
| 5. Exit    |
**************

Enter your choice: 3
Enter a key to delete: 6

Result: Mandy is removed

+=====+
|  0  |-(Empty)
+=====+
+=====+ +-----+------+ +------+------+
|  1  |-|  1  + Andy |-|  11  + Judy |
+=====+ +-----+------+ +------+------+
+=====+
|  2  |-(Empty)
+=====+
+=====+
|  3  |-(Empty)
+=====+
+=====+ +-----+------+
|  4  |-|  4  + Lulu |
+=====+ +-----+------+

**** Menu ****
| 1. Add     |
| 2. Lookup  |
| 3. Remove  |
| 4. Print   |
| 5. Exit    |
**************

Enter your choice: 5
Exit the program...

Final Chaining:
[0]: (Empty)
[1]: 1-Andy 11-Judy
[2]: (Empty)
[3]: (Empty)
[4]: 4-Lulu

+=====+
|  0  |-(Empty)
+=====+
+=====+ +-----+------+ +------+------+
|  1  |-|  1  + Andy |-|  11  + Judy |
+=====+ +-----+------+ +------+------+
+=====+
|  2  |-(Empty)
+=====+
+=====+
|  3  |-(Empty)
+=====+
+=====+ +-----+------+
|  4  |-|  4  + Lulu |
+=====+ +-----+------+

*/