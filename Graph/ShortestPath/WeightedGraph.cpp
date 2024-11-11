#include "WeightedGraph.hpp"

#include <iomanip>

#include "Dijkstra.cpp"
#include "Floyd-Warshall.cpp"

// constructor
WeightedGraph::WeightedGraph(int size) : numVertices(0) {
  adjacencyMatrix.resize(size);
  for (int i = 0; i < size; i++) {
    adjacencyMatrix[i].resize(size, 0);
  }
  vertexLabels.resize(size);
}

bool WeightedGraph::addVertex(const std::string& label) {
  // vertex already exists
  if (searchVertex(label)) {
    return false;
  }

  // if number of vertices is less than the size
  if (numVertices < vertexLabels.size()) {
    vertexLabels[numVertices] = label;
  } else {
    vertexLabels.push_back(label);
    adjacencyMatrix.resize(numVertices + 1);
    for (int i = 0; i < numVertices + 1; i++) {
      adjacencyMatrix[i].resize(numVertices + 1, 0);
    }
  }

  numVertices++;
  return true;
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

Vertices: a b c d e

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

Adding vertex:

 +-----+ 3 +-----+ 6 +-----+
 |  a  |---|  b  |---|  c  |
 +--+--+   +-----+   +-----+
    |   \           /
  5 |    \ 2     4 /
    |     \       /
 +--+--+ 1 +-----+   +-----+
 |  d  |---|  e  |   |  f  |
 +-----+   +-----+   +-----+

Vertices: a b c d e f

                +-----+-----+-----+-----+-----+-----+
  vertexLabels  |  a  |  b  |  c  |  d  |  e  |  f  |
                +-----+-----+-----+-----+-----+-----+

Matrix:
   | a b c d e f
---+------------
 a | 0 3 0 5 2 0
 b | 3 0 6 0 0 0
 c | 0 6 0 0 4 0
 d | 5 0 0 0 1 0
 e | 2 0 4 1 0 0
 f | 0 0 0 0 0 0

*/

bool WeightedGraph::addEdge(const std::string& src, const std::string& des,
                            int weight) {
  if (weight <= 0) {
    return false;
  }

  int srcIndex = findVertexIndex(src);
  int desIndex = findVertexIndex(des);

  // one or both vertices not found
  if (srcIndex == -1 || desIndex == -1) {
    return false;
  }

  // edge already exists
  if (searchEdge(src, des)) {
    return false;
  }

  adjacencyMatrix[srcIndex][desIndex] = weight;
  adjacencyMatrix[desIndex][srcIndex] = weight;

  // verify symmetry after modification
  verifyMatrixSymmetry();

  return true;
}
/*

 +-----+ 3 +-----+ 6 +-----+
 |  a  |---|  b  |---|  c  |
 +--+--+   +-----+   +-----+
    |   \           /
  5 |    \ 2     4 /
    |     \       /
 +--+--+ 1 +-----+   +-----+
 |  d  |---|  e  |   |  f  |
 +-----+   +-----+   +-----+

Matrix:
   | a b c d e f
---+------------
 a | 0 3 0 5 2 0
 b | 3 0 6 0 0 0
 c | 0 6 0 0 4 0
 d | 5 0 0 0 1 0
 e | 2 0 4 1 0 0
 f | 0 0 0 0 0 0

Adding edge ef with weight 7:

 +-----+ 3 +-----+ 6 +-----+
 |  a  |---|  b  |---|  c  |
 +--+--+   +-----+   +-----+
    |   \           /
  5 |    \ 2     4 /
    |     \       /
 +--+--+ 1 +-----+ 7 +-----+
 |  d  |---|  e  |---|  f  |
 +-----+   +-----+   +-----+

Matrix:
   | a b c d e f
---+------------
 a | 0 3 0 5 2 0
 b | 3 0 6 0 0 0
 c | 0 6 0 0 4 0
 d | 5 0 0 0 1 0
 e | 2 0 4 1 0 7
 f | 0 0 0 0 7 0

*/

bool WeightedGraph::searchVertex(const std::string& label) const {
  for (int i = 0; i < numVertices; i++) {
    if (vertexLabels[i] == label) {
      return true;
    }
  }
  return false;
}
/*

Searching vertex f:

Vertices: a b c d e f

                +-----+-----+-----+-----+-----+-----+
  vertexLabels  |  a  |  b  |  c  |  d  |  e  |  f  |
                +-----+-----+-----+-----+-----+-----+
                                                 ^
                                               found!

*/

bool WeightedGraph::searchEdge(const std::string& src,
                               const std::string& des) const {
  int srcIndex = findVertexIndex(src);
  int desIndex = findVertexIndex(des);

  // one or both vertices not found
  if (srcIndex == -1 || desIndex == -1) {
    return false;
  }

  return adjacencyMatrix[srcIndex][desIndex] != 0;
}
/*

Searching edge ef:

 +-----+ 3 +-----+ 6 +-----+
 |  a  |---|  b  |---|  c  |
 +--+--+   +-----+   +-----+
    |   \           /
  5 |    \ 2     4 /
    |     \       /
 +--+--+ 1 +-----+ 7 +-----+
 |  d  |---|  e  |---|  f  |
 +-----+   +-----+   +-----+

Matrix:
   | a b c d e  f
---+--------------
 a | 0 3 0 5 2  0
 b | 3 0 6 0 0  0
 c | 0 6 0 0 4  0
 d | 5 0 0 0 1  0
 e | 2 0 4 1 0 '7'  <-- found!
 f | 0 0 0 0 7  0

*/

bool WeightedGraph::removeVertex(const std::string& labelToRemove) {
  int index = findVertexIndex(labelToRemove);
  if (index == -1) {
    return false;
  }

  std::vector<std::vector<int>> tempMatrix;
  std::vector<std::string> tempLabels;

  for (int i = 0; i < numVertices; i++) {
    if (i == index) {
      continue;
    }
    std::vector<int> tempRow;
    for (int j = 0; j < numVertices; j++) {
      if (j == index) {
        continue;
      }
      tempRow.push_back(adjacencyMatrix[i][j]);
    }

    tempMatrix.push_back(tempRow);
    tempLabels.push_back(vertexLabels[i]);
  }

  adjacencyMatrix = tempMatrix;
  vertexLabels = tempLabels;
  numVertices--;

  return true;
}
/*

 +-----+ 3 +-----+ 6 +-----+
 |  a  |---|  b  |---|  c  |
 +--+--+   +-----+   +-----+
    |   \           /
  5 |    \ 2     4 /
    |     \       /
 +--+--+ 1 +-----+ 7 +-----+
 |  d  |---|  e  |---|  f  |
 +-----+   +-----+   +-----+

Matrix:
   | a b c d e f
---+------------
 a | 0 3 0 5 2 0
 b | 3 0 6 0 0 0
 c | 0 6 0 0 4 0
 d | 5 0 0 0 1 0
 e | 2 0 4 1 0 7
 f | 0 0 0 0 7 0

Removing vertex f:

 +-----+ 3 +-----+ 6 +-----+
 |  a  |---|  b  |---|  c  |
 +--+--+   +-----+   +-----+
    |   \           /
  5 |    \ 2     4 /
    |     \       /
 +--+--+ 1 +-----+
 |  d  |---|  e  |
 +-----+   +-----+

Matrix:
   | a b c d e
---+----------
 a | 0 3 0 5 2
 b | 3 0 6 0 0
 c | 0 6 0 0 4
 d | 5 0 0 0 1
 e | 2 0 4 1 0

*/

bool WeightedGraph::removeEdge(const std::string& src, const std::string& des) {
  int srcIndex = findVertexIndex(src);
  int desIndex = findVertexIndex(des);

  // one or both vertices not found
  if (srcIndex == -1 || desIndex == -1) {
    return false;
  }
  // edge doesn't exist
  if (!searchEdge(src, des)) {
    return false;
  }

  adjacencyMatrix[srcIndex][desIndex] = 0;
  adjacencyMatrix[desIndex][srcIndex] = 0;

  // verify symmetry after modification
  verifyMatrixSymmetry();

  return true;
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

Matrix:
   | a b c d e
---+----------
 a | 0 3 0 5 2
 b | 3 0 6 0 0
 c | 0 6 0 0 4
 d | 5 0 0 0 1
 e | 2 0 4 1 0

Removing edge bc:

 +-----+ 3 +-----+   +-----+
 |  a  |---|  b  |   |  c  |
 +--+--+   +-----+   +-----+
    |   \           /
  5 |    \ 2     4 /
    |     \       /
 +--+--+ 1 +-----+
 |  d  |---|  e  |
 +-----+   +-----+

Matrix:
   | a  b  c  d e
---+-------------
 a | 0  3  0  5 2
 b | 3  0 '0' 0 0
 c | 0 '0' 0  0 4
 d | 5  0  0  0 1
 e | 2  0  4  1 0

*/

int WeightedGraph::getNumVertices() const { return numVertices; }

int WeightedGraph::getWeight(const std::string& src,
                             const std::string& des) const {
  int srcIndex = findVertexIndex(src);
  int desIndex = findVertexIndex(des);
  if (srcIndex == -1 || desIndex == -1) {
    return -1;
  }

  return adjacencyMatrix[srcIndex][desIndex];
}
/*

 +-----+ 3 +-----+   +-----+
 |  a  |---|  b  |   |  c  |
 +--+--+   +-----+   +-----+
    |   \           /
  5 |    \ 2     4 /
    |     \       /
 +--+--+ 1 +-----+
 |  d  |---|  e  |
 +-----+   +-----+

Matrix:
   | a b c d e
---+----------
 a | 0 3 0 5 2
 b | 3 0 0 0 0
 c | 0 0 0 0 4
 d | 5 0 0 0 1
 e | 2 0 4 1 0

Getting the weight of edge ae:

Matrix:
   | a b c d  e
---+------------
 a | 0 3 0 5 '2'  <-- return 2
 b | 3 0 0 0  0
 c | 0 0 0 0  4
 d | 5 0 0 0  1
 e | 2 0 4 1  0

*/

bool WeightedGraph::isEmpty() const { return numVertices == 0; }

void WeightedGraph::printInfo() const {
  cout << "Vertices: ";
  printVertices();
  cout << "Matrix: \n";
  printMatrix();
}

void WeightedGraph::printVertices() const {
  for (int i = 0; i < numVertices; i++) {
    cout << vertexLabels[i] << " ";
  }
  cout << "\n";
}

void WeightedGraph::printMatrix() const {
  cout << "   | ";
  for (std::size_t col = 0; col < numVertices; col++) {
    cout << vertexLabels[col] << " ";
  }
  cout << "\n---+";
  for (std::size_t count = 0; count < numVertices; count++) {
    cout << "--";
  }
  cout << "\n";
  for (std::size_t row = 0; row < numVertices; row++) {
    cout << std::setw(2) << vertexLabels[row] << " | ";
    for (std::size_t col = 0; col < numVertices; col++) {
      cout << adjacencyMatrix[row][col] << " ";
    }
    cout << "\n";
  }
  cout << "\n";
}

int WeightedGraph::findVertexIndex(const std::string& label) const {
  for (int i = 0; i < numVertices; i++) {
    if (vertexLabels[i] == label) {
      return i;
    }
  }
  return -1;
}

void WeightedGraph::verifyMatrixSymmetry() const {
  for (int i = 0; i < numVertices; i++) {
    for (int j = i + 1; j < numVertices; j++) {
      assert(adjacencyMatrix[i][j] == adjacencyMatrix[j][i] &&
             "Matrix symmetry violation detected!");
    }
  }
}