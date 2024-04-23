#include "Node.h"

Node::Node(){

}
Node::Node(int data, Node* next) : data(data), next(next) {
    
}

Node::Node(Node& other) : data(other.data), next(other.next) {
}

Node::~Node(){
    delete next;
}