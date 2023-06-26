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
        Graph case1;

        Node A(1, "A", "1", 1), B(2, "B", "1", 2), C(3, "C", "1", 3), D1(41, "D1", "2", 4), D2(42, "D2", "2", 4), D3(43, "D3", "2", 4),
            E(5, "E", "2", 5), F(6, "F", "2", 6), G(7, "G", "3", 7), H(8, "H", "4", 8);

        case1.addNode(A);
        case1.addNode(B);
        case1.addNode(C);
        case1.addNode(D1);
        case1.addNode(D2);
        case1.addNode(D3);
        case1.addNode(E);
        case1.addNode(F);
        case1.addNode(G);
        case1.addNode(H);

        case1.addConnection(A, B, 100);
        case1.addConnection(B, C, 120);
        case1.addConnection(C, B, 100);
        case1.addConnection(C, D1, 50);
        case1.addConnection(D1, D2, 100);
        case1.addConnection(D2, D3, 70);
        case1.addConnection(D3, D1, 80);
        case1.addConnection(C, E, 5000);
        case1.addConnection(E, F, 10);
        case1.addConnection(E, G, 90);
        case1.addConnection(E, H, 500);
        case1.addConnection(G, H, 10);

        cout << case1.isCyclic() << '\n';

        case1.deleteNode(C);

        cout << case1.isCyclic() << '\n';

        case1.deleteNode(D1);

        cout << case1.isCyclic() << '\n';

        case1.deleteNode(E);

        cout << case1.isCyclic();
    }

    return 0;
}
