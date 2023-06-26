#include "Node.h"
#include "NodeManager.h"
#include "Action.h"

int main() {

	NodeManager* nm = new NodeManager();
	nm->addRelation(1, 2);
	nm->addRelation(1, 5);
	nm->addRelation(1, 3);
	nm->addRelation(2, 10);
	nm->addRelation(2, 20);
	nm->addRelation(10, 15);
	nm->addRelation(10, 25);
	nm->addRelation(3, 30);
	nm->addRelation(30, 33);
	nm->addRelation(30, 66);
	nm->addRelation(30, 99);
	nm->addRelation(33, 100);

	nm->setDataToNode(15, '?');
	nm->setDataToNode(20, '?');
	nm->setDataToNode(99, '?');
	nm->setDataToNode(100, '?');

	const Node& root = nm->getNode(1);
	//cout << root << endl;

	Action* action = new CutAction('?');
	Node* cutTree = action->act(&root);

	cout << *cutTree << endl;

	delete action;
	delete cutTree;
	delete nm;

	return 0;
}