#include "Node.h"
#include <iostream>

using std::string;
using std::cout;
<<<<<<< HEAD

Node::Node() : next(nullptr) {

}
=======
using std::endl;
>>>>>>> d9755384e1557bafc554d40eaf59c72b62619ba3

FoodItem::FoodItem(){
    on_hand=DEFAULT_FOOD_STOCK_LEVEL;
    id="FXXXX";
    name="Name";
    description="DESC";
    price=0.00;
}

<<<<<<< HEAD
FoodItem::FoodItem(string ID,string name,string desc,double P) :id(ID),name(name),description(desc),price(P) {
    std::cout<<"Gotten food name:\t"+name<<std::endl;
    on_hand=DEFAULT_FOOD_STOCK_LEVEL;
=======
FoodItem::FoodItem(string ID,string Name,string desc,unsigned int P) {
    this->id=ID;
    this->name=Name;
    this->description=desc;
    this->price=P;
    this->on_hand=DEFAULT_FOOD_STOCK_LEVEL;
>>>>>>> d9755384e1557bafc554d40eaf59c72b62619ba3
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

FoodItem::~FoodItem(){

<<<<<<< HEAD
}

Node::Node(int data, std::shared_ptr<Node> next) : data(data), next(next) {

=======

Node::Node(): 
    dataFood(nullptr),
    next(nullptr)
    {}

Node::Node(const Node& other){
    this->dataFood = other.dataFood;
    this->next = other.next;
>>>>>>> d9755384e1557bafc554d40eaf59c72b62619ba3
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
<<<<<<< HEAD
        cout << id << "|" << this->name << "|" << description<<"|" << price << "\n";
    }
}

void FoodItem::printInfoBrief() {
        if (id!=""){
            cout << id<< "|" << this->name << "                                           |" << price << "\n";
    }
}

string FoodItem::getId() {
    return id;
}

double FoodItem::getPrice() {
    return price;
}

=======
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
>>>>>>> d9755384e1557bafc554d40eaf59c72b62619ba3

Node::~Node(){
}