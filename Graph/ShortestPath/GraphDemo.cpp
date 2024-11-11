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
        cout << "Enter starting vertex for Dijkstra's algorithm: ";
        cin >> label;
        cout << "\n";
        graph.dijkstra(label);
        break;
      }
      case 2: {
        cout << "Enter starting vertex for Floyd-Warshall algorithm: ";
        cin >> label;
        cout << "\n";
        graph.floydWarshall(label);
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
  cout << "\n******** Menu ********\n";
  cout << "| 1. Dijkstra's      |\n";
  cout << "| 2. Floyd-Warshall  |\n";
  cout << "| 3. Exit            |\n";
  cout << "**********************\n\n";
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


******** Menu ********
| 1. Dijkstra's      |
| 2. Floyd-Warshall  |
| 3. Exit            |
**********************

Enter your choice: 1
Enter starting vertex for Dijkstra's algorithm: a

 +-----+ 3 +-----+ 6 +-----+
 |  a  |---|  b  |---|  c  |
 +--+--+   +-----+   +-----+
    |   \           /
  5 |    \ 2     4 /
    |     \       /
 +--+--+ 1 +-----+
 |  d  |---|  e  |
 +-----+   +-----+

The shortest path from vertex a:
 * To vertex a: 0
 * To vertex b: 3
 * To vertex c: 6
 * To vertex d: 3
 * To vertex e: 2


******** Menu ********
| 1. Dijkstra's      |
| 2. Floyd-Warshall  |
| 3. Exit            |
**********************

Enter your choice: 2
Enter starting vertex for Floyd-Warshall algorithm: a

 +-----+ 3 +-----+ 6 +-----+
 |  a  |---|  b  |---|  c  |
 +--+--+   +-----+   +-----+
    |   \           /
  5 |    \ 2     4 /
    |     \       /
 +--+--+ 1 +-----+
 |  d  |---|  e  |
 +-----+   +-----+

Shortest paths from vertex a:
 * To vertex a: 0
 * To vertex b: 3
 * To vertex c: 6
 * To vertex d: 3
 * To vertex e: 2


******** Menu ********
| 1. Dijkstra's      |
| 2. Floyd-Warshall  |
| 3. Exit            |
**********************

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

*/