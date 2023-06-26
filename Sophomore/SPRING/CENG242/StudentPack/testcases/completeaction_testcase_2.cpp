#include "Node.h"
#include "NodeManager.h"
#include "Action.h"

int main() {

	NodeManager* nm1 = new NodeManager;
	nm1->addRelation(100, 1);
	nm1->addRelation(100, 2);
	nm1->addRelation(100, 3);
	nm1->addRelation(50, 10);
	nm1->addRelation(50, 20);
	nm1->addRelation(20, 4);
	nm1->addRelation(48, 14);
	nm1->addRelation(10, 48);
	nm1->addRelation(19, 50);
	nm1->addRelation(20, 5);
	nm1->addRelation(2, 19);
	nm1->addRelation(3, 23);

	NodeManager* nm2 = new NodeManager;
	nm2->addRelation(100, 1);
	nm2->addRelation(100, 2);
	nm2->addRelation(100, 3);
	nm2->setDataToNode(1, 'A');
	nm2->addRelation(50, 10);
	nm2->addRelation(50, 20);
	nm2->setDataToNode(20, 'B');
	nm2->addRelation(20, 4);
	nm2->setDataToNode(14, 'C');
	nm2->addRelation(48, 14);
	nm2->addRelation(10, 48);
	nm2->addRelation(19, 50);
	nm2->addRelation(20, 5);
	nm2->addRelation(2, 19);
	nm2->addRelation(3, 23);

	const Node& root1 = nm1->getNode(100);
	const Node& root2 = nm2->getNode(100);

	//cout << root1 << endl;
	//cout << root2 << endl;
	
	Action* action = new CompleteAction(root1);
	Node* completeTree = action->act(&root2);

	cout << *completeTree << endl;
	
	delete action;
	delete completeTree;
	delete nm1;
	delete nm2;

	return 0;
}