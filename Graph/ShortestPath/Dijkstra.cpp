#include <queue>

#include "WeightedGraph.hpp"

/*

Dijkstra's Algorithm is a graph search algorithm that solves the single-source
shortest path problem for a graph with non-negative edge weights.

 Characteristics:
 * Greedy approach - always selects the minimum-weight path
 * Works on both directed and undirected graphs
 * Requires all edge weights to be non-negative
 * Maintains a set of visited vertices and distances

 Time Complexity:
 * With binary heap: O((V + E) log V)
   - V is the number of vertices
   - E is the number of edges
 * With array implementation: O(V²)
   - Space Complexity: O(V)

 Space Complexity: O(V)

 Pros:
 * Guarantees the optimal (shortest) path
 * Efficient for dense graphs when using a priority queue
 * Can be modified to track the actual path, not just distances
 * Works well with positive edge weights

 Cons:
 * Doesn't work with negative edge weights
 * May be slower for sparse graphs compared to other algorithms
 * Requires all nodes to be accessible
 * Can be memory-intensive for very large graphs

*/

void WeightedGraph::dijkstra(const std::string& startLabel) {
  int startIndex = findVertexIndex(startLabel);
  if (startIndex == -1) {
    cout << "Error! Vertex doesn't exist\n";
    return;
  }
  // priority queue to store {distance, vertex} pairs
  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                      std::greater<std::pair<int, int>>>
      pq;

  // vector to store distances
  std::vector<int> dist(numVertices, std::numeric_limits<int>::max());

  // assign the start vertex with distance 0
  dist[startIndex] = 0;

  // insert startIndex
  pq.push({0, startIndex});

  // track visited vertices
  std::vector<bool> visited(numVertices, false);

  while (!pq.empty()) {
    // get vertex with minimum distance
    int u = pq.top().second;
    pq.pop();

    // skip if already visited
    if (visited[u]) {
      continue;
    }

    // mark as visited
    visited[u] = true;

    // check all adjacent vertices
    for (int vertexIndex = 0; vertexIndex < numVertices; vertexIndex++) {
      // if there is an edge and vertex not visited
      if (adjacencyMatrix[u][vertexIndex] > 0 && !visited[vertexIndex]) {
        // calculate new distance
        int newDist = dist[u] + adjacencyMatrix[u][vertexIndex];

        // update distance if shorter path found
        if (newDist < dist[vertexIndex]) {
          dist[vertexIndex] = newDist;
          pq.push({newDist, vertexIndex});
        }
      }
    }
  }

  // output the result
  cout << "The shortest path from vertex " << startLabel << ": \n";

  for (int i = 0; i < numVertices; i++) {
    if (dist[i] == std::numeric_limits<int>::max()) {
      dist[i] = -1;
    }
    cout << " * To vertex " << vertexLabels[i] << ": " << dist[i] << "\n";
  }
  cout << "\n";
}

