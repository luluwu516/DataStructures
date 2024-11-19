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


******************

Enter your choice: 3
Exit the program...

Final Graph:
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