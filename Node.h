// Node.h

#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

#include <string>

class Node {
  public:
    int key;
    int npl; // null path length
    bool found; // used for printing out merged array
    Node* left;
    Node* right;

    Node();
    Node(int key);
};
#endif
