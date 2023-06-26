#include "Node.h"

// OPERATOR& TEST
int main() {

	Node* n = new Node(10);
	Node* dn = new DataNode(10, 'A');

	Node* out = *n & *dn;
	cout << *out << endl;

	Node* out2 = *dn & *n;
	cout << *out2 << endl;

	delete n;
	delete dn;
	delete out;
	delete out2;

	return 0;
}

