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

        /*CASE 1*/

        {
            // testcase 4
            Graph graph;
            Node a, b, c, d, e, f, g, h;
            a.setCountry("a");
            b.setCountry("b");
            c.setCountry("c");
            d.setCountry("d");
            e.setCountry("e");

            a.setVid(1);
            b.setVid(2);
            c.setVid(3);
            d.setVid(4);
            e.setVid(5);

            graph.addNode(a);
            graph.addNode(b);
            graph.addNode(c);
            graph.addNode(d);
            graph.addNode(e);

            graph.addConnection(a, b, 4);
            graph.addConnection(a, c, 1);
            graph.addConnection(c, b, 2);
            graph.addConnection(b, d, 1);
            graph.addConnection(c, d, 5);
            graph.addConnection(d, e, 3);

            cout << "isCyclic" << endl;
            cout << graph.isCyclic() << endl;

            cout << "Least Cost Path: ";
            list<string> res;
            res = graph.findLeastCostPath(a, e);
            list<string>::iterator it;
            for (it = res.begin(); it != res.end(); it++)
                cout << *it << " ";
        }
    }

    return 0;
}
