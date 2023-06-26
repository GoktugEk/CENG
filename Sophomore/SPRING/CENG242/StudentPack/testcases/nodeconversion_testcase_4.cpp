#include "Node.h"
#include "NodeManager.h"

int main() {

	NodeManager* nm = new NodeManager();
	nm->addRelation(50, 10);
	nm->addRelation(50, 20);
	nm->setDataToNode(50, '*');
	nm->addRelation(10, 48);
	nm->addRelation(48, 14);
	nm->setDataToNode(4, '?');
	nm->addRelation(20, 4);
	nm->addRelation(20, 5);
	nm->addRelation(20, 6);
	nm->setDataToNode(10, 'x');

	const Node& root = nm->getNode(50);
	cout << root << endl;
	delete nm;

	return 0;
}