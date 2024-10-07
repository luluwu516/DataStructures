#include <iomanip>
#include <iostream>  // preprocessor directive
#include <sstream>
#include <string>
#include <vector>

using std::cin;  // using declaration
using std::cout;

/*
Undirected graph
 An undirected graph is a type of graph where edges have no direction. In other
 words, the relationship between any two connected vertices is symmetrical.

 +-----+  +-----+  +-----+
 |  A  |--|  B  |--|  C  |
 +--+--+  +-----+  +-----+
    |   \         /
    |    \       /
 +--+--+  +-----+
 |  D  |  |  E  |
 +-----+  +-----+

Vertices: A, B, C, D, E
Edges:
 A: A-B, A-D, A-E
 B: B-A, B-C
 C: C-B, C-E
 D: D-A
 E: E-A, E-C

 Characteristics:
  * Edges are bidirectional (two-way)
  * If vertex A is connected to vertex B, then B is also connected to A
  * Usually represented as (u, v), where u and v are vertices

Adjacency Matrix Representation:
An adjacency matrix is a 2D array representation of a graph where both
dimensions represent vertices, and the values indicate whether there's an edge
between two vertices.

     |  A  B  C  D  E
  ---+----------------
   A |  0  1  0  1  1
   B |  1  0  1  0  0
   C |  0  1  0  0  1
   D |  1  0  0  0  0
   E |  1  0  1  0  0

 Characteristics:
 * Symmetry: The matrix is symmetric about the main diagonal.
 * Space Complexity: O(V^2), where V is the number of vertices. The matrix is n
   x n in size.
 * Quick Edge Lookup: Checking if an edge exists between two vertices takes O(1)
   time.
 * Simple Implementation: Easy to implement and understand. Matrix[i][j] = 1 if
   there's an edge between vertex i and j, 0 otherwise.

 Pros:
 * Fast edge lookup: Checking if an edge exists between any two vertices is
   O(1).
 * Easy to implement: The concept is straightforward and can be implemented
   using a 2D array or vector.
 * Efficient for dense graphs: Works well when the number of edges is close to
   the maximum possible.
 * Simple to add or remove edges: Just change the corresponding matrix elements.

 Cons:
 * Space inefficiency: Requires O(V^2) space, which can be wasteful for sparse
   graphs.
 * Lack of scalability: Adding new vertices requires recreating the entire
   matrix.
 * Redundant storage for undirected graphs: The information is stored twice due
   to symmetry.
 * Not suitable for graphs with parallel edges: Can't easily represent multiple
   edges between the same pair of vertices.

*/

class GraphAdjacencyMatrix {
 public:
  // constructor
  GraphAdjacencyMatrix() {}

  void setUpGraph(int vertices, std::string labels) {
    numVertices = vertices;

    // initialize the adjacency matrix with zeros
    adjacencyMatrix.resize(numVertices, std::vector<int>(numVertices, 0));
    vertexLabels.resize(numVertices);

    // declaration
    std::stringstream stream;
    std::string label;

    // processing
    // parse the input string to extract individual vertex labels
    stream << labels;
    for (int i = 0; i < numVertices; i++) {
      stream >> label;
      vertexLabels[i] = label;
      cout << "Vertex " << vertexLabels[i] << " added.\n";
    }
  }

  void addEdge(std::string srcLabel, std::string desLabel) {
    int src = findIndex(srcLabel);
    int des = findIndex(desLabel);
    if (src == -1 || des == -1) {
      throw std::runtime_error("Error! One or both vertices not found.\n");
    }

    // set both directions for undirected graph
    adjacencyMatrix[src][des] = 1;
    adjacencyMatrix[des][src] = 1;
  }

  void removeEdge(std::string srcLabel, std::string desLabel) {
    int src = findIndex(srcLabel);
    int des = findIndex(desLabel);
    if (src == -1 || des == -1) {
      throw std::runtime_error("Error! One or both vertices not found.\n");
    }

    // remove both directions for undirected graph
    adjacencyMatrix[src][des] = 0;
    adjacencyMatrix[des][src] = 0;
  }

  bool checkEdge(std::string srcLabel, std::string desLabel) {
    int src = findIndex(srcLabel);
    int des = findIndex(desLabel);
    if (src == -1 || des == -1) {
      throw std::runtime_error("Error! One or both vertices not found.\n");
    }

    return adjacencyMatrix[src][des] == 1;
  }

  void printMatrix() const {
    cout << "Adjacency Matrix: \n   ";
    for (std::size_t col = 0; col < numVertices; col++) {
      cout << vertexLabels[col] << " ";
    }
    cout << "\n";
    for (std::size_t row = 0; row < numVertices; row++) {
      cout << std::setw(2) << vertexLabels[row] << " ";
      for (std::size_t col = 0; col < numVertices; col++) {
        cout << adjacencyMatrix[row][col] << " ";
      }
      cout << "\n";
    }
    cout << "\n";
  }

