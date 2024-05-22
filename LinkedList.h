#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <vector>
#include <limits>
#include <map>

#include "Node.h"
#include "Helper.h"

using std::string;
using std::vector;
using std::shared_ptr;
using std::make_shared;
using std::cout;    
using std::endl;
using std::map;

class LinkedList {
public:
    LinkedList();
    ~LinkedList();

    // initializing the linked list with the FoodItem Vector
    LinkedList(std::map<std::string, std::shared_ptr<Node>>& foodsMap);

    // Add & Delete Method
    void addFront(shared_ptr<FoodItem>& foodData);
    void addEnd(shared_ptr<FoodItem>& foodData);
    void deleteFront();
    void deleteEnd();

    //Insert by alphabetical with aid of a dictionary for quick lookup
    void insertNewPairtoMap(shared_ptr<FoodItem>& newFoodData, map<string, shared_ptr<Node>>& refMap);
    void deleteFood(map<string, shared_ptr<Node>>& refMap); //Delete a node by food item id

    // Getters & Setters
    int getSize(); // Return size of the linked list

    // Utility method
    void printMenuFood();
    void addNewFood(std::map<std::string, std::shared_ptr<Node>>& refMap);
    std::shared_ptr<FoodItem> searchFoodItemByName(std::string name);
    std::shared_ptr<FoodItem> searchFoodItemByID(std::string ID);
    std::string getItemDetails(int listPosition);

private:
    shared_ptr<Node> head;
    shared_ptr<Node> tail;
    int mySize;
};

#endif //LINKEDLIST_H 