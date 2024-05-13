#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Node.h"
#include <iostream>
#include <vector>
#include <memory>
#include <limits>

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
    LinkedList(vector<std::shared_ptr<FoodItem>>& foodItemvector);

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
    FoodItem searchFoodItemByName(std::string name);
    FoodItem searchFoodItemByID(std::string ID);

private:
    shared_ptr<Node> head;
    int mySize;
};

#endif //LINKEDLIST_H 