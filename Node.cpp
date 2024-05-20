
#include "Node.h"
#include <iostream>

using std::string;
using std::cout;
using std::to_string;

Node::Node() : next(nullptr) {

}

FoodItem::FoodItem(){
    on_hand=DEFAULT_FOOD_STOCK_LEVEL;
    id="FXXXX";
    name="Name";
    description="DESC";
    price=0.00;
}

FoodItem::FoodItem(string ID,string name,string desc,double P) :id(ID),name(name),description(desc),price(P) {
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

FoodItem::~FoodItem(){

}

Node::Node(int data, std::shared_ptr<Node> next) : data(data), next(next) {

}


Node::Node(std::shared_ptr<FoodItem>& foodData,  std::shared_ptr<Node>next) : next(next) {
    if (foodData != nullptr) {
    dataFood = std::make_shared<FoodItem>(*foodData); // Deep copy using copy constructor
  }
}

string FoodItem::getInfo(){
    string line = "";
    if (id != ""){
        line = id + "|" + this->name + "|" + description + "|" + to_string(price) + "\n";
    }
    return line;
}

/*string FoodItem::getInfoForSaveFile() {
    string line = id + "," + this->name + "," + description + "," + to_string(price) + "\n";
    return line;
}*/

// bruh what is this
//It was meant to be a placeholder for formatting the display meal options. 
//It's "brief" as the example program doesn't print out the description like the above printInfo()
//Yes it's lazy
void FoodItem::printInfoBrief() {
        if (id!=""){
            cout <<id<<"|"<<this->name<<"                                           |"<<price <<"\n";
    }
}

string FoodItem::getId() {
    return id;
}

double FoodItem::getPrice() {
    return price;
}


Node::~Node(){
}
