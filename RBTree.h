#include <iostream>
#include "RBTreeNode.h"

using namespace std;

struct successorReturnValues{
  RBTreeNode* succ;
  RBTreeNode* sp;
  bool successorUsed;
};


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
    RBTreeNode* getSuccessor(RBTreeNode *d, RBTreeNode** successorParent, bool* successorUsed, bool* successorIsRightBelow);
    RBTreeNode* getPredecessor(RBTreeNode *d, RBTreeNode** successorParent, bool* successorUsed, bool* successorIsRightBelow);
    bool isEmpty();
    RBTreeNode* getMin();
    RBTreeNode* getMax();
    void recPrint(RBTreeNode *node); // recursive print

    void fixDoubleBlack(RBTreeNode *parent, RBTreeNode *node);
    void fixDoubleRed(RBTreeNode *node);
    void rotateTriangleRight(RBTreeNode *current, RBTreeNode *parent, RBTreeNode *gp);
    void rotateTriangleLeft(RBTreeNode *current, RBTreeNode *parent, RBTreeNode *gp);
    void rotateSideHeavyRight(RBTreeNode *parent, RBTreeNode *gp, RBTreeNode *greatGP);
    void rotateSideHeavyLeft(RBTreeNode *parent, RBTreeNode *gp, RBTreeNode *greatGP);

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
  cout << node->key << "\t" << node->getColor() << endl;
  recPrint(node->right);
}

