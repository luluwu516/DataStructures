#include "GraphAdjacencyList.hpp"

// destructor
GraphAdjacencyList::~GraphAdjacencyList() {
  for (int i = 0; i < adjacencyList.size(); i++) {
    Node* curr = adjacencyList[i];
    while (curr) {
      Node* temp = curr;
      curr = curr->next;
      delete temp;
    }
  }
}

bool GraphAdjacencyList::addVertex(const std::string& label) {
  // vertex already exists
  if (searchLabel(label)) {
    return false;
  }

  vertexLabels.push_back(label);
  adjacencyList.push_back(new Node(label));

  return true;
}
/*

Adding a, b, c, d:
                +-----+-----+-----+-----+
  vertexLabels  |  a  |  b  |  c  |  d  |
                +-----+-----+-----+-----+

                +=====+=====+=====+=====+
  adjacencyList |  a  |  b  |  c  |  d  |
                +=====+=====+=====+=====+

*/

bool GraphAdjacencyList::addEdge(const std::string& src,
                                 const std::string& des) {
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

  addDirectedEdge(des, srcIndex, desIndex);
  addDirectedEdge(src, desIndex, srcIndex);

  return true;
}
/*

********** Example 1 **********
Adding a-b:
                   0     1     2     3
                +-----+-----+-----+-----+
  vertexLabels  |  a  |  b  |  c  |  d  |
                +-----+-----+-----+-----+
                   ^     ^
                 found found

 add to the vertice's linked list

 adjacencyList
   +=====+  +-----+
 0 |  a  |--|  b  |
   +=====+  +-----+
   +=====+  +-----+
 1 |  b  |--|  a  |
   +=====+  +-----+
   +=====+
 2 |  c  |
   +=====+
   +=====+
 3 |  d  |
   +=====+

********** Example 2 **********
Adding a-d:
                   0     1     2     3
                +-----+-----+-----+-----+
  vertexLabels  |  a  |  b  |  c  |  d  |
                +-----+-----+-----+-----+
                   ^                 ^
                 found             found

 add to the vertice's linked list

 adjacencyList
   +=====+  +-----+  +-----+
 0 |  a  |--|  b  |--|  d  |
   +=====+  +-----+  +-----+
   +=====+  +-----+
 1 |  b  |--|  a  |
   +=====+  +-----+
   +=====+
 2 |  c  |
   +=====+
   +=====+  +-----+
 3 |  d  |--|  a  |
   +=====+  +-----+

*/

void GraphAdjacencyList::addDirectedEdge(const std::string& label,
                                         const int& srcIndex,
                                         const int& desIndex) {
  Node* newNode = new Node(label);
  Node* curr = adjacencyList[srcIndex];
  while (curr->next && curr->label > label) {
    curr = curr->next;
  }
  newNode->next = curr->next;
  curr->next = newNode;
}

bool GraphAdjacencyList::searchLabel(const std::string& label) const {
  int index = findVertexIndex(label);
  return index != -1;
}
/*

Searching c:
                   0     1     2     3
                +-----+-----+-----+-----+
  vertexLabels  |  a  |  b  |  c  |  d  |
                +-----+-----+-----+-----+
                               ^
                             found

*/

bool GraphAdjacencyList::searchEdge(const std::string& src,
                                    const std::string& des) const {
  int srcIndex = findVertexIndex(src);
  int desIndex = findVertexIndex(des);
  if (srcIndex == -1 || desIndex == -1) {
    return false;
  }

  Node* curr = adjacencyList[srcIndex];
  while (curr) {
    if (curr->label == des) {
      return true;
    }
    curr = curr->next;
  }
  return false;
}
/*

Searching a-d:

 find the first vertex, a:

 adjacencyList
   +=====+  +-----+  +-----+
 > |  a  |--|  b  |--|  d  |
   +=====+  +-----+  +-----+
   +=====+  +-----+
   |  b  |--|  a  |
   +=====+  +-----+
   +=====+
   |  c  |
   +=====+
   +=====+  +-----+
   |  d  |--|  a  |
   +=====+  +-----+

 iterate vertex a's linked list...

   +=====+  +-----+  +-----+
   |  a  |--|  b  |--|  d  |
   +=====+  +-----+  +-----+
                        ^
                      found!

*/

bool GraphAdjacencyList::removeVertex(const std::string& labelToRemove) {
  int index = findVertexIndex(labelToRemove);
  if (index == -1) {
    return false;
  }

  // delete the entire list for the removed vertex
  Node* curr = adjacencyList[index];
  while (curr) {
    Node* temp = curr;
    curr = curr->next;
    delete temp;
  }

  // erase the vertex from the adjacencyList
  adjacencyList.erase(adjacencyList.begin() + index);

  // remove edges to the deleted vertex from other lists
  for (int i = 0; i < adjacencyList.size(); i++) {
    if (searchEdge(vertexLabels[i], vertexLabels[index])) {
      removeDirectedEdge(i, index);
    }
  }

  // remove the label from the vertexLabels
  vertexLabels.erase(vertexLabels.begin() + index);

  return true;
}

