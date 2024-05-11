#include "LinkedList.h"

LinkedList::LinkedList() : head(nullptr), mySize(0) {}

// new Linked List via FoodItem vector
LinkedList::LinkedList(vector<FoodItem>& foodItemvector)  {
    for (int i = foodItemvector.size() - 1; i >= 0; --i) {
        std::shared_ptr<Node> newNode = std::make_shared<Node>(foodItemvector[i]);
        addFront(newNode);
    }
}

LinkedList::~LinkedList() {
    // shared_ptr automatically deletes nodes when the last reference goes out of scope
}


void LinkedList::addFront(shared_ptr<Node>& insertingNode) {
    if (!head) { // head == nullptr
        head = insertingNode;
    } else {
        insertingNode->next = head->next;
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

FoodItem LinkedList::searchFoodItemByName(std::string name) {
    auto temp = head;
    try {
        while (temp) {
            if (temp->dataFood->getName() == name) {
                return (*temp->dataFood);
            }
            temp = temp->next;
        }
        throw std::runtime_error("Food Item can't be found.");
    } catch (const std::runtime_error& e) {
        cout << "Error: "<< e.what() << endl;
    } 
}


FoodItem LinkedList::searchFoodItemByID(std::string ID) {
    auto temp = head;
    try {
        while (temp) {
            if (temp->dataFood->getID() == ID) {
                return (*temp->dataFood);
            }
            temp = temp->next;
        }
        throw std::runtime_error("Food Item can't be found.");
    } catch (const std::runtime_error& e) {
        cout << "Error: "<< e.what() << endl;
    } 
}


// int LinkedList::getItem(int p) {
//     if (p < 1) {
//         cout << std::numeric_limits<int>::max() << "\n";
//         return std::numeric_limits<int>::max();
//     }
//     auto temp = head;
//     for (int pos = 1; temp && pos <= p; ++pos, temp = temp->next) {
//         if (pos == p) {
//             cout << temp->dataFood << "\n";
//             return temp->dataFood;
//         }
//     }
//     cout << std::numeric_limits<int>::max() << "\n";
//     return std::numeric_limits<int>::max();
// }

// shared_ptr<Node> LinkedList::getItem(int p);