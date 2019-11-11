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

void RBTreeNode::setColor(Color c){
  col = c;
}

bool RBTreeNode::isRed(){
  return (col == RED);
}

bool RBTreeNode::isBlack(){
  return (col == BLACK);
}
