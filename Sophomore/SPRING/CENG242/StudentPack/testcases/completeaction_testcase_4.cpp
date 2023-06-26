#include "Node.h"
#include "NodeManager.h"
#include "Action.h"

int main() {

	NodeManager* nm1 = new NodeManager;
	nm1->addRelation(100, 45);
	nm1->setDataToNode(100, 'X');
	nm1->addRelation(45, 19);
	nm1->setDataToNode(45, 'Y');
	nm1->addRelation(45, 18);
	nm1->setDataToNode(18, 'Z');
	nm1->addRelation(45, 50);
	nm1->setDataToNode(95, 'W');
	nm1->addRelation(50, 95);

	NodeManager* nm2 = new NodeManager;
	nm2->addRelation(50, 95);
	nm2->addRelation(45, 18);
	nm2->addRelation(45, 19);
	nm2->addRelation(45, 50);
	nm2->addRelation(100, 45);
	nm2->setDataToNode(100, 'X');
	nm2->setDataToNode(45, 'Y');
	nm2->setDataToNode(18, 'Z');
	nm2->setDataToNode(95, 'W');

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