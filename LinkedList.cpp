#include "LinkedList.h"

LinkedList::LinkedList() : head(nullptr), mySize(0) {}

LinkedList::LinkedList(vector<int> a,int nNodes)  {
    for (int i = a.size() - 1; i >= 0; --i) {
        addFront(a[i]);
    }
}

LinkedList::~LinkedList() {
    // shared_ptr automatically deletes nodes when the last reference goes out of scope
}

void LinkedList::addFront(int data) {
    head = make_shared<Node>(data, head);
    mySize++;
}

void LinkedList::addFront( shared_ptr<FoodItem>& foodData) {
    //For food item type
    head = make_shared<Node>(foodData, head);
    mySize++;
}

void LinkedList::addEnd(int data) {
    auto newNode = make_shared<Node>(data);
    if (!head) {
        head = newNode;
    } else {
        auto temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    mySize++;
}

shared_ptr<Node> LinkedList::addEnd( shared_ptr<FoodItem>& foodData) {
    //For food item type, return the newly added node
    auto newNode = make_shared<Node>(foodData);
    // cout << newNode<<"\n"; for debug
    if (!head) {
        head = newNode;
    } else {
        auto temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    // for debug
    // cout << "Added food:\n\t";
    // (*foodData).printInfo();
    mySize++;
    return newNode;
    
}

void LinkedList::addAtPosition(int pos, int data) {
    if (pos <= 0) {
        addFront(data);
    } else if (pos >= mySize) {
        addEnd(data);
    } else {
        auto temp = head;
        for (int i = 1; i < pos; ++i) {
            temp = temp->next;
        }
        auto newNode = make_shared<Node>(data, temp->next);
        temp->next = newNode;
        mySize++;
    }
}

void LinkedList::addAtPosition(int pos,  shared_ptr<FoodItem>& foodData) {
    //For food item type
    if (pos <= 0) {
        addFront(foodData);
    } else if (pos >= mySize) {
        addEnd(foodData);
    } else {
        auto temp = head;
        for (int i = 1; i < pos; ++i) {
            temp = temp->next;
        }
        auto newNode = make_shared<Node>(foodData, temp->next);
        temp->next = newNode;
        mySize++;
    }
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

void LinkedList::deletePosition(int pos) {
    if (pos <= 0 || pos > mySize) {
        cout << "Position out of range\n";
        return;
    }

    if (pos == 1) {
        deleteFront();
        return;
    }

    auto temp = head;
    for (int i = 1; i < pos - 1; ++i) {
        temp = temp->next;
    }
    temp->next = temp->next->next;
    mySize--;
}

//Ultility methods
void LinkedList::printItems() {
    string currentItem = "";
    auto temp = head;
    while (temp) {
        if (temp->dataFood) {
            currentItem = (*temp->dataFood).getInfo();
            cout << currentItem;
        }
        temp = temp->next;
    }
    cout << endl;
}


/*
    A specific list position is passed in, returns a string.
    With each iteration of loop, check if listPosition is the same position as the currentListPosition.
    If it is, return details of current position in format suitable for saving to the .dat file, and end lookingForItem loop
    If not, increment the position and set the currentNode to the next node in the linked list, as long as next node isn't null

    This is a new method as I didn't want to mess with the above printItems method too much in case it broke too much.
*/
string LinkedList::getItemDetails(int listPosition) {
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

int LinkedList::search(int item) {
    int pos = 1;
    auto temp = head;
    while (temp) {
        if (temp->data == item) {
            cout << pos << "\n";
            return pos;
        }
        temp = temp->next;
        pos++;
    }
    cout << "0\n";
    return 0;
}

int LinkedList::getItem(int p) {
    if (p < 1) {
        cout << std::numeric_limits<int>::max() << "\n";
        return std::numeric_limits<int>::max();
    }
    auto temp = head;
    for (int pos = 1; temp && pos <= p; ++pos, temp = temp->next) {
        if (pos == p) {
            cout << temp->data << "\n";
            return temp->data;
        }
    }
    cout << std::numeric_limits<int>::max() << "\n";
    return std::numeric_limits<int>::max();
}

int LinkedList::getSize(){
    return mySize;
}

// shared_ptr<Node> LinkedList::getItem(int p);

void LinkedList::printItemsBrief() {
    auto temp = head;
    while (temp) {
        if (temp->dataFood) {
            (*temp->dataFood).printInfoBrief();
        }
        temp = temp->next;
    }
    cout << endl;
}