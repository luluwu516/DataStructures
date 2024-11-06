#include <stack>

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

void GraphAdjacencyMatrix::DFS(const std::string& startLabel) {
  int startIndex = findVertexIndex(startLabel);
  if (startIndex == -1) {
    cout << "Starting vertex not found!\n";
    return;
  }

  // keep track of visited vertices
  std::vector<std::string> visited;
  std::stack<std::string> stack;

  // start DFS from the given vertex
  stack.push(startLabel);

  cout << "DFS starting from " << startLabel << ": ";

  while (!stack.empty()) {
    // get the next vertex to process
    std::string currLabel = stack.top();
    stack.pop();

    // if we haven't visited this vertex yet
    if (std::find(visited.begin(), visited.end(), currLabel) == visited.end()) {
      cout << currLabel << " ";
      visited.push_back(currLabel);

      // find the index of current vertex
      int currIndex = findVertexIndex(currLabel);

      // add all unvisited adjacent vertices to stack
      // reverse order for correct DFS ordering
      for (int i = numVertices - 1; i >= 0; i--) {
        if (adjacencyMatrix[currIndex][i] &&
            std::find(visited.begin(), visited.end(), vertexLabels[i]) ==
                visited.end()) {
          stack.push(vertexLabels[i]);
        }
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

Enter starting vertex for DFS: a

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
  stack    |  a  |
           +-----+
           +-----+
  visited  (empty)
           +-----+

 start dfs...
 ********** stack is not empty **********
  +-----+
  |  a  |
  +-----+
 currLabel

           +-----+
  stack    (empty)
           +-----+
           +-----+
  visited  |  a  |
           +-----+

  +-----+
  |  0  |
  +-----+
 currIndex

           +-----+
 tempStack (empty)
           +-----+

 adjacencyMatrix:
    | a b c d e
  --+----------
  a | 0 1 0 1 1  <-- this line
  b | 1 0 1 0 0
  c | 0 1 0 0 1
  d | 1 0 0 0 0
  e | 1 0 1 0 0

           +-----+
  visited  |  a  |
           +-----+
           +-----+-----+-----+
 tempStack |  b  |  d  |  e  |
           +-----+-----+-----+
           +-----+-----+-----+
  stack    |  e  |  d  |  b  |
           +-----+-----+-----+

 ********** stack is not empty **********
  +-----+
  |  b  |
  +-----+
 currLabel

           +-----+-----+
  stack    |  e  |  d  |
           +-----+-----+
           +-----+-----+
  visited  |  a  |  b  |
           +-----+-----+

  +-----+
  |  1  |
  +-----+
 currIndex

           +-----+
 tempStack (empty)
           +-----+

 adjacencyMatrix:
    | a b c d e
  --+----------
  a | 0 1 0 1 1
  b | 1 0 1 0 0  <-- this line
  c | 0 1 0 0 1
  d | 1 0 0 0 0
  e | 1 0 1 0 0

           +-----+-----+
  visited  |  a  |  b  |
           +-----+-----+
           +-----+
 tempStack |  c  |
           +-----+
           +-----+-----+-----+
  stack    |  e  |  d  |  c  |
           +-----+-----+-----+

 ********** stack is not empty **********
  +-----+
  |  c  |
  +-----+
 currLabel

           +-----+-----+
  stack    |  e  |  d  |
           +-----+-----+
           +-----+-----+-----+
  visited  |  a  |  b  |  c  |
           +-----+-----+-----+

  +-----+
  |  2  |
  +-----+
 currIndex

           +-----+
 tempStack (empty)
           +-----+

 adjacencyMatrix:
    | a b c d e
  --+----------
  a | 0 1 0 1 1
  b | 1 0 1 0 0
  c | 0 1 0 0 1  <-- this line
  d | 1 0 0 0 0
  e | 1 0 1 0 0

           +-----+-----+-----+
  visited  |  a  |  b  |  c  |
           +-----+-----+-----+
           +-----+
 tempStack |  e  |
           +-----+
           +-----+-----+-----+
  stack    |  e  |  d  |  e  |
           +-----+-----+-----+

 ********** stack is not empty **********
  +-----+
  |  e  |
  +-----+
 currLabel

           +-----+-----+
  stack    |  e  |  d  |
           +-----+-----+
           +-----+-----+-----+-----+
  visited  |  a  |  b  |  c  |  e  |
           +-----+-----+-----+-----+

  +-----+
  |  4  |
  +-----+
 currIndex

           +-----+
 tempStack (empty)
           +-----+

 adjacencyMatrix:
    | a b c d e
  --+----------
  a | 0 1 0 1 1
  b | 1 0 1 0 0
  c | 0 1 0 0 1
  d | 1 0 0 0 0
  e | 1 0 1 0 0  <-- this line

           +-----+-----+-----+-----+
  visited  |  a  |  b  |  c  |  e  |
           +-----+-----+-----+-----+
           +-----+
 tempStack (empty)
           +-----+
           +-----+-----+
  stack    |  e  |  d  |
           +-----+-----+

 ********** stack is not empty **********
  +-----+
  |  d  |
  +-----+
 currLabel

           +-----+
  stack    |  e  |
           +-----+
           +-----+-----+-----+-----+-----+
  visited  |  a  |  b  |  c  |  e  |  d  |
           +-----+-----+-----+-----+-----+

  +-----+
  |  3  |
  +-----+
 currIndex

           +-----+
 tempStack (empty)
           +-----+

 adjacencyMatrix:
    | a b c d e
  --+----------
  a | 0 1 0 1 1
  b | 1 0 1 0 0
  c | 0 1 0 0 1
  d | 1 0 0 0 0  <-- this line
  e | 1 0 1 0 0

           +-----+-----+-----+-----+-----+
  visited  |  a  |  b  |  c  |  e  |  d  |
           +-----+-----+-----+-----+-----+
           +-----+
 tempStack (empty)
           +-----+
           +-----+
  stack    |  e  |
           +-----+

 ********** stack is not empty **********
  +-----+
  |  e  |
  +-----+
 currLabel

           +-----+
  stack    (empty)
           +-----+
           +-----+-----+-----+-----+-----+
  visited  |  a  |  b  |  c  |  e  |  d  |
           +-----+-----+-----+-----+-----+

  +-----+
  |  4  |
  +-----+
 currIndex

           +-----+
 tempStack (empty)
           +-----+

 adjacencyMatrix:
    | a b c d e
  --+----------
  a | 0 1 0 1 1
  b | 1 0 1 0 0
  c | 0 1 0 0 1
  d | 1 0 0 0 0
  e | 1 0 1 0 0  <-- this line

           +-----+-----+-----+-----+-----+
  visited  |  a  |  b  |  c  |  e  |  d  |
           +-----+-----+-----+-----+-----+
           +-----+
 tempStack (empty)
           +-----+
           +-----+
  stack    (empty)
           +-----+

 // stack is empty!

Output:
DFS starting from a: a b c e d

*/