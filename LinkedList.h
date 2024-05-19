#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Node.h"
#include <iostream>
#include <vector>
#include <memory>
#include <limits>
#include <map>
#include <string.h>

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
    //Insertion methods for int and foodItem nodes
    void addFront(int data);
    void addFront( shared_ptr<FoodItem>& foodData);
    void addEnd(int data);
    shared_ptr<Node> addEnd( shared_ptr<FoodItem>& foodData);
    void addAtPosition(int pos, int data);
    void addAtPosition(int pos,  shared_ptr<FoodItem>& foodData); //Insert at position, from prac
    //Insert by alphabetical with aid of a dictionary for quick lookup
    shared_ptr<Node> insert(shared_ptr<FoodItem>& newFoodData, map<string, shared_ptr<Node>>& refMap);
    void printItemsBrief(); //reformatteed printItems
    void deleteFront();
    void deleteEnd();
    void deletePosition(int pos);
    void deleteFood(const string& foodID, map<string, shared_ptr<Node>>& refMap); //Delete a node by food item id
    void printItems();
    int search(int item, shared_ptr<FoodItem>& foodData); //return index of item
    //Get item, 1-based indexing
    int getItem(int p);
    int getSize(); // Return size of the linked list
    // shared_ptr<Node> getItem(int p);
    


private:
    shared_ptr<Node> head;
    shared_ptr<Node> tail;
    int mySize;
};

#endif //LINKEDLIST_H 