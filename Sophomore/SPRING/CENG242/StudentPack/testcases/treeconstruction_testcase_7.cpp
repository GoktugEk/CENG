#include "Node.h"
#include "NodeManager.h"

int main() {

	NodeManager* nm = new NodeManager;
	nm->addRelation(100, 99);
	nm->addRelation(98, 97);
	nm->addRelation(96, 95);
	nm->addRelation(94, 93);
	nm->addRelation(92, 100);
	nm->addRelation(91, 98);
	nm->addRelation(90, 96);
	nm->addRelation(89, 94);
	nm->addRelation(88, 89);
	nm->addRelation(88, 90);
	nm->addRelation(87, 91);
	nm->addRelation(87, 92);
	
	const Node& root = nm->getNode(87);
	cout << root << endl;

	const Node& root2 = nm->getNode(88);
	cout << root2 << endl;

	delete nm;

	return 0;
}
