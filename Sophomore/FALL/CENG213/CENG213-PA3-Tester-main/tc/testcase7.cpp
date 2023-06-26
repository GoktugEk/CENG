#include "../solutions/Graph.h"
#include <iostream>
/*You can add additional libraries here to read and process the dataset*/
#include <fstream> // file read/write

using namespace std;

// tester
int main()
{

    // YOU CAN WRITE YOUR TEST CASES BELOW
    //Testcase7
    {
        Graph case3;

        Node A(1, "A", "1", 1), B(2, "B", "1", 2), C(3, "C", "1", 3), D(4, "D", "2", 4);
        case3.addNode(A);
        case3.addNode(B);
        case3.addNode(C);
        case3.addNode(D);

        case3.addConnection(A, C, 20);
        case3.addConnection(A, B, 60);
        case3.addConnection(A, D, 35);
        case3.addConnection(C, B, 30), case3.addConnection(D, B, 10);

        list<string> fuq = case3.findLeastCostPath(A, B);

        for (auto it = fuq.begin(); it != fuq.end(); it++)
            cout << *it << " ";
    }

    return 0;
}
