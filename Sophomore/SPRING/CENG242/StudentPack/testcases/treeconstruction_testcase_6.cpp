#include "Node.h"
#include "NodeManager.h"

int main() {

	NodeManager* nm = new NodeManager;
	nm->addRelation(1, 2);
	nm->addRelation(2, 3);
	nm->addRelation(10, 9);
	nm->addRelation(10, 8);
	nm->addRelation(10, 7);

	nm->addRelation(9, 90);
	nm->addRelation(8, 80);
	nm->addRelation(6, 60);
	nm->addRelation(1, 6);

	nm->addRelation(25, 10);
	nm->addRelation(45, 35);
	
	const Node& root = nm->getNode(1);
	cout << root << endl;

	const Node& root2 = nm->getNode(25);
	cout << root2 << endl;

	const Node& root3 = nm->getNode(45);
	cout << root3 << endl;

	delete nm;

	return 0;
}
