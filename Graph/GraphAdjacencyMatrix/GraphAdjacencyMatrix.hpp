#include <iostream>  // preprocessor directive
#include <string>
#include <vector>

#ifndef GRAPHADJACENCYMATRIX_HPP
#define GRAPHADJACENCYMATRIX_HPP

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
  GraphAdjacencyMatrix(int);

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
  void printMatrix() const;
  void printInfo() const;

 private:
  int numVertices;
  std::vector<std::vector<int>> adjacencyMatrix;
  std::vector<std::string> vertexLabels;

  int findVertexIndex(const std::string&) const;
};

#endif