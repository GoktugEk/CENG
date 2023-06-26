#include "Node.h"
#include "NodeManager.h"

int main() {

	NodeManager* nm = new NodeManager;
	nm->addRelation(100, 50);
	nm->addRelation(50, 75);
	
	const Node& root = nm->getNode(100);
	cout << root << endl;

	delete nm;

	return 0;
}
