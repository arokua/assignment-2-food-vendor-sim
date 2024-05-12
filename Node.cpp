#include "Node.h"
#include <iostream>

using std::string;
using std::cout;
Node::Node() : next(nullptr) {}

FoodItem::FoodItem(){
    on_hand=DEFAULT_FOOD_STOCK_LEVEL;
    id="FXXXX";
    name="Name";
    description="DESC";
    price=0;
}

FoodItem::FoodItem(string ID,string name,string desc,unsigned int P) :id(ID),name(name),description(desc),price(P) {
    std::cout<<"Gotten food name:\t"+name<<std::endl;
    on_hand=DEFAULT_FOOD_STOCK_LEVEL;
}

bool FoodItem::sold(){
    bool soldable=true;
    if (on_hand) on_hand--;
    else soldable=false;
    return soldable;
}

void FoodItem::reStock(int val){
    on_hand=val;
}

FoodItem::~FoodItem(){}

Node::Node(int data, std::shared_ptr<Node> next) : data(data), next(next) {}


Node::Node(std::shared_ptr<FoodItem>& foodData,  std::shared_ptr<Node>next) : next(next) {
    if (foodData != nullptr) {
    dataFood = std::make_shared<FoodItem>(*foodData); // Deep copy using copy constructor
  }
}

void FoodItem::printInfo(){
    if (id!=""){
        cout <<id<<"|"<<this->name<<"|"<<description<<"|"<<price <<"\n";
    }
}
Node::~Node(){
}