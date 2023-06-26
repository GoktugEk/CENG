#include "Node.h"
#include "NodeManager.h"

int main() {

	NodeManager* nm = new NodeManager;
	nm->addRelation(100, 1);
	nm->addRelation(100, 2);
	nm->addRelation(100, 3);
	nm->addRelation(50, 10);
	nm->addRelation(50, 20);
	nm->addRelation(20, 4);
	nm->addRelation(48, 14);
	nm->addRelation(10, 48);
	nm->addRelation(19, 50);
	nm->addRelation(20, 5);
	nm->addRelation(2, 19);
	nm->addRelation(3, 23);
	
	const Node& root = nm->getNode(100);
	cout << root << endl;

	delete nm;

	return 0;
}