/*

 +-----+ 3 +-----+ 6 +-----+
 |  A  |---|  B  |---|  C  |
 +--+--+   +-----+   +-----+
    |   \           /
  5 |    \ 2     4 /
    |     \       /
 +--+--+ 1 +-----+
 |  D  |---|  E  |
 +-----+   +-----+

        0 1 2 3 4
      | a b c d e
    --+----------
  0 a | 0 3 0 5 2
  1 b | 3 0 6 0 0
  2 c | 0 6 0 0 4
  3 d | 5 0 0 0 1
  4 e | 2 0 4 1 0

               startIndex
                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
  vertexLabels  |  a  |  b  |  c  |  d  |  e  |
                +-----+-----+-----+-----+-----+
                   ^
               startLabel

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
                |     |     |     |     |     |  (distance)
            pq  +--|--+--|--+--|--+--|--+--|--+
                |     |     |     |     |     |  (index)
                +-----+-----+-----+-----+-----+

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
          dist  |  ∞  |  ∞  |  ∞  |  ∞  |  ∞  |
                +-----+-----+-----+-----+-----+


 since we start with start vertex, assign start index to be 0

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
          dist  |  0  |  ∞  |  ∞  |  ∞  |  ∞  |
                +-----+-----+-----+-----+-----+

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
                |  0  |     |     |     |     |  (distance)
            pq  +--|--+--|--+--|--+--|--+--|--+
                |  0  |     |     |     |     |  (index)
                +-----+-----+-----+-----+-----+

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
       visited  |  f  |  f  |  f  |  f  |  f  |
                +-----+-----+-----+-----+-----+

 start dijkstra's algorithm...
 ********** pq is not empty **********

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
                |  0  |     |     |     |     |  (distance)
            pq  +--|--+--|--+--|--+--|--+--|--+
                |  0  |     |     |     |     |  (index)
                +-----+-----+-----+-----+-----+

                +-----+
                |  0  |  get vertex with minimum distance
                +-----+
                   u

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
                |     |     |     |     |     |  (distance)
            pq  +--|--+--|--+--|--+--|--+--|--+
                |     |     |     |     |     |  (index)
                +-----+-----+-----+-----+-----+

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
       visited  |  t  |  f  |  f  |  f  |  f  |
                +-----+-----+-----+-----+-----+
                   ^
                set visited index [u] to be true

      | a b c d e
    --+----------
    a | 0 3 0 5 2  <-- this line
    b | 3 0 6 0 0
    c | 0 6 0 0 4
    d | 5 0 0 0 1
    e | 2 0 4 1 0

   ========== vertexIndex = 0 ==========

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
          dist  |  0  |  ∞  |  ∞  |  ∞  |  ∞  |
                +-----+-----+-----+-----+-----+

   vertexIndex     0     1     2     3     4
                +-----+-----+-----+-----+-----+
[u][vertexIndex]|  0  |  3  |  0  |  5  |  2  |
[0]     [0]     +-----+-----+-----+-----+-----+
                   ^
                [0][0] == 0 do nothing

   ========== vertexIndex = 1 ==========

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
          dist  |  0  |  ∞  |  ∞  |  ∞  |  ∞  |
                +-----+-----+-----+-----+-----+

   vertexIndex     0     1     2     3     4
                +-----+-----+-----+-----+-----+
[u][vertexIndex]|  0  |  3  |  0  |  5  |  2  |
[0]     [1]     +-----+-----+-----+-----+-----+
                         ^

                +-----+  dist[u] + adjacencyMatrix[u][vertexIndex]
                |  3  |  = dist[0] + adjacencyMatrix[0][1]
                +-----+  = 0 + 3
                newDist  = 3

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
          dist  |  0  |  3  |  ∞  |  ∞  |  ∞  |
                +-----+-----+-----+-----+-----+

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
                |  3  |     |     |     |     |  (distance)
            pq  +--|--+--|--+--|--+--|--+--|--+
                |  1  |     |     |     |     |  (index)
                +-----+-----+-----+-----+-----+

   ========== vertexIndex = 2 ==========

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
          dist  |  0  |  3  |  ∞  |  ∞  |  ∞  |
                +-----+-----+-----+-----+-----+

   vertexIndex     0     1     2     3     4
                +-----+-----+-----+-----+-----+
[u][vertexIndex]|  0  |  3  |  0  |  5  |  2  |
[0]     [2]     +-----+-----+-----+-----+-----+
                               ^
                         [0][2] == 0 do nothing

   ========== vertexIndex = 3 ==========

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
          dist  |  0  |  3  |  ∞  |  ∞  |  ∞  |
                +-----+-----+-----+-----+-----+

   vertexIndex     0     1     2     3     4
                +-----+-----+-----+-----+-----+
[u][vertexIndex]|  0  |  3  |  0  |  5  |  2  |
[0]     [3]     +-----+-----+-----+-----+-----+
                                     ^

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
       visited  |  t  |  f  |  f  |  f  |  f  |
                +-----+-----+-----+-----+-----+
                                     ^

                +-----+  dist[u] + adjacencyMatrix[u][vertexIndex]
                |  5  |  = dist[0] + adjacencyMatrix[0][3]
                +-----+  = 0 + 5
                newDist  = 5

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
          dist  |  0  |  3  |  ∞  |  5  |  ∞  |
                +-----+-----+-----+-----+-----+

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
                |  3  |  5  |     |     |     |  (distance)
            pq  +--|--+--|--+--|--+--|--+--|--+
                |  1  |  3  |     |     |     |  (index)
                +-----+-----+-----+-----+-----+

   ========== vertexIndex = 4 ==========

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
          dist  |  0  |  3  |  ∞  |  5  |  ∞  |
                +-----+-----+-----+-----+-----+

   vertexIndex     0     1     2     3     4
                +-----+-----+-----+-----+-----+
[u][vertexIndex]|  0  |  3  |  0  |  5  |  2  |
[0]     [4]     +-----+-----+-----+-----+-----+
                                           ^

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
       visited  |  t  |  f  |  f  |  f  |  f  |
                +-----+-----+-----+-----+-----+
                                           ^

                +-----+  dist[u] + adjacencyMatrix[u][vertexIndex]
                |  2  |  = dist[0] + adjacencyMatrix[0][4]
                +-----+  = 0 + 2
                newDist  = 2

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
          dist  |  0  |  3  |  ∞  |  5  |  2  |
                +-----+-----+-----+-----+-----+

 2 < 3, so the pair will be inserted to index 0

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
                |  2  |  3  |  5  |     |     |  (distance)
            pq  +--|--+--|--+--|--+--|--+--|--+
                |  4  |  1  |  3  |     |     |  (index)
                +-----+-----+-----+-----+-----+
                   ^

 ********** pq is not empty **********

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
                |  2  |  3  |  5  |     |     |  (distance)
            pq  +--|--+--|--+--|--+--|--+--|--+
                |  4  |  1  |  3  |     |     |  (index)
                +-----+-----+-----+-----+-----+

                +-----+
                |  4  |
                +-----+
                   u

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
                |  3  |  5  |     |     |     |  (distance)
            pq  +--|--+--|--+--|--+--|--+--|--+
                |  1  |  3  |     |     |     |  (index)
                +-----+-----+-----+-----+-----+

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
       visited  |  t  |  f  |  f  |  f  |  t  |
                +-----+-----+-----+-----+-----+
                                           ^
                 set visited index u to be true

      | a b c d e
    --+----------
    a | 0 3 0 5 2
    b | 3 0 6 0 0
    c | 0 6 0 0 4
    d | 5 0 0 0 1
    e | 2 0 4 1 0  <-- this line

   ========== vertexIndex = 0 ==========

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
          dist  |  0  |  3  |  ∞  |  5  |  2  |
                +-----+-----+-----+-----+-----+

   vertexIndex     0     1     2     3     4
                +-----+-----+-----+-----+-----+
[u][vertexIndex]|  2  |  0  |  4  |  1  |  0  |
[4]     [0]     +-----+-----+-----+-----+-----+
                   ^

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
       visited  |  t  |  f  |  f  |  f  |  t  |
                +-----+-----+-----+-----+-----+
                   ^
                we visited before!

   ========== vertexIndex = 1 ==========

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
          dist  |  0  |  3  |  ∞  |  5  |  2  |
                +-----+-----+-----+-----+-----+

   vertexIndex     0     1     2     3     4
                +-----+-----+-----+-----+-----+
[u][vertexIndex]|  2  |  0  |  4  |  1  |  0  |
[4]     [1]     +-----+-----+-----+-----+-----+
                         ^
                    [4][1] == 0, do nothing

   ========== vertexIndex = 2 ==========

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
          dist  |  0  |  3  |  ∞  |  5  |  2  |
                +-----+-----+-----+-----+-----+

   vertexIndex     0     1     2     3     4
                +-----+-----+-----+-----+-----+
[u][vertexIndex]|  2  |  0  |  4  |  1  |  0  |
[4]     [2]     +-----+-----+-----+-----+-----+
                               ^

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
       visited  |  t  |  f  |  f  |  f  |  t  |
                +-----+-----+-----+-----+-----+
                               ^

                +-----+  dist[u] + adjacencyMatrix[u][vertexIndex]
                |  6  |  = dist[4] + adjacencyMatrix[4][2]
                +-----+  = 2 + 4
                newDist  = 6

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
          dist  |  0  |  3  |  6  |  5  |  2  |
                +-----+-----+-----+-----+-----+
                               ^
                            6 < ∞, so set it to 6

                a can't reach c directly,
                the algorithm found a way to c
                  a --2--> e --4--> c
                which costs 6

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
                |  3  |  5  |  6  |     |     |  (distance)
            pq  +--|--+--|--+--|--+--|--+--|--+
                |  1  |  3  |  4  |     |     |  (index)
                +-----+-----+-----+-----+-----+

   ========== vertexIndex = 3 ==========

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
          dist  |  0  |  3  |  6  |  5  |  2  |
                +-----+-----+-----+-----+-----+

   vertexIndex     0     1     2     3     4
                +-----+-----+-----+-----+-----+
[u][vertexIndex]|  2  |  0  |  4  |  1  |  0  |
[4]     [3]     +-----+-----+-----+-----+-----+
                                     ^

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
       visited  |  t  |  f  |  f  |  f  |  t  |
                +-----+-----+-----+-----+-----+
                                     ^

                +-----+  dist[u] + adjacencyMatrix[u][vertexIndex]
                |  3  |  = dist[4] + adjacencyMatrix[4][3]
                +-----+  = 2 + 1
                newDist  = 3

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
          dist  |  0  |  3  |  6  |  3  |  2  |
                +-----+-----+-----+-----+-----+
                                     ^
                            3 < 5, so set it to 3

                It takes 5 to go from a to d directly,
                the algorithm found a shorter way to d
                  a --2--> e --1--> d
                which costs only 3

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
                |  3  |  3  |  5  |  6  |     |  (distance)
            pq  +--|--+--|--+--|--+--|--+--|--+
                |  1  |  3  |  3  |  4  |     |  (index)
                +-----+-----+-----+-----+-----+

   ========== vertexIndex = 4 ==========

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
          dist  |  0  |  3  |  6  |  5  |  2  |
                +-----+-----+-----+-----+-----+

   vertexIndex     0     1     2     3     4
                +-----+-----+-----+-----+-----+
[u][vertexIndex]|  2  |  0  |  4  |  1  |  0  |
[4]     [4]     +-----+-----+-----+-----+-----+
                                           ^
                            [4][4] == 0, do nothing

 ********** pq is not empty **********

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
                |  3  |  3  |  5  |  6  |     |  (distance)
            pq  +--|--+--|--+--|--+--|--+--|--+
                |  1  |  3  |  3  |  4  |     |  (index)
                +-----+-----+-----+-----+-----+

                +-----+
                |  3  |
                +-----+
                   u

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
                |  3  |  5  |  6  |     |     |  (distance)
            pq  +--|--+--|--+--|--+--|--+--|--+
                |  3  |  3  |  4  |     |     |  (index)
                +-----+-----+-----+-----+-----+

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
       visited  |  t  |  f  |  f  |  t  |  t  |
                +-----+-----+-----+-----+-----+
                                     ^
                set visited index u to be true

      | a b c d e
    --+----------
    a | 0 3 0 5 2
    b | 3 0 6 0 0
    c | 0 6 0 0 4
    d | 5 0 0 0 1  <-- this line
    e | 2 0 4 1 0

   ========== vertexIndex = 0 ==========

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
          dist  |  0  |  3  |  6  |  5  |  2  |
                +-----+-----+-----+-----+-----+

   vertexIndex     0     1     2     3     4
                +-----+-----+-----+-----+-----+
[u][vertexIndex]|  5  |  0  |  0  |  0  |  1  |
[3]     [0]     +-----+-----+-----+-----+-----+
                   ^

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
       visited  |  t  |  f  |  f  |  t  |  t  |
                +-----+-----+-----+-----+-----+
                   ^
                we visited before!

   ========== vertexIndex = 1 ==========

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
          dist  |  0  |  3  |  6  |  5  |  2  |
                +-----+-----+-----+-----+-----+

   vertexIndex     0     1     2     3     4
                +-----+-----+-----+-----+-----+
[u][vertexIndex]|  5  |  0  |  0  |  0  |  1  |
[3]     [1]     +-----+-----+-----+-----+-----+
                         ^
                    [3][1] == 0, do nothing

   ========== vertexIndex = 2 ==========

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
          dist  |  0  |  3  |  6  |  5  |  2  |
                +-----+-----+-----+-----+-----+

   vertexIndex     0     1     2     3     4
                +-----+-----+-----+-----+-----+
[u][vertexIndex]|  5  |  0  |  0  |  0  |  1  |
[3]     [2]     +-----+-----+-----+-----+-----+
                               ^
                      [3][2] == 0, do nothing

   ========== vertexIndex = 3 ==========

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
          dist  |  0  |  3  |  6  |  5  |  2  |
                +-----+-----+-----+-----+-----+

   vertexIndex     0     1     2     3     4
                +-----+-----+-----+-----+-----+
[u][vertexIndex]|  5  |  0  |  0  |  0  |  1  |
[3]     [3]     +-----+-----+-----+-----+-----+
                                     ^
                        [3][3] == 0, do nothing

   ========== vertexIndex = 4 ==========

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
          dist  |  0  |  3  |  6  |  5  |  2  |
                +-----+-----+-----+-----+-----+

   vertexIndex     0     1     2     3     4
                +-----+-----+-----+-----+-----+
[u][vertexIndex]|  5  |  0  |  0  |  0  |  1  |
[3]     [4]     +-----+-----+-----+-----+-----+
                                           ^

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
       visited  |  t  |  f  |  f  |  t  |  t  |
                +-----+-----+-----+-----+-----+
                                           ^
                             we visited before!

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
                |  3  |  5  |  6  |     |     |  (distance)
            pq  +--|--+--|--+--|--+--|--+--|--+
                |  3  |  3  |  4  |     |     |  (index)
                +-----+-----+-----+-----+-----+

 ********** pq is not empty **********

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
                |  3  |  5  |  6  |     |     |  (distance)
            pq  +--|--+--|--+--|--+--|--+--|--+
                |  3  |  3  |  4  |     |     |  (index)
                +-----+-----+-----+-----+-----+

                +-----+
                |  3  |
                +-----+
                   u

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
                |  5  |  6  |     |     |     |  (distance)
            pq  +--|--+--|--+--|--+--|--+--|--+
                |  3  |  4  |     |     |     |  (index)
                +-----+-----+-----+-----+-----+

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
       visited  |  t  |  f  |  f  |  t  |  t  |
                +-----+-----+-----+-----+-----+
                                     ^
                          we visited it before!

 ********** pq is not empty **********

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
                |  5  |  6  |     |     |     |  (distance)
            pq  +--|--+--|--+--|--+--|--+--|--+
                |  3  |  4  |     |     |     |  (index)
                +-----+-----+-----+-----+-----+

                +-----+
                |  3  |
                +-----+
                   u

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
                |  6  |     |     |     |     |  (distance)
            pq  +--|--+--|--+--|--+--|--+--|--+
                |  4  |     |     |     |     |  (index)
                +-----+-----+-----+-----+-----+

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
       visited  |  t  |  f  |  f  |  t  |  t  |
                +-----+-----+-----+-----+-----+
                                     ^
                          we visited it before!

 ********** pq is not empty **********

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
                |  6  |     |     |     |     |  (distance)
            pq  +--|--+--|--+--|--+--|--+--|--+
                |  4  |     |     |     |     |  (index)
                +-----+-----+-----+-----+-----+

                +-----+
                |  4  |
                +-----+
                   u

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
                |     |     |     |     |     |  (distance)
            pq  +--|--+--|--+--|--+--|--+--|--+
                |     |     |     |     |     |  (index)
                +-----+-----+-----+-----+-----+

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
       visited  |  t  |  f  |  f  |  t  |  t  |
                +-----+-----+-----+-----+-----+
                                           ^
                          we visited it before!

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
                |     |     |     |     |     |  (distance)
            pq  +--|--+--|--+--|--+--|--+--|--+
                |     |     |     |     |     |  (index)
                +-----+-----+-----+-----+-----+
                // pq is empty!

************************************************************

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
          dist  |  0  |  3  |  6  |  5  |  2  |
                +-----+-----+-----+-----+-----+

Output:
The shortest path from vertex a:
 * To vertex a: 0
 * To vertex b: 3
 * To vertex c: 6
 * To vertex d: 3
 * To vertex e: 2

*/