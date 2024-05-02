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
    if (!head) {
        head = newNode;
    } else {
        auto temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    return newNode;
    mySize++;
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
    auto temp = head;
    while (temp) {
        if (temp->data) {
            cout << temp->data << " ";
        } else if (temp->dataFood) {
            cout << temp->dataFood->name << " ";
        }
        temp = temp->next;
    }
    cout << endl;
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

// shared_ptr<Node> LinkedList::getItem(int p);