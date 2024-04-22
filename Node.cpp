#include "Node.h"

Node::Node(int data, Node* next) : data(data), next(next) {
    
}

Node::Node(Node& other) : data(other.data), next(other.next) {
}