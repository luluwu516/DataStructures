#include <queue>

#include "WeightedGraph.hpp"

/*

Prim's algorithm is a greedy algorithm used to find the Minimum Spanning Tree
(MST) in a weighted, undirected graph. It determines the subset of edges that
connects all vertices with the minimum total edge weight.

How it works:
1. Select an initial vertex
2. Identify all adjacent edges
3. Choose the minimum-weight edge
4. Add the selected edge and vertex to the MST
5. Repeat steps 2-4 until all vertices are included

 Characteristics:
 * Builds MST by starting from an arbitrary vertex
 * Grows the spanning tree one edge at a time
 * Always selects the minimum-weight edge connecting a vertex in the tree to a
   vertex outside the tree
 * Guarantees a minimal-cost connection for all graph vertices

 Time Complexity:
 * With adjacency matrix: O(V^2)
 * With binary heap: O(E log V)
 * With Fibonacci heap: O(E + V log V)

 Space Complexity: O(V + E)

 Pros:
 * Efficiently finds minimum spanning tree
 * Works well for sparse graphs
 * Simple implementation
 * Handles disconnected graphs

 Cons:
 * Less efficient for dense graphs
 * Requires complete graph representation
 * Performance depends on data structure used

*/

void WeightedGraph::prim(const std::string& startLabel) {
  int startIndex = findVertexIndex(startLabel);
  if (startIndex == -1) {
    cout << "Error! Vertex doesn't exist\n";
    return;
  }

  std::vector<Edge> minimumSpanningTree;
  int totalWeight = 0;

  std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> pq;

  // track visited vertices
  std::vector<bool> visited(numVertices, false);
  visited[startIndex] = true;

  // add all edges from the starting vertex to the priority queue
  for (int j = 0; j < numVertices; j++) {
    if (adjacencyMatrix[startIndex][j] > 0) {
      pq.push(Edge(vertexLabels[startIndex], vertexLabels[j],
                   adjacencyMatrix[startIndex][j]));
    }
  }

  // continue until all vertices are included or no more edges
  while (!pq.empty()) {
    Edge currentEdge = pq.top();
    pq.pop();

    // find indices of source and destination
    int srcIndex = findVertexIndex(currentEdge.src);
    int desIndex = findVertexIndex(currentEdge.des);

    // skip if destination already visited
    if (visited[desIndex]) {
      continue;
    }

    // add edge to MST
    minimumSpanningTree.push_back(currentEdge);
    totalWeight += currentEdge.weight;
    visited[desIndex] = true;

    // add new edges from the newly added vertex
    for (int j = 0; j < numVertices; j++) {
      if (!visited[j] && adjacencyMatrix[desIndex][j] > 0) {
        pq.push(Edge(currentEdge.des, vertexLabels[j],
                     adjacencyMatrix[desIndex][j]));
      }
    }
  }

  // print prim's MST results
  cout << "Prim's Minimum Spanning Tree (starting from " << startLabel
       << "):\n";
  if (minimumSpanningTree.empty()) {
    cout << "No spanning tree exists\n";
    return;
  }

  cout << "Edges in MST:\n";
  for (const auto& edge : minimumSpanningTree) {
    cout << " " << edge.src << "-" << edge.des << " " << edge.weight << "\n";
  }
  cout << "\nTotal weight: " << totalWeight << "\n";
}

