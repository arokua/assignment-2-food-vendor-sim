#include "LinkedList.h"

LinkedList::LinkedList() : head(nullptr), tail(nullptr), mySize(0) {}

// Linked List constructor uses FoodItem map to initialize
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
 

void LinkedList::deleteFront() {
    if (head) {
        head->next->prev = nullptr; // dereference the next node's prev pointer to the head node
        head = head->next;
        mySize--;
    }
}

void LinkedList::deleteEnd() {
    if (head) {
        if (!head->next) { // when head (= tail) is the only node
            head = nullptr;
            tail = nullptr;
        } else {
            tail->prev->next = nullptr;
            tail = tail->prev;
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
    /***
     * @brief This function iterates through the LinkedList to find the Node that holds the shared_ptr
     * that points to the correct FoodItem objec by comparing the FoodItem's name.
     * @param ID Specified ID to locate the FoodItem 
    ***/

    auto temp = head;
    std::shared_ptr<FoodItem> searchedFoodItem = nullptr; 
    bool found = false;
    try {
        if (name.length() > NAMELEN) {
            throw std::invalid_argument("Invalid name length");
        }
        while (temp && !found) {
            if (temp->dataFood->getName() == name) {
                searchedFoodItem = temp->dataFood;
                found = true;
            }
            temp = temp->next;
        }
    } catch (const std::runtime_error& e) {
        cout << "Error: "<< e.what() << endl;
        throw;
    } catch (const std::invalid_argument& e) {
        cout << "Error: "<< e.what() << endl;
        throw;
    }
    return searchedFoodItem;
}


std::shared_ptr<FoodItem> LinkedList::searchFoodItemByID(std::string ID) {
    /***
     * @brief This function iterates through the LinkedList to find the Node that holds the shared_ptr
     * that points to the correct FoodItem objec by comparing the FoodItem's ID.
     * @param ID Specified ID to locate the FoodItem 
    ***/
    
    auto temp = head;
    std::shared_ptr<FoodItem> searchedFoodItem = nullptr;
    bool found = false;
    try {
        if (ID.length() > IDLEN) {
            throw std::invalid_argument("Invalid ID length");
        }
        while (temp && !found) {
            if (temp->dataFood->getID() == ID) {
                searchedFoodItem = temp->dataFood; // assign to the empty ptr
                found = true;
            }
            temp = temp->next;
        }
    } catch (const std::runtime_error& e) {
        cout << "Error: "<< e.what() << endl;
        throw;
    } catch (const std::invalid_argument& e) {
        cout << "Error: "<< e.what() << endl;
        throw;
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


void LinkedList::addNewFood(std::map<std::string, std::shared_ptr<Node>>& refMap) {
    string addFoodId = "";
    string addFoodName = "";
    string addFoodDesc = "";
    string addFood="";
    string addFoodPrice = "";
    bool freeSlotAvailable = true;
    bool done = false;
        
    /*  Check the range of the next food ID to be added (current list size + 1) and append to end of appropriate ID
        Eg: if next ID 1 digit long, append to an ID string that is missing 1 digit
        If next is 2 digits long, append to ID that is missing 2 digits, etc
        Caps at 4 digits. If next ID is 5 digits, display error message and cancel adding a new item.
    */
    if (mySize + 1 <= 9) {
        addFoodId = "F000";
    }
    else if (mySize + 1 > 9 && mySize + 1 < 100) {
        addFoodId = "F00";
    }
    else if (mySize + 1 > 99 && mySize + 1 < 1000) {
        addFoodId = "F0";
    }
    else if (mySize + 1 > 999 && mySize + 1 < 10000) {
        addFoodId = "F";
    }
    else {
        cout << "Maximum number of food items reached!\n";
        freeSlotAvailable = false;
    }

    if (freeSlotAvailable){
        // Still able to add food
        addFoodId.append(to_string(mySize + 1));
    }

    while (freeSlotAvailable && !done) {
        cout << "\nThe new meal item will have the item id of " << addFoodId;
        cout << "\nEnter the item name: ";
        getline(cin, addFoodName);
        bool isNameGood = true;

        for (char c : addFoodName) { // checks if the name contains non-alphabetic char
            if (!std::isalpha(c)) {
                cout << "Error: Name contains non-alphabetic character" << endl;
                isNameGood = false;
            }
        }

        if (isNameGood && addFoodName.length() <= NAMELEN) {
            while (isNameGood && !done) {
                cout << "\nEnter the item description: ";
                getline(cin, addFoodDesc);
                bool isDescGood = true;

                if (addFoodDesc.length() <= DESCLEN) { // validating Desc input
                    while (isDescGood && !done) {
                        cout << "\nEnter the item price: ";
                        getline(cin, addFoodPrice);

                        if (addFoodPrice.find('.') > addFoodPrice.length() || !Helper::isNumber(addFoodPrice)) {
                            cout << "Error: money is not formatted correctly. (<dollars>.<cents>)";
                        }
                        else {
                            auto newFood = make_shared<FoodItem>(addFoodId, addFoodName, addFoodDesc, stod(addFoodPrice));
                            insertNewPairtoMap(newFood, refMap); // Orderly insertion with use of refMap
                            cout << "New food item added to the menu!" << endl;
                            done = true;
                        }
                    }
                    
                } else {
                    cout << "Error: Desc is too long" << endl;
                }
            }
        } else if (addFoodName.length() > NAMELEN) {
            cout << "Error: Name is too long" << endl;
        } 
    }
}


void LinkedList::insertNewPairtoMap(shared_ptr<FoodItem>& newFoodData, map<string, shared_ptr<Node>>& refMap) {
    /***
     * @brief This functions create a new pair {<Food Name>, <shared_ptr<FoodItem>>} and then insert
     * into the refMap
     * @param newFoodData A shared_ptr points to the newly added FoodItem
     * @param refMap A map that stored Food Name as keys and a shared_ptr points to FoodItem objects  
    ***/

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
}


// the function is currently searching for pair via ID (which should be via names)
void LinkedList::deleteFood(map<string, shared_ptr<Node>>& refMap) {
    /***
     * @brief This function takes in Food ID, locate the pair that holds the pointer to the correct
     * FoodItem object and then delete it from the refMap.
     * @param foodID specified food ID
     * @param refMap A map that stored Food Name as keys and a shared_ptr points to FoodItem objects
    ***/

    try {
        string foodIdSelection = "";
        cout << "Please enter the ID of the food to remove from the menu: ";
        cin >> foodIdSelection;

        // return a shared_ptr that points towards that Food Item
        std::shared_ptr<FoodItem> chosenFoodItem = searchFoodItemByID(foodIdSelection);

        // Find the correct pair in the refMap
        auto it = refMap.find(chosenFoodItem->getName());
        if (it == refMap.end()) {
            cout << "Food item with ID " << foodIdSelection << " not found." << endl;
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

            cout << "Food item with ID " << foodIdSelection << " has been removed from the system." << endl;
        }
    } catch (const std::runtime_error& e) {
        cout << "Error: "<< e.what() << endl;
        throw;
    } catch (const std::invalid_argument& e) {
        cout << "Error: "<< e.what() << endl;
        throw;
    }
    
}



LinkedList::~LinkedList() {} // shared_ptr automatically deletes nodes when the last reference goes out of scope


int LinkedList::getSize(){
    return mySize;
}