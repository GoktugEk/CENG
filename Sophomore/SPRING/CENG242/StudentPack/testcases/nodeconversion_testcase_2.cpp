#include "Node.h"
#include "NodeManager.h"

int main() {

	NodeManager* nm = new NodeManager();
	nm->addRelation(10, 1);
	nm->setDataToNode(10, '*');

	const Node& root = nm->getNode(10);
	cout << root << endl;
	delete nm;

	return 0;
}