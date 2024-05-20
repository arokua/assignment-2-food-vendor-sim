#ifndef NODE_H
#define NODE_H
#include <string> 
#include <memory> 
#include "Coin.h"


//The length of the id string not counting the nul terminator
#define IDLEN 5

//The maximum length of a food item name not counting the nul terminator
#define NAMELEN 40

//The maximum length of a food item description not counting the nul terminator.
#define DESCLEN 255

//The default coin level to reset the coins to on request
#define DEFAULT_COIN_COUNT 20

//The possible default food stock level that all new stock should start at and that we should reset to on restock
#define DEFAULT_FOOD_STOCK_LEVEL 20

//The number of denominations of currency available in the system 
#define NUM_DENOMS 8


/**
 * data structure to represent a food item within the system
 **/
class FoodItem
{
public:
    //the unique id for this food item
    std::string id;

    //the name of this food item
    std::string name;
    
    //the description of this food item   
    std::string description;
    
    //the price of this food item (base value is 1 cent)
    double price;
    
    // how many of this food item do we have on hand? 
    unsigned on_hand;
    //Default constructor
    FoodItem();
    //Initialize with value
    FoodItem(std::string,std::string,std::string,double price);
    double getPrice(); // Return the price
    std::string getId();
    bool sold(); //Food is sucessfully sold if its still have stock
    void reStock(int); //Restock to an integer value
    //Return the information for current node as a string
    std::string getInfo();
    void printInfoBrief();
    ~FoodItem();
};

/**
 * the node that holds the data about a food item stored in memory
 **/
class Node {
public:
    Node();
    Node(int data, std::shared_ptr<Node> next = nullptr);
    Node(std::shared_ptr<FoodItem>& foodData, std::shared_ptr<Node> next = nullptr);
    Node(const Node& other);
    ~Node();

    std::shared_ptr<FoodItem> dataFood;
    int data;
    std::shared_ptr<Node> next;  // Now using shared_ptr for next
};


#endif // NODE_H