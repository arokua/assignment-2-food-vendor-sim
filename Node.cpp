#include "Node.h"
#include <iostream>

Node::Node() {next=nullptr;}

Node::Node(int data, Node* next) : data(data), next(next) {
    
}

Node::Node(Node& other) : data(other.data), next(other.next) {
    // dataFood = new FoodItem(*other.dataFood);//Copy the food item
}

Node::~Node(){
    next = nullptr;
	delete next;
    // std::cout<<"Destructed\n";
    // delete dataFood;
}