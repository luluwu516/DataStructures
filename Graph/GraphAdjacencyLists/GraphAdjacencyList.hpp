#include <iostream>  // preprocessor directive
#include <string>
#include <vector>

#ifndef GRAPHADJACENCYLIST_HPP
#define GRAPHADJACENCYLIST_HPP

using std::cin;  // using declaration
using std::cout;

struct Node {
  std::string label;
  Node* next;

  Node(std::string l) : label(l), next(nullptr) {}
};

/*
Undirected Graph
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
 private:
  std::vector<std::string> vertexLabels;
  std::vector<Node*> adjacencyList;

  int findVertexIndex(const std::string&) const;
  void addDirectedEdge(const std::string&, const int&, const int&);
  void removeDirectedEdge(const int&, const int&);

 public:
  // destructor
  ~GraphAdjacencyList();

  bool addVertex(const std::string&);
  bool addEdge(const std::string&, const std::string&);
  bool searchLabel(const std::string&) const;
  bool searchEdge(const std::string&, const std::string&) const;
  bool removeVertex(const std::string&);
  bool removeEdge(const std::string&, const std::string&);
  bool isEmpty() const;

  // breadth-first traversal
  void BFS(const std::string&);

  // depth-first traversal
  void DFS(const std::string&);

  void printVertices() const;
  void printEdges() const;
  void printInfo() const;
};

#endif