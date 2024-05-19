#include "LinkedList.h"

LinkedList::LinkedList() : head(nullptr), mySize(0) {}

// new Linked List via FoodItem vector
LinkedList::LinkedList(std::map<std::string, std::shared_ptr<Node>>& foodsMap){
    // Accessing value in each pair containing shared_ptr points to the object

    // for (size_t = 0; i < foodItemvector.size(); i++) {
    //     // for each pointer in the vector, create a new Node pointer
    //     // foodItemvector[i] == shared_ptr<FoodItem>
    //     std::shared_ptr<Node> newNode = std::make_shared<Node>(foodItemvector[i]); 
    // }

    for (auto& pair : foodsMap) {
        addEnd(pair.second);
    }
    
}

LinkedList::~LinkedList() {
    // shared_ptr automatically deletes nodes when the last reference goes out of scope
}


// Functions 
void LinkedList::addFront(shared_ptr<Node>& insertingNode) {
    if (!head) { // head == nullptr
        head = insertingNode;
    } else { 
        insertingNode->next = head->next;
        head->next = nullptr;
        head = insertingNode;
    }
    mySize++;
}


void LinkedList::addEnd(shared_ptr<Node>& insertingNode) {
    try {
        if (insertingNode->next) {
            throw std::logic_error("This Node can't be at the end cause this Node is pointing to another Node!");
        }
        if (!head) {
            head = insertingNode;
        } else {
            auto temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = insertingNode;
            insertingNode->next = nullptr;
        }
    } catch (const std::logic_error& e) {
        cout << "Error: "<< e.what() << endl;
    }
    mySize++;
}


void LinkedList::addAtPosition(int pos, shared_ptr<Node>& insertingNode) {
    try {
        if (pos < 0 || pos > mySize + 1) { // if the position is outside the range of the linkedlist
            throw std::out_of_range("Invalid position");
        }
        if (pos == 0) { // at the head
            addFront(insertingNode);
        } else if (pos == mySize + 1) { // at the end
            addEnd(insertingNode);
        } else {
            auto temp = head;
            for (int i = 1; i < pos; ++i) { // traverse (pos)th times to reach the desired position
                temp = temp->next;
            }
            temp->next = insertingNode;
            mySize++;
        }
    } catch (const std::out_of_range& e) {
        cout << "Error: "<< e.what() << endl;
    }
}


//Delete head node, check if null for safe operation
void LinkedList::deleteFront() {
    try {
        if (!head) {
            // not really sure about the error name
            throw std::runtime_error("There's nothing to be deleted!");
        } else {
            head = head->next;
            mySize--;
        }
    } catch (const std::runtime_error& e) {
        cout << "Error: "<< e.what() << endl;
    }
}

void LinkedList::deleteEnd() {
    try {
        if (!head) {
            // not really sure about the error name
            throw std::runtime_error("There's nothing to be deleted!");
        } else {
            if (!head->next) { // the only node in the list
                head = nullptr;
            } else {
                auto temp = head;
                while (temp->next->next) {
                    temp = temp->next;
                }
                temp->next = nullptr;
                temp.reset();
            }
            mySize--;
        }
    } catch (const std::runtime_error& e) {
        cout << "Error: "<< e.what() << endl;
    }
}

void LinkedList::deletePosition(int pos) {
    try {
        if (pos <= 0 || pos > mySize) {
            throw std::out_of_range("Invalid position");
        }
        if (!head) {
            // not really sure about the error name
            throw std::runtime_error("There's nothing to be deleted!");
        } 
        if (pos == 1) {
            deleteFront();
        } else {
            auto temp = head;
            for (int i = 1; i < pos - 1; ++i) {
                temp = temp->next;
            }
            temp->next = temp->next->next;
            temp.reset();
            mySize--;
        }

    } catch (const std::out_of_range& e) {
        cout << "Error: "<< e.what() << endl;
    } catch (const std::runtime_error& e) {
        cout << "Error: "<< e.what() << endl;
    }
}

//Ultility methods
void LinkedList::printItems() {
    auto temp = head;
    while (temp) {
        if (temp->dataFood) {
            (*temp->dataFood).printInfo();
        }
        temp = temp->next;
    }
    cout << endl;
}

std::shared_ptr<FoodItem> LinkedList::searchFoodItemByName(std::string name) {
    auto& temp = head;
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
        if (!found) {
            throw std::runtime_error("Food Item can't be found.");
        }
    } catch (const std::runtime_error& e) {
        cout << "Error: "<< e.what() << endl;
    } 
    return searchedFoodItem;
}


std::shared_ptr<FoodItem> LinkedList::searchFoodItemByID(std::string ID) {
    auto& temp = head;
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
        if (!found) {
            throw std::runtime_error("Food Item can't be found.");
        }
    } catch (const std::runtime_error& e) {
        cout << "Error: "<< e.what() << endl;
    } 
    return searchedFoodItem;
}