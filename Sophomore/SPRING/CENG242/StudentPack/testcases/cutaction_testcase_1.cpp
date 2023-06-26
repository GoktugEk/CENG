#include "Node.h"
#include "NodeManager.h"
#include "Action.h"

int main() {

	NodeManager* nm = new NodeManager();
	nm->addRelation(9, 3);
	nm->addRelation(9, 8);
	nm->addRelation(8, 6);
	nm->addRelation(8, 7);
	nm->addRelation(6, 1);
	nm->addRelation(6, 2);

	nm->setDataToNode(7, 'X');
	nm->setDataToNode(1, 'X');
	nm->setDataToNode(2, 'X');

	const Node& root = nm->getNode(9);
	//cout << root << endl;

	Action* action = new CutAction('X');
	Node* cutTree = action->act(&root);

	cout << *cutTree << endl;

	delete action;
	delete cutTree;
	delete nm;

	return 0;
}