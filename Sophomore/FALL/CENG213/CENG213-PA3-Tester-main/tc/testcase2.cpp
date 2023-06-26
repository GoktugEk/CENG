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
        Graph case2;

        Node A(1, "A", "1", 1), B(2, "B", "1", 2), C(3, "C", "1", 3), D(4, "D", "2", 4), E(5, "E", "2", 5),
            F(6, "F", "2", 6), G(7, "G", "3", 7), H(8, "H", "4", 8), I(9, "I", "5", 0), J(10, "J", "6", 25);

        case2.addNode(A);
        case2.addNode(B);
        case2.addNode(C);
        case2.addNode(D);
        case2.addNode(E);
        case2.addNode(F);
        case2.addNode(G);
        case2.addNode(H);
        case2.addNode(I);
        case2.addNode(J);

        case2.addConnection(A, B, 10);
        case2.addConnection(A, F, 1);
        case2.addConnection(A, H, 1);
        case2.addConnection(B, C, 10);
        case2.addConnection(B, G, 5);
        case2.addConnection(C, J, 5);
        case2.addConnection(C, D, 15);
        case2.addConnection(D, G, 5);
        case2.addConnection(D, E, 1);
        case2.addConnection(E, I, 10);
        case2.addConnection(F, G, 20);
        case2.addConnection(F, E, 10);
        case2.addConnection(G, A, 15);
        case2.addConnection(G, C, 5);
        case2.addConnection(G, E, 10);
        case2.addConnection(H, A, 60);
        case2.addConnection(I, E, 70);
        case2.addConnection(J, C, 90);

        //add test cases

        list<string> res;
        res = case2.getBFSPath(A, E);
        std::cout << "BFS PATH BETWEEN A AND E" << std::endl;
        list<string>::iterator it;
        for (it = res.begin(); it != res.end(); it++)
            std::cout << *it << " ";
        std::cout << std::endl;

        std::list<string> path;
        path = case2.findLeastCostPath(A, G);
        std::cout << "LeastCostPath:" << std::endl;
        auto iter = path.begin();
        for (iter; iter != path.end(); iter++)
        {
            std::cout << *iter << "  ";
        }
        std::cout << std::endl;
        std::cout << "LeastCostPath:" << std::endl;
        path = case2.findLeastCostPath(J, E);
        auto iter1 = path.begin();
        for (iter1; iter1 != path.end(); iter1++)
        {
            std::cout << *iter1 << "  ";
        }
        std::cout << std::endl;
        std::cout << "isCyclic ?  --->  " << case2.isCyclic() << std::endl;
        case2.deleteNode(J);
        std::cout << "isCyclic ?  --->  " << case2.isCyclic() << std::endl;
        case2.deleteNode(H);
        std::cout << "isCyclic ?  --->  " << case2.isCyclic() << std::endl;
        case2.deleteNode(I);
        std::cout << "isCyclic ?  --->  " << case2.isCyclic() << std::endl;
        case2.deleteNode(G);
        std::cout << "isCyclic ?  --->  " << case2.isCyclic();
    }

    return 0;
}
