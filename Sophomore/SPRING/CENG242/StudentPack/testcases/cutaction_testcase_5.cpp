#include "Node.h"
#include "NodeManager.h"
#include "Action.h"

int main() {

	NodeManager* nm = new NodeManager();
	nm->addRelation(100, 20);
	nm->addRelation(100, 50);
	nm->addRelation(100, 10);
	nm->addRelation(20, 3);
	nm->addRelation(20, 7);
	nm->addRelation(7, 5);
	nm->addRelation(7, 4);
	nm->addRelation(50, 1);
	nm->addRelation(50, 90);
	nm->addRelation(90, 8);
	nm->addRelation(8, 6);
	nm->addRelation(8, 70);
	nm->addRelation(6, 60);
	nm->addRelation(6, 80);
	nm->addRelation(10, 2);
	nm->addRelation(2, 30);
	nm->addRelation(2, 40);
	nm->addRelation(2, 9);
	nm->addRelation(40, 242);

	nm->setDataToNode(5, '*');
	nm->setDataToNode(60, '*');
	nm->setDataToNode(80, '*');
	nm->setDataToNode(70, '*');
	nm->setDataToNode(242, '*');
	nm->setDataToNode(9, '*');

	const Node& root = nm->getNode(100);
	//cout << root << endl;

	Action* action = new CutAction('*');
	Node* cutTree = action->act(&root);

	cout << *cutTree << endl;

	delete action;
	delete cutTree;
	delete nm;

	return 0;
}