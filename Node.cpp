// Node.cpp

#include "Node.h"

Node::Node() {
  npl = 0;
  found = false;
  left = NULL;
  right = NULL;
} // end constructor

Node::Node(int key) {
  Node::key = key;
  npl = 0;
  found = false;
  left = NULL;
  right = NULL;
} // end overloaded constructor 
