#include "LinkedList.h"
#include "Helper.h"

LinkedList::LinkedList() : head(nullptr), tail(nullptr), mySize(0) {}

// new Linked List via FoodItem map
LinkedList::LinkedList(std::map<std::string, std::shared_ptr<Node>>& foodsMap) :
    mySize(0)
{
    // Accessing value in each pair containing shared_ptr points to the object
    for (auto& pair : foodsMap) {
        addEnd(pair.second->dataFood);
    }
}


void LinkedList::addFront(shared_ptr<FoodItem>& foodData) {
    //Food data for vendor
    shared_ptr<Node> newNode = make_shared<Node>(foodData, nullptr, nullptr);
    if (head) {
        head->prev = newNode;
        newNode->next = head;
    }
    head = newNode;
    mySize++;
}


void LinkedList::addEnd(shared_ptr<FoodItem>& foodData) {
    //For food item type, return the newly added node
    shared_ptr<Node> newNode = make_shared<Node>(foodData, nullptr, nullptr);
    if (!head) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    mySize++;
}


//Delete head node, check if null for safe operation
void LinkedList::deleteFront() {
    if (head) {
        head = head->next;
        mySize--;
    }
}

void LinkedList::deleteEnd() {
    if (head) {
        if (!head->next) {
            head = nullptr;
        } else {
            auto temp = head;
            while (temp->next->next) {
                temp = temp->next;
            }
            temp->next = nullptr;
        }
        mySize--;
    }
}


//Ultility methods
void LinkedList::printMenuFood() {
    cout << "\nFood Menu";
    cout << "\n------------" << endl;
    cout << std::left << std::setw(5) << "ID" << "|"
         << std::setw(45) << "Name" << "|"
         << std::setw(5) << "Length" << "\n";
    for (int i = 0; i < 60; i++) {
        cout << "-";
    }
    cout << endl;

    auto temp = head;
    while (temp) {
        if (temp->dataFood) {
            (*temp->dataFood).printInfoBrief();
        }
        temp = temp->next;
    }
    cout << endl;
}


std::shared_ptr<FoodItem> LinkedList::searchFoodItemByName(std::string name) {
    auto temp = head;
    std::shared_ptr<FoodItem> searchedFoodItem = nullptr; 
    bool found = false;
    try {
        while (temp && !found) {
            if (temp->dataFood->getName() == name) {
                searchedFoodItem = temp->dataFood;
                found = true;
            }
            temp = temp->next;
        }
    } catch (const std::runtime_error& e) {
        cout << "Error: "<< e.what() << endl;
    } 
    return searchedFoodItem;
}


std::shared_ptr<FoodItem> LinkedList::searchFoodItemByID(std::string ID) {
    auto temp = head;
    std::shared_ptr<FoodItem> searchedFoodItem = nullptr;
    bool found = false;
    try {
        while (temp && !found) {
            if (temp->dataFood->getID() == ID) {
                searchedFoodItem = temp->dataFood; // assign to the empty ptr
                found = true;
            }
            temp = temp->next;
        }
    } catch (const std::runtime_error& e) {
        cout << "Error: "<< e.what() << endl;
    } 
    return searchedFoodItem;
}


std::string LinkedList::getItemDetails(int listPosition) {
    string itemInfo = "";
    shared_ptr<Node> currentNode = head;
    int currentListPosition = 0;
    bool lookingForItem = true;
    
    while (lookingForItem) {
        if (currentListPosition == listPosition) {  
            itemInfo = currentNode->dataFood->getInfo();
            //cout << itemInfo;
            //cout << currentNode->dataFood->getId() << endl;
            lookingForItem = false;
        }
        else {
            currentListPosition++;            
            if (currentNode->next != nullptr) currentNode = currentNode->next;
            else lookingForItem = false;

        }
    }
    return itemInfo;
}


void LinkedList::insert(shared_ptr<FoodItem>& newFoodData, map<string, shared_ptr<Node>>& refMap) {
    // Create a new node for the food data
    shared_ptr<Node> newNode = make_shared<Node>(newFoodData);

    if (!head || Helper::strSmaller(newFoodData->name, head->dataFood->name)) {
        //If food is before head
        addFront(newNode->dataFood);
        refMap[newFoodData->name] = head;
    }
    else{
        auto currNode = head;
        while (currNode->next != nullptr && 
        Helper::strSmaller(currNode->dataFood->name, newFoodData->name)) {
            currNode = currNode->next;
        }

        // Insert after currNode
        newNode->next = currNode->next;
        if (currNode->next) {
            currNode->next->prev = newNode;
        }
        currNode->next = newNode;
        newNode->prev = currNode;

        if (!newNode->next) {
            tail = newNode;
        }

        refMap[newFoodData->name] = newNode;
        mySize++;
    }
    // return newNode;
}


// the function is currently searching for pair via ID (which should be via names)
void LinkedList::deleteFood(const string& foodID, map<string, shared_ptr<Node>>& refMap) {
    
    std::shared_ptr<FoodItem> chosenFoodItem = searchFoodItemByID(foodID);
    
    auto it = refMap.find(chosenFoodItem->getName());
    if (it == refMap.end()) {
        cout << "Food item with ID " << foodID << " not found." << endl;
    }
    else{
        //Node do exists to be deleted
        // Get the node to be deleted
        shared_ptr<Node> nodeToDelete = it->second;

        // If the node is the head, update the head pointer
        if (nodeToDelete == head) {
            head = nodeToDelete->next;
        }

        // If the node is the tail, update the tail pointer
        if (nodeToDelete == tail) {
            tail = nodeToDelete->prev;
        }

        // Update the previous node's next pointer, if it exists
        if (nodeToDelete->prev) {
            nodeToDelete->prev->next = nodeToDelete->next;
        }

        // Update the next node's previous pointer, if it exists
        if (nodeToDelete->next) {
            nodeToDelete->next->prev = nodeToDelete->prev;
        }

        // Remove the node from the refMap
        refMap.erase(it);

        // Decrement the size of the linked list
        mySize--;
        chosenFoodItem = nullptr;

        cout << "Food item with ID " << foodID << " has been removed from the system." << endl;
    }
}



LinkedList::~LinkedList() {} // shared_ptr automatically deletes nodes when the last reference goes out of scope


int LinkedList::getSize(){
    return mySize;
}