#ifndef WEIGHTEDGRAPH_HPP
#define WEIGHTEDGRAPH_HPP

#include <iostream>  // preprocessor directive
#include <string>
#include <vector>

using std::cin;  // using declaration
using std::cout;

struct Edge {
  std::string src;
  std::string des;
  int weight;

  Edge(const std::string& srcLabel, const std::string& desLabel, int w)
      : src(srcLabel), des(desLabel), weight(w) {}

  bool operator<(const Edge& other) const { return weight < other.weight; }
};

/*

A Weighted Graph is a graph where each edge has an associated weight or cost.
These weights could represent various real-world values like:
 * Distances between cities
 * Cost of operations
 * Time to travel
 * Network bandwidth
 * Reliability of connections

Types of Weighted Graphs:
 * Undirected Weighted Graph (we'll use this type)
   - Edges have no direction
   - Weight is same in both directions

 +-----+ 3 +-----+ 6 +-----+
 |  a  |---|  b  |---|  c  |
 +--+--+   +-----+   +-----+
    |   \           /
  5 |    \ 2     4 /
    |     \       /
 +--+--+ 1 +-----+
 |  d  |---|  e  |
 +-----+   +-----+

 * Directed Weighted Graph (Digraph)
   - Edges have direction
   - Weight A->B might differ from B->A

 +-----+ 3 +-----+ 7 +-----+
 |  a  |-->|  b  |-->|  c  |
 |     |<--|     |   |     |
 +--+--+ 6 +-----+   +-----+
    ^   ^           ^
  5 |    \ 2     4 /
    |     \       /
 +--+--+ 8 +-----+
 |  d  |-->|  e  |
 |     |<--|     |
 +-----+ 1 +-----+

Common Representations:

 +-----+ 3 +-----+ 6 +-----+
 |  a  |---|  b  |---|  c  |
 +--+--+   +-----+   +-----+
    |   \           /
  5 |    \ 2     4 /
    |     \       /
 +--+--+ 1 +-----+
 |  d  |---|  e  |
 +-----+   +-----+

 * Adjacency Matrix (we'll use this representation)
   - Good for dense graphs
   - O(1) edge lookup
   - O(V^2) space complexity

      | a b c d e
    --+----------
    a | 0 3 0 5 2
    b | 3 0 6 0 0
    c | 0 6 0 0 4
    d | 5 0 0 0 1
    e | 2 0 4 1 0

 * Adjacency List
   - Better for sparse graphs
   - More space-efficient
   - Faster iteration over edges

   +=====+  +-----+  +-----+  +-----+
   |  a  |--| b:3 |--| d:5 |--| e:2 |
   +=====+  +-----+  +-----+  +-----+
   +=====+  +-----+  +-----+
   |  b  |--| a:3 |--| c:6 |
   +=====+  +-----+  +-----+
   +=====+  +-----+  +-----+
   |  c  |--| b:6 |--| e:4 |
   +=====+  +-----+  +-----+
   +=====+  +-----+
   |  d  |--| a:5 |
   +=====+  +-----+
   +=====+  +-----+  +-----+
   |  e  |--| a:2 |--| c:4 |
   +=====+  +-----+  +-----+

*/

class WeightedGraph {
 public:
  // constructor
  WeightedGraph(int);

  bool addVertex(const std::string&);
  bool addEdge(const std::string&, const std::string&, int);
  bool searchVertex(const std::string&) const;
  bool searchEdge(const std::string&, const std::string&) const;
  bool removeVertex(const std::string&);
  bool removeEdge(const std::string&, const std::string&);

  int getNumVertices() const;
  int getWeight(const std::string&, const std::string&) const;
  bool isEmpty() const;

  // Kruskal's minimum spanning tree algorithm
  void kruskal();

  // Prim’s minimum spanning tree algorithm
  void prim(const std::string&);

  void printVertices() const;
  void printMatrix() const;
  void printEdges() const;
  void printInfo() const;

 private:
  int numVertices;
  std::vector<std::vector<int>> adjacencyMatrix;
  std::vector<std::string> vertexLabels;
  std::vector<Edge> edges;

  // disjoint set
  std::vector<int> parent;
  std::vector<int> rank;

  int findVertexIndex(const std::string&) const;
  void verifyMatrixSymmetry() const;
  int find(int);
  void unite(int, int);
};

#endif