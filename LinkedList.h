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

    void addFront(int data);
    void addFront( shared_ptr<FoodItem>& foodData);
    void addEnd(int data);
    void addEnd( shared_ptr<FoodItem>& foodData);
    void addAtPosition(int pos, int data);
    void addAtPosition(int pos,  shared_ptr<FoodItem>& foodData);
    void deleteFront();
    void deleteEnd();
    void deletePosition(int pos);
    void printItems();
    int search(int item);
    int getItem(int p);

private:
    shared_ptr<Node> head;
    int mySize;
};

