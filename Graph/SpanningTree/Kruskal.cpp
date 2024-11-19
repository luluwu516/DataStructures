#include <algorithm>

#include "WeightedGraph.hpp"

/*

Kruskal's algorithm is a greedy algorithm that finds a minimum spanning tree
(MST) for a connected weighted undirected graph by selecting edges in ascending
order of weight.
It starts with a forest of single-vertex trees and iteratively adds the
lowest-weight edge that connects two different trees (avoiding cycles), until
all vertices are connected into a single tree. The algorithm uses a disjoint-set
data structure to efficiently track connected components and detect cycles,
achieving a time complexity of O(E log E) where E is the number of edges.
How it works:
1. Sort all edges in the graph in ascending order of weight
2. Create a DisjointSet data structure to track connected components
3. Take current edge with lowest weight and check if adding the edge created a
   cycle, then skip this edge and continue to next.
4. Continue step 3 until having (V-1) edges in our MST or we've examined all
   edges


 Characteristics
 * Greedy Algorithm: Selects the locally optimal choice at each step
 * Edge-Based: Processes edges in order of increasing weight
 * Uses Disjoint Sets: Implements Union-Find data structure to detect cycles
 * Global Optimality: Produces a globally optimal solution
 * Undirected Graph: Works on undirected, weighted graphs


 Time Complexity: O(E log E) or O(E log V)
 - Sorting edges: O(E log E)
 - Union-Find operations: O(E α(V)) where α is the inverse Ackermann function
 - Total dominated by the sorting step

 Space Complexity: O(V + E)
 - Disjoint-set data structure: O(V)
 - Edge list: O(E)
 - Output MST: O(V-1)


 Pros
 * Easy to implement and understand
 * Works well on sparse graphs
 * Produces optimal solution
 * Can be modified for parallel implementation
 * Good for graphs with sorted edges
 * Efficient when using optimized disjoint-set data structure

 Cons
 * Not as efficient for dense graphs compared to Prim's algorithm
 * Requires sorting all edges
 * Needs explicit edge representation
 * Additional memory for disjoint-set structure
 * Not suitable for directed graphs


 When to Use
 * Sparse graphs where |E| is much less than |V^2|
 * When edges are already sorted
 * When implementing in parallel environments
 * When simplicity of implementation is important
 * When working with undirected, weighted graphs

 When Not to Use
 * Dense graphs (Prim's algorithm might be better)
 * Directed graphs requiring minimum spanning arborescence
 * When memory is very constrained
 * When edges are constantly changing (dynamic graphs)
 * When needing to find MST from a specific starting vertex

*/

void WeightedGraph::kruskal() {
  if (numVertices < 2) {
    cout << "Insufficient vertices for MST\n";
    return;
  }

  // initialize disjoint set
  parent.resize(numVertices);
  rank.resize(numVertices, 0);
  for (int i = 0; i < numVertices; i++) {
    parent[i] = i;  // each vertex is initially its own parent
  }

  int totalWeight = 0;
  int edgesInMST = 0;

  // sort edges by weight
  std::sort(edges.begin(), edges.end());

  // check the lowest weight and add it to the spanning tree or skip it
  std::cout << "Minimum Spanning Tree (Kruskal's):\n";

  for (const auto& edge : edges) {
    int srcIndex = findVertexIndex(edge.src);
    int desIndex = findVertexIndex(edge.des);

    if (find(srcIndex) != find(desIndex)) {
      unite(srcIndex, desIndex);
      std::cout << " " << edge.src << "-" << edge.des << " " << edge.weight
                << "\n";
      totalWeight += edge.weight;
      edgesInMST++;
    }
  }

  // final check if we found a spanning tree or not
  if (edgesInMST != numVertices - 1) {
    cout << "Graph is not connected - no spanning tree exists\n";
    return;
  }

  cout << "\nTotal MST weight: " << totalWeight << "\n";
}

int WeightedGraph::find(int x) {
  if (parent[x] != x) {
    parent[x] = find(parent[x]);
  }
  return parent[x];
}

