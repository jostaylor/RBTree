#include <iostream>

using namespace std;

class TreeNode{
  public:
    TreeNode();
    TreeNode(int k); //k = key, which in this example is also the value(data)
    ~TreeNode(); // when creating a template class, destructor must be virtual

    int key;
    TreeNode *left;
    TreeNode *right;
};

TreeNode::TreeNode(){
  left = NULL;
  right = NULL;
}

TreeNode::TreeNode(int k){
  key = k;
  left = NULL;
  right = NULL;
}

TreeNode::~TreeNode(){
  // diy
}
