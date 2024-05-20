#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <vector>
#include <memory>
#include <limits>
#include <map>

#include "Node.h"

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
    LinkedList(vector<int>, int);
    ~LinkedList();

    // initializing the linked list with the FoodItem Vector
    LinkedList(std::map<std::string, std::shared_ptr<Node>>& foodsMap);

    // void addFront(shared_ptr<Node>& insertingNode);
    // void addEnd(shared_ptr<Node>& insertingNode);
    // void addAtPosition(int pos, shared_ptr<Node>& insertingNode);

    void addFront(shared_ptr<FoodItem>& foodData);
    void addEnd(shared_ptr<FoodItem>& foodData);
    void addAtPosition(int pos, shared_ptr<FoodItem>& foodData);

    //Insert by alphabetical with aid of a dictionary for quick lookup
    void insert(shared_ptr<FoodItem>& newFoodData, map<string, shared_ptr<Node>>& refMap);
    void printItemsBrief(); //reformatteed printItems
    void deleteFront();
    void deleteEnd();
    void deleteFood(const string& foodID, map<string, shared_ptr<Node>>& refMap); //Delete a node by food item id
    void printItems();

    int getSize(); // Return size of the linked list
    // shared_ptr<Node> getItem(int p);
    std::shared_ptr<FoodItem> searchFoodItemByName(std::string name);
    std::shared_ptr<FoodItem> searchFoodItemByID(std::string ID);

private:
    shared_ptr<Node> head;
    shared_ptr<Node> tail;
    int mySize;
};

#endif //LINKEDLIST_H 