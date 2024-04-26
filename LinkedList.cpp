#include "Node.h"
#include "LinkedList.h"
#include <vector>
#include <iostream>
#include <limits>

using namespace std;
//size of the linked list
LinkedList::LinkedList(){
    //Constructor with empty head
    head = NULL;
    mySize = 0;
}
LinkedList::LinkedList(vector<int> a, int n){
    //Create a list from a given array
    for (int i = n - 1; i > -1; i--){
        addFront(a[i]);
    }
}

//Adding 
void LinkedList::addFront(int nI){
    //Add a new node to the begining of list
    mySize++; //Increment size as it is added
    //head ref , use to advoid segfault
    Node ** hf = &head;
    //Create a new node object
    Node * newbie = new Node(nI,NULL);
    newbie->next=head;
    // cout <<"Checking data:\n\t"<<newbie->data<<"\n";
    //Change the pointer head is pointing to this new node
    *hf = newbie;
}

void LinkedList::addEnd(int nI) {
  // Add a new node to the end of list
  mySize++;
  // Head reference, use to avoid segfault
  Node** hf = &head;
  // Create a new node object with the data
  Node* newbie = new Node(nI, NULL);
  // Incase the list is currently empty
  if (*hf == NULL) {
    *hf = newbie;
  } else {
    // Else
    // Get the last node in the current list
    Node* temp = *hf;
    while (temp->next != NULL) {
      temp = temp->next;
    }
    // Newbie is now the last node of the list
    temp->next = newbie;
  }
}

void LinkedList::addAtPosition(int pos, int nI) {
  // Add a new node to the given position
  if (pos < 1) {
    addFront(nI);
    // Stop the function since adding is complete
  }
  else if (pos > mySize) {
    addEnd(nI);
    // Stop the function since adding is complete
  }
  else{
    // Head reference, use to avoid segfault
    Node** hf = &head;

    // The node before pos
    Node* now = *hf;
    // Create a new node object with the data
    Node* newbie = new Node(nI, NULL);
    while (pos > 2) {
        now = now->next;
        pos--;
    }
    newbie->next = now->next;
    now->next = newbie;
    mySize++;
   }
}


//Removing

void LinkedList::deleteFront() {
  // Delete the first node
  // If the list is empty then exit
  if (mySize == 0) {
    return;
  }
  // Head reference, use to avoid segfault
  Node** hf = &head;
  Node* temp = *hf;
  (*hf) = temp->next;
  delete temp;
  mySize--;
}

void LinkedList::deleteEnd() {
  // Delete the final node
  // If the list is empty then exit
  if (mySize == 0) {
    return;
  }
  // Head reference, use to avoid segfault
  Node** hf = &head;
  // The node before the last node (or head if there's only one node)
  Node* temp = *hf;
  while (temp->next != NULL) {
    if (temp->next->next != NULL) {
      temp = temp->next;
    } else {
      break;
    }
  }
  mySize--;
  // Handle cases where there's only one node (temp points to it)
  if (temp->next == NULL) {
    *hf = NULL;
  } else {
    // Delete the last node
    delete temp->next;
    temp->next = NULL;
  }
}

void LinkedList::deletePosition(int pos) {
  // Delete the node at the given position

  // Invalid position given
  if (pos < 1 || pos > mySize) {
    cout << "outside range\n";
    return;
  }

  if (pos == 1) {
    deleteFront();
    return;
  }

  // Reduce size by 1
  mySize--;

  // Head reference, use to avoid segfault
  Node** hf = &head;
  Node* temp = *hf;

  // Special case: Delete the last node
  if (pos == mySize) {
    // Get the second-last node (temp points to it)
    while (temp->next->next != NULL) {
      temp = temp->next;
    }
    // Delete the last node
    delete temp->next;
    temp->next = NULL;
  }

  else{// Get the node that points to the node at pos
    for (int i = 1; i < pos - 1; i++) {
        temp = temp->next;
    }

    // Store the node to be deleted
    Node* toDelete = temp->next;

    // Link the previous node to the node after the one to be deleted
    temp->next = toDelete->next;

    // Free the memory of the deleted node
    delete toDelete;
  }
}


void LinkedList::printItems(){   
    //Print data values of all current nodes in the list
    if (head == NULL){
        return;
    }
    //Head reference
    Node ** hf = &head;
    Node * now = (*hf);

    vector<int> out;
    int size = 1;
    out.push_back(now->data);
    while (now->next != NULL){
        now = now->next;
        out.push_back(now->data );
        size++;
    }
    for (int v = 0; v  < size; v++){
        cout << out[v] << " ";
    }cout <<endl;
}

int LinkedList::search(int item){
    /*Print out the position of a node that contains a given 
      value if exist, else print 0 */
    int pos = 1;
    Node * temp = *(&head);
    while (temp != NULL){
        if (temp->data == item){
          cout << pos <<"\n";
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
        cout << numeric_limits<int>::max() << "\n";
        return numeric_limits<int>::max();
    }
    
    Node* temp = head;
    for (int pos = 1; temp != nullptr && pos <= p; ++pos, temp = temp->next) {
        if (pos == p) {
            cout << temp->data << "\n";
            return temp->data;
        }
    }
    
    cout << numeric_limits<int>::max() << "\n";
    return numeric_limits<int>::max();
}

//List destructor
LinkedList::~LinkedList(){
    //Delete all remaining nodes
    while (mySize > 0){
        deleteFront();
    }
}