void WeightedGraph::unite(int x, int y) {
  x = find(x);  // 2
  y = find(y);  // 3
  if (x == y) {
    return;
  }
  if (rank[x] < rank[y]) {
    parent[x] = y;
  } else if (rank[x] > rank[y]) {
    parent[y] = x;
  } else {
    parent[y] = x;
    rank[x]++;
  }
}

/*

Current Graph:

 +-----+ 3 +-----+ 6 +-----+
 |  a  |---|  b  |---|  c  |
 +--+--+   +-----+   +-----+
    |   \           /
  5 |    \ 2     4 /
    |     \       /
 +--+--+ 1 +-----+
 |  d  |---|  e  |
 +-----+   +-----+

Vertices: a b c d e

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
  vertexLabels  |  a  |  b  |  c  |  d  |  e  |
                +-----+-----+-----+-----+-----+

Matrix:
   | a b c d e
---+----------
 a | 0 3 0 5 2
 b | 3 0 6 0 0
 c | 0 6 0 0 4
 d | 5 0 0 0 1
 e | 2 0 4 1 0

Edges:
 a-b 3
 a-d 5
 a-e 2
 b-c 6
 c-e 4
 d-e 1

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
        parent  |  0  |  1  |  2  |  3  |  4  |
                +-----+-----+-----+-----+-----+

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
          rank  |  0  |  0  |  0  |  0  |  0  |
                +-----+-----+-----+-----+-----+

                +-----+
   totalWeight  |  0  |
                +-----+

                +-----+
    edgesInMST  |  0  |
                +-----+

 Sort the edges...

                   0     1     2     3     4     5
                +-----+-----+-----+-----+-----+-----+
                | d-e | a-e | a-b | c-e | a-d | b-c |
         edges  +--|--+--|--+--|--+--|--+--|--+-----+
                |  1  |  2  |  3  |  4  |  5  |  6  |
                +-----+-----+-----+-----+-----+-----+

 +-----+   +-----+   +-----+
 |  a  |   |  b  |   |  c  |
 +--+--+   +-----+   +-----+



 +--+--+   +-----+
 |  d  |   |  e  |
 +-----+   +-----+

============================================================

                   0     1     2     3     4     5
                +-----+-----+-----+-----+-----+-----+
                | d-e | a-e | a-b | c-e | a-d | b-c |
         edges  +--|--+--|--+--|--+--|--+--|--+-----+
                |  1  |  2  |  3  |  4  |  5  |  6  |
                +-----+-----+-----+-----+-----+-----+

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
  vertexLabels  |  a  |  b  |  c  |  d  |  e  |
                +-----+-----+-----+-----+-----+
                                     ^     ^
                +-----+   +-----+
                |  3  |   |  4  |
                +-----+   +-----+
                srcIndex  desIndex

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
        parent  |  0  |  1  |  2  |  3  |  4  |
                +-----+-----+-----+-----+-----+
                                     ^     ^

 Update parent[4] = 3

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
        parent  |  0  |  1  |  2  |  3  |  3  |
                +-----+-----+-----+-----+-----+
                                     ^     ^

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
          rank  |  0  |  0  |  0  |  1  |  0  |
                +-----+-----+-----+-----+-----+

                   0     1     2     3     4     5
                +-----+-----+-----+-----+-----+-----+
                | d-e | a-e | a-b | c-e | a-d | b-c |
         edges  +--|--+--|--+--|--+--|--+--|--+-----+
                |  1  |  2  |  3  |  4  |  5  |  6  |
                +-----+-----+-----+-----+-----+-----+
                   ^

                +-----+   +-----+
                |  1  |   |  1  |
                +-----+   +-----+
             totalWeight  edgesInMST

 +-----+   +-----+   +-----+
 |  a  |   |  b  |   |  c  |
 +--+--+   +-----+   +-----+



 +--+--+ 1 +-----+
 |  d  |---|  e  |
 +-----+   +-----+

 **************************************************

                   0     1     2     3     4     5
                +-----+-----+-----+-----+-----+-----+
                | d-e | a-e | a-b | c-e | a-d | b-c |
         edges  +--|--+--|--+--|--+--|--+--|--+-----+
                |  1  |  2  |  3  |  4  |  5  |  6  |
                +-----+-----+-----+-----+-----+-----+
                         ^

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
  vertexLabels  |  a  |  b  |  c  |  d  |  e  |
                +-----+-----+-----+-----+-----+
                   ^                       ^
                +-----+   +-----+
                |  0  |   |  4  |
                +-----+   +-----+
                srcIndex  desIndex

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
        parent  |  0  |  1  |  2  |  3  |  3  |
                +-----+-----+-----+-----+-----+
                   ^                       ^

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
          rank  |  0  |  0  |  0  |  1  |  0  |
                +-----+-----+-----+-----+-----+
                   ^                 ^
                   x                 y

 Update parent[0] = 3

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
        parent  |  3  |  1  |  2  |  3  |  3  |
                +-----+-----+-----+-----+-----+
                                     ^     ^

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
          rank  |  0  |  0  |  0  |  1  |  0  |
                +-----+-----+-----+-----+-----+

                   0     1     2     3     4     5
                +-----+-----+-----+-----+-----+-----+
                | d-e | a-e | a-b | c-e | a-d | b-c |
         edges  +--|--+--|--+--|--+--|--+--|--+-----+
                |  1  |  2  |  3  |  4  |  5  |  6  |
                +-----+-----+-----+-----+-----+-----+
                         ^

                +-----+   +-----+
                |  3  |   |  2  |
                +-----+   +-----+
             totalWeight  edgesInMST

 +-----+   +-----+   +-----+
 |  a  |   |  b  |   |  c  |
 +--+--+   +-----+   +-----+
        \
         \ 2
          \
 +--+--+ 1 +-----+
 |  d  |---|  e  |
 +-----+   +-----+

 **************************************************

                   0     1     2     3     4     5
                +-----+-----+-----+-----+-----+-----+
                | d-e | a-e | a-b | c-e | a-d | b-c |
         edges  +--|--+--|--+--|--+--|--+--|--+-----+
                |  1  |  2  |  3  |  4  |  5  |  6  |
                +-----+-----+-----+-----+-----+-----+
                               ^

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
  vertexLabels  |  a  |  b  |  c  |  d  |  e  |
                +-----+-----+-----+-----+-----+
                   ^     ^
                +-----+   +-----+
                |  0  |   |  1  |
                +-----+   +-----+
                srcIndex  desIndex

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
        parent  |  3  |  1  |  2  |  3  |  3  |
                +-----+-----+-----+-----+-----+
                   ^     ^
                   x     y

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
          rank  |  0  |  0  |  0  |  1  |  0  |
                +-----+-----+-----+-----+-----+
                         ^           ^
                         y           x

 Update parent[1] = 3

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
        parent  |  3  |  3  |  2  |  3  |  3  |
                +-----+-----+-----+-----+-----+
                         ^           ^

                   0     1     2     3     4     5
                +-----+-----+-----+-----+-----+-----+
                | d-e | a-e | a-b | c-e | a-d | b-c |
         edges  +--|--+--|--+--|--+--|--+--|--+-----+
                |  1  |  2  |  3  |  4  |  5  |  6  |
                +-----+-----+-----+-----+-----+-----+
                               ^

                +-----+   +-----+
                |  6  |   |  3  |
                +-----+   +-----+
             totalWeight  edgesInMST

 +-----+ 3 +-----+   +-----+
 |  a  |---|  b  |   |  c  |
 +--+--+   +-----+   +-----+
        \
         \ 2
          \
 +--+--+ 1 +-----+
 |  d  |---|  e  |
 +-----+   +-----+

 **************************************************

                   0     1     2     3     4     5
                +-----+-----+-----+-----+-----+-----+
                | d-e | a-e | a-b | c-e | a-d | b-c |
         edges  +--|--+--|--+--|--+--|--+--|--+-----+
                |  1  |  2  |  3  |  4  |  5  |  6  |
                +-----+-----+-----+-----+-----+-----+
                                     ^

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
  vertexLabels  |  a  |  b  |  c  |  d  |  e  |
                +-----+-----+-----+-----+-----+
                               ^           ^
                +-----+   +-----+
                |  2  |   |  4  |
                +-----+   +-----+
                srcIndex  desIndex

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
        parent  |  3  |  3  |  2  |  3  |  3  |
                +-----+-----+-----+-----+-----+
                               ^           ^
                               x           y

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
          rank  |  0  |  0  |  0  |  1  |  0  |
                +-----+-----+-----+-----+-----+
                               ^     ^
                               x     y

 Update parent[2] = 3

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
        parent  |  3  |  3  |  3  |  3  |  3  |
                +-----+-----+-----+-----+-----+
                               ^           ^

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
          rank  |  0  |  0  |  0  |  1  |  0  |
                +-----+-----+-----+-----+-----+

                   0     1     2     3     4     5
                +-----+-----+-----+-----+-----+-----+
                | d-e | a-e | a-b | c-e | a-d | b-c |
         edges  +--|--+--|--+--|--+--|--+--|--+-----+
                |  1  |  2  |  3  |  4  |  5  |  6  |
                +-----+-----+-----+-----+-----+-----+
                                     ^

                +------+   +-----+
                |  10  |   |  4  |
                +------+   +-----+
             totalWeight  edgesInMST

 +-----+ 3 +-----+   +-----+
 |  a  |---|  b  |   |  c  |
 +--+--+   +-----+   +-----+
        \           /
         \ 2     4 /
          \       /
 +--+--+ 1 +-----+
 |  d  |---|  e  |
 +-----+   +-----+

**************************************************

                   0     1     2     3     4     5
                +-----+-----+-----+-----+-----+-----+
                | d-e | a-e | a-b | c-e | a-d | b-c |
         edges  +--|--+--|--+--|--+--|--+--|--+-----+
                |  1  |  2  |  3  |  4  |  5  |  6  |
                +-----+-----+-----+-----+-----+-----+
                                           ^

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
  vertexLabels  |  a  |  b  |  c  |  d  |  e  |
                +-----+-----+-----+-----+-----+
                   ^                 ^
                +-----+   +-----+
                |  0  |   |  3  |
                +-----+   +-----+
                srcIndex  desIndex

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
        parent  |  3  |  3  |  3  |  3  |  3  |
                +-----+-----+-----+-----+-----+
                   ^                 ^
                   x                 y

**************************************************

                   0     1     2     3     4     5
                +-----+-----+-----+-----+-----+-----+
                | d-e | a-e | a-b | c-e | a-d | b-c |
         edges  +--|--+--|--+--|--+--|--+--|--+-----+
                |  1  |  2  |  3  |  4  |  5  |  6  |
                +-----+-----+-----+-----+-----+-----+
                                                 ^

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
  vertexLabels  |  a  |  b  |  c  |  d  |  e  |
                +-----+-----+-----+-----+-----+
                         ^     ^
                +-----+   +-----+
                |  1  |   |  2  |
                +-----+   +-----+
                srcIndex  desIndex

                   0     1     2     3     4
                +-----+-----+-----+-----+-----+
        parent  |  3  |  3  |  3  |  3  |  3  |
                +-----+-----+-----+-----+-----+
                         ^     ^
                         x     y

============================================================

                +------+   +-----+
                |  10  |   |  4  |
                +------+   +-----+
             totalWeight  edgesInMST

Output:
Minimum Spanning Tree (Kruskal's):

 +-----+ 3 +-----+   +-----+
 |  a  |---|  b  |   |  c  |
 +--+--+   +-----+   +-----+
        \           /
         \ 2     4 /
          \       /
 +--+--+ 1 +-----+
 |  d  |---|  e  |
 +-----+   +-----+

 d-e 1
 a-e 2
 a-b 3
 c-e 4

Total MST weight: 10

*/