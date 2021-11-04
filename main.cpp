//main.cpp

#include "Node.h"
#include "Heap.h"
#include <string>
#include <iostream>
#include <cstdlib> // system()
#include <stack>

//prototypes
Node* merge(Node* x, Node* y);
bool mergeArray(Node*currentNode, int parentKey, int i, bool found);
void printTree(Node* node, int space);

std::stack<Node*> remember;
int a3[58];

int main() {
  // clear screen to start the program
  system("clear");

  // create two heap arrays
  int a1[16] = {0,4,19,8,27,20,12,0,43,0,0,0,15,25,0,0};
  int a2[8] = {0,6,8,7,14,0,0,0};

  // create two heaps
  Heap h1 = Heap(a1[1]);
  Heap h2 = Heap(a2[1]);

  // starting with the first key until length/2
  // build trees by inserting parent keys and setting their left and right children
  for (int i = 1; i < 8; i++) {
    // start at root; pass keys for parent, left, right
    h1.insert(h1.root, a1[i], a1[2*i], a1[2*i + 1]);
  } // end build h1
  for (int i = 1; i < 4; i++) {
    // start at root; pass parent, left, right
    h2.insert(h2.root, a2[i], a2[2*i], a2[2*i + 1]);
  } // end build h2

  std::cout << "a1[] = {0,4,19,8,27,20,12,0,43,0,0,0,15,25,0,0}" << std::endl << std::endl;
  printTree(h1.root, 0);
  std::cout << std::endl << std::endl;

  std::cout << "int a2[] = {0,6,8,7,14,0,0,0}" << std::endl << std::endl;
  printTree(h2.root, 0);
  std::cout << std::endl << std::endl;

  // merge heaps
  Node* newRoot = merge(h1.root, h2.root);

  a3[0] = 0;
  a3[1] = newRoot -> key;
  // starting with the first key until length/2
  for (int i = 1; i < 29; i++) {
    mergeArray(newRoot, a3[i], i, true);
  } // end initialize merged array

  std::cout << "a3[] = {";
  for (int i = 0; i < 57; i++) {
    std::cout << a3[i] << ",";
  } // end for
  std::cout << a3[57] << "}" << std::endl << std::endl;
  printTree(newRoot, 0);
} // end main

Node* merge(Node* x, Node* y) {
  Node* returnNode;

  // if both x and y are not NULL
  if (x -> key != 0 && y -> key != 0) {
    // get smaller node and insert it into stack
    Node* smaller;
    Node* larger;
    if (x -> key < y -> key) {
      smaller = x;
      larger = y;
      remember.push(smaller);
    } else {
      smaller = y;
      larger = x;
      remember.push(smaller);
    } // end if smaller

    // set smaller node's new child
    // as long as left child is not NULL, right child will normally be set
    Node* newChild = merge(smaller -> right, larger);
    if (remember.top() -> left -> key == 0) {
      // set left to ensure remember.top() is leftist
      remember.top() -> left = newChild;
    } else {
      remember.top() -> right = newChild;
    } // end set child

    // make top node in stack leftist
    // if right's npl >= left's npl, swap children
    if (remember.top() -> right -> npl > remember.top() -> left -> npl) {
      Node* temp = remember.top() -> left;
      remember.top() -> left = remember.top() -> right;
      remember.top() -> right = temp;
    } // end make leftist

    // update npl
    if (remember.top() -> left -> key != 0 && remember.top() -> right -> key != 0) {
      remember.top() -> npl = 1 + remember.top() -> right -> npl;
    } // end if

    // return top node and pop it off stack
    returnNode = remember.top();
    remember.pop();

  // if one node is NULL
  } else {
    // return non-NULL node
    if (x -> key == 0) {
      returnNode = y;
    } else {
      returnNode = x;
    } // end set returnNode
  } // end if NULL

  return returnNode;
} // end merge

bool mergeArray(Node*currentNode, int parentKey, int i, bool keepGoing) {
  // if node with parentKey is found
  if (currentNode -> key == parentKey && currentNode -> found == false) {
    if (currentNode -> left != NULL && currentNode -> left != 0) {
      a3[2*i] = currentNode -> left -> key;
    } else {
      a3[2*i] = 0;
    } // end if left is null
    if (currentNode -> right != NULL && currentNode -> right != 0) {
      a3[2*i + 1] = currentNode -> right -> key;
    } else {
      a3[2*i + 1] = 0;
    } // end if right is null

    currentNode -> found = true;
    keepGoing = false;

  // keep searching for node with parentKey
  } else {
    if (currentNode -> left != NULL && keepGoing == true) {
      keepGoing = mergeArray(currentNode -> left, parentKey, i, keepGoing);
    } // end if

    if (currentNode -> right != NULL && keepGoing == true) {
       keepGoing = mergeArray(currentNode -> right, parentKey, i, keepGoing);
    } // end if
  } // end if currentNode is found
  return keepGoing;
} // end insert

/*
  prints Heap sideways
  traverses through tree backwards
  increases spacing everytime function is called recursively / deeper into the tree
  space is initally 0 in main()
*/
void printTree(Node* node, int space) {
  if (node != NULL) {
    space += 8;
    printTree(node -> right, space);

    // print row
    for (int i = 8; i < space; i++) {
      std::cout << " ";
    } // end for

    //std::cout << node -> key << "(" << node -> npl << ")" << std::endl; // prints npls too
    std::cout << node -> key << std::endl;

    printTree(node -> left, space);
  } // end if
} // end printTree()
