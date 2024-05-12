/*Manul compile command because make isn't making a runnable file for some reason...
  g++ -Wall -Werror -std=c++14 -O -o ftt main.cpp Coin.cpp Helper.cpp LinkedList.cpp Node.cpp
 ./ftt
*/

#include <limits>
#include <algorithm>
#include "Node.h"
#include "LinkedList.h"
#include "Helper.h"
#include <map>
#include <cmath>
#include <fstream>
#include <string.h>


#define MENU_DESC "Main Menu:\n1. Display Meal Options\n2. Purchase Meal\n3. Save and Exit\n\
Administrator-Only Menu:\n4. Add Food\n5. Remove Food\n6. Display Balance\n7. Abort Program\n\
Select your option (1-7) :\n\n\
DEBUG: 9. LinkedList test/demo implementation "

using std::map;
using std::vector;
using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::stoi;
using std::to_string;
using std::fstream;
using std::ostream;



void LinkedListDemo(int argc);
bool verifyFoodFile(char ** argv,LinkedList& foodList, map<string,shared_ptr<Node>>& refMap);
bool verifyCoinsFile(int argc, char ** argv);

int main(int argc, char ** argv){

    int menuChoice = 0;
    bool mainMenuLoop = false;
    bool verifyFiles = true;
    string foodIdSelection = "";

    if (argc != 3) {
        cout << "Incorrect number of arguments supplied.\n";
        mainMenuLoop = false;
        verifyFiles = false;
    }
    //Correct number of argument, initialize an empty food linked list
    LinkedList foods;
    map<string,shared_ptr<Node>> refMap;
    if (verifyFiles) {
        if (verifyFoodFile(argv,foods,refMap) == true) {
            cout << "about to check coins";
            if (verifyCoinsFile(argc, argv) == true) {
                mainMenuLoop = true;
            }
        }
    }

    while (mainMenuLoop) {
        cout << MENU_DESC;
        cin >> menuChoice;
        cin.ignore();


            if (cin.fail()) {
                cin.clear();
                cin.ignore();
                cout << "\nError in input. Please try again.\n";
                menuChoice=0;
            }
            
            else if (menuChoice == 1) {
                cout << "\nFood Menu\n";
                cout << "\n---------";
                cout << "\nID |Name                                                |Length";
                cout << "\n------------------------------------------------------------------\n";
                foods.printItemsBrief();
                cout << "\n";
                
            } 
            else if (menuChoice == 2) {
                bool payingForItem = false;

                cout << "\nPurchase Meal";
                cout << "\n-------------";
                cout << "\nPlease enter the ID of the food you wish to purchase: ";
                cin >> foodIdSelection;
                //Assume food id selected is valid
                unsigned int foodPrice=refMap[foodIdSelection]->dataFood->price;
                //TODO: Make it so you can press enter to exit back to menu
                cout << "\nYou have selected: " << foodIdSelection << ". This will cost you " << foodPrice << "\n\n";
                cout << "Please hand over the money - type in the value of each note/coin in cents.";
                cout << "\nPlease enter ctrl-D or enter on a new line to cancel this purchase.";
                cout << "You still need to give us: " << foodPrice << "\n";
                
                string inputChange = "";
                payingForItem = true;

                while (payingForItem) {
                    getline(cin, inputChange);
                    //cin >> inputChange;
                    //cin.ignore();

                    if (cin.fail()) {
                        // if (cin.isEof()) payingForItem=false;
                        cin.clear();
                        cin.ignore();
                        cout << "Error: input was not numeric";
                    }

                    else if (cin.get() == '\n') {
                        cout << "\nPurchase cancelled.";
                        payingForItem = false;
                    }
                    
                    else {
                        //Anh note: when you 
                        cout << "\nPlaceholder: still need to do the menu payment functionality.\n";
                        payingForItem = false;
                    }
                }

            } 

            else if (menuChoice == 3) {
                cout << "\nSaving data...";
                cout << "\nSAVING TBD\n\n";
                //Once save completed, exit so
                menuChoice=7;
            } 
            else if (menuChoice == 4) {
                string addFoodName = "";
                string addFoodDesc = "";
                string addFoodPrice = "";
                bool inputtingPrice = false;

                cout << "\nThe new meal item will have the item id of " << "<ID HERE>";
                cout << "Enter the item name: ";
                cin >> addFoodName;
                cout << "Enter the item description: ";
                cin >> addFoodDesc;

                inputtingPrice = true;

                while (inputtingPrice) {
                    cout << "Enter the item price: ";
                    cin >> addFoodPrice;

                    if (addFoodPrice.find('.') > addFoodPrice.length()) {
                        cout << "Error: money is not formatted correctly";
                    }
                    else {
                       cout << "\n\nFood name: " << addFoodName << "\nFood desc: " << addFoodDesc << "Food price: " << addFoodPrice;

                       //How do I just add a new item to the linked list simply?
                        //How do I get the values of a food item at a certain position in the LL? Why does getItem just return 0?

                       //foods.getItem(2);
                       //FoodItem data = foods.getItem(2);
                       //make_shared<FoodItem>("asdf", addFoodName, addFoodDesc, addFoodPrice);
                    //foods.addEnd(make_shared<FoodItem>("asdf", addFoodName, addFoodDesc, addFoodPrice));
                        inputtingPrice = false;
                    }
                    
                }
            } 
            else if (menuChoice == 5) {
                cout << "Please enter the ID of the food to remove from the menu: ";
                cin >> foodIdSelection;
                cout << "<ITEM ID, NAME, DESC HERE> has been removed from the system";
            } 
            else if (menuChoice == 6) {
                cout << "\n\nBalance Summary";
                cout << "\n---------------";
                cout << "\nDenom  | Quantity | Value";
                cout << "\n---------------------------";
                cout << "\nCOIN FILE DETAILS GET PRINTED HERE AS A TABLE\n\n";
            } 
            else if (menuChoice == 7) {
                mainMenuLoop = false;
            } 
            else if (menuChoice == 9) {
                LinkedListDemo(argc);
            } 
            else if (menuChoice < 1 || menuChoice > 9 ) {
                cout << "\nError: number was outside of range.\n";
            }
    }

    return EXIT_SUCCESS;
    
 
}

