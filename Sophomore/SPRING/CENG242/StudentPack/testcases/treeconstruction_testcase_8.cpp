#include "Node.h"
#include "NodeManager.h"

int main() {

	NodeManager* nm = new NodeManager;
	nm->addRelation(1, 2);
	nm->addRelation(3, 4);
	nm->addRelation(3, 1);
	nm->addRelation(3, 5);
	nm->addRelation(5, 10);
	nm->addRelation(100, 95);
	nm->addRelation(90, 85);
	nm->addRelation(80, 75);
	nm->addRelation(80, 70);
	nm->addRelation(80, 65);
	nm->addRelation(5, 80);
	nm->addRelation(50, 45);
	nm->addRelation(45, 19);
	nm->addRelation(45, 18);
	nm->addRelation(45, 100);
	
	const Node& root = nm->getNode(3);
	cout << root << endl;

	const Node& root2 = nm->getNode(50);
	cout << root2 << endl;

	const Node& root3 = nm->getNode(90);
	cout << root3 << endl;

	const Node& not_root = nm->getNode(80);
	cout << not_root << endl;

	delete nm;

	return 0;
}
