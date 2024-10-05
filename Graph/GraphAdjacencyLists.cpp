#include <iostream>  // preprocessor directive
#include <sstream>
#include <string>
#include <vector>
#define MAX_VERTICES 10

using std::cin;  // using declaration
using std::cout;

struct Node {
  std::string label;
  int weight;
  Node* next;
  Node(std::string l, int w) : label(l), weight(w), next(nullptr) {}
};

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


Adjacency List Representation
 An adjacency list is a way to represent a graph as a collection of lists, where
 each list describes the set of neighbors of a vertex in the graph.

 A: [B, D, E]
 B: [A, C]
 C: [B, E]
 D: [A]
 E: [A, C]

 adjacencyList
   +=====+  +-----+  +-----+  +-----+
   |  A  |--|  B  |--|  D  |--|  E  |
   +=====+  +-----+  +-----+  +-----+
   +=====+  +-----+  +-----+
   |  B  |--|  A  |--|  C  |
   +=====+  +-----+  +-----+
   +=====+  +-----+  +-----+
   |  C  |--|  B  |--|  E  |
   +=====+  +-----+  +-----+
   +=====+  +-----+
   |  D  |--|  A  |
   +=====+  +-----+
   +=====+  +-----+  +-----+
   |  E  |--|  A  |--|  C  |
   +=====+  +-----+  +-----+

 Characteristics:
  * Each vertex has a list of its adjacent vertices
  * For undirected graphs, each edge appears twice in the overall structure

 Pros:
  * Space-efficient for sparse graphs
  * Faster to add new edges
  * Provides faster iteration over all edges of a vertex

 Cons:
  * Slower to check if there is an edge between two vertices
  * Uses more space for dense graphs compared to adjacency matrices

*/

class GraphAdjacencyList {
 public:
  // constructor
  GraphAdjacencyList() : numVertices(0) {
    adjacencyList.resize(MAX_VERTICES, nullptr);
    vertexLabels.resize(MAX_VERTICES);
  }

  // destructor
  ~GraphAdjacencyList() {
    // free dynamically allocated memory
    for (int i = 0; i < numVertices; i++) {
      Node* curr = adjacencyList[i];
      while (curr) {
        Node* next = curr->next;
        delete curr;
        curr = next;
      }
    }
  }

  void addVertex(const std::string& label) {
    if (isFull()) {
      throw std::runtime_error("Error! Maxium number of vertices reached.\n");
    }
    vertexLabels[numVertices++] = label;
  }

  void removeVertex(const std::string& label) {
    int index = findVertexIndex(label);
    if (index == -1) {
      throw std::runtime_error("Error! Vertex not found.\n");
    }

    // remove all edges with this vertex
    for (int i = 0; i < numVertices; i++) {
      if (i == index) {
        // delete the entire list for the removed vertex
        Node* curr = adjacencyList[index];
        while (curr) {
          Node* next = curr->next;
          delete curr;
          curr = next;
        }
        adjacencyList[index] = nullptr;
      } else {
        // remove edges to the deleted vertex from other lists
        removeDirectedEdge(i, index);
      }
    }

    // shift the remaining vertices to fill the gap
    for (int i = index; i < numVertices - 1; i++) {
      adjacencyList[i] = adjacencyList[i + 1];
      vertexLabels[i] = vertexLabels[i + 1];
    }

    // update the number of vertices
    numVertices--;
  }

  void addEdge(const std::string& srcLabel, const std::string& desLabel,
               int weight) {
    int src = findVertexIndex(srcLabel);
    int des = findVertexIndex(desLabel);

    if (src == -1 || des == -1) {
      throw std::runtime_error("Error! One or both vertices not found.\n");
    }

    // add edge from src to des
    Node* newNode = new Node(desLabel, weight);
    newNode->next = adjacencyList[src];
    adjacencyList[src] = newNode;

    // add edge from des to src (since it's undirected)
    newNode = new Node(srcLabel, weight);
    newNode->next = adjacencyList[des];
    adjacencyList[des] = newNode;
  }

