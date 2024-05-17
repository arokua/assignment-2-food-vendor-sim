#include "Node.h"
#include <iostream>

using std::string;
using std::cout;
using std::endl;

FoodItem::FoodItem(){
    id="FXXXX";
    name="Name";
    description="DESC";
    price=0.0;
    on_hand=DEFAULT_FOOD_STOCK_LEVEL;
}

FoodItem::FoodItem(string ID,string Name,string desc,double P) {
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

void FoodItem::reStock(){
    // when restocking, the value always return to DEFAULT_FOOD_STOCK_LEVEL
    on_hand=DEFAULT_FOOD_STOCK_LEVEL;
}


Node::Node(): 
    dataFood(nullptr),
    next(nullptr)
    {}

Node::Node(const Node& other){
    this->dataFood = other.dataFood;
    this->next = other.next;
}


// creating a Node based on specified pointer to a FoodItem
Node::Node(std::shared_ptr<FoodItem>& foodData,  std::shared_ptr<Node> nextNode) {
    if (foodData != nullptr) {
        this->dataFood = std::make_shared<FoodItem>(*foodData); // Deep copy using copy constructor
        // dataFood (Node's pointer) is pointing to foodData (FoodItem's pointer) 
        // which points to FoodItem object 
        this->next = nextNode;
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
double FoodItem::getPrice(){
    return price;
}
unsigned int FoodItem::getOnHand(){
    return on_hand;
}

Node::~Node(){}
FoodItem::~FoodItem(){}