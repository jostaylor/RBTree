#include <iostream>
#include "RBTree.h"

using namespace std;

int main(int argc, char** argv){
  cout << "test main" << endl;

  RBTree *myTree = new RBTree();

  myTree->insert(69);
  myTree->insert(12);
  myTree->insert(30);
  myTree->insert(47);
  myTree->insert(4);
  myTree->insert(96);
  myTree->printTree();
  myTree->deleteNode(12);
  myTree->printTree();
  myTree->deleteNode(4);
  myTree->printTree();
  /*
  myTree->insert(22);
  myTree->insert(12);
  myTree->insert(30);
  myTree->printTree();
  myTree->insert(40);
  myTree->printTree();
  myTree->insert(50);
  myTree->printTree();
  myTree->insert(60);
  myTree->printTree();
  myTree->insert(70);
  myTree->printTree();
  myTree->insert(80);
  myTree->printTree();
  myTree->insert(35);
  myTree->insert(10);
  myTree->insert(5);
  myTree->insert(15);
  myTree->insert(17);
  myTree->printTree();
  myTree->insert(11);
  myTree->printTree();
  myTree->insert(95);
  myTree->insert(96);
  myTree->insert(97);
  myTree->insert(98);
  myTree->insert(99);
  myTree->insert(75);
  myTree->insert(76);
  myTree->insert(77);
  myTree->printTree();
  */

  return 0;
}
