#include "Node.h"
#include <iostream>

using std::string;
using std::cout;
using std::to_string;

Node::Node() : 
    next(nullptr),
    prev(nullptr)
{}

FoodItem::FoodItem() {
    id="FXXXX";
    name="Name";
    description="DESC";
    price=0.00;
    on_hand=DEFAULT_FOOD_STOCK_LEVEL;
}

FoodItem::FoodItem(string ID, string name, string desc, double P) :
    id(ID), name(name), description(desc), price(P) 
    {
        on_hand=DEFAULT_FOOD_STOCK_LEVEL;
    }

bool FoodItem::sold(){
    bool soldable=true;
    if (on_hand) on_hand--;
    else soldable=false;
    return soldable;
}

void FoodItem::reStock(){
    on_hand=DEFAULT_FOOD_STOCK_LEVEL;
}



Node::Node(std::shared_ptr<FoodItem>& foodData,  std::shared_ptr<Node>next, std::shared_ptr<Node> prev) :
    dataFood(foodData),next(next),prev(prev) {}



void FoodItem::printInfo(){
    if (id!=""){
        cout <<id<<"|"<<this->name<<"|"<<description<<"|"<<price <<"\n";
    }
}


void FoodItem::printInfoBrief() {
        if (id!=""){
            cout <<id<<"|"<<this->name<<"                                           |"<<price <<"\n";
    }
}



std::string FoodItem::getName(){
    return name;
}
std::string FoodItem::getID() {
    return id;
}
std::string FoodItem::getDesc(){
    return description;
}
double FoodItem::getPrice(){
    return price;
}
unsigned int FoodItem::getOnHand(){
    return on_hand;
}

Node::~Node(){}
FoodItem::~FoodItem(){}




string FoodItem::getInfo(){
    string line = "";
    if (id != ""){
        line = id + "|" + this->name + "|" + description + "|" + to_string(price) + "\n";
    }
    return line;
}
