#include <iostream>
#include "RBTreeNode.h"

using namespace std;

class RBTree{
  private:
    RBTreeNode *root;
  public:
    RBTree();
    ~RBTree();

    bool search(int value);
    void insert(int value);
    bool deleteNode(int value);
    void printTree();

    // helper functions
    RBTreeNode* getSuccessor(RBTreeNode *d);
    bool isEmpty();
    RBTreeNode* getMin();
    RBTreeNode* getMax();
    void recPrint(RBTreeNode *node); // recursive print

    void fixDoubleBlack(RBTreeNode n);
    void fixDoubleRed(RBTreeNode n);
};

RBTree::RBTree(){
  root = NULL;
}

bool RBTree::isEmpty(){
  if (root == NULL){
    return true;
  }
  else{
    return false;
  }
}

void RBTree::recPrint(RBTreeNode *node){
  if (node == NULL){
    return;
  }

  recPrint(node->left);
  cout << node->key << "   " << node->col << endl;
  recPrint(node->right);
}

void RBTree::printTree(){
  recPrint(root);
}

RBTreeNode* RBTree::getMax(){

  RBTreeNode *curr = root;

  if (root == NULL){
    return NULL;
  }
  while(curr->right != NULL){
    curr = curr->right; // keep going down to the right
  }

  return curr;
}

RBTreeNode* RBTree::getMin(){
  RBTreeNode *curr = root;

  if (root == NULL){
    return NULL;
  }
  while(curr->left != NULL){
    curr = curr->left; // keep going down to the left
  }

  return curr;
}

void RBTree::insert(int value){

  // check if value exists in tree already before proceding
  // every key is unique, so if it is already in the tree, we cannot insert

  RBTreeNode *node = new RBTreeNode(value);

  if (root == NULL){ // empty tree
    root = node;
  }
  else{
    // tree is not empty
    // let's find the insertion point
    RBTreeNode *current = root;
    RBTreeNode *parent = NULL;

    int deez = 0 ;
    int nuts = 0;
    while(deez == nuts){
      parent = current;

      if (value < current->key){
        // go left
        current = current->left;

        if (current == NULL){ // found insertion point
          parent->left = node;
          break;
        }
      }
      else{
        // go right
        current = current->right;

        if (current == NULL){ // found the insertion point
          parent->right = node;
          break;
        }
      }
    }
  }
}

// this function may change to return a RBTreeNode* for assignment_5
bool RBTree::search(int value){

  // if the tree is empty
  if (root == NULL){
    return false;
  }

  // made it here? the tree is for shizzle not empty
  RBTreeNode *current = root;
  while (current->key != value){
    if (value < current->key){
      current = current->left;
    }
    else{
      current = current->right;
    }

    if (current == NULL){ //  value not in tree
      return false;
    }
  }
  return true;
}

bool RBTree::deleteNode(int value){

  if (root == NULL) // tree is empty
    return false;

  RBTreeNode *parent = root;
  RBTreeNode *current = root;
  bool isLeft = true;

  // let's attempt to find the node to be deleted
  while (current->key != value)
  {
    parent = current;

    if (value < current->key){
      // go left
      isLeft = true;
      current = current->left;
    }
    else{
      // go right
      isLeft = false;
      current = current->right;
    }

    if (current == NULL){
      // value doesn't exist
      return false;
    }
  }

  // if we make it here, then we have found the node to be deleted

  // if node is external / has 0 children / is a leaf
  if (current->left == NULL && current->right == NULL){

    if (current == root){
      root = NULL;
    }
    else if (isLeft){
      parent->left = NULL;
    }
    else{
      parent->right = NULL;
    }
  }
  // if node has 1 child; and it's a left (no right child)
  else if (current->right == NULL){

    if (current == root){
      root = current->left;
    }
    else if (isLeft){
      parent->left = current->left;
    }
    else{
      parent->right = current->left;
    }
  }
  // if node has 1 child; and it's a right (no left child)
  else if (current->left == NULL){

    if (current == root){
      root = current->right;
    }
    else if (isLeft){
      parent->left = current->right;
    }
    else{
      parent->right = current->right;
    }
  }
  // if the node has 2 children --> uh oh lmao
  // get ready to rumble
  else{

    RBTreeNode *successor = getSuccessor(current);

    if (current == root){
      root = successor;
    }
    else if (isLeft){
      parent->left = successor;
    }
    else{
      parent->right = successor;
    }

    successor->left = current->left;
  }
  return true;
}

RBTreeNode* RBTree::getSuccessor(RBTreeNode *d){ // d is the node to be deleted
  // the successor can either be the largest number less than d
  // or the smallest number greater than d.
  // Either of these work --> it doesn't matter which route you take --> it's personal preference
  // in this case, we will be choosing the latter --> right once than all the way left
  RBTreeNode *current = d->right;
  RBTreeNode *sp = d; // Successor's Parent
  RBTreeNode *successor = d;

  while(current != NULL){
    sp = successor;
    successor = current;
    current = current->left;
  }
  // we made it here, that means we found our successor
  if (successor != d->right){
    // if our successor is NOT just the node right of our deleted node
    // i.e. the tree is complicated and we have some work to do
    sp->left = successor->right;
    successor->right = d->right;
  }
  return successor;

}

void RBTree::fixDoubleRed(RBTreeNode n){
  // stuff
}

void RBTree::fixDoubleBlack(RBTreeNode n){
  // stuff
}
