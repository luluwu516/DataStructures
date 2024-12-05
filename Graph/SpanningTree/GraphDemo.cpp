#include "WeightedGraph.cpp"

// function prototype
void printMenu();

int main() {
  // declaration
  WeightedGraph graph(5);
  std::string label, src, des;
  int count = 0, weight, input;
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

  cout << "\nEnter an edge and its weight (a b 1), -1 to stop: \n";
  while (true) {
    cout << "> ";
    cin >> src;
    if (src == "-1") {
      break;
    }
    cin >> des;
    cin >> weight;

    if (graph.addEdge(src, des, weight)) {
      cout << "...Added edge " << src << "-" << des << " with weight " << weight
           << "\n";
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
        graph.kruskal();
        break;
      }
      case 2: {
        cout << "Enter starting vertex for Prim's algorithm: ";
        cin >> label;
        cout << "\n";
        graph.prim(label);
        break;
      }
      case 3: {
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
  cout << "\n****** Menu ******\n";
  cout << "| 1. Kruskal's   |\n";
  cout << "| 2. Prim's      |\n";
  cout << "| 3. Exit        |\n";
  cout << "******************\n\n";
}

// Output:
/*

Enter 5 labels:
> a b c d e

Enter an edge and its weight (a b 1), -1 to stop:
> a b 3
...Added edge a-b with weight 3
> a d 5
...Added edge a-d with weight 5
> a e 2
...Added edge a-e with weight 2
> b c 6
...Added edge b-c with weight 6
> c e 4
...Added edge c-e with weight 4
> d e 1
...Added edge d-e with weight 1
> -1


Initial Graph:
Vertices: a b c d e

 +-----+ 3 +-----+ 6 +-----+
 |  a  |---|  b  |---|  c  |
 +--+--+   +-----+   +-----+
    |   \           /
  5 |    \ 2     4 /
    |     \       /
 +--+--+ 1 +-----+
 |  d  |---|  e  |
 +-----+   +-----+

Matrix:
   | a b c d e
---+----------
 a | 0 3 0 5 2
 b | 3 0 6 0 0
 c | 0 6 0 0 4
 d | 5 0 0 0 1
 e | 2 0 4 1 0

Edges:
 a-b 3
 a-d 5
 a-e 2
 b-c 6
 c-e 4
 d-e 1


****** Menu ******
| 1. Kruskal's   |
| 2. Prim's      |
| 3. Exit        |
******************

Enter your choice: 1
Minimum Spanning Tree (Kruskal's):
 d-e 1
 a-e 2
 a-b 3
 c-e 4

 +-----+ 3 +-----+   +-----+
 |  a  |---|  b  |   |  c  |
 +--+--+   +-----+   +-----+
        \           /
         \ 2     4 /
          \       /
 +--+--+ 1 +-----+
 |  d  |---|  e  |
 +-----+   +-----+

Total MST weight: 10

****** Menu ******
| 1. Kruskal's   |
| 2. Prim's      |
| 3. Exit        |
******************

Enter your choice: 2
Enter starting vertex for Prim's algorithm: a

Prim's Minimum Spanning Tree (starting from a):
Edges in MST:
 a-e 2
 e-d 1
 a-b 3
 e-c 4

 +-----+ 3 +-----+   +-----+
 |  a  |---|  b  |   |  c  |
 +--+--+   +-----+   +-----+
        \           /
         \ 2     4 /
          \       /
 +--+--+ 1 +-----+
 |  d  |---|  e  |
 +-----+   +-----+

Total weight: 10

****** Menu ******
| 1. Kruskal's   |
| 2. Prim's      |
| 3. Exit        |
******************

Enter your choice: 3
Exit the program...

Final Graph:

 +-----+ 3 +-----+ 6 +-----+
 |  a  |---|  b  |---|  c  |
 +--+--+   +-----+   +-----+
    |   \           /
  5 |    \ 2     4 /
    |     \       /
 +--+--+ 1 +-----+
 |  d  |---|  e  |
 +-----+   +-----+

Vertices: a b c d e

Matrix:
   | a b c d e
---+----------
 a | 0 3 0 5 2
 b | 3 0 6 0 0
 c | 0 6 0 0 4
 d | 5 0 0 0 1
 e | 2 0 4 1 0

Edges:
 d-e 1
 a-e 2
 a-b 3
 c-e 4
 a-d 5
 b-c 6

*/