void RBTree::printTree(){
  cout << "Tree where root = " << root->key << endl;
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
  if (search(value) == true){
    // node already in tree
    cout << "Node already in tree. Cannot add " << value << endl;
    exit(1);
  }

  RBTreeNode *node = new RBTreeNode(value);

  if (root == NULL){ // empty tree
    node->setColor(BLACK);
    root = node;
  }
  else{
    // tree is not empty
    // let's find the insertion point
    RBTreeNode *current = root;
    RBTreeNode *parent = NULL;

    int deez = 0;
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
    // check for double red
    if (parent->isRed() && node->isRed()){
      cout << "Double red detected" << endl;
      fixDoubleRed(node);
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
  cout << "deleting " << value << endl;
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
  cout << "found node to be deleted: " << current->key << ". color is " << current->getColor() << endl;
  RBTreeNode *replacementNode;
  RBTreeNode *sp = parent;
  bool successorUsed;
  bool successorIsRightBelow;
  RBTreeNode *deletedNode = current;

  // if node is external / has 0 children / is a leaf
  if (current->left == NULL && current->right == NULL){

    replacementNode = NULL; // save for color flip

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

    replacementNode = current->left; // save for color flip

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

    replacementNode = current->right; // save for color flip

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

    RBTreeNode *successor;
    successor = getSuccessor(current, &sp, &successorUsed, &successorIsRightBelow);

    cout << "succesor/predecessor = " << successor->key << endl;

    replacementNode = successor; // save for color flip

    if (current == root){
      root = successor;
    }
    else if (isLeft){
      parent->left = successor;
    }
    else{
      parent->right = successor;
    }

    // Makes sure the right pointer is changed depending on if successor or predecessor is used
    if (successorUsed){
      successor->left = current->left;
    }
    else{
      successor->right = current->right;
    }

    /*
    // Change color of replacementNode to color of deletedNode
    if (deletedNode->getColor() == "RED"){
      replacementNode->setColor(RED);
    }
    else{
      replacementNode->setColor(BLACK);
    }
    */
  }
  // end of standard BST delete

  // ------------------------------ Handle colors ------------------------------
  cout << "deleted node: " << deletedNode->key << endl;
  // take out deleted node

  // Changes direction of pointer of realReplacementNode (most likely the null node)
  // This section of code fixes the case where the successor (or predecessor) is the node right below the current one
  RBTreeNode *realReplacementNode;
  RBTreeNode *realReplacementNodeParent;
  if (successorUsed == true && successorIsRightBelow == false){
    realReplacementNode = sp->left;
  }
  else if (successorUsed == false && successorIsRightBelow == false){
    realReplacementNode = sp->right;
  }
  else if (successorUsed == false && successorIsRightBelow == true){
    realReplacementNode = sp->left->left;
  }
  else{
    realReplacementNode = sp->right->right;
  }


  // Makes color shift depending colors of replacementNode and realReplacementNode
  cout << "sp=" << sp->key << endl;
  if (successorUsed){
    realReplacementNode = sp->left;
    realReplacementNodeParent = sp;
    if (successorIsRightBelow){
      realReplacementNode = sp->right->right;
      realReplacementNodeParent = sp->right;
    }

    if (replacementNode->getColor() == "RED" || realReplacementNode->getColor() == "RED"){
      // Either u or v is red, make replacementNode color black
      cout << "changing pointer to black." << endl;
      realReplacementNode->setColor(BLACK);
    }
    else{
      // Double black found
      cout << "double black found in successor" << endl;
      if (successorIsRightBelow){
        if (realReplacementNodeParent->getColor() == "RED"){
          realReplacementNodeParent->setColor(BLACK);
        }
        else{
          realReplacementNodeParent->setColor(RED);
        }
      }
      fixDoubleBlack(realReplacementNodeParent, realReplacementNode);
    }
  }
  // predecessor used and NOT successor
  else{

    realReplacementNode = sp->right;
    realReplacementNodeParent = sp;
    cout << "sp color: " << sp->getColor() << endl;
    if (successorIsRightBelow){
      realReplacementNode = sp->left->left;
      realReplacementNodeParent = sp->left;
      cout << "sp changed to " << sp->left->key << ". color now: " << sp->left->getColor() << endl;
    }

    //cout << replacementNode->key << endl;

    if (replacementNode->getColor() == "RED" || realReplacementNode->getColor() == "RED"){
      // Either u or v is red, make replacementNode color black
      cout << "changing pointer to black." << endl;
      realReplacementNode->setColor(BLACK);
    }
    else{
      // Double black found
      cout << "double black found in predecessor" << endl;
      if (successorIsRightBelow){
        if (realReplacementNodeParent->getColor() == "RED"){
          realReplacementNodeParent->setColor(BLACK);
        }
        else{
          realReplacementNodeParent->setColor(RED);
        }
      }
      fixDoubleBlack(realReplacementNodeParent, realReplacementNode);
    }
  }

  return true;
}

// rewrite
RBTreeNode* RBTree::getSuccessor(RBTreeNode *d, RBTreeNode** successorParent, bool* successorUsed, bool* successorIsRightBelow){ // d is the node to be deleted
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

  // Check if successor should be used and not the predecessor
  // Rule = if (successor == red OR successor != black leaf) then use successor
  // Otherwise/else --> use predecessor
  if (successor->right->getColor() != "RED" && successor->getColor() != "RED"){
    // we should use predecessor instead of successor
    cout << "Grabbing predecessor instead" << endl;
    return getPredecessor(d, successorParent, successorUsed, successorIsRightBelow);
  }

  if (successor != d->right){

    // change checker variable
    *successorIsRightBelow = false;

    // Check for double black HERE
    // v - node to be deleted - successor
    // u - node to replace - successor->right
    bool isDoubleBlack;
    if (successor->getColor() == "BLACK" && successor->right->getColor() == "BLACK"){
      // double black here --> needs to be fixed
      //successor->right->setColor(DOUBLEBLACK);
      cout << "double black detected" << endl;
      //fixDoubleBlack
    }

    // if our successor is NOT just the node right of our deleted node
    // i.e. the tree is complicated and we have some work to do
    sp->left = successor->right;
    successor->right = d->right;
  }
  else{
    // Sets successor's parent to d if d->right is successor and flips boolean
    // this allow the direction of sp's pointer to switch (since it is different in this case)
    *successorParent = d;
    *successorIsRightBelow = true;
    cout << "succesor parent is d and successorIsRightBelow is true" << endl;
  }
  *successorParent = sp;
  *successorUsed = true;
  return successor;

}

// rewrite
RBTreeNode* RBTree::getPredecessor(RBTreeNode *d, RBTreeNode** successorParent, bool* successorUsed, bool* successorIsRightBelow){ // d is the node to be deleted
  // the successor can either be the largest number less than d
  // or the smallest number greater than d.
  // Either of these work --> it doesn't matter which route you take --> it's personal preference
  // in this case, we will be choosing the former --> left once than all the way right
  RBTreeNode *current = d->left;
  RBTreeNode *sp = d; // Successor's Parent
  RBTreeNode *successor = d;

  while(current != NULL){
    sp = successor;
    successor = current;
    current = current->right;
  }
  // we made it here, that means we found our successor
  if (successor != d->left){

    // change checker variable
    *successorIsRightBelow = false;

    // Check for double black HERE
    // v - node to be deleted - successor
    // u - node to replace - successor->left
    bool isDoubleBlack;
    if (successor->getColor() == "BLACK" && successor->left->getColor() == "BLACK"){
      // double black here --> needs to be fixed
      //successor->left->setColor(DOUBLEBLACK);
      cout << "double black detected" << endl;
    }

    // if our successor is NOT just the node right of our deleted node
    // i.e. the tree is complicated and we have some work to do
    sp->right = successor->left;
    successor->left = d->left;
  }
  else{
    // Sets successor's parent to d if d->left is successor and flips boolean
    // this allow the direction of sp's pointer to switch (since it is different in this case)
    *successorParent = d;
    *successorIsRightBelow = true;
    cout << "succesor parent is d and successorIsRightBelow is true" << endl;
  }
  *successorParent = sp;
  *successorUsed = false;
  return successor;
}

void RBTree::fixDoubleRed(RBTreeNode *node){
  cout << "fixing double red" << endl;
  // finds node while keeping track of parent and grandparent
  RBTreeNode *current = root;
  RBTreeNode *parent = root;
  RBTreeNode *gp = root;
  RBTreeNode *greatGP = root;
  int value = node->key;
  bool lastTurnLeft = true;
  bool secondLastTurnLeft = true;
  while (current->key != value){

    greatGP = gp;
    gp = parent;
    parent = current;

    secondLastTurnLeft = lastTurnLeft;

    if (value < current->key){
      current = current->left;
      lastTurnLeft = true;
    }
    else{
      current = current->right;
      lastTurnLeft = false;
    }

  }
  cout << "found node " << value << endl;

  // ----- finds uncle and checks if uncle is red or black -----
  RBTreeNode *uncle;

  if (secondLastTurnLeft){
    // parent is left child --> uncle must be right child
    uncle = gp->right;
  }
  else{
    // parent is right child --> uncle must be left child
    uncle = gp->left;
  }

  // Uncle is red ------------ COLOR FLIP
  if (uncle->isRed()){
    cout << "uncle is red --> recoloring" << endl;
    // parent and uncle (parent's sibling) turn to black
    parent->setColor(BLACK);
    uncle->setColor(BLACK);
    // and their parent (grandparent) turn to red
    if (gp != root) // unless it is the root
      gp->setColor(RED);
    else
      gp->setColor(BLACK);

    // Check for another instance of double red
    if (greatGP->getColor() == "RED"){
      // both grandparent and great-grandparent are red --> recur
      cout << "Double red detected -- recur" << endl;
      fixDoubleRed(gp);
    }
  }
  // Uncle is black ----------- ROTATION
  else{
    cout << "uncle is black --> rotating" << endl;

    // Case Right-then-Left --- Triangle
    if (lastTurnLeft == true && secondLastTurnLeft == false){
      cout << "rotation triangle" << endl;
      rotateTriangleLeft(current, parent, gp);
      RBTreeNode *temp = current;
      current = parent;
      parent = temp;
    }
    // Case Left-then-Right --- Triangle
    else if (lastTurnLeft == false && secondLastTurnLeft == true){
      cout << "rotation triangle" << endl;
      rotateTriangleRight(current, parent, gp);
      RBTreeNode *temp = current;
      current = parent;
      parent = temp;
    }

    // Case Right-Right --- Side Heavy
    if (lastTurnLeft == false && secondLastTurnLeft == false){
      cout << "rotation side heavy" << endl;
      rotateSideHeavyLeft(parent, gp, greatGP);
      // Flipping colors after rotation
      current->setColor(RED);
      parent->setColor(BLACK);
      gp->setColor(RED);
    }

    // Case Left-Left --- Side Heavy --- (lastTurnLeft == true && secondLastTurnLeft == true)
    else{
      cout << "rotation side heavy" << endl;
      rotateSideHeavyRight(parent, gp, greatGP);
      // Flipping colors after rotation
      current->setColor(RED);
      parent->setColor(BLACK);
      gp->setColor(RED);
    }

  }

}

void RBTree::fixDoubleBlack(RBTreeNode *parent, RBTreeNode *node){
  cout << "fixing double black. parent = " << parent->key << ". node = " << node << endl;
  // Case 1: Root
  if (node == root){
    node->setColor(BLACK);
    return;
  }

  // Has search loop find the parent if the double black node is NULL
  bool dblBlackNull;
  bool isLeft;
  if (node == NULL){
    cout << "parent->left: " << parent->left << endl;
    if (parent->left != NULL){
      isLeft = false;
    }
    else{
      isLeft = true;
    }
    cout << "node is null. isLeft is: " << isLeft << endl;
    node = parent;
    dblBlackNull = true;
  }

  // We must find the node and keep track of its family
  RBTreeNode *current = root;
  RBTreeNode *parentNode = root;
  RBTreeNode *grandparentNode = root;
  bool lastTurnLeft;
  int value = node->key;
  cout << "looking for value : " << value << endl;
  while (current->key != value || dblBlackNull == true){
    cout << "running loop. current = " << current->key << ". color= " << current->getColor() << endl;
    grandparentNode = parentNode;
    parentNode = current;

    if (value < current->key){
      current = current->left;
      lastTurnLeft = true;
    }
    else if (value > current->key){
      current = current->right;
      lastTurnLeft = false;
    }
    else{
      // current->key = value, which means the double black node is NULL
      if (isLeft == true){
        current = current->left;
        lastTurnLeft = true;
      }
      else{
        current = current->right;
        lastTurnLeft = false;
      }
      cout << "about to break" << endl;
      break;
    }
  }
  // Found double black node
  //cout << "Found double black node to delete: " << current->key << endl;
  // Declare more family members: sibling and nephewLeft and nephewRight
  RBTreeNode *sibling;
  bool siblingIsLeftChild;
  RBTreeNode *nephewLeft;
  RBTreeNode *nephewRight;
  if (lastTurnLeft == true){
    sibling = parentNode->right;
    siblingIsLeftChild = false;
    cout << "double black node is left child" << endl;
  }
  else{
    cout << "parent node: " << parentNode->key << endl;
    sibling = parentNode->left;
    siblingIsLeftChild = true;
    cout << "double black node is right child" << endl;
  }
  cout << "sibling: " << sibling->key << endl;
  nephewLeft = sibling->left;
  nephewRight = sibling->right;


  // Case 2: Sibling is RED
  if (sibling->getColor() == "RED"){
    cout << "sibling is red" << endl;
    // sibling is right child
    if (lastTurnLeft == true){
      rotateSideHeavyLeft(sibling, parentNode, grandparentNode);
    }
    // sibling is left child
    else{
      rotateSideHeavyRight(sibling, parentNode, grandparentNode);
    }
    // Color FLIP
    sibling->setColor(BLACK);
    parentNode->setColor(RED);
    // Recursion!
    fixDoubleBlack(parentNode, current);
  }

  cout << "parent node: " << parentNode->key << endl;
  cout << "parent node color: " << parentNode->getColor() << endl;

  // Case 3: Sibling is black and BOTH nephews are black
  if (sibling->getColor() == "BLACK" && nephewLeft->getColor() == "BLACK" && nephewRight->getColor() == "BLACK"){
    cout << "case 3, sibling and both nephews black" << endl;
    // If parent is black --> recolor sibling and set the parent to double black; recur
    if (parentNode->getColor() == "BLACK"){
      cout << "parent is black --> recur" << endl;
      sibling->setColor(RED);
      fixDoubleBlack(grandparentNode, parentNode);
    }
    // Else, parent is red --> recolor and done!
    else{
      cout << "parent is red!" << endl;
      parentNode->setColor(BLACK);
      sibling->setColor(RED);
    }
  }
  // Case 4: If sibling is black and at least one nephew is red
  if (sibling->getColor() == "BLACK" && (nephewLeft->getColor() == "RED" || nephewRight->getColor() == "RED")){
    cout << "At least one nephew is red" << endl;
    // Left Right Case --> Double rotation
    // Triangle rotation to the right, then side heavy right rotation
    if (siblingIsLeftChild == true && nephewRight->getColor() == "RED" && nephewLeft->getColor() == "BLACK"){
      cout << "Left Right case, triangle" << endl;
      rotateTriangleLeft(nephewRight, sibling, parentNode);
      nephewLeft = sibling;
      sibling = nephewRight;
      sibling->setColor(BLACK);
      nephewLeft->setColor(RED);
    }

    // Right Left Case --> Double Rotation
    // Triangle rotation to the left, then side heavy left rotation
    if (siblingIsLeftChild == false && nephewLeft->getColor() == "RED" && nephewRight->getColor() == "BLACK"){
      cout << "Right Left case, triangle" << endl;
      rotateTriangleRight(nephewLeft, sibling, parentNode);
      nephewRight = sibling;
      sibling = nephewLeft;
      sibling->setColor(BLACK);
      nephewRight->setColor(RED);
    }

    // Left Left Case --> side heavy rotation to the right
    if (siblingIsLeftChild == true && nephewLeft->getColor() == "RED"){
      cout << "Left Left case, side heavy" << endl;
      cout << "gp node: " << grandparentNode->key << endl;
      rotateSideHeavyRight(sibling, parentNode, grandparentNode);
      nephewLeft->setColor(BLACK);
      sibling->setColor(RED);
      parentNode->setColor(BLACK);
    }

    // Right Right Case --> side heavy rotation to the left
    if (siblingIsLeftChild == false && nephewRight->getColor() == "RED"){
      cout << "Right Right case, side heavy" << endl;
      rotateSideHeavyLeft(sibling, parentNode, grandparentNode);
      nephewRight->setColor(BLACK);
      sibling->setColor(RED);
      parentNode->setColor(BLACK);
    }
  }

}

void RBTree::rotateTriangleLeft(RBTreeNode *current, RBTreeNode *parent, RBTreeNode *gp){
  gp->right = current;
  parent->left = current->right;
  current->right = parent;
}

void RBTree::rotateTriangleRight(RBTreeNode *current, RBTreeNode *parent, RBTreeNode *gp){
  gp->left = current;
  parent->right = current->left;
  current->left = parent;
}

void RBTree::rotateSideHeavyLeft(RBTreeNode *parent, RBTreeNode *gp, RBTreeNode *greatGP){
  if (greatGP->right == gp){ // grandparent is RIGHT child
    greatGP->right = parent;
  }
  else if (greatGP->left == gp){ // grandparent is LEFT child
    greatGP->left = parent;
  }
  else{ // grandparent is not child of greatGP, meaning grandparent is root --> move root to parent
    root = parent;
  }
  // Pointer updates
  gp->right = parent->left;
  parent->left = gp;
}

void RBTree::rotateSideHeavyRight(RBTreeNode *parent, RBTreeNode *gp, RBTreeNode *greatGP){
  if (greatGP->right == gp){ // grandparent is RIGHT child
    greatGP->right = parent;
  }
  else if (greatGP->left == gp){ // grandparent is LEFT child
    cout << "we should be good" << endl;
    greatGP->left = parent;
  }
  else{ // grandparent is not child of greatGP, meaning grandparent is root --> move root to parent
    cout << "the problem" << endl;
    root = parent;
  }
  // Pointer updates
  gp->left = parent->right;
  parent->right = gp;
}
