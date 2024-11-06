#include "GraphAdjacencyMatrix.cpp"

// function prototype
void printMenu();

int main() {
  // declaration
  GraphAdjacencyMatrix graph(5);
  std::string label, src, des;
  int count = 0, input;
  bool isRunning = true;

  // define the initial graph
  cout << "\nEnter 5 labels: \n> ";
  while (count < 5) {
    cin >> label;
    if (!graph.addVertex(label)) {
      cout << "...Vertex " << label
           << " already exists. Ignore the second one.\n";
      continue;
    }
    count++;
  }

  cout << "\nDefine an edge by listing a pair of vertices -1 to stop: \n";
  while (true) {
    cout << "> ";
    cin >> src;
    if (src == "-1") {
      break;
    }
    cin >> des;

    if (graph.addEdge(src, des)) {
      cout << "...Added edge " << src << "-" << des << "\n";
    } else {
      cout << "...Error! One or both vertices not found or edge already "
              "exists.\n";
    }
  }

  // initial graph
  cout << "\n\nInitial Graph:\n";
  graph.printInfo();

  while (isRunning) {
    printMenu();
    cout << "Enter your choice: ";
    cin >> input;

    switch (input) {
      case 1: {
        cout << "Enter a label: ";
        cin >> label;

        if (graph.addVertex(label)) {
          cout << "\n...Added Vertex " << label << "\n";
        } else {
          cout << "...Vertex " << label << " already exists.\n";
        }
        break;
      }
      case 2: {
        cout << "Define an edge by listing a pair of vertices: ";
        cin >> src >> des;
        if (graph.addEdge(src, des)) {
          cout << "\n...Added edge " << src << "-" << des << "\n";
        } else {
          cout << "\n...Error! One or both vertices not found or edge already "
                  "exists.\n";
        }
        break;
      }
      case 3: {
        cout << "Enter a label to search: ";
        cin >> label;

        cout << "\n...Label " << label << " is "
             << (graph.searchLabel(label) ? "found\n" : "not found\n");
        break;
      }
      case 4: {
        cout << "Enter an edge to search: ";
        cin >> src >> des;
        cout << "\n...Edge " << src << "-" << des << " is "
             << (graph.searchEdge(src, des) ? "found\n" : "not found\n");
        break;
      }
      case 5: {
        cout << "Enter a label to remove: ";
        cin >> label;
        if (graph.removeVertex(label)) {
          cout << "\n...Vertex " << label << " is deleted.\n";
        } else {
          cout << "\nError! Vertax not found.\n";
        }
        break;
      }
      case 6: {
        cout << "Enter an edge to remove: ";
        cin >> src >> des;
        if (graph.removeEdge(src, des)) {
          cout << "\n...Edge " << src << "-" << des << " is deleted.\n";
        } else {
          cout << "\nError! One or both vertices not found.\n";
        }
        break;
      }
      case 7: {
        cout << "Enter starting vertex for BFS: ";
        cin >> label;
        cout << "\n";
        graph.BFS(label);
        break;
      }
      case 8: {
        cout << "Enter starting vertex for DFS: ";
        cin >> label;
        cout << "\n";
        graph.DFS(label);
        break;
      }
      case 9: {
        cout << "\nCurrent Graph:\n";
        graph.printInfo();
        break;
      }
      case 10: {
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

  // Final Tree
  cout << "\nFinal Graph:\n";
  graph.printInfo();
  cout << "\n";

  return 0;
}

void printMenu() {
  cout << "\n******* Menu *******\n";
  cout << "| 1. Add Vertex    |\n";
  cout << "| 2. Add Edge      |\n";
  cout << "| 3. Lookup Vertex |\n";
  cout << "| 4. Lookup Edge   |\n";
  cout << "| 5. Delete Vertex |\n";
  cout << "| 6. Delete Edge   |\n";
  cout << "| 7. BFS           |\n";
  cout << "| 8. DFS           |\n";
  cout << "| 9. Print         |\n";
  cout << "| 10. Exit         |\n";
  cout << "********************\n\n";
}

// Output:
/*

Enter 5 labels:
> a b c d e

Define an edge by listing a pair of vertices -1 to stop:
> a b
...Added edge a-b
> a d
...Added edge a-d
> a e
...Added edge a-e
> b c
...Added edge b-c
> c e
...Added edge c-e
> -1


Initial Graph:

 +-----+  +-----+  +-----+
 |  a  |--|  b  |--|  c  |
 +--+--+  +-----+  +-----+
    |   \         /
    |    \       /
 +--+--+  +-----+
 |  d  |  |  e  |
 +-----+  +-----+

Vertices: a b c d e

                +-----+-----+-----+-----+-----+
  vertexLabels  |  a  |  b  |  c  |  d  |  e  |
                +-----+-----+-----+-----+-----+

Matrix:
   | a b c d e
---+----------
 a | 0 1 0 1 1
 b | 1 0 1 0 0
 c | 0 1 0 0 1
 d | 1 0 0 0 0
 e | 1 0 1 0 0


******* Menu *******
| 1. Add Vertex    |
| 2. Add Edge      |
| 3. Lookup Vertex |
| 4. Lookup Edge   |
| 5. Delete Vertex |
| 6. Delete Edge   |
| 7. BFS           |
| 8. DFS           |
| 9. Print         |
| 10. Exit         |
********************

Enter your choice: 3
Enter a label to search: f

...Label f is not found

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
  vertexLabels  |  a  |  b  |  c  |  d  |  e  |
                +-----+-----+-----+-----+-----+
                                                  ^
                                              not found

******* Menu *******
| 1. Add Vertex    |
| 2. Add Edge      |
| 3. Lookup Vertex |
| 4. Lookup Edge   |
| 5. Delete Vertex |
| 6. Delete Edge   |
| 7. BFS           |
| 8. DFS           |
| 9. Print         |
| 10. Exit         |
********************

Enter your choice: 3 d
Enter a label to search:
...Label d is found

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
  vertexLabels  |  a  |  b  |  c  |  d  |  e  |
                +-----+-----+-----+-----+-----+
                         ^
                       found

******* Menu *******
| 1. Add Vertex    |
| 2. Add Edge      |
| 3. Lookup Vertex |
| 4. Lookup Edge   |
| 5. Delete Vertex |
| 6. Delete Edge   |
| 7. BFS           |
| 8. DFS           |
| 9. Print         |
| 10. Exit         |
********************

Enter your choice: 4
Enter an edge to search: a c

...Edge a-c is not found

   | a b  c  d e
---+------------
 a | 0 1 '0' 1 1
 b | 1 0  1  0 0
 c | 0 1  0  0 1
 d | 1 0  0  0 0
 e | 1 0  1  0 0

******* Menu *******
| 1. Add Vertex    |
| 2. Add Edge      |
| 3. Lookup Vertex |
| 4. Lookup Edge   |
| 5. Delete Vertex |
| 6. Delete Edge   |
| 7. BFS           |
| 8. DFS           |
| 9. Print         |
| 10. Exit         |
********************

Enter your choice: 4
Enter an edge to search: a b

...Edge a-b is found

   | a  b  c d e
---+------------
 a | 0 '1' 0 1 1
 b | 1  0  1 0 0
 c | 0  1  0 0 1
 d | 1  0  0 0 0
 e | 1  0  1 0 0

******* Menu *******
| 1. Add Vertex    |
| 2. Add Edge      |
| 3. Lookup Vertex |
| 4. Lookup Edge   |
| 5. Delete Vertex |
| 6. Delete Edge   |
| 7. BFS           |
| 8. DFS           |
| 9. Print         |
| 10. Exit         |
********************

Enter your choice: 7
Enter starting vertex for BFS: a

BFS starting from vertex a: a b d e c

 +-----+  +-----+  +-----+
 |  a  |--|  b  |--|  c  |
 +--+--+  +-----+  +-----+
    |   \         /
    |    \       /
 +--+--+  +-----+
 |  d  |  |  e  |
 +-----+  +-----+

 * check the Breadth-FirstTraversal.cpp file to learn more

******* Menu *******
| 1. Add Vertex    |
| 2. Add Edge      |
| 3. Lookup Vertex |
| 4. Lookup Edge   |
| 5. Delete Vertex |
| 6. Delete Edge   |
| 7. BFS           |
| 8. DFS           |
| 9. Print         |
| 10. Exit         |
********************

Enter your choice: 8
Enter starting vertex for DFS: a

DFS starting from a: a b c e d

 +-----+  +-----+  +-----+
 |  a  |--|  b  |--|  c  |
 +--+--+  +-----+  +-----+
    |   \         /
    |    \       /
 +--+--+  +-----+
 |  d  |  |  e  |
 +-----+  +-----+

 * check the Depth-FirstTraversal.cpp file to learn more

******* Menu *******
| 1. Add Vertex    |
| 2. Add Edge      |
| 3. Lookup Vertex |
| 4. Lookup Edge   |
| 5. Delete Vertex |
| 6. Delete Edge   |
| 7. BFS           |
| 8. DFS           |
| 9. Print         |
| 10. Exit         |
********************

Enter your choice: 9

Current Graph:

 +-----+  +-----+  +-----+
 |  a  |--|  b  |--|  c  |
 +--+--+  +-----+  +-----+
    |   \         /
    |    \       /
 +--+--+  +-----+
 |  d  |  |  e  |
 +-----+  +-----+

Vertices: a b c d e

                +-----+-----+-----+-----+-----+
  vertexLabels  |  a  |  b  |  c  |  d  |  e  |
                +-----+-----+-----+-----+-----+

Matrix:
   | a b c d e
---+----------
 a | 0 1 0 1 1
 b | 1 0 1 0 0
 c | 0 1 0 0 1
 d | 1 0 0 0 0
 e | 1 0 1 0 0


******* Menu *******
| 1. Add Vertex    |
| 2. Add Edge      |
| 3. Lookup Vertex |
| 4. Lookup Edge   |
| 5. Delete Vertex |
| 6. Delete Edge   |
| 7. BFS           |
| 8. DFS           |
| 9. Print         |
| 10. Exit         |
********************

Enter your choice: 6
Enter an edge to remove: b c

...Edge b-c is deleted.

 +-----+  +-----+  +-----+
 |  a  |--|  b  |  |  c  |
 +--+--+  +-----+  +-----+
    |   \         /
    |    \       /
 +--+--+  +-----+
 |  d  |  |  e  |
 +-----+  +-----+

                +-----+-----+-----+-----+-----+
  vertexLabels  |  a  |  b  |  c  |  d  |  e  |
                +-----+-----+-----+-----+-----+

   | a b c d e
---+----------
 a | 0 1 0 1 1
 b | 1 0 0 0 0
 c | 0 0 0 0 1
 d | 1 0 0 0 0
 e | 1 0 1 0 0

******* Menu *******
| 1. Add Vertex    |
| 2. Add Edge      |
| 3. Lookup Vertex |
| 4. Lookup Edge   |
| 5. Delete Vertex |
| 6. Delete Edge   |
| 7. BFS           |
| 8. DFS           |
| 9. Print         |
| 10. Exit         |
********************

Enter your choice: 5
Enter a label to remove: a

...Vertex a is deleted.

          +-----+  +-----+
          |  b  |  |  c  |
          +-----+  +-----+
                  /
                 /
 +-----+  +-----+
 |  d  |  |  e  |
 +-----+  +-----+

                +-----+-----+-----+-----+
  vertexLabels  |  b  |  c  |  d  |  e  |
                +-----+-----+-----+-----+

   | b c d e
---+--------
 b | 0 0 0 0
 c | 0 0 0 1
 d | 0 0 0 0
 e | 0 1 0 0


******* Menu *******
| 1. Add Vertex    |
| 2. Add Edge      |
| 3. Lookup Vertex |
| 4. Lookup Edge   |
| 5. Delete Vertex |
| 6. Delete Edge   |
| 7. BFS           |
| 8. DFS           |
| 9. Print         |
| 10. Exit         |
********************

Enter your choice: 10
Exit the program...

Final Graph:

          +-----+  +-----+
          |  b  |  |  c  |
          +-----+  +-----+
                  /
                 /
 +-----+  +-----+
 |  d  |  |  e  |
 +-----+  +-----+

Vertices: b c d e
Matrix:
   | b c d e
---+--------
 b | 0 0 0 0
 c | 0 0 0 1
 d | 0 0 0 0
 e | 0 1 0 0

*/