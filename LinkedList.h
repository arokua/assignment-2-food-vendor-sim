#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <vector>
#include <memory>
#include <limits>
#include <map>

#include "Node.h"

using std::vector;
using std::shared_ptr;
using std::make_shared;
using std::cout;
using std::endl;

class LinkedList {
public:
    LinkedList();
    LinkedList(vector<int>, int);
    ~LinkedList();

    // initializing the linked list with the FoodItem Vector
    LinkedList(std::map<std::string, std::shared_ptr<Node>>& foodsMap);

    // void addFront(int data);
    void addFront(shared_ptr<Node>& insertingNode);

    // void addEnd(int data);
    void addEnd(shared_ptr<Node>& insertingNode);

    // void addAtPosition(int pos, int data);
    void addAtPosition(int pos, shared_ptr<Node>& insertingNode);

    void deleteFront();
    void deleteEnd();
    void deletePosition(int pos);
    
    void printItems();
    int search(int item);
    //Get item, 1-based indexing
    int getItem(int p);
    // shared_ptr<Node> getItem(int p);
    std::shared_ptr<FoodItem> searchFoodItemByName(std::string name);
    std::shared_ptr<FoodItem> searchFoodItemByID(std::string ID);

private:
    shared_ptr<Node> head;
    int mySize;
};

#endif //LINKEDLIST_H 