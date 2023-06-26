#include "Node.h"
#include "NodeManager.h"

int main() {

	NodeManager* nm = new NodeManager;
	nm->addRelation(100, 50);
	nm->addRelation(100, 75);
	nm->addRelation(75, 15);
	nm->addRelation(75, 5);
	nm->addRelation(50, 10);
	nm->addRelation(50, 9);
	nm->addRelation(50, 8);
	
	const Node& root = nm->getNode(100);
	cout << root << endl;

	delete nm;

	return 0;
}
