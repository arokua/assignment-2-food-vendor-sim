/*Manul compile command because make isn't making a runnable file for some reason...
  g++ -Wall -Werror -std=c++14 -O -o ftt main.cpp Coin.cpp Helper.cpp LinkedList.cpp Node.cpp
 ./ftt
*/
#include <limits>
#include <algorithm>
#include <map>
#include <string>
#include <iostream>
#include <cmath>
#include <fstream>

#include "Node.h"
#include "LinkedList.h"
#include "Helper.h"

#define MENU_DESC "Main Menu:\n1. Display Meal Options\n2. Purchase Meal\n3. Save and Exit\n\
Administrator-Only Menu:\n4. Add Food\n5. Remove Food\n6. Display Balance\n7. Abort Program\n\
Select your option (1-7) :\n\n\
DEBUG: 99. LinkedList test/demo implementation "

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

//Move this inside a method somewhere?

void LinkedListDemo(int argc);
bool isFoodFileValid(std::fstream& fileStream);
bool isCoinFileValid(std::fstream& fileStream);


std::vector<std::shared_ptr<FoodItem>> readFoodDataFile(const std::string& fileName);
std::vector<std::shared_ptr<Coin>> readCoinDataFile(const std::string& fileName);



int main(int argc, char ** argv){

    // int menuChoice = 0;
    // bool mainMenuLoop = true;
    // string foodIdSelection = "";

    // while (mainMenuLoop == true) {
    //     cout << MENU_DESC;
    //     cin >> menuChoice;
    //     cin.ignore();
    // int menuChoice = 0;
    // bool mainMenuLoop = false;
    // bool verifyFiles = true;
    // string foodIdSelection = "";

    // if (argc != 3) {
    //     cout << "Incorrect number of arguments supplied.";
    //     mainMenuLoop = false;
    //     verifyFiles = false;
    // }

    // if (verifyFiles) {
    //     if (verifyFoodFile(argc, argv) == true) {
    //         cout << "about to check coins";
    //         if (verifyCoinsFile(argc, argv) == true) {
    //             mainMenuLoop = true;
    //         }
    //     }
    // }

    // while (mainMenuLoop) {
    //     cout << MENU_DESC;
    //     cin >> menuChoice;
    //     cin.ignore();

    //     if (menuChoice == 1) {
    //         cout << "\nFood Menu\n";
    //         cout << "\n---------";
    //         cout << "\nID |Name                                                |Length";
    //         cout << "\n------------------------------------------------------------------\n";
    //         cout << "\n LINKED LIST ITEMS WILL GO HERE";
    //     } 
    //     else if (menuChoice == 2) {
    //         cout << "\nPurchase Meal";
    //         cout << "\n-------------";
    //         cout << "\nPlease enter the ID of the food you wish to purchase: ";
    //         cin >> foodIdSelection;
    //         cout << "\nSelected: " << foodIdSelection << "\n\n";
    //     } 
    //     else if (menuChoice == 3) {
    //         cout << "\nSaving data...";
    //         cout << "\nSAVING TBD\n\n";
    //     } 
    //     else if (menuChoice == 4) {
    //         string addFoodName = "";
    //         string addFoodDesc = "";
    //         float addFoodPrice = 0.00;

    //         cout << "\nThe new meal item will have the item id of " << "<ID HERE>";
    //         cout << "Enter the item name: ";
    //         cin >> addFoodName;
    //         cout << "Enter the item description: ";
    //         cin >> addFoodDesc;
    //         cout << "Enter the item price: ";
    //         cin >> addFoodPrice;
    //         cout << "\n\nFood name: " << addFoodName << "\nFood desc: " << addFoodDesc << "Food price: " << addFoodPrice;
    //     } 
    //     else if (menuChoice == 5) {
    //         cout << "Please enter the ID of the food to remove from the menu: ";
    //         cin >> foodIdSelection;
    //         cout << "<ITEM ID, NAME, DESC HERE> has been removed from the system";
    //     } 
    //     else if (menuChoice == 6) {
    //         cout << "\n\nBalance Summary";
    //         cout << "\n---------------";
    //         cout << "\nDenom  | Quantity | Value";
    //         cout << "\n---------------------------";
    //         cout << "\nCOIN FILE DETAILS GET PRINTED HERE AS A TABLE\n\n";
    //     } 
    //     else if (menuChoice == 7) {
    //         mainMenuLoop = false;
    //     } 
    //      else if (menuChoice == 99) {
    //         LinkedListDemo(argc);
    //     } 
    // }

    readFoodDataFile(argv[1]);
    cout << endl;
    readCoinDataFile(argv[2]);

    return EXIT_SUCCESS;
    
 
}


