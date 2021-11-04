// Node.cpp

#include "Node.h"
#include "Heap.h"

Heap::Heap() {
  root = NULL;
} // end constructor

Heap::Heap(int key) {
  root = new Node(key);
} // end overloaded constructor

void Heap::insert(Node* currentNode, int parentKey, int leftKey, int rightKey) {
  // if node with parentKey is found
  if (currentNode -> key == parentKey && parentKey != 0) {
    // set left and right children
    currentNode -> left = new Node(leftKey);
    currentNode -> right = new Node(rightKey);

    if (leftKey != 0 && rightKey != 0) {
      currentNode -> npl++;
    } // end increase null path length

  // keep searching for node with parentKey
  } else {
    if (currentNode -> left != NULL) {
      insert(currentNode -> left, parentKey, leftKey, rightKey);
    } // end if

    if (currentNode -> right != NULL) {
      insert(currentNode -> right, parentKey, leftKey, rightKey);
    } // end if
  } // end if currentNode is found
} // end insert