bool verifyFoodFile(char ** argv, LinkedList& foodList, map<string,shared_ptr<Node>>& refMap) {
    bool success = false;

    string foodFile = argv[1];
    string currentLine = "";
    vector<string> lineSplit;
    vector<string> price;

    fstream file;
    file.open(foodFile);
    int foodCounter=0;

    // Ordered-map, so then 
    //If the whole file is valid, the foods will be add to
    // linked list in an order ordered by name
    map<string,vector<string>> nameAndFoodData; 

    if (file.is_open()) {
        while (getline(file, currentLine)) {
            Helper::splitString(currentLine, lineSplit, "|");

                if (lineSplit.size() == 4) {
                    Helper::splitString(lineSplit[3], price, ".");
                }
                
                //If there aren't exactly 4 pieces of data per line
                if (lineSplit.size() != 4) {
                    success = false;
                    file.close();
                }
                //If the first letter of the food code isn't F
                else if (lineSplit[0][0] != 'F') {
                    success = false;
                    file.close();
               } 
                //If the price is not a decimal number
                else if (!lineSplit[3].find(".")) {
                    success = false;
                    file.close();
                }
                //If there is no cents place
                else if (price.size() != 2) {
                        cout << "\nIs not a full decimal number!";
                        success = false;
                        file.close();
                }
                else {
                    success = true;
                    foodCounter++;
                    nameAndFoodData[lineSplit[1]]=lineSplit;//Store data mapping to map
            }
        }
        if (success){
        //Only initialize food linked list if the whole process is success
            for (auto &key:nameAndFoodData){
                auto newFoodItem = make_shared<FoodItem>(key.second[0], key.second[1], key.second[2], stod(key.second[3]));
                // Add the food item to list by sorted name due to ordered map key property
                refMap[key.second[0]]=foodList.addEnd(newFoodItem); 
            }
        }
    file.close();
    
    }
    cout << "\n\n" << success;
    return success;
}

bool verifyCoinsFile(int argc, char** argv) {
    bool success = false;
    string coinFile = argv[2];
    string currentLine = "";
    vector <string> coinsSplit;

    fstream file;

    cout << coinFile;

    file.open(coinFile);
    if (file.is_open()) {
        while (getline(file, currentLine)) {
            Helper::splitString(currentLine, coinsSplit, ",");

            if (coinsSplit.size() != 2) {
                success = false;
                file.close();
            }
            else if (!Helper::isNumber(coinsSplit[0]) || !Helper::isNumber(coinsSplit[1])) {
                success = false;
                file.close();
            }
            else {
                success = true;
            }
            
        }
        file.close();
    }
    return success;
}