// missing file validation
// check for data shuffle
// Assuming each data input are unique

std::vector<std::shared_ptr<FoodItem>> readFoodDataFile(const std::string& fileName){
    std::string line;
    std::fstream openfile(fileName);
    std::vector<std::shared_ptr<FoodItem>> objectVector;

    try {
        if (!isFoodFileValid(openfile)) {
            throw std::runtime_error("Invalid food data file!");
        }

        std::fstream openfile(fileName); // re-open file data
        if (openfile.is_open()) {
            while(std::getline(openfile, line)) {
                // reading each line in the file
                std::vector<std::string> dataVector;
                // splitting data with "|" delimiter
                Helper::splitString(line, dataVector, FOODITEM_DELIM);

                // new Object for each FoodItem
                std::shared_ptr<FoodItem> newObject = std::make_shared<FoodItem>(dataVector[0], dataVector[1], dataVector[2], std::stod(dataVector[3]) * 100);
                objectVector.push_back(newObject);
                dataVector.clear();
            }
            openfile.close();

        } else { // if can't locate/open data file
            throw std::ifstream::failure("Failed to open file");
        }
    } catch (const std::ifstream::failure& e) {
        std::cout << "Error: " << e.what() << std::endl;
    } catch (const std::runtime_error& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    
    // printing out FoodItem
    for (size_t i = 0; i < objectVector.size(); i++) {
        objectVector[i]->printInfo();
    }

    // return a vector containing shared_ptr pointing to each Object
    return objectVector;
}


// Assuming each data input are unique
std::vector<std::shared_ptr<Coin>> readCoinDataFile(const std::string& fileName){
    std::string line;
    std::fstream openfile(fileName);
    std::vector<std::shared_ptr<Coin>> coinVector;

    try {
        if (!isCoinFileValid(openfile)) {
            throw std::runtime_error("Invalid coin data file!");
        }

        std::fstream openfile(fileName); // re-open file data
        if (openfile.is_open()) {
            while(std::getline(openfile, line)) {
                // reading each line in the file
                std::vector<std::string> dataVector;
                // splitting data with "|" delimiter
                Helper::splitString(line, dataVector, COIN_DELIM);

                // Pointers to new Coin object
                std::shared_ptr<Coin> newObject;
                if (std::stoi(dataVector[0]) == 5) {
                    newObject = std::make_shared<Coin>(Denomination::FIVE_CENTS, std::stoi(dataVector[1]));

                } else if (std::stoi(dataVector[0]) == 10) {
                    newObject = std::make_shared<Coin>(Denomination::TEN_CENTS, std::stoi(dataVector[1]));

                } else if (std::stoi(dataVector[0]) == 20) {
                    newObject = std::make_shared<Coin>(Denomination::TWENTY_CENTS, std::stoi(dataVector[1]));

                } else if (std::stoi(dataVector[0]) == 50) {
                    newObject = std::make_shared<Coin>(Denomination::FIFTY_CENTS, std::stoi(dataVector[1]));

                } else if (std::stoi(dataVector[0]) == 100) {
                    newObject = std::make_shared<Coin>(Denomination::ONE_DOLLAR, std::stoi(dataVector[1]));

                } else if (std::stoi(dataVector[0]) == 200) {
                    newObject = std::make_shared<Coin>(Denomination::TWO_DOLLARS, std::stoi(dataVector[1]));

                } else if (std::stoi(dataVector[0]) == 500) {
                    newObject = std::make_shared<Coin>(Denomination::FIVE_DOLLARS, std::stoi(dataVector[1]));

                } else if (std::stoi(dataVector[0]) == 1000) {
                    newObject = std::make_shared<Coin>(Denomination::TEN_DOLLARS, std::stoi(dataVector[1]));

                } else if (std::stoi(dataVector[0]) == 2000) {
                    newObject = std::make_shared<Coin>(Denomination::TWENTY_DOLLARS, std::stoi(dataVector[1]));

                } else if (std::stoi(dataVector[0]) == 5000) {
                    newObject = std::make_shared<Coin>(Denomination::FIFTY_DOLLARS, std::stoi(dataVector[1]));
                } 
                else {
                    throw std::invalid_argument("Invalid data arguments!");
                }
                coinVector.push_back(newObject);
                dataVector.clear();
            } 

            openfile.close();
        } else { // if can't locate/open data file
            throw std::ifstream::failure("Failed to open file");
        }
        
    } catch (const std::ifstream::failure& e) {
        std::cout << "Error: " << e.what() << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cout << "Error: " << e.what() << std::endl;
    } catch (const std::runtime_error& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    
    // printing out Coin
    for (size_t i = 0; i < coinVector.size(); i++) {
        coinVector[i]->printInfo();
    }

    // return a vector containing shared_ptr pointing to each Object
    return coinVector;
}


// REMEMBER TO CHECK FOR WHITESPACE
// since there's a fileReader function, this verification only needs to pass in the reference file
bool isFoodFileValid(std::fstream& fileStream) {
        bool success = false;
        string currentLine = "";
        vector<string> lineSplit;
        vector<string> price;

        try {
            if (fileStream.is_open()) {
                while (getline(fileStream, currentLine)) {
                    // for debug
                    // cout << currentLine << endl;
                    
                    Helper::splitString(currentLine, lineSplit, FOODITEM_DELIM); // "|"

                    if (lineSplit.size() == FOODITEM_ARGC) { // 4
                        // If the first letter of the food code isn't F
                        if (lineSplit[0][0] != 'F') {
                            throw std::invalid_argument("The ID does not follow the correct format!");
                        } else {
                            // If the rest of the ID char are not ints
                            for (long unsigned int i = 1; i < lineSplit[0].size(); i++) {
                                if (!isdigit(lineSplit[0][i])) {
                                    throw std::invalid_argument("The ID does not follow the correct format!");
                                }
                            }
                        }

                        //If the price is not a double number
                        Helper::splitString(lineSplit[3], price, ".");
                        if (!lineSplit[3].find(".") || price.size() != 2) {
                            throw std::invalid_argument("The price does not follow the correct format!");
                        }

                        success = true;
                    }
                    
                    else { //If there aren't exactly 4 pieces of data per line
                        throw std::invalid_argument("Invalid number of data arguments!");
                    }
                }
                fileStream.close();

            } else { // if can't locate/open data file
                throw std::ifstream::failure("Failed to open file");
            }
        } catch (const std::ifstream::failure& e) {
            std::cout << "Error: " << e.what() << std::endl;
        } catch (const std::invalid_argument& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
        return success;
}


bool isCoinFileValid(std::fstream& fileStream) {
    bool success = false;
    string currentLine = "";
    vector <string> coinsSplit;

    try {
        if (fileStream.is_open()) {
            while (getline(fileStream, currentLine)) {
                // for debug
                // cout << currentLine << "\n";

                Helper::splitString(currentLine, coinsSplit, COIN_DELIM); // ","
                    if (coinsSplit.size() == COIN_ARGC) { // 2
                        // If the data are not int
                        if (!stoi(coinsSplit[0]) || !stoi(coinsSplit[1]) ) {
                            throw std::invalid_argument("The coins data does not follow the correct format!");
                        } 
                        success = true;
                    }
                    
                    else { //If there aren't exactly 2 pieces of data per line
                        throw std::invalid_argument("Invalid number of data arguments!");
                    }
            }
            fileStream.close();
        }
    } catch (const std::invalid_argument& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    return success;
}

// void LinkedListDemo(int argc) {
        
//     // assume inputs are of correct format
//     //Get number of queries
//     if (argc ==1 || argc ==3 || argc==4) {
//         //argc is 4 when testing with text file input, 3 when take 2 files and run in terminal
//     //     int n=0;
//     //     string numInp="";
//     //     if (argc==3) cout << "File names:\t" << argv[1]<<", "<< argv[2]<<endl;
//     //     cout << "Enter number of queries:\t";
//     //     getline(cin,numInp);
//     //     n=stoi(numInp);
//     //     for (int i=0; i < n;i++){    //Get input
//     //         int nNodes=0;
//     //         vector<string> ins = takeInput( nNodes);
//     //         nNodes=stoi(ins.back());
            
            
//     //         //Take in the list of nodes value   
//     //         vector<int> arr; //vector that holds the node values
//     //         cout << "Total number of nodes:\t"<< nNodes<<"\n";
//     //         for (int i = 0; i < nNodes; i++){
//     //             arr.push_back(stoi(ins[i].c_str()));
//     //         }
//     //         //Make a linked list object using above values
//     //         LinkedList ll(arr,nNodes);
//     //         //Operations to be performed
//     //         string order = ins[nNodes];
//     //         if (order == "AF") ll.addFront(stoi(ins[nNodes + 1].c_str()));
//     //         else if (order == "AE") ll.addEnd(stoi(ins[nNodes + 1].c_str()));
//     //         // else if (order == "AP") ll.addAtPosition(stoi(ins[nNodes + 1].c_str()), stoi(ins[nNodes + 2].c_str()));
//     //         else if (order == "DF") ll.deleteFront();
//     //         else if (order == "DE") ll.deleteEnd();
//     //         else if (order == "DP") ll.deletePosition(stoi(ins[nNodes + 1].c_str()));
//     //         else if (order == "S") ll.search(stoi(ins[nNodes + 1].c_str()));
//     //         else if (order == "GI") ll.getItem(stoi(ins[nNodes + 1].c_str()));
//     //         else cout << "Invalid command\n";
//     //         //Print out result
//     //         ll.printItems();
//     //     }
//     // }else{
//     //     //Incorrect number of file inputs
//     //     cout << "Expect 2 file inputs!\n";
//     //     cout << "Usage: ./main coin.dat food.dat\n";
//     // }
//         cout <<"The following is for demonstration purposes, to be removed.\n";
//         cout << "No input is required.\n";
//         Helper helperObject; // Create an instance of Helper
//         //Initialize the coins denom
//         vector<int> coinsExample={1,4, 7,9};
//         for (int i=0;i<7;i++){
//             coinsExample.push_back(coinsExample[i]*10);
//         }
//         vector<int> coinCounts(coinsExample.size(),DEFAULT_COIN_COUNT);
//         cout <<"current coins denominator:\t";helperObject.vectorPrint(coinsExample);
//         cout <<"current amounts:\t";helperObject.vectorPrint(coinCounts);

//         vector<int> changeTest={2,135,502,4750,5210};
//         for (auto& n:changeTest){
//             cout <<"For n = "<<n<<endl;
//             int changes=helperObject.change_making(coinsExample,coinCounts,n);
//             if (changes > 0){
//                 cout <<"New count:\n\t";
//                 helperObject.vectorPrint(coinCounts);
//             }
//         }
//         cout << "Dummy food item map:\n";
//         //Inplace of reading input from file:
//         map<string, vector<string>> foods;
//         foods["F0001"]={"F0001","Name1","Desc1","8.50"};
//         foods["F0003"]={"F0003","Name3","Desc3","28.50"};
//         foods["F0002"]={"F0002","Name2","Desc2","18.50"};
//         // Map to keep references to the food items
//         map<int, shared_ptr<Node>> refMap;
//         LinkedList foodList;
//         //Only do this once is sure the input is valid!
//         //Put in try catch to handle missed invalid input that cause access problems
//         for (auto& k:foods){
//             cout <<k.first <<" ";
//             helperObject.vectorPrint<string>(k.second);
//             // Creating a shared_ptr FoodItem
//                 auto newFoodItem = make_shared<FoodItem>(k.second[0], k.second[1], k.second[2], stod(k.second[3])*100);

//             // Add to LinkedList and store in map for reference
//             refMap[stoi(k.second[0].substr(k.second[0].length()-3,3))]=foodList.addEnd(newFoodItem);
//         }
//         string userInput="";
//         bool keepGoing = true;
//         while (keepGoing) {
//             cout << "Enter a food item key , or 'X' to stop): ";
//             std::getline(std::cin, userInput);
//             keepGoing = ! ((userInput=="X") || (userInput=="x")) ;
//             // Validate input
//             if (keepGoing){
//                 int key = 0;
//                 try {
//                     key = stoi(userInput);
//                     if (key <= 0) {
//                     throw std::invalid_argument("Invalid key: Must be a positive integer.");
//                     }
//                 } catch (const std::invalid_argument& e) {
//                     std::cerr << "Error: " << e.what() << endl;
                
//                 } catch (const std::out_of_range& e) {
//                     std::cerr << "Error: Input value out of range." << std::endl;
//                 }

//                 // Check if key exists in refMap
//                 if (refMap.count(key) == 0) {
//                     std::cerr << "Error: Key " << key << " not found in reference map." << endl;
//                     continue; // Skip to next iteration if key doesn't exist
//                 }

//                 // Access the corresponding FoodItem using the key
//                 shared_ptr<Node> nodePtr = refMap[key];
//                 if (nodePtr)  nodePtr->dataFood->printInfo();
//                 else std::cerr << "Error: Unexpected error retrieving FoodItem." << std::endl;
//             }
//         }

//     }
//     else {
//         //Incorrect number of file inputs
//         cout << "Expect 2 file inputs!\n";
//         cout << "Usage: ./main coin.dat food.dat\n";
//     }
// }