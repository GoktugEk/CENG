#include "Graph.h"

/*Do not add new libraries or files*/


Graph::Graph() {
    // TODO: IMPLEMENT THIS FUNCTION.

}

Graph::Graph(const Graph& rhs) {
    this->adjList = rhs.adjList;

}

Graph& Graph::operator=(const Graph& rhs) {
    this->adjList = rhs.adjList;

    return *this;

}

Graph::~Graph() {

}


void Graph::addNode(const Node &node) {
    list<Edge> theList;
    this->adjList.Insert(node.getCountry(), theList);

}

void Graph::addConnection(const Node& headNode, const Node& tailNode, int import) {
    Edge theEdge(tailNode,import);

    adjList.Get(headNode.getCountry()).push_back(theEdge);

}

list<Node> Graph::getAdjacentNodes(const Node& node) {
    list<Node> theList;
    list<Edge> mainList = adjList.Get(node.getCountry());

    for(Edge i : mainList ){
        theList.push_back(i.getTailNode());
    }

    return theList;
}

long Graph::getTotalImports(const Node& node) {
    long sum = 0;
    list<Edge> mainList = adjList.Get(node.getCountry());

    for (Edge i : mainList){
        sum += i.getImport();
    }

    return sum;
}

void Graph::deleteNode(const Node& node) {
    string *keys;
    keys = new string[adjList.Size()];
    adjList.getKeys(keys);

    for (int i = 0; i < adjList.Size(); ++i) {
        if (node.getCountry() == keys[i]){
            continue;
        }
        else{
            list<Edge> &mainList = adjList.Get(keys[i]);
            list<Edge>::iterator i;
            for (i = mainList.begin(); i != mainList.end(); i++){
                if((*i).getTailNode().getCountry() == node.getCountry()){
                    mainList.erase(i);
                    break;
                }
            }
        }
    }

    delete[] keys;
    adjList.Delete(node.getCountry());
}

list<string> Graph::findLeastCostPath(const Node& srcNode, const Node& destNode) {
    string *keys = new string[adjList.Size()];
    adjList.getKeys(keys);

    vector<int> distances(adjList.Size(),-1);
    vector<bool> visitList(adjList.Size(),false);
    vector<string> fromwhere(adjList.Size());

    string theNode = srcNode.getCountry();
    int idx = getIdx(theNode, keys, adjList.Size());
    visitList[idx] = true;
    distances[idx] = 0;
    fromwhere[idx] = "X";


    while (true){
        std::list<Edge> mylis = adjList.Get(keys[idx]);

        for ( Edge i : mylis) {
            long import = i.getImport();
            int edgeidx = getIdx(i.getTailNode().getCountry(), keys, adjList.Size());

            string name = keys[idx], secname = keys[edgeidx];
            long val = import + distances[idx];
            if (distances[edgeidx] == -1 || val < distances[edgeidx]){
                distances[edgeidx] = val;
                fromwhere[edgeidx] = keys[idx];
            }

        }


        visitList[idx] = true;
        idx = smallest(distances,visitList);
        if (idx == -1){
            break;
        }
    }

    int target = getIdx(destNode.getCountry(),keys,adjList.Size());
    std::list<string> reslist;

    while (fromwhere[target] != "X" && target != -1){
        reslist.push_front(keys[target]);
        target = getIdx(fromwhere[target],keys,adjList.Size());
    }

    delete[] keys;
    reslist.push_front(srcNode.getCountry());
    return reslist;

}


bool Graph::isCyclic() {
    std::stack<string> s;
    string *keys = new string[adjList.Size()];
    adjList.getKeys(keys);

    vector<bool> visitList(adjList.Size(),false);
    bool res = false;
    int thevisit = isVisited(visitList);
    vector<bool> visitList2(adjList.Size(),false);
    while(thevisit!= -1 && !res){
        string deneme = keys[thevisit];

        vector<bool> path(adjList.Size(),false);
        res = findCycle(keys, visitList2, path, keys[thevisit]);
        visitList[thevisit] = true;
        thevisit = isVisited(visitList);
    }
    delete[] keys;
    return res;
}


list<string> Graph::getBFSPath(const Node& srcNode, const Node& destNode) {
    std::list<string> reslis;
    std::queue<string> q;

    q.push(srcNode.getCountry());

    while (!q.empty()){
        string thenode = q.front();
        q.pop();

        int isin= 0;
        for(string i : reslis){
            if (i == thenode) isin = 1;
        }
        if (!isin) reslis.push_back(thenode);

        if(thenode == destNode.getCountry()) return reslis;

        std::list<Edge> edges = adjList.Get(thenode);

        for (Edge i : edges){
            q.push(i.getTailNode().getCountry());
        }

    }

    return reslis;
}


int Graph::smallest(std::vector<int> intvec, std::vector<bool> boolvec) {
    int min = -1;

    for (int i = 0; i < intvec.size(); ++i) {
        if(intvec[i] == -1) continue;
        else if (min == -1 && !boolvec[i]){
            min = i;
        }
        else if (min != -1 && intvec[i] < intvec[min] && !boolvec[i]){
            min = i;
        }
    }

    return min;
}

int Graph::getIdx(string node, string *vec, int size) {

    for (int i = 0; i < size; ++i) {
        if (vec[i] == node) return i;
    }
    return -1;
}

bool Graph::findCycle(string *keys, std::vector<bool>& visitList, std::vector<bool> &path,string initNode) {
    int idx = getIdx(initNode,keys,adjList.Size());
    string deneme2 = keys[idx];
    if (!visitList[idx]){
        visitList[idx] = true;
        path[idx] = true;
        std::list<Edge> mylis = adjList.Get(keys[idx]);

        for (Edge i : mylis){
            int edgeidx = getIdx(i.getTailNode().getCountry(),keys,adjList.Size());
            string deneme = keys[edgeidx];
            bool deneme3 = path[edgeidx];
            if (path[edgeidx]) return true;
            else{
                path[edgeidx] = true;
                if (findCycle(keys,visitList,path,i.getTailNode().getCountry())) return true;
                deneme3 = path[edgeidx];
                int a = 3;
            }
        }
    }

    path[idx] = false;
    return false;
}

int Graph::isVisited(std::vector<bool> visitList) {

    for (int i = 0; i < visitList.size(); ++i) {
        if (!visitList[i]) return i;
    }
    return -1;
}


