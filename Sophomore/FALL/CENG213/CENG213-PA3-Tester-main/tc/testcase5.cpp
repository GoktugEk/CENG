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

        //testcase 5
        Graph graph;
        Node a, b, c, d, e, f, g, h;
        a.setCountry("a");
        b.setCountry("b");
        c.setCountry("c");
        d.setCountry("d");
        e.setCountry("e");
        f.setCountry("f");

        a.setVid(1);
        b.setVid(2);
        c.setVid(3);
        d.setVid(4);
        e.setVid(5);
        e.setVid(6);

        graph.addNode(a);
        graph.addNode(b);
        graph.addNode(c);
        graph.addNode(d);
        graph.addNode(e);
        graph.addNode(f);

        graph.addConnection(a, b, 5);
        graph.addConnection(a, c, 1);
        graph.addConnection(c, b, 3);
        graph.addConnection(b, c, 2);
        graph.addConnection(c, e, 12);
        graph.addConnection(b, d, 3);
        graph.addConnection(b, e, 20);
        graph.addConnection(d, c, 3);
        graph.addConnection(d, e, 2);
        graph.addConnection(e, f, 1);
        graph.addConnection(d, f, 6);

        cout << "isCyclic" << endl;
        cout << graph.isCyclic() << endl;

        cout << "Least Cost Path: ";
        list<string> res;
        res = graph.findLeastCostPath(a, f);
        list<string>::iterator it;
        for (it = res.begin(); it != res.end(); it++)
            cout << *it << " ";
    }

    return 0;
}
