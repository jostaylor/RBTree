#include <iostream>
#include "RBTree.h"

using namespace std;

int main(int argc, char** argv){
  cout << "test main" << endl;

  RBTree *myTree = new RBTree();
  myTree->insert(22);
  myTree->insert(12);
  myTree->insert(30);
  myTree->printTree();

  return 0;
}
