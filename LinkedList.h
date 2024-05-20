
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
using std::ofstream;
using std::string;

class LinkedList {
public:
    LinkedList();
    LinkedList(vector<int>, int);
    ~LinkedList();

    void addFront(int data);
    void addFront( shared_ptr<FoodItem>& foodData);
    void addEnd(int data);
    shared_ptr<Node> addEnd( shared_ptr<FoodItem>& foodData);
    void addAtPosition(int pos, int data);
    void addAtPosition(int pos,  shared_ptr<FoodItem>& foodData);
    //Placeholder method for printing items in a formatted way in the display meal options menu choice.
    void printItemsBrief();
    void deleteFront();
    void deleteEnd();
    void deletePosition(int pos);
    //Return an item in the linked list as a string at the position passed in. Used for saving items to the file.
    string getItemDetails(int listPosition);
    void printItems();
    void saveCurrentItemsToFile();
    int search(int item);
    //Get item, 1-based indexing
    int getItem(int p);
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
