#include <iostream>

using namespace std;

enum Color{RED, BLACK};

class RBTreeNode{
  public:

    Color col;

    RBTreeNode();
    RBTreeNode(int k); //k = key, which in this example is also the value(data)
    ~RBTreeNode(); // when creating a template class, destructor must be virtual

    int key;
    RBTreeNode *left;
    RBTreeNode *right;

    string getColor();
    void setColor(Color c);
    bool isRed();
    bool isBlack();
};

RBTreeNode::RBTreeNode(){
  left = NULL;
  right = NULL;
  col = RED; // new nodes are red
}

RBTreeNode::RBTreeNode(int k){
  key = k;
  left = NULL;
  right = NULL;
  col = RED; // new nodes are red
}

RBTreeNode::~RBTreeNode(){
  // diy
}

string RBTreeNode::getColor(){
  if (this == NULL){ // no object exists --> NULL LEAF NODE here. return black
      return "BLACK";
  }
  if (col == RED){
    return "RED";
  }
  else if (col == BLACK){
    return "BLACK";
  }
  else{
    return "N/A";
  }
}

void RBTreeNode::setColor(Color c){
  col = c;
}

bool RBTreeNode::isRed(){
  if (this == NULL){ // no object exists --> LEAF NODE here. set it to black
      return false;
  }
  return (col == RED);
}

bool RBTreeNode::isBlack(){
  if (this == NULL){ // no object exists --> LEAF NODE here. set it to black
      return true;
  }
  return (col == BLACK);
}
