#include <stack>

#include "GraphAdjacencyList.hpp"

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

void GraphAdjacencyList::DFS(const std::string& startLabel) {
  int startIndex = findVertexIndex(startLabel);
  if (startIndex == -1) {
    cout << "Starting vertex not found!\n";
    return;
  }

  // Keep track of visited vertices
  std::vector<std::string> visited;
  std::stack<std::string> stack;

  // Start DFS from the given vertex
  stack.push(startLabel);

  cout << "DFS starting from " << startLabel << ": ";

  while (!stack.empty()) {
    // Get the next vertex to process
    std::string currentLabel = stack.top();
    stack.pop();

    // If we haven't visited this vertex yet
    if (std::find(visited.begin(), visited.end(), currentLabel) ==
        visited.end()) {
      cout << currentLabel << " ";
      visited.push_back(currentLabel);

      // Find the index of current vertex
      int currentIndex = findVertexIndex(currentLabel);

      // Add all unvisited adjacent vertices to stack
      // We use a temporary stack to reverse the order
      // so we visit vertices in alphabetical order
      std::stack<std::string> tempStack;
      Node* curr = adjacencyList[currentIndex]->next;
      while (curr) {
        if (std::find(visited.begin(), visited.end(), curr->label) ==
            visited.end()) {
          tempStack.push(curr->label);
        }
        curr = curr->next;
      }

      // Transfer from temporary stack to main stack
      while (!tempStack.empty()) {
        stack.push(tempStack.top());
        tempStack.pop();
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

   +=====+  +-----+  +-----+  +-----+
   |  a  |--|  b  |--|  d  |--|  e  |
   +=====+  +-----+  +-----+  +-----+

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

   +=====+  +-----+  +-----+
   |  b  |--|  a  |--|  c  |
   +=====+  +-----+  +-----+

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

   +=====+  +-----+  +-----+
   |  c  |--|  b  |--|  e  |
   +=====+  +-----+  +-----+

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

   +=====+  +-----+  +-----+
   |  e  |--|  a  |--|  c  |
   +=====+  +-----+  +-----+

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

   +=====+  +-----+
   |  d  |--|  a  |
   +=====+  +-----+

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

   +=====+  +-----+  +-----+
   |  e  |--|  a  |--|  c  |
   +=====+  +-----+  +-----+

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