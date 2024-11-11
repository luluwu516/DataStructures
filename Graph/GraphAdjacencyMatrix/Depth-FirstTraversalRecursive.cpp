#include "GraphAdjacencyMatrix.hpp"

/*

Depth First Search is a graph/tree traversal algorithm that explores as far as
possible along each branch before backtracking. Think of it like exploring a
maze by following each path to its end before going back to try other paths.

 Characteristics:
 * Uses a Stack (LIFO) or Recursion
 * Explores deep into the graph before exploring neighbors
 * Backtracking occurs when no unvisited adjacent vertices exist
 * Memory efficient for deep graphs
 * Can get stuck in infinite paths if not implemented carefully

 Time Complexity: O(V + E)
 - V: number of vertices
 - E: number of edges
 - Must visit every vertex once: O(V)
 - Must explore every edge once: O(E)

 Space Complexity: O(V)
 - In worst case, stack might contain all vertices
 - Better than BFS for deep graphs
 - Recursive call stack can be deep

 Pros:
 * Uses less memory than BFS
 * Solution found faster than BFS if solution is deep in the tree
 * Naturally suited for problems requiring backtracking
 * Good for:
   * Topological sorting
   * Finding connected components
   * Solving puzzles with only one solution
   * Path finding in a maze

 Cons:
 * May not find shortest path
 * Can get stuck in infinite loops (need cycle detection)
 * Not guaranteed to find solution closest to start
 * Not suitable for shortest path problems
 * Can be inefficient for shallow, wide trees

*/

void GraphAdjacencyMatrix::DFSrecursive(const std::string& startLabel) {
  int startIndex = findVertexIndex(startLabel);
  if (startIndex == -1) {
    cout << "Error!! Vertex not found!\n";
    return;
  }

  std::vector<bool> visited(numVertices, false);

  cout << "DFS starting from " << startLabel << ": ";
  DFSRec(visited, startIndex);
  cout << "\n";
}

