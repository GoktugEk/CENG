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

        // Testcase 3
        Graph graph;
        Node a, b, c, d, e, f, g, h;
        a.setCountry("a");
        b.setCountry("b");
        c.setCountry("c");
        d.setCountry("d");
        e.setCountry("e");
        f.setCountry("f");
        g.setCountry("g");
        h.setCountry("h");

        a.setVid(1);
        b.setVid(2);
        c.setVid(3);
        d.setVid(4);
        e.setVid(5);
        f.setVid(6);
        g.setVid(7);
        h.setVid(8);

        graph.addNode(a);
        graph.addNode(b);
        graph.addNode(c);
        graph.addNode(d);
        graph.addNode(e);
        graph.addNode(f);
        graph.addNode(g);
        graph.addNode(h);

        graph.addConnection(a, b, 3);
        graph.addConnection(a, c, 6);
        graph.addConnection(b, c, 4);
        graph.addConnection(b, d, 4);
        graph.addConnection(c, d, 8);
        graph.addConnection(c, g, 11);
        graph.addConnection(b, e, 11);
        graph.addConnection(d, e, 4); // in photo it was -4, regard it as 4.
        graph.addConnection(d, f, 5);
        graph.addConnection(d, g, 2);
        graph.addConnection(e, h, 9);
        graph.addConnection(f, h, 1);
        graph.addConnection(g, h, 2);

        cout << "isCyclic" << endl;
        cout << graph.isCyclic() << endl;

        cout << "Least Cost Path: ";
        list<string> res;
        res = graph.findLeastCostPath(a, h);
        list<string>::iterator it;
        for (it = res.begin(); it != res.end(); it++)
            cout << *it << " ";
    }

    return 0;
}
