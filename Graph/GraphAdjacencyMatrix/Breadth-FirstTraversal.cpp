#include <queue>

#include "GraphAdjacencyMatrix.hpp"

/*

Breadth First Search is a graph/tree traversal algorithm that explores all
vertices at the present depth level before moving to vertices at the next depth
level. Think of it like exploring a tree level by level, from left to right.

 Characteristics:
 * Uses a Queue (FIFO) data structure
 * Explores neighbors first before moving to next level
 * Guarantees shortest path in unweighted graphs
 * Visits all vertices at distance 'k' before any vertices at distance 'k+1'

 Time Complexity: O(V + E)
 - V: number of vertices
 - E: number of edges
 - Must visit every vertex once: O(V)
 - Must explore every edge once: O(E)

 Space Complexity: O(V)
 In worst case, queue might contain all vertices (Typically happens in wide
 graphs)

 Pros:
 * Finds shortest path in unweighted graphs
 * Complete algorithm (will find a solution if it exists)
 * Good for finding closest/nearest neighbor type problems
 * Memory efficient when search area is closer to source
 * Optimal for shallow but wide trees/graphs

 Cons:
 * Uses more memory than Depth First Search (DFS)
 * Not suitable for game trees or decision trees (where depth is important)
 * Less memory efficient for deep graphs
 * Not ideal for very large graphs due to memory requirements

*/

void GraphAdjacencyMatrix::BFS(const std::string& startLabel) {
  int startIndex = findVertexIndex(startLabel);
  if (startIndex == -1) {
    cout << "Error!! Vertex not found!\n";
    return;
  }

  // keep track of visited vertices
  std::vector<std::string> visited;
  std::queue<std::string> queue;

  // start BFS from the given vertex
  queue.push(startLabel);
  visited.push_back(startLabel);

  cout << "BFS starting from vertex " << startLabel << ": ";

  while (!queue.empty()) {
    // get the next vertex to process
    std::string currLabel = queue.front();
    queue.pop();
    cout << currLabel << " ";

    // find the index of current vertex
    int currIndex = findVertexIndex(currLabel);

    // process all adjacent vertices
    for (int i = 0; i < numVertices; i++) {
      if (adjacencyMatrix[currIndex][i] &&
          std::find(visited.begin(), visited.end(), vertexLabels[i]) ==
              visited.end()) {
        queue.push(vertexLabels[i]);
        visited.push_back(vertexLabels[i]);
      }
    }
  }
  cout << "\n";
}

/*

 +-----+  +-----+  +-----+
 |  a  |--|  b  |--|  c  |
 +--+--+  +-----+  +-----+
    |   \         /
    |    \       /
 +--+--+  +-----+
 |  d  |  |  e  |
 +-----+  +-----+

Enter starting vertex for BFS: a

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
  vertexLabels  |  a  |  b  |  c  |  d  |  e  |
                +-----+-----+-----+-----+-----+
                   ^

  +-----+       +-----+
  |  a  |       |  0  |
  +-----+       +-----+
 startLabel    startIndex

              0
           +-----+
  queue    |  a  |
           +-----+

              0
           +-----+
  visited  |  a  |
           +-----+

 start bfs...
 ********** queue is not empty **********
           +-----+
  queue    |  a  |
           +-----+

  +-----+       +-----+
  |  a  |       |  0  |
  +-----+       +-----+
 currLabel     currIndex

           +-----+
  queue    (empty)
           +-----+

 adjacencyMatrix:
    | a b c d e
  --+----------
  a | 0 1 0 1 1  <-- this line
  b | 1 0 1 0 0
  c | 0 1 0 0 1
  d | 1 0 0 0 0
  e | 1 0 1 0 0

           +-----+-----+-----+
  queue    |  b  |  d  |  e  |
           +-----+-----+-----+
           +-----+-----+-----+-----+
  visited  |  a  |  b  |  d  |  e  |
           +-----+-----+-----+-----+

 ********** queue is not empty **********

  +-----+       +-----+
  |  b  |       |  1  |
  +-----+       +-----+
 currLabel     currIndex

           +-----+-----+
  queue    |  d  |  e  |
           +-----+-----+

 adjacencyMatrix:
    | a b c d e
  --+----------
  a | 0 1 0 1 1
  b | 1 0 1 0 0  <-- this line
  c | 0 1 0 0 1
  d | 1 0 0 0 0
  e | 1 0 1 0 0

           +-----+-----+-----+
  queue    |  d  |  e  |  c  |
           +-----+-----+-----+
           +-----+-----+-----+-----+-----+
  visited  |  a  |  b  |  d  |  e  |  c  |
           +-----+-----+-----+-----+-----+

 ********** queue is not empty **********

  +-----+       +-----+
  |  d  |       |  3  |
  +-----+       +-----+
 currLabel     currIndex

           +-----+-----+
  queue    |  e  |  c  |
           +-----+-----+

 adjacencyMatrix:
    | a b c d e
  --+----------
  a | 0 1 0 1 1
  b | 1 0 1 0 0
  c | 0 1 0 0 1
  d | 1 0 0 0 0  <-- this line
  e | 1 0 1 0 0

           +-----+-----+
  queue    |  e  |  c  |
           +-----+-----+
           +-----+-----+-----+-----+-----+
  visited  |  a  |  b  |  d  |  e  |  c  |
           +-----+-----+-----+-----+-----+

 ********** queue is not empty **********

  +-----+       +-----+
  |  e  |       |  4  |
  +-----+       +-----+
 currLabel     currIndex

           +-----+
  queue    |  c  |
           +-----+

 adjacencyMatrix:
    | a b c d e
  --+----------
  a | 0 1 0 1 1
  b | 1 0 1 0 0
  c | 0 1 0 0 1
  d | 1 0 0 0 0
  e | 1 0 1 0 0  <-- this line

           +-----+
  queue    |  c  |
           +-----+
           +-----+-----+-----+-----+-----+
  visited  |  a  |  b  |  d  |  e  |  c  |
           +-----+-----+-----+-----+-----+

 ********** queue is not empty **********

  +-----+       +-----+
  |  c  |       |  2  |
  +-----+       +-----+
 currLabel     currIndex

           +-----+
  queue    (empty)
           +-----+

 adjacencyMatrix:
    | a b c d e
  --+----------
  a | 0 1 0 1 1
  b | 1 0 1 0 0
  c | 0 1 0 0 1  <-- this line
  d | 1 0 0 0 0
  e | 1 0 1 0 0

           +-----+
  queue    (empty)
           +-----+
           +-----+-----+-----+-----+-----+
  visited  |  a  |  b  |  d  |  e  |  c  |
           +-----+-----+-----+-----+-----+

 // queue is empty!

Output:
BFS starting from vertex a: a b d e c

*/