  void removeEdge(const std::string& srcLabel, const std::string& desLabel) {
    int src = findVertexIndex(srcLabel);
    int des = findVertexIndex(desLabel);

    if (src == -1 || des == -1) {
      throw std::runtime_error("Error! One or both vertices not found.\n");
    }

    // remove edge from src to des
    removeDirectedEdge(src, des);

    // remove edge from des to src
    removeDirectedEdge(des, src);
  }

  bool isEmpty() const { return numVertices == 0; }

  bool isFull() const { return numVertices == MAX_VERTICES; }

  void printVertices() const {
    cout << "Number of Vertices: " << numVertices << "\n";
    cout << "List of Vertices: ";
    for (const std::string& label : vertexLabels) {
      cout << label << " ";
    }
    cout << "\n";
  }

  void printEdges() const {
    for (int i = 0; i < numVertices; i++) {
      cout << "Edges from " << vertexLabels[i] << ": \n";
      Node* curr = adjacencyList[i];
      if (!curr) {
        cout << "(empty)\n";
      }
      while (curr) {
        cout << " To " << curr->label << " with weight " << curr->weight
             << "\n";
        curr = curr->next;
      }
      cout << "\n";
    }
  }

 private:
  size_t numVertices;
  std::vector<Node*> adjacencyList;
  std::vector<std::string> vertexLabels;

  int findVertexIndex(const std::string& label) const {
    for (int i = 0; i < numVertices; i++) {
      if (vertexLabels[i] == label) {
        return i;
      }
    }
    return -1;
  }

  void removeDirectedEdge(const int& src, const int& des) {
    Node* curr = adjacencyList[src];
    Node* prev = nullptr;

    while (curr && curr->label != vertexLabels[des]) {
      prev = curr;
      curr = curr->next;
    }

    if (curr) {
      if (prev) {
        prev->next = curr->next;
      } else {
        adjacencyList[src] = curr->next;
      }
      delete curr;
    }
  }
};

int main() {
  // declaration
  GraphAdjacencyList graph;
  std::string labels, label;
  std::string srcLabel, desLabel;
  int weight;
  std::stringstream stream;

  // input vertices
  cout << "\nEnter the label for each vertices: ";
  getline(cin, labels);
  stream << labels;
  while (stream >> label) {
    graph.addVertex(label);
  }
  stream.clear();

  // input edges
  cout << "\nDefine an edge by listing a pair of vertices, i.e. 'AB', "
          "or -1 to finish: ";
  getline(cin, labels);

  while (labels != "-1") {
    if (labels.length() != 2) {
      std::cout << "Invalid input. Please enter two vertices (e.g., 'AB').\n";
      continue;
    }
    cout << "Enter the weight of the edge: ";
    cin >> weight;
    cin.ignore();
    graph.addEdge(std::string(1, labels[0]), std::string(1, labels[1]), weight);

    cout << "Define an edge by listing a pair of vertices, i.e. 'AB', "
            "or -1 to stop: ";
    getline(cin, labels);
  }

  // print initial graph
  cout << "\n\nInitial Graph:\n";
  graph.printVertices();
  cout << "\n";
  graph.printEdges();

  // remove edges
  std::cout << "\nEnter an edge to remove (e.g., 'AB') or -1 to finish: ";
  std::cin >> labels;
  while (labels != "-1") {
    if (labels.length() != 2) {
      std::cout << "Invalid input. Please enter two vertices (e.g., 'AB').\n";
      continue;
    }
    try {
      graph.removeEdge(std::string(1, labels[0]), std::string(1, labels[1]));
      std::cout << "Edge removed.\n";
    } catch (const std::exception& e) {
      std::cout << e.what();
    }
    std::cout << "\nEnter an edge to remove (e.g., 'AB') or -1 to finish: ";
    std::cin >> labels;
  }

  // print graph after edge removal
  std::cout << "\nGraph after edge removal:\n";
  graph.printVertices();
  std::cout << "\n";
  graph.printEdges();

  // remove vertices
  std::cout << "\nEnter a vertex to remove or -1 to finish: ";
  std::cin >> labels;

  while (labels != "-1") {
    if (labels.length() != 1) {
      std::cout << "Invalid input. Please enter a single vertex.\n";
      continue;
    }
    try {
      graph.removeVertex(labels);
      std::cout << "Vertex removed.\n";
    } catch (const std::exception& e) {
      std::cout << e.what();
    }
    std::cout << "\nEnter a vertex to remove or -1 to finish: ";
    std::cin >> labels;
  }

  // print final graph
  std::cout << "\nFinal Graph:\n";
  graph.printVertices();
  std::cout << "\n";
  graph.printEdges();

  return 0;
}

