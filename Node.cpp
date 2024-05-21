#include "Node.h"


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

bool FoodItem::sold(){ // deduct on_hand by 1
    bool soldable=true;
    if (on_hand) on_hand--;
    else soldable=false;
    return soldable;
}

void FoodItem::reStock(){ // restock always return to pre-defined stock value
    on_hand=DEFAULT_FOOD_STOCK_LEVEL;
}


Node::Node(std::shared_ptr<FoodItem>& foodData,  std::shared_ptr<Node>next, std::shared_ptr<Node> prev) :
    dataFood(foodData),next(next),prev(prev) {}



void FoodItem::printInfo(){ // fully detailed printing function
    if (id!=""){
        cout <<id<<"|"<<this->name<<"|"<<description<<"|"<<price <<"\n";
    }
}


void FoodItem::printInfoBrief() { // printing function that used in printMenuItems function
    if (id != "") {
        std::ostringstream priceStream;
        priceStream << std::fixed << std::setprecision(2) << price;

        std::cout << std::left << std::setw(5) << id << "|"
                  << std::setw(45) << name << "|"
                  << "$" << std::right << std::setw(5) << priceStream.str() << std::endl;
    }
}


string FoodItem::getInfo(){
    string line = "";
    std::ostringstream priceStream;
    priceStream << std::fixed << std::setprecision(2) << price;
    std::string priceStr = priceStream.str();
    if (id != ""){
        line = id + "|" + this->name + "|" + description + "|" + priceStr + "\n";
    }
    return line;
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

