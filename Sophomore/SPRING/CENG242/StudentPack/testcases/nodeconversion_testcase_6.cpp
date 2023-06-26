#include "Node.h"
#include "NodeManager.h"

int main() {

	NodeManager* nm = new NodeManager();
	nm->setDataToNode(50, '*');
	nm->addRelation(50, 10);
	nm->setDataToNode(10, '*');
	nm->setDataToNode(20, '*');
	nm->addRelation(50, 20);
	nm->setDataToNode(48, '*');
	nm->addRelation(10, 48);
	nm->addRelation(48, 14);
	nm->setDataToNode(14, '*');
	nm->addRelation(20, 4);
	nm->setDataToNode(4, '*');
	nm->setDataToNode(5, '*');
	nm->addRelation(20, 5);
	nm->addRelation(20, 6);
	nm->setDataToNode(6, '*');

	const Node& root = nm->getNode(50);
	cout << root << endl;
	delete nm;

	return 0;
}