#include "Node.h"
#include "NodeManager.h"


// addRelation() AND getNode() TEST
int main() {

	NodeManager* nodeManager = new NodeManager();
	nodeManager->addRelation(10, 12);
	nodeManager->addRelation(3, 10);
	nodeManager->addRelation(12, 2);
	nodeManager->addRelation(3, 5);

	nodeManager->setDataToNode(5, 'A');

	nodeManager->addRelation(5, 40);
	nodeManager->addRelation(5, 37);
	nodeManager->addRelation(37, 20);
	nodeManager->addRelation(12, 9);

	nodeManager->setDataToNode(9, 'B');
	nodeManager->setDataToNode(38, 'C');

	nodeManager->addRelation(12, 39);
	nodeManager->addRelation(22, 38);
	nodeManager->addRelation(39, 15);
	nodeManager->addRelation(3, 22);
	nodeManager->addRelation(22, 4);

	const Node& node = nodeManager->getNode(3);	// const Node& node
	cout << node << endl;
	delete nodeManager;

	return 0;
}