 private:
  size_t numVertices;
  std::vector<std::vector<int>> adjacencyMatrix;
  std::vector<std::string> vertexLabels;

  int findIndex(const std::string& label) const {
    for (int i = 0; i < numVertices; i++) {
      if (vertexLabels[i] == label) {
        return i;
      }
    }
    return -1;  // return -1 if label not found
  }
};

int main() {
  // declaration
  GraphAdjacencyMatrix graph;
  std::string input, srcLabel, desLabel;
  int numVertices;

  // input
  cout << "\nEnter the number of vertices: ";
  while (!(cin >> numVertices)) {
    // clear the error flags on the input stream
    cin.clear();
    // clear the input buffer by ignoring characters
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cout << "Invalid input. Please the number of vertices: ";
  }

  cout << "Enter labels for " << numVertices
       << " vertices (seperated with space): ";
  cin.ignore();
  std::getline(cin, input);
  graph.setUpGraph(numVertices, input);

  // processing
  while (true) {
    cout << "\nDefine an edge by listing a pair of vertices, i.e. 'AB', or -1 "
            "to finish: ";
    cin >> input;

    if (input == "-1") {
      break;
    }
    if (input.length() != 2) {
      cout << "Invalid input. Please enter two vertices (e.g., 'AB').\n";
      continue;
    }
    try {
      graph.addEdge(std::string(1, input[0]), std::string(1, input[1]));
      cout << "Edge added.\n";
    } catch (const std::exception& e) {
      cout << e.what() << std::endl;
    }
  }

  // print initial graph
  cout << "\n\nInitial Graph Matrix:\n";
  graph.printMatrix();

  // remove edges
  while (true) {
    cout << "\nEnter an edge to remove (e.g., 'AB') or -1 to finish: ";
    cin >> input;

    if (input == "-1") {
      break;
    }
    if (input.length() != 2) {
      cout << "Invalid input. Please enter two vertices (e.g., 'AB').\n";
      continue;
    }
    try {
      srcLabel = std::string(1, input[0]);
      desLabel = std::string(1, input[1]);
      graph.removeEdge(srcLabel, desLabel);
      cout << "Edge removed.\n";

      // check and print if the edge still exists
      cout << "\nChecking if edge exists between '" << srcLabel << "' and '"
           << desLabel
           << "': " << (graph.checkEdge(srcLabel, desLabel) ? "Yes" : "No")
           << "\n";
    } catch (const std::exception& e) {
      cout << e.what() << std::endl;
    }
  }

  // print graph after edge removal
  cout << "\nGraph after edge removal:\n";
  graph.printMatrix();
  cout << "\n";

  return 0;
}

// Output:
/*

Enter the number of vertices: 5
Enter labels for 5 vertices (seperated with space): a b c d e
Vertex a added.
Vertex b added.
Vertex c added.
Vertex d added.
Vertex e added.

Define an edge by listing a pair of vertices, i.e. 'AB', or -1 to finish: ab
Edge added.

Define an edge by listing a pair of vertices, i.e. 'AB', or -1 to finish: ad
Edge added.

Define an edge by listing a pair of vertices, i.e. 'AB', or -1 to finish: ae
Edge added.

Define an edge by listing a pair of vertices, i.e. 'AB', or -1 to finish: bc
Edge added.

Define an edge by listing a pair of vertices, i.e. 'AB', or -1 to finish: ce
Edge added.

Define an edge by listing a pair of vertices, i.e. 'AB', or -1 to finish: -1


Initial Graph Matrix:
Adjacency Matrix:
   a b c d e
 a 0 1 0 1 1
 b 1 0 1 0 0
 c 0 1 0 0 1
 d 1 0 0 0 0
 e 1 0 1 0 0

 +-----+  +-----+  +-----+
 |  a  |--|  b  |--|  c  |
 +--+--+  +-----+  +-----+
    |   \         /
    |    \       /
 +--+--+  +-----+
 |  d  |  |  e  |
 +-----+  +-----+

Enter an edge to remove (e.g., 'AB') or -1 to finish: ab
Edge removed.

Checking if edge exists between 'a' and 'b': No

Enter an edge to remove (e.g., 'AB') or -1 to finish: -1

Graph after edge removal:
Adjacency Matrix:
   a b c d e
 a 0 0 0 1 1
 b 0 0 1 0 0
 c 0 1 0 0 1
 d 1 0 0 0 0
 e 1 0 1 0 0

 +-----+  +-----+  +-----+
 |  a  |  |  b  |--|  c  |
 +--+--+  +-----+  +-----+
    |   \         /
    |    \       /
 +--+--+  +-----+
 |  d  |  |  e  |
 +-----+  +-----+

*/