// Output:
/*

Enter the label for each vertices: a b c d e

Define an edge by listing a pair of vertices, i.e. 'AB', or -1 to finish: ab
Enter the weight of the edge: 1
Define an edge by listing a pair of vertices, i.e. 'AB', or -1 to stop: ad
Enter the weight of the edge: 2
Define an edge by listing a pair of vertices, i.e. 'AB', or -1 to stop: ae
Enter the weight of the edge: 3
Define an edge by listing a pair of vertices, i.e. 'AB', or -1 to stop: bc
Enter the weight of the edge: 4
Define an edge by listing a pair of vertices, i.e. 'AB', or -1 to stop: ce
Enter the weight of the edge: 5
Define an edge by listing a pair of vertices, i.e. 'AB', or -1 to stop: -1


Initial Graph:
Number of Vertices: 5
List of Vertices: a b c d e

Edges from a:
 To e with weight 3
 To d with weight 2
 To b with weight 1

Edges from b:
 To c with weight 4
 To a with weight 1

Edges from c:
 To e with weight 5
 To b with weight 4

Edges from d:
 To a with weight 2

Edges from e:
 To c with weight 5
 To a with weight 3

 +-----+ 1 +-----+ 4 +-----+
 |  A  |---|  B  |---|  C  |
 +--+--+   +-----+   +-----+
    |   \           /
    | 2  \ 3       / 5
    |     \       /
 +--+--+   +-----+
 |  D  |   |  E  |
 +-----+   +-----+

Enter an edge to remove (e.g., 'AB') or -1 to finish: ab
Edge removed.

Enter an edge to remove (e.g., 'AB') or -1 to finish: -1

Graph after edge removal:
Number of Vertices: 5
List of Vertices: a b c d e

Edges from a:
 To e with weight 3
 To d with weight 2

Edges from b:
 To c with weight 4

Edges from c:
 To e with weight 5
 To b with weight 4

Edges from d:
 To a with weight 2

Edges from e:
 To c with weight 5
 To a with weight 3

 +-----+   +-----+ 4 +-----+
 |  A  |   |  B  |---|  C  |
 +--+--+   +-----+   +-----+
    |   \           /
    | 2  \ 3       / 5
    |     \       /
 +--+--+   +-----+
 |  D  |   |  E  |
 +-----+   +-----+

Enter a vertex to remove or -1 to finish: d
Vertex removed.

Enter a vertex to remove or -1 to finish: -1

Final Graph:
Number of Vertices: 4
List of Vertices: a b c e e

Edges from a:
 To e with weight 3

Edges from b:
 To c with weight 4

Edges from c:
 To e with weight 5
 To b with weight 4

Edges from e:
 To c with weight 5
 To a with weight 3

 +-----+   +-----+ 4 +-----+
 |  A  |   |  B  |---|  C  |
 +--+--+   +-----+   +-----+
        \           /
         \ 3       / 5
          \       /
           +-----+
           |  E  |
           +-----+

*/