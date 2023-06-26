#include "Node.h"
#include "NodeManager.h"
#include "Action.h"

// COMPLETE ACTION TEST
int main() {

	// A new NodeManager : nm1
	NodeManager* nm1 = new NodeManager();
	nm1->addRelation(10, 2);
	nm1->addRelation(8, 6);
	nm1->addRelation(8, 70);
	nm1->addRelation(6, 60);
	
	nm1->setDataToNode(50, 'A');
	nm1->setDataToNode(2, 'C');
	nm1->setDataToNode(60, 'E');
	nm1->setDataToNode(5, 'B');
	
	nm1->addRelation(7, 5);
	nm1->addRelation(7, 4);
	nm1->addRelation(20, 3);
	nm1->addRelation(20, 7);
	nm1->addRelation(100, 50);
	nm1->addRelation(50, 1);
	nm1->addRelation(100, 10);
	
	nm1->setDataToNode(70, 'D');
	nm1->setDataToNode(9, 'F');

	nm1->addRelation(2, 30);
	nm1->addRelation(2, 40);
	nm1->addRelation(2, 9);
	nm1->addRelation(100, 20);
	nm1->addRelation(50, 90);
	nm1->addRelation(90, 8);
	nm1->addRelation(6, 80);
	
	// A new NodeManager : nm2
	NodeManager* nm2 = new NodeManager();
	nm2->addRelation(10, 2);
	nm2->addRelation(8, 6);
	nm2->addRelation(8, 70);
	nm2->addRelation(6, 60);

	nm2->setDataToNode(50, 'A');
	nm2->setDataToNode(2, 'C');
	nm2->setDataToNode(100, 'G');
	nm2->setDataToNode(1, 'I');

	nm2->addRelation(7, 5);
	nm2->addRelation(7, 4);
	nm2->addRelation(20, 3);
	nm2->addRelation(20, 7);
	nm2->addRelation(100, 50);
	nm2->addRelation(50, 1);
	nm2->addRelation(100, 10);

	nm2->setDataToNode(10, 'H');
	nm2->setDataToNode(40, 'K');
	nm2->setDataToNode(80, 'J');

	nm2->addRelation(2, 30);
	nm2->addRelation(2, 40);
	nm2->addRelation(2, 9);
	nm2->addRelation(100, 20);
	nm2->addRelation(50, 90);
	nm2->addRelation(90, 8);
	nm2->addRelation(6, 80);
	
	const Node& root1 = nm1->getNode(100);
	const Node& root2 = nm2->getNode(100);

	cout << root1 << endl;
	cout << root2 << endl;
	
	Action* action = new CompleteAction(root1);
	Node* completeTree = action->act(&root2);

	cout << *completeTree << endl;
	
	delete action;
	delete completeTree;
	delete nm1;
	delete nm2;
	
	return 0;
}