void LinkedListDemo(int argc) {
        
    // assume inputs are of correct format
    //Get number of queries
    if (argc ==1 || argc ==3 || argc==4) {
        Helper helperObject; // Create an instance of Helper
        //argc is 4 when testing with text file input, 3 when take 2 files and run in terminal
        int n=0;
        string numInp="";
        cout << "Enter number of queries:\t";
        getline(cin,numInp);
        n=stoi(numInp);
        for (int i=0; i < n;i++){    //Get input
            int nNodes=0;
            vector<string> ins = helperObject.takeInput( nNodes);
            nNodes=stoi(ins.back());
            
            
            //Take in the list of nodes value   
            vector<int> arr; //vector that holds the node values
            cout << "Total number of nodes:\t"<< nNodes<<"\n";
            for (int i = 0; i < nNodes; i++){
                arr.push_back(stoi(ins[i].c_str()));
            }
            //Make a linked list object using above values
            LinkedList ll(arr,nNodes);
            //Operations to be performed
            string order = ins[1];
            if (order == "AF") ll.addFront(stoi(ins[nNodes + 1].c_str()));
            else if (order == "AE") ll.addEnd(stoi(ins[nNodes + 1].c_str()));
            else if (order == "AP") ll.addAtPosition(stoi(ins[nNodes + 1].c_str()), stoi(ins[nNodes + 2].c_str()));
            else if (order == "DF") ll.deleteFront();
            else if (order == "DE") ll.deleteEnd();
            else if (order == "DP") ll.deletePosition(stoi(ins[nNodes + 1].c_str()));
            else if (order == "S") ll.search(stoi(ins[nNodes + 1].c_str()));
            else if (order == "GI") ll.getItem(stoi(ins[nNodes + 1].c_str()));
            else cout << "Invalid command\n";
            //Print out result
            ll.printItems();
        }

        // Done linked list non-food demo
        cout <<"The following is for demonstration purposes, to be removed.\n";
        cout << "No input is required.\n";
        
        //Initialize the coins denom
        vector<int> coinsExample={1,4, 7,9};
        for (int i=0;i<7;i++){
            coinsExample.push_back(coinsExample[i]*10);
        }
        vector<int> coinCounts(coinsExample.size(),DEFAULT_COIN_COUNT);
        cout <<"current coins denominator:\t";helperObject.vectorPrint(coinsExample);
        cout <<"current amounts:\t";helperObject.vectorPrint(coinCounts);

        vector<int> changeTest={2,135,502,4750,5210};
        for (auto& n:changeTest){
            cout <<"For n = "<<n<<endl;
            int changes=helperObject.change_making(coinsExample,coinCounts,n);
            if (changes > 0){
                cout <<"New count:\n\t";
                helperObject.vectorPrint(coinCounts);
            }
        }
        cout << "Dummy food item map:\n";
        //Inplace of reading input from file:
        map<string, vector<string>> foods;
        foods["F0001"]={"F0001","Name1","Desc1","8.50"};
        foods["F0003"]={"F0003","Name3","Desc3","28.50"};
        foods["F0002"]={"F0002","Name2","Desc2","18.50"};
        // Map to keep references to the food items
        map<int, shared_ptr<Node>> refMap;
        LinkedList foodList;
        //Only do this once is sure the input is valid!
        //Put in try catch to handle missed invalid input that cause access problems
        for (auto& k:foods){
            cout <<k.first <<" ";
            helperObject.vectorPrint<string>(k.second);
            // Creating a shared_ptr FoodItem
                auto newFoodItem = make_shared<FoodItem>(k.second[0], k.second[1], k.second[2], stod(k.second[3])*100);

            // Add to LinkedList and store in map for reference
            refMap[stoi(k.second[0].substr(k.second[0].length()-3,3))]=foodList.addEnd(newFoodItem);
        }
        string userInput="";
        bool keepGoing = true;
        while (keepGoing) {
            cout << "Enter a food item key , or 'X' to stop): ";
            std::getline(std::cin, userInput);
            keepGoing = ! ((userInput=="X") || (userInput=="x")) ;
            // Validate input
            if (keepGoing){
                int key = 0;
                try {
                    key = stoi(userInput);
                    if (key <= 0) {
                    throw std::invalid_argument("Invalid key: Must be a positive integer.");
                    }
                } catch (const std::invalid_argument& e) {
                    std::cerr << "Error: " << e.what() << endl;
                
                } catch (const std::out_of_range& e) {
                    std::cerr << "Error: Input value out of range." << std::endl;
                }

                // Check if key exists in refMap
                if (refMap.count(key) == 0) {
                    std::cerr << "Error: Key " << key << " not found in reference map." << endl;
                    continue; // Skip to next iteration if key doesn't exist
                }

                // Access the corresponding FoodItem using the key
                shared_ptr<Node> nodePtr = refMap[key];
                if (nodePtr)  nodePtr->dataFood->printInfo();
                else std::cerr << "Error: Unexpected error retrieving FoodItem." << std::endl;
            }
        }
    }else{
        //Incorrect number of file inputs
        cout << "Expect 2 file inputs!\n";
        cout << "Usage: ./main coin.dat food.dat\n";
    }
        
}