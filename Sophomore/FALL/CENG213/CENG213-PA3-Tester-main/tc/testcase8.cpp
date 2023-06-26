#include "../solutions/Graph.h"
#include <iostream>
/*You can add additional libraries here to read and process the dataset*/
#include <fstream> // file read/write

using namespace std;

// tester
int main()
{

    // YOU CAN WRITE YOUR TEST CASES BELOW
    //Testcase8
    {
        Graph graph;
        Node A(1, "A", "A", 1);
        Node B(2, "B", "B", 2);
        Node C(3, "C", "C", 3);
        Node D(4, "D", "D", 4);
        Node E(5, "E", "E", 5);
        Node F(6, "F", "F", 6);
        Node G(7, "G", "G", 7);
        Node H(8, "H", "H", 8);

        graph.addNode(A);
        graph.addNode(B);
        graph.addNode(C);
        graph.addNode(D);
        graph.addNode(E);
        graph.addNode(F);
        graph.addNode(G);
        graph.addNode(H);

        graph.addConnection(A, B, 7);
        graph.addConnection(A, C, 4);
        graph.addConnection(A, D, 13);
        graph.addConnection(B, C, 1);
        graph.addConnection(B, D, 5);
        graph.addConnection(C, B, 1);
        graph.addConnection(C, D, 5);
        graph.addConnection(D, E, 4);
        graph.addConnection(E, F, 1);
        graph.addConnection(E, H, 20);
        graph.addConnection(F, G, 2);
        graph.addConnection(F, H, 12);
        graph.addConnection(G, H, 4);
        graph.addConnection(H, G, 4);
        graph.addConnection(G, E, 2);

        std::list<std::string> path = graph.findLeastCostPath(A, H);
        for (const auto &node : path)
        {
            std::cout << node << " ";
        }
        std::cout << std::endl;

        std::cout << graph.isCyclic() << std::endl;

        graph.deleteNode(B);

        std::cout << graph.isCyclic() << std::endl;

        graph.deleteNode(H);

        std::cout << graph.isCyclic() << std::endl;

        //Remove the bridge
        graph.deleteNode(D);

        std::cout << graph.isCyclic() << std::endl;

        graph.deleteNode(F);

        std::cout << graph.isCyclic();

        return 0;
    }

    return 0;
}
