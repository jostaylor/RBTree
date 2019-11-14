#include <iostream>
#include "RBTree.h"

using namespace std;

int main(int argc, char** argv){
  cout << "test main" << endl;

  RBTree *myTree = new RBTree();

  myTree->insert(34);
  myTree->insert(56);
  myTree->insert(30);
  myTree->insert(20);
  myTree->insert(10);
  myTree->insert(50);
  myTree->insert(42);
  myTree->insert(85);
  myTree->insert(5);
  myTree->insert(2);
  myTree->insert(100);
  myTree->insert(101);
  myTree->printTree();
  myTree->insert(102);
  myTree->insert(103);
  myTree->insert(104);
  myTree->insert(105);
  myTree->insert(110);
  myTree->insert(120);
  myTree->insert(130);
  myTree->insert(140);
  myTree->insert(280);
  myTree->insert(281);
  myTree->insert(282);
  myTree->insert(283);
  myTree->insert(284);
  myTree->insert(285);
  myTree->insert(286);
  myTree->insert(287);
  myTree->insert(288);
  myTree->insert(288); // Node already in tree, node not added
  myTree->printTree();
  myTree->printTree();
  myTree->deleteNode(34); // Case 4 -> Left Left
  myTree->printTree();
  myTree->deleteNode(56); // Case 3 -> Black, Case 4 -> Right Right
  myTree->printTree();
  myTree->deleteNode(30); // node is correct color, move on without correction
  myTree->printTree();
  myTree->deleteNode(20); // single color shift to black
  myTree->printTree();
  myTree->deleteNode(280);
  myTree->printTree();
  myTree->deleteNode(281);
  myTree->printTree();
  myTree->deleteNode(282); // Case 4 -> Left Right and Left Left
  myTree->printTree();
  myTree->deleteNode(283);
  myTree->printTree();
  myTree->deleteNode(284);
  myTree->printTree();
  myTree->deleteNode(285);
  myTree->printTree();
  myTree->deleteNode(286); // Case 3 -> Red
  myTree->printTree();
  myTree->deleteNode(287);
  myTree->printTree();
  myTree->deleteNode(288); // Case 1 (root)
  myTree->printTree();
  myTree->deleteNode(10);
  myTree->printTree();
  myTree->deleteNode(50);
  myTree->printTree();
  myTree->deleteNode(42);
  myTree->printTree();
  myTree->deleteNode(85);
  myTree->printTree();
  myTree->deleteNode(5); // Case 2
  myTree->printTree();
  myTree->deleteNode(100);
  myTree->printTree();
  myTree->deleteNode(101); // Case 4 -> Right Left and Right Right
  myTree->printTree();
  myTree->deleteNode(102);
  myTree->printTree();
  myTree->deleteNode(103);
  myTree->printTree();
  myTree->deleteNode(104);
  myTree->printTree();
  myTree->deleteNode(105);
  myTree->printTree();
  myTree->deleteNode(110);
  myTree->printTree();
  myTree->deleteNode(120);
  myTree->printTree();
  myTree->deleteNode(130);
  myTree->printTree();
  myTree->deleteNode(140);
  myTree->printTree();
  myTree->deleteNode(3); // deleting node that doesn't exist
  myTree->deleteNode(2); // deleting LAST node
  myTree->printTree();
  myTree->deleteNode(2); // delete from an empty tree

  // All cases met except fixDoubleRed 2.1 and 2.2
  // Attempting to satisfy with new tree inserts
  myTree->insert(500);
  myTree->insert(400);
  myTree->insert(600);
  myTree->insert(300);
  myTree->insert(200);
  myTree->insert(100);
  myTree->insert(700);
  myTree->insert(450);
  myTree->insert(650); // Case 2.1
  myTree->insert(10);
  myTree->insert(12);
  myTree->insert(11);
  myTree->insert(13);
  myTree->insert(14);
  myTree->insert(15); // Case 2.2
  myTree->printTree();

  delete myTree;
  
  return 0;
}