void GraphAdjacencyMatrix::DFSRec(std::vector<bool>& visited, int index) {
  visited[index] = true;

  // print the current vertex
  cout << vertexLabels[index] << " ";

  // recursively visit all adjacent vertices that are not visited yet
  for (int i = 0; i < numVertices; i++) {
    if (adjacencyMatrix[index][i] && !visited[i]) {
      DFSRec(visited, i);
    }
  }
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

Enter starting vertex for DFS: a

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
  vertexLabels  |  a  |  b  |  c  |  d  |  e  |
                +-----+-----+-----+-----+-----+
                   ^

                +-----+
                |  0  |
                +-----+
              startIndex

create a vector
                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
       visited  |  f  |  f  |  f  |  f  |  f  |
                +-----+-----+-----+-----+-----+

Starting reursion:
Pass the startIndex, 0
 +-----+
 |  0  |
 +-----+
  index
                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
       visited  |  t  |  f  |  f  |  f  |  f  |
                +-----+-----+-----+-----+-----+

   | a b c d e
 --+----------
 a | 0 1 0 1 1 <-- this line
 b | 1 0 1 0 0
 c | 0 1 0 0 1
 d | 1 0 0 0 0
 e | 1 0 1 0 0

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
       visited  |  t  |  f  |  f  |  f  |  f  |
                +-----+-----+-----+-----+-----+
                         ^

 Pass index 1
 +-----+
 |  1  |
 +-----+
  index
                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
       visited  |  t  |  t  |  f  |  f  |  f  |
                +-----+-----+-----+-----+-----+

   | a b c d e
 --+----------
 a | 0 1 0 1 1
 b | 1 0 1 0 0 <-- this line
 c | 0 1 0 0 1
 d | 1 0 0 0 0
 e | 1 0 1 0 0

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
       visited  |  t  |  t  |  f  |  f  |  f  |
                +-----+-----+-----+-----+-----+
                               ^

 Pass index 2
 +-----+
 |  2  |
 +-----+
  index
                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
       visited  |  t  |  t  |  t  |  f  |  f  |
                +-----+-----+-----+-----+-----+

   | a b c d e
 --+----------
 a | 0 1 0 1 1
 b | 1 0 1 0 0
 c | 0 1 0 0 1 <-- this line
 d | 1 0 0 0 0
 e | 1 0 1 0 0

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
       visited  |  t  |  t  |  t  |  f  |  f  |
                +-----+-----+-----+-----+-----+
                                           ^

 Pass index 4
 +-----+
 |  4  |
 +-----+
  index
                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
       visited  |  t  |  t  |  t  |  f  |  t  |
                +-----+-----+-----+-----+-----+

   | a b c d e
 --+----------
 a | 0 1 0 1 1
 b | 1 0 1 0 0
 c | 0 1 0 0 1
 d | 1 0 0 0 0
 e | 1 0 1 0 0 <-- this line

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
       visited  |  t  |  t  |  t  |  f  |  t  |
                +-----+-----+-----+-----+-----+
                   ^           ^
 Index 0 and 2 are visited, so let's go back to index 2

 +-----+
 |  2  |
 +-----+
  index
                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
       visited  |  t  |  t  |  t  |  f  |  t  |
                +-----+-----+-----+-----+-----+

   | a b c d e
 --+----------
 a | 0 1 0 1 1
 b | 1 0 1 0 0
 c | 0 1 0 0 1 <-- this line
 d | 1 0 0 0 0
 e | 1 0 1 0 0

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
       visited  |  t  |  t  |  t  |  f  |  t  |
                +-----+-----+-----+-----+-----+
                         ^                 ^

 We finished the index 2, so let's go back to index 1
 +-----+
 |  1  |
 +-----+
  index
                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
       visited  |  t  |  t  |  t  |  f  |  t  |
                +-----+-----+-----+-----+-----+

   | a b c d e
 --+----------
 a | 0 1 0 1 1
 b | 1 0 1 0 0 <-- this line
 c | 0 1 0 0 1
 d | 1 0 0 0 0
 e | 1 0 1 0 0

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
       visited  |  t  |  t  |  t  |  f  |  t  |
                +-----+-----+-----+-----+-----+
                   ^           ^

 We finished the index 1, so let's go back to index 0
 +-----+
 |  0  |
 +-----+
  index
                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
       visited  |  t  |  t  |  t  |  f  |  t  |
                +-----+-----+-----+-----+-----+

   | a b c d e
 --+----------
 a | 0 1 0 1 1 <-- this line
 b | 1 0 1 0 0
 c | 0 1 0 0 1
 d | 1 0 0 0 0
 e | 1 0 1 0 0

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
       visited  |  t  |  t  |  t  |  f  |  t  |
                +-----+-----+-----+-----+-----+
                                     ^

 Pass index 3
 +-----+
 |  3  |
 +-----+
  index
                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
       visited  |  t  |  t  |  t  |  t  |  t  |
                +-----+-----+-----+-----+-----+

   | a b c d e
 --+----------
 a | 0 1 0 1 1
 b | 1 0 1 0 0
 c | 0 1 0 0 1
 d | 1 0 0 0 0 <-- this line
 e | 1 0 1 0 0

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
       visited  |  t  |  t  |  t  |  t  |  t  |
                +-----+-----+-----+-----+-----+
                   ^
 Index 0 is visited, so let's go back to index 0

 We finished the index 1, so let's go back to index 0
 +-----+
 |  0  |
 +-----+
  index
                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
       visited  |  t  |  t  |  t  |  t  |  t  |
                +-----+-----+-----+-----+-----+

   | a b c d e
 --+----------
 a | 0 1 0 1 1 <-- this line
 b | 1 0 1 0 0
 c | 0 1 0 0 1
 d | 1 0 0 0 0
 e | 1 0 1 0 0

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
       visited  |  t  |  t  |  t  |  t  |  t  |
                +-----+-----+-----+-----+-----+

 We finished the recursion!
 **************************************************

Output:
DFS starting from a: a b c e d

*/