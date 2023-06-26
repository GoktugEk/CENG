#include "Node.h"
#include "NodeManager.h"
#include "Action.h"

int main() {

	NodeManager* nm1 = new NodeManager;
	nm1->addRelation(100, 1);
	nm1->addRelation(100, 2);
	nm1->addRelation(100, 3);
	nm1->setDataToNode(3, 'A');
	nm1->addRelation(1, 4);
	nm1->addRelation(1, 5);

	NodeManager* nm2 = new NodeManager;
	nm2->addRelation(100, 1);
	nm2->addRelation(100, 2);
	nm2->addRelation(100, 3);
	nm2->addRelation(1, 4);
	nm2->setDataToNode(4, 'B');
	nm2->addRelation(1, 5);

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