/*

Removing b:

 adjacencyList
   +=====+  +-----+  +-----+
   |  a  |--|  b  |--|  d  |
   +=====+  +-----+  +-----+
   +=====+  +-----+
 > |  b  |--|  a  |
   +=====+  +-----+
   +=====+
   |  c  |
   +=====+
   +=====+  +-----+
   |  d  |--|  a  |
   +=====+  +-----+

 1. clean vertex b's linked list

 adjacencyList
   +=====+  +-----+  +-----+
   |  a  |--|  b  |--|  d  |
   +=====+  +-----+  +-----+
   +=====+
 > |  b  |
   +=====+
   +=====+
   |  c  |
   +=====+
   +=====+  +-----+
   |  d  |--|  a  |
   +=====+  +-----+

 2. erase vertex b from the adjacencyList

   +=====+  +-----+  +-----+
   |  a  |--|  b  |--|  d  |
   +=====+  +-----+  +-----+
   +=====+
   |  c  |
   +=====+
   +=====+  +-----+
   |  d  |--|  a  |
   +=====+  +-----+

 3. remove edges to the deleted vertex from other lists

  3-1. iterate other lists and search the edge to the removed edge
   +=====+  +-----+  +-----+
   |  a  |--|  b  |--|  d  |
   +=====+  +-----+  +-----+
               ^ found!
   +=====+
   |  c  |
   +=====+
   +=====+  +-----+
   |  d  |--|  a  |
   +=====+  +-----+

  3-2. remove it!
   +=====+  +-----+
   |  a  |--|  d  |
   +=====+  +-----+
   +=====+
   |  c  |
   +=====+
   +=====+  +-----+
   |  d  |--|  a  |
   +=====+  +-----+

 4. erase the label from the vertexLabels

                   0     1     2
                +-----+-----+-----+
  vertexLabels  |  a  |  c  |  d  |
                +-----+-----+-----+

*/

bool GraphAdjacencyList::removeEdge(const std::string& src,
                                    const std::string& des) {
  int srcIndex = findVertexIndex(src);
  int desIndex = findVertexIndex(des);
  if (srcIndex == -1 || desIndex == -1) {
    return false;
  }

  removeDirectedEdge(srcIndex, desIndex);
  removeDirectedEdge(desIndex, srcIndex);

  return true;
}
/*

Removing a-d:

                   0     1     2
                +-----+-----+-----+
  vertexLabels  |  a  |  c  |  d  |
                +-----+-----+-----+
                   ^           ^
                 found       found

 remove the edges

   +=====+
 0 |  a  |
   +=====+
   +=====+
 1 |  c  |
   +=====+
   +=====+
 2 |  d  |
   +=====+

*/

void GraphAdjacencyList::removeDirectedEdge(const int& srcIndex,
                                            const int& desIndex) {
  Node* curr = adjacencyList[srcIndex];
  Node* prev = nullptr;

  while (curr && curr->label != vertexLabels[desIndex]) {
    prev = curr;
    curr = curr->next;
  }

  if (curr) {
    if (prev) {
      prev->next = curr->next;
    } else {
      adjacencyList[srcIndex] = curr->next;
    }
    delete curr;
  }
}

/*
********** Example 1 **********
Removing directed edge a-d:

 find the edges

   +=====+  +-----+
 0 |  a  |--|  d  |
   +=====+  +-----+
               ^ found!
   +=====+
 1 |  c  |
   +=====+
   +=====+  +-----+
 2 |  d  |--|  a  |
   +=====+  +-----+

 delete the vertex in the linked list

   +=====+
 0 |  a  |
   +=====+
   +=====+
 1 |  c  |
   +=====+
   +=====+  +-----+
 2 |  d  |--|  a  |
   +=====+  +-----+

********** Example 2 **********
Removing directed edge d-a:

 find the edges

   +=====+
 0 |  a  |
   +=====+
   +=====+
 1 |  c  |
   +=====+
   +=====+  +-----+
 2 |  d  |--|  a  |
   +=====+  +-----+
               ^ found!

 delete the vertex in the linked list

   +=====+
 0 |  a  |
   +=====+
   +=====+
 1 |  c  |
   +=====+
   +=====+
 2 |  d  |
   +=====+

*/

bool GraphAdjacencyList::isEmpty() const { return vertexLabels.size() == 0; }

void GraphAdjacencyList::printInfo() const {
  cout << "Vertices: ";
  printVertices();
  cout << "Edges: \n";
  printEdges();
}

void GraphAdjacencyList::printVertices() const {
  for (auto label : vertexLabels) {
    cout << label << " ";
  }
  cout << "\n";
}

void GraphAdjacencyList::printEdges() const {
  for (int i = 0; i < vertexLabels.size(); i++) {
    cout << " * " << vertexLabels[i] << ": ";
    Node* curr = adjacencyList[i]->next;
    if (!curr) {
      cout << "(Edges from " << vertexLabels[i] << " is Empty)\n";
      continue;
    }
    while (curr) {
      cout << vertexLabels[i] << "-" << curr->label << " ";
      curr = curr->next;
    }
    cout << "\n";
  }
}

int GraphAdjacencyList::findVertexIndex(const std::string& label) const {
  for (int i = 0; i < vertexLabels.size(); i++) {
    if (vertexLabels[i] == label) {
      return i;
    }
  }
  return -1;
}