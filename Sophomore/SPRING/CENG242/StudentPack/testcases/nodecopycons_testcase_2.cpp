#include "Node.h"

int main() {

	Node* root = new Node(50);
	Node* n1 = new Node(10);
	Node* n2 = new Node(20);
	Node* n3 = new Node(47);
	Node* n4 = new DataNode(48, 'A');
	Node* n5 = new Node(49);
	Node* n6 = new Node(14);
	Node* n7 = new DataNode(4, 'B');
	Node* n8 = new Node(5);


	*root += *n1;
	*root += *n2;
	*n1 += *n3;
	*n1 += *n4;
	*n1 += *n5;
	*n4 += *n6;
	*n2 += *n7;
	*n2 += *n8;

	cout << *root << endl;
	Node* copy = new Node(*root);
	cout << *copy << endl;

	delete root;
	delete copy;

	return 0;
}