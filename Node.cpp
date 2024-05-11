#include "Node.h"
#include <iostream>

using std::string;
using std::cout;
using std::endl;

FoodItem::FoodItem(){
    on_hand=DEFAULT_FOOD_STOCK_LEVEL;
    id="FXXXX";
    name="Name";
    description="DESC";
}

FoodItem::FoodItem(string ID,string Name,string desc,unsigned int P) {
    this->id=ID;
    this->name=Name;
    this->description=desc;
    this->price=P;
    this->on_hand=DEFAULT_FOOD_STOCK_LEVEL;
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


Node::Node() : next(nullptr) {}

Node::Node(std::shared_ptr<FoodItem>& foodData,  std::shared_ptr<Node>next) {
    if (foodData != nullptr) {
        dataFood = std::make_shared<FoodItem>(*foodData); // Deep copy using copy constructor
        // dataFood (Node's pointer) is pointing to foodData (FoodItem's pointer) 
        // which points to FoodItem object 
        next = std::make_shared<Node>(next);
    }
}

void FoodItem::printInfo(){
    if (id!=""){
        cout << getID() << "|" << getName() << "|" << getDesc() 
             << "|" << getPrice() << "|" << getOnHand() << endl;
    }
}







std::string FoodItem::getName(){
    return name;
}
std::string FoodItem::getID(){
    return id;
}
std::string FoodItem::getDesc(){
    return description;
}
unsigned int FoodItem::getPrice(){
    return price;
}
unsigned int FoodItem::getOnHand(){
    return on_hand;
}

Node::~Node(){
}