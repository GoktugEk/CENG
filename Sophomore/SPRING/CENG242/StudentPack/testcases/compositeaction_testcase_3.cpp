#include "Node.h"
#include "NodeManager.h"
#include "Action.h"

int main() {

	NodeManager* nm = new NodeManager();
	nm->addRelation(1, 2);
	nm->addRelation(1, 3);
	nm->addRelation(1, 4);
	nm->addRelation(1, 5);
	nm->addRelation(3, 6);
	nm->addRelation(3, 7);
	nm->addRelation(3, 8);
	nm->addRelation(3, 9);
	nm->addRelation(3, 10);
	nm->addRelation(7, 13);
	nm->addRelation(9, 14);
	nm->addRelation(9, 15);
	nm->addRelation(9, 16);
	nm->addRelation(10, 17);
	nm->addRelation(10, 18);
	nm->addRelation(14, 25);
	nm->addRelation(14, 26);
	nm->addRelation(15, 27);
	nm->addRelation(18, 28);
	nm->addRelation(18, 32);
	nm->addRelation(26, 29);
	nm->addRelation(26, 30);
	nm->addRelation(26, 31);
	nm->addRelation(30, 33);
	nm->addRelation(30, 34);
	nm->addRelation(5, 11);
	nm->addRelation(5, 12);
	nm->addRelation(12, 19);
	nm->addRelation(12, 20);
	nm->addRelation(19, 21);
	nm->addRelation(20, 22);
	nm->addRelation(20, 23);
	nm->addRelation(20, 24);
	nm->addRelation(22, 35);
	nm->addRelation(22, 36);
	nm->addRelation(36, 37);

	nm->setDataToNode(33, 'A');
	nm->setDataToNode(28, 'B');
	nm->setDataToNode(27, 'A');
	nm->setDataToNode(21, 'A');
	nm->setDataToNode(23, 'C');
	nm->setDataToNode(35, 'A');
	nm->setDataToNode(37, 'A');
	nm->setDataToNode(30, 'B');
	nm->setDataToNode(31, 'B');
	nm->setDataToNode(25, 'C');
	nm->setDataToNode(13, 'C');

	NodeManager* nm2 = new NodeManager();
	nm2->addRelation(1, 2);
	nm2->addRelation(1, 3);
	nm2->addRelation(1, 4);
	nm2->addRelation(1, 5);
	nm2->addRelation(3, 6);
	nm2->addRelation(3, 7);
	nm2->addRelation(3, 8);
	nm2->addRelation(3, 9);
	nm2->addRelation(3, 10);
	nm2->addRelation(7, 13);
	nm2->addRelation(9, 14);
	nm2->addRelation(9, 15);
	nm2->addRelation(9, 16);
	nm2->addRelation(10, 17);
	nm2->addRelation(10, 18);
	nm2->addRelation(14, 25);
	nm2->addRelation(14, 26);
	nm2->addRelation(15, 27);
	nm2->addRelation(18, 28);
	nm2->addRelation(18, 32);
	nm2->addRelation(26, 29);
	nm2->addRelation(26, 30);
	nm2->addRelation(26, 31);
	nm2->addRelation(30, 33);
	nm2->addRelation(30, 34);
	nm2->addRelation(5, 11);
	nm2->addRelation(5, 12);
	nm2->addRelation(12, 19);
	nm2->addRelation(12, 20);
	nm2->addRelation(19, 21);
	nm2->addRelation(20, 22);
	nm2->addRelation(20, 23);
	nm2->addRelation(20, 24);
	nm2->addRelation(22, 35);
	nm2->addRelation(22, 36);
	nm2->addRelation(36, 37);

	nm2->setDataToNode(17, 'B');
	nm2->setDataToNode(19, 'C');
	nm2->setDataToNode(27, 'C');

	const Node& root = nm->getNode(1);
	const Node& root2 = nm2->getNode(1);

	Action* action1 = new CompleteAction(root2);
	Action* action2 = new CutAction('B');
	Action* action3 = new CutAction('C');
	
	CompositeAction* action = new CompositeAction();
	action->addAction(action1)->addAction(action2)->addAction(action3);

	Node* finalTree = action->act(&root);

	cout << *finalTree << endl;



	delete action;
	delete action1;
	delete action2;
	delete action3;
	delete nm;
	delete nm2;
	delete finalTree;

	return 0;
}