/*

 +-----+ 3 +-----+ 6 +-----+
 |  a  |---|  b  |---|  c  |
 +--+--+   +-----+   +-----+
    |   \           /
  5 |    \ 2     4 /
    |     \       /
 +--+--+ 1 +-----+
 |  d  |---|  e  |
 +-----+   +-----+

      | a b c d e
    --+----------
    a | 0 3 0 5 2
    b | 3 0 6 0 0
    c | 0 6 0 0 4
    d | 5 0 0 0 1
    e | 2 0 4 1 0

               startIndex
                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
  vertexLabels  |  a  |  b  |  c  |  d  |  e  |
                +-----+-----+-----+-----+-----+
                   ^
               startLabel

                +-----+
   totalWeight  |  0  |
                +-----+

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
                |     |     |     |     |     |  (edge)
            pq  +--|--+--|--+--|--+--|--+--|--+
                |     |     |     |     |     |  (weight)
                +-----+-----+-----+-----+-----+

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
       visited  |  f  |  f  |  f  |  f  |  f  |
                +-----+-----+-----+-----+-----+

 since we start with vertex a (in this example), assign it to be true

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
       visited  |  t  |  f  |  f  |  f  |  f  |
                +-----+-----+-----+-----+-----+

 add all edges from the starting vertex to the pq

                   0     1     2
                +-----+-----+-----+
                | a-e | a-b | a-d |  (edge)
            pq  +--|--+--|--+--|--+
                |  2  |  3  |  5  |  (weight)
                +-----+-----+-----+

 start prim's algorithm...
 ********** pq is not empty **********

                +-----+
                | a-e |
                +-----+
              currentEdge

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
  vertexLabels  |  a  |  b  |  c  |  d  |  e  |
                +-----+-----+-----+-----+-----+

                +-----+     +-----+
                |  0  |     |  4  |
                +-----+     +-----+
                srcIndex    desIndex

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
       visited  |  t  |  f  |  f  |  f  |  f  |
                +-----+-----+-----+-----+-----+
                                           ^

                   0
                +-----+
           mst  | a-e |
                +-----+

                   0
                +-----+
   totalWeight  |  2  |
                +-----+

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
       visited  |  t  |  f  |  f  |  f  |  t  |
                +-----+-----+-----+-----+-----+
                                           ^

                   0     1     2     3
                +-----+-----+-----+-----+
                | e-d | a-b | e-c | a-d |  (edge)
            pq  +--|--+--|--+--|--+--|--+
                |  1  |  3  |  4  |  5  |  (weight)
                +-----+-----+-----+-----+

   ========== pq is not empty ==========

                +-----+
                | e-d |
                +-----+
              currentEdge

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
  vertexLabels  |  a  |  b  |  c  |  d  |  e  |
                +-----+-----+-----+-----+-----+

                +-----+     +-----+
                |  4  |     |  3  |
                +-----+     +-----+
                srcIndex    desIndex

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
       visited  |  t  |  f  |  f  |  f  |  t  |
                +-----+-----+-----+-----+-----+
                                     ^

                   0     1
                +-----+-----+
           mst  | a-e | e-d |
                +-----+-----+

                   0
                +-----+
   totalWeight  |  3  |
                +-----+

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
       visited  |  t  |  f  |  f  |  t  |  t  |
                +-----+-----+-----+-----+-----+
                                     ^

                   0     1     2
                +-----+-----+-----+
                | a-b | e-c | a-d |  (edge)
            pq  +--|--+--|--+--|--+
                |  3  |  4  |  5  |  (weight)
                +-----+-----+-----+

   ========== pq is not empty ==========

                +-----+
                | a-b |
                +-----+
              currentEdge

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
  vertexLabels  |  a  |  b  |  c  |  d  |  e  |
                +-----+-----+-----+-----+-----+

                +-----+     +-----+
                |  0  |     |  1  |
                +-----+     +-----+
                srcIndex    desIndex

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
       visited  |  t  |  f  |  f  |  t  |  t  |
                +-----+-----+-----+-----+-----+
                         ^

                   0     1     2
                +-----+-----+-----+
           mst  | a-e | e-d | a-b |
                +-----+-----+-----+

                   0
                +-----+
   totalWeight  |  6  |
                +-----+

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
       visited  |  t  |  t  |  f  |  t  |  t  |
                +-----+-----+-----+-----+-----+
                         ^

                   0     1     2
                +-----+-----+-----+
                | e-c | a-d | b-c |  (edge)
            pq  +--|--+--|--+--|--+
                |  4  |  5  |  6  |  (weight)
                +-----+-----+-----+

   ========== pq is not empty ==========

                +-----+
                | e-c |
                +-----+
              currentEdge

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
  vertexLabels  |  a  |  b  |  c  |  d  |  e  |
                +-----+-----+-----+-----+-----+

                +-----+     +-----+
                |  4  |     |  2  |
                +-----+     +-----+
                srcIndex    desIndex

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
       visited  |  t  |  t  |  f  |  t  |  t  |
                +-----+-----+-----+-----+-----+
                               ^

                   0     1     2     3
                +-----+-----+-----+-----+
           mst  | a-e | e-d | a-b | e-c |
                +-----+-----+-----+-----+

                   0
                +------+
   totalWeight  |  10  |
                +------+

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
       visited  |  t  |  t  |  t  |  t  |  t  |
                +-----+-----+-----+-----+-----+
                               ^

                   0     1
                +-----+-----+
                | a-d | b-c |  (edge)
            pq  +--|--+--|--+
                |  5  |  6  |  (weight)
                +-----+-----+

   ========== pq is not empty ==========

                +-----+
                | a-d |
                +-----+
              currentEdge

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
  vertexLabels  |  a  |  b  |  c  |  d  |  e  |
                +-----+-----+-----+-----+-----+

                +-----+     +-----+
                |  0  |     |  3  |
                +-----+     +-----+
                srcIndex    desIndex

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
       visited  |  t  |  t  |  t  |  t  |  t  |
                +-----+-----+-----+-----+-----+
                                     ^

                   0
                +-----+
                | b-c |  (edge)
            pq  +--|--+
                |  6  |  (weight)
                +-----+

   ========== pq is not empty ==========

                +-----+
                | b-c |
                +-----+
              currentEdge

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
  vertexLabels  |  a  |  b  |  c  |  d  |  e  |
                +-----+-----+-----+-----+-----+

                +-----+     +-----+
                |  1  |     |  2  |
                +-----+     +-----+
                srcIndex    desIndex

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
       visited  |  t  |  t  |  t  |  t  |  t  |
                +-----+-----+-----+-----+-----+
                               ^

// pq is empty!
************************************************************

                   0     1     2     3
                +-----+-----+-----+-----+
           mst  | a-e | e-d | a-b | e-c |
                +-----+-----+-----+-----+

                   0
                +------+
   totalWeight  |  10  |
                +------+

Prim's Minimum Spanning Tree (starting from a):
Edges in MST:
 a-e 2
 e-d 1
 a-b 3
 e-c 4

Total weight: 10

*/