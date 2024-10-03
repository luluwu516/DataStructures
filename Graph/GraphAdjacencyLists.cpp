#include <iostream>  // preprocessor directive
#include <string>
#include <vector>

using std::cin;  // using declaration
using std::cout;
using std::string;

struct Node {
  string label;
  int weight;
  Node* next;
  Node(string l, int w) : label(l), weight(w), next(nullptr) {}
};

/*
Undirected graph

*/

class GraphAdjacencyList {
 public:
  // constructor
  GraphAdjacencyList(int size) : maxSize(size), numVertices(0) {
    vertexLabels.resize(maxSize);
    adjacencyList.resize(maxSize, nullptr);
  }

  // destructor
  ~GraphAdjacencyList() {
    for (int i = 0; i < numVertices; i++) {
      Node* curr = adjacencyList[i];
      while (curr) {
        Node* next = curr->next;
        delete curr;
        curr = next;
      }
    }
  }

  void addVertex(const string& label) {
    if (isFull()) {
      throw std::runtime_error("Error! Maxium number of vertices reached.\n");
    }
    vertexLabels[numVertices++] = label;
  }

  void addEdge(const string& srcLabel, const string& desLabel, int weight) {
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

  bool isEmpty() { return numVertices == 0; }

  bool isFull() { return numVertices == maxSize; }

  void printVertices() {
    cout << "Number of Vertices: " << numVertices << "\n";
    cout << "List of Vertices: ";
    for (int i = 0; i < numVertices; i++) {
      cout << vertexLabels[i] << " ";
    }
    cout << "\n";
  }

  void printEdges() {
    for (int i = 0; i < numVertices; i++) {
      cout << "Edges from " << vertexLabels[i] << ": \n";
      Node* curr = adjacencyList[i];
      while (curr) {
        cout << " To " << curr->label << " with weight " << curr->weight
             << "\n";
        curr = curr->next;
      }
      cout << "\n";
    }
  }

 private:
  int maxSize;
  int numVertices;
  std::vector<std::string> vertexLabels;
  std::vector<Node*> adjacencyList;

  int findVertexIndex(const string& label) const {
    for (int i = 0; i < numVertices; i++) {
      if (vertexLabels[i] == label) {
        return i;
      }
    }
    return -1;
  }
};

int main() {
  // declaration
  int numVertices;
  std::string label;

  char grade = ' ';

  if ('a' <= grade && grade >= 'z') {
    printf("%d", 'a' + 'b');
  }

  // input and processing
  cout << "\nEnter the number of vertices: ";
  cin >> numVertices;
  GraphAdjacencyList graph(numVertices);

  cout << "\nEnter labels for " << numVertices << " vertices: \n";
  for (int i = 0; i < numVertices; i++) {
    cout << "Label for vertex " << i + 1 << ": ";
    cin >> label;
    graph.addVertex(label);
  }

  cout << "\n";
  graph.printVertices();

  return 0;
}

// Output:
/*


*/

/*
Example:

 +-----+  +-----+  +-----+
 |  A  |--|  B  |--|  C  |
 +--+--+  +-----+  +-----+
    |   \         /
    |    \       /
 +--+--+  +-----+
 |  D  |--|  E  |
 +-----+  +-----+

Edges:
 A: A-B, A-D, A-E
 B: B-A, B-C
 C: C-B, C-E
 D: D-A, D-E
 E: E-A, E-C

Inside the List:

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
   +=====+  +-----+  +-----+
   |  D  |--|  A  |--|  E  |
   +=====+  +-----+  +-----+
   +=====+  +-----+  +-----+
   |  E  |--|  A  |--|  C  |
   +=====+  +-----+  +-----+

*/