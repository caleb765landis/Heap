// Heap.h

#ifndef HEAP_H_INCLUDED
#define HEAP_H_INCLUDED

#include "Node.h"
#include <string>

class Heap {
  public:
    Node* root;

    Heap();
    Heap(int key);
    void insert(Node* currentNode, int parentKey, int leftKey, int rightKey);
};
#endif
