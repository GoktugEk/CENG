#include "Node.h"
#include "NodeManager.h"
#include "Action.h"

int main() {

	NodeManager* nm = new NodeManager();
	nm->addRelation(1, 2);
	nm->addRelation(1, 5);
	nm->addRelation(1, 3);
	nm->addRelation(2, 4);
	nm->addRelation(2, 6);
	nm->addRelation(4, 7);
	nm->addRelation(4, 8);
	nm->addRelation(5, 9);
	nm->addRelation(5, 10);
	nm->addRelation(10, 11);
	nm->addRelation(11, 12);
	nm->addRelation(11, 13);
	nm->addRelation(12, 14);
	nm->addRelation(12, 15);
	nm->addRelation(3, 16);
	nm->addRelation(16, 17);
	nm->addRelation(16, 18);
	nm->addRelation(16, 19);
	nm->addRelation(17, 20);

	nm->setDataToNode(7, '%');
	nm->setDataToNode(13, '%');
	nm->setDataToNode(14, '%');
	nm->setDataToNode(15, '%');
	nm->setDataToNode(19, '%');
	nm->setDataToNode(20, '%');

	const Node& root = nm->getNode(1);
	//cout << root << endl;

	Action* action = new CutAction('%');
	Node* cutTree = action->act(&root);

	cout << *cutTree << endl;

	delete action;
	delete cutTree;
	delete nm;

	return 0;
}