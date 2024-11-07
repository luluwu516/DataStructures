#ifndef WEIGHTEDGRAPH_HPP
#define WEIGHTEDGRAPH_HPP

#include <iostream>  // preprocessor directive
#include <string>
#include <vector>

using std::cin;  // using declaration
using std::cout;

/*

A Weighted Graph is a graph where each edge has an associated weight or cost.
These weights could represent various real-world values like:
 * Distances between cities
 * Cost of operations
 * Time to travel
 * Network bandwidth
 * Reliability of connections

Types of Weighted Graphs:
 * Directed Weighted Graph (Digraph)
   - Edges have direction
   - Weight A->B might differ from B->A

 +-----+ 3 +-----+ 7 +-----+
 |  A  |-->|  B  |-->|  C  |
 |     |<--|     |   |     |
 +--+--+ 6 +-----+   +-----+
    ^   ^           ^
  5 |    \ 2     4 /
    |     \       /
 +--+--+ 8 +-----+
 |  D  |-->|  E  |
 |     |<--|     |
 +-----+ 1 +-----+

 * Undirected Weighted Graph
   - Edges have no direction
   - Weight is same in both directions

 +-----+ 3 +-----+ 6 +-----+
 |  A  |---|  B  |---|  C  |
 +--+--+   +-----+   +-----+
    |   \           /
  5 |    \ 2     4 /
    |     \       /
 +--+--+ 1 +-----+
 |  D  |---|  E  |
 +-----+   +-----+

Common Representations:

 +-----+ 3 +-----+ 6 +-----+
 |  A  |---|  B  |---|  C  |
 +--+--+   +-----+   +-----+
    |   \           /
  5 |    \ 2     4 /
    |     \       /
 +--+--+ 1 +-----+
 |  D  |---|  E  |
 +-----+   +-----+

 * Adjacency Matrix
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

  // Dijkstra's algorithm single point shortest path
  void dijkstra(const std::string&);

  // Floyd-Warshall all pair shortest path
  void floydWarshall(const std::string&);

  // Kruskal's minimum spanning tree algorithm
  void kruskal(const std::string&);

  void printVertices() const;
  void printMatrix() const;
  void printInfo() const;

 private:
  int numVertices;
  std::vector<std::vector<int>> adjacencyMatrix;
  std::vector<std::string> vertexLabels;

  int findVertexIndex(const std::string&) const;
  void verifyMatrixSymmetry() const;
};

#endif