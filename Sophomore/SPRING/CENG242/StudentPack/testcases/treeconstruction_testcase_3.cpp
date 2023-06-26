#include "Node.h"
#include "NodeManager.h"

int main() {

	NodeManager* nm = new NodeManager;
	nm->addRelation(10, 50);
	nm->addRelation(50, 75);
	nm->addRelation(10, 100);
	nm->addRelation(50, 60);
	nm->addRelation(75, 5);
	
	const Node& root = nm->getNode(10);
	cout << root << endl;

	delete nm;

	return 0;
}
