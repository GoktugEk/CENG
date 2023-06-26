#include "Node.h"

// // // THE FRIEND METHODS ARE ALREADY IMPLEMENTED BELOW. // // //
// // // // // // // DO NOT CHANGE THEM! // // // // // // //

Node::Node(int id) {
    this->id = id;
}

Node::~Node() {
    // TODO
}

Node::Node(const Node& node) {
    this->id = node.id;
    this->children = node.children;
}

int Node::getId() const {
    return this->id;
}

char Node::getData() const {
    // TODO

}

vector<Node*>& Node::getChildren() {
    return this->children;
}

void Node::operator+=(Node& childNode) {
    this->getChildren().push_back()
}

Node* Node::operator&(const Node& node) const {

}

// This is already implemented for you, do NOT change it!
ostream& operator<<(ostream& os, const Node& node) {
    try {
        node.getData();
        os << *(DataNode*)&node;
    }
    catch (InvalidRequest e) {
        os << "[" << node.id;
        for (int i = 0; i < node.children.size(); i++)
            os << ", " << *node.children[i];
        os << "]";
        return os;
    }
}

/*************** DataNode *****************/

DataNode::DataNode(int id, char data) {
    this->id = id;
    this->data = data;
}

DataNode::~DataNode() {
    // TODO
}

DataNode::DataNode(const DataNode& dataNode) {
    this->data = dataNode.data;
    this->id = dataNode.id;
    this->children = dataNode.children;
}

DataNode::DataNode(const Node& node, char data) {
    this->id = node.getId();
    this->children = node.children;
    this->data = data;
}

char DataNode::getData() const {
    return this->data;
}

// This is already implemented for you, do NOT change it!
ostream& operator<<(ostream& os, const DataNode& dataNode) {
    os << "[" << "(" << dataNode.id << ", \'" << dataNode.data << "\')";
    for (int i = 0; i < dataNode.children.size(); i++)
        os << ", " << *dataNode.children[i];
    os << "]";
    return os;
}
