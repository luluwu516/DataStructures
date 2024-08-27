#include <iomanip>
#include <iostream>  // preprocess directive
#include <string>
#define MONTH 12

using std::cin;  // using declaration
using std::cout;

int main() {
  // Array are a list of the same data type
  int months[MONTH] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
  std::string monthsAbbr[MONTH] = {"Jan", "Feb", "Mar", "Apr", "May", "Jan",
                                   "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

  cout << "\nMonth Abbreviation:\n";
  for (int i = 0; i < MONTH; i++) {
    cout << monthsAbbr[i] << " - " << months[i] << "\n";
  }
  /*
  Month Abbreviation:
  Jan - 1
  Feb - 2
  Mar - 3
  Apr - 4
  May - 5
  Jan - 6
  Jul - 7
  Aug - 8
  Sep - 9
  Oct - 10
  Nov - 11
  Dec - 12
  */

  // 2D array
  cout << "\n2D Array: \n";
  const int ROW{2}, COL{3};
  int twoDimensionalArray[ROW][COL] = {1, 2, 3, 4, 5, 6};

  cout << "--------------------\n";
  cout << "|" << std::setw(6) << "|";
  for (int col = 0; col < COL; col++) {
    cout << std::setw(4) << "col";
  }
  cout << "|" << std::endl << "|" << std::setw(6) << "|";
  for (int col = 0; col < COL; col++) {
    cout << std::setw(4) << col;
  }
  cout << "|\n|-----|------------|\n";
  for (int row = 0; row < ROW; row++) {
    cout << std::setw(3) << "|row" << std::setw(2) << row << "|";
    for (int col = 0; col < COL; col++) {
      cout << std::setw(4) << twoDimensionalArray[row][col];
    }
    cout << "|" << std::endl;
  }
  cout << "--------------------\n";

  /*
  2D Array:
  --------------------
  |     | col col col|
  |     |   0   1   2|
  |-----|------------|
  |row 0|   1   2   3|
  |row 1|   4   5   6|
  --------------------
  */

  // multiple dimensional array
  cout << "\nMultiple Dimensional Array:\n";
  int multiDimensionalArray[1][2][3] = {0, 1, 2, 3, 4, 5};
  for (int i = 0; i < 1; i++) {
    for (int j = 0; j < 2; j++) {
      for (int k = 0; k < 3; k++) {
        cout << "Element at index [" << i << "][" << j << "][" << k
             << "] = " << multiDimensionalArray[i][j][k] << "\n";
      }
    }
  }
  cout << std::endl;
  /*
  Multiple Dimensional Array:
  Element at index [0][0][0] = 0
  Element at index [0][0][1] = 1
  Element at index [0][0][2] = 2
  Element at index [0][1][0] = 3
  Element at index [0][1][1] = 4
  Element at index [0][1][2] = 5
  */

  return 0;
}