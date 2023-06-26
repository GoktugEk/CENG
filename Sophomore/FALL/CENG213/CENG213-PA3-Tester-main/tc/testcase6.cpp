#include "../solutions/Graph.h"
#include <iostream>
/*You can add additional libraries here to read and process the dataset*/
#include <fstream> // file read/write

using namespace std;

// tester
int main()
{

    // YOU CAN WRITE YOUR TEST CASES BELOW
    {

        //testcase 6
        Graph graph;
        Node A(1, "A", "M8", 31);
        Node B(2, "B", "M8", 31);
        Node C(3, "C", "M8", 31);
        Node D(4, "D", "M8", 31);
        Node E(5, "E", "M8", 31);
        Node F(6, "F", "M8", 31);
        Node G(7, "G", "M8", 31);
        Node H(8, "H", "M8", 31);
        Node I(9, "I", "M8", 31);
        Node J(10, "J", "M8", 31);
        Node K(11, "K", "M8", 31);
        Node L(12, "L", "M8", 31);
        Node M(13, "M", "M8", 31);
        Node N(14, "N", "M8", 31);
        Node O(15, "O", "M8", 31);
        Node Z(26, "Z", "M8", 31);

        graph.addNode(A);
        graph.addNode(B);
        graph.addNode(C);
        graph.addNode(D);
        graph.addNode(E);
        graph.addNode(F);
        graph.addNode(G);
        graph.addNode(H);
        graph.addNode(I);
        graph.addNode(J);
        graph.addNode(K);
        graph.addNode(L);
        graph.addNode(M);
        graph.addNode(N);
        graph.addNode(O);
        graph.addNode(Z);

        graph.addConnection(A, B, 1);

        graph.addConnection(B, C, 1);
        graph.addConnection(B, D, 20);

        graph.addConnection(C, H, 1);
        graph.addConnection(C, E, 10);
        graph.addConnection(C, Z, 20);

        graph.addConnection(D, Z, 20);
        graph.addConnection(D, F, 20);

        graph.addConnection(E, G, 10);

        graph.addConnection(F, G, 40);

        graph.addConnection(G, Z, 10);
        graph.addConnection(G, L, 1);

        graph.addConnection(H, I, 1);
        graph.addConnection(H, C, 1);

        graph.addConnection(I, E, 40);
        graph.addConnection(I, J, 1);

        graph.addConnection(J, K, 1);

        graph.addConnection(K, G, 1);
        graph.addConnection(K, O, 1);

        graph.addConnection(M, L, 1);

        graph.addConnection(N, F, 1);

        list<string> res;
        res = graph.findLeastCostPath(A, G);
        list<string>::iterator it;
        for (it = res.begin(); it != res.end(); it++)
            cout << *it << ' ';
        cout << endl;

        cout << graph.isCyclic() << endl;

        graph.deleteNode(C);

        cout << graph.isCyclic() << endl;

        res = graph.findLeastCostPath(A, G);
        for (it = res.begin(); it != res.end(); it++)
            cout << *it << ' ';
    }

    return 0;
}
