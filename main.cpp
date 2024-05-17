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
#include "Coin.h"

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

bool isFoodFileValid(std::fstream& fileStream);
bool isCoinFileValid(std::fstream& fileStream);

std::map<std::string ,std::shared_ptr<Node>> readFoodDataFile(const std::string& fileName);
std::vector<std::shared_ptr<Coin>> readCoinDataFile(const std::string& fileName);



int main(int argc, char ** argv){

    int menuChoice = 0;
    bool mainMenuLoop = false;
    bool verifyFiles = true;
    string foodIdSelection = "";

    // will be disable when doing tests
    if (argc != 3) {
        cout << "Incorrect number of arguments supplied.\n";
        mainMenuLoop = false;
        verifyFiles = false;
    }

    std::vector<std::shared_ptr<Coin>> coinVector = readCoinDataFile(argv[2]);

    std::map<std::string, std::shared_ptr<Node>> refMap = readFoodDataFile(argv[1]);

    LinkedList foodsLinkedList(refMap);
    
    cout << endl;

    while(true) {
        if (Coin::purchaseMeal(foodsLinkedList, coinVector)) {
            cout << endl;
            for (size_t i = 0; i < coinVector.size(); i++) {
                coinVector[i]->printInfo();
            }
            return EXIT_SUCCESS;
        } else {}
    }
    
    //Correct number of argument, initialize an empty food linked list
    //Assumme the type of denominations are set

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
                foodsLinkedList.printItems();
                cout << "\n";
                
            } 
            else if (menuChoice == 2) {
                bool payingForItem = false;

                cout << "\nPurchase Meal";
                cout << "\n-------------";
                
                Coin::purchaseMeal(foodsLinkedList, coinVector);
                } 

            else if (menuChoice == 3) {
                cout << "\nSaving data...";
                cout << "\nSAVING TBD\n\n";
                //Once save completed, exit so
                menuChoice=7;
            } 
            else if (menuChoice == 4) {
                string addFoodId = "";
                string addFoodName = "";
                string addFoodDesc = "";
                string addFoodPrice = "";
                bool freeSlotAvailable = true;
                bool inputtingPrice = false;
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
                cout << "\n---------------------------\n";
                double sum=0;
                for (auto& k : myBalance){
                    double thisTypeTotal = k.first * (k.second / 100.0);
                    cout << k.first <<"|\t"<< k.second<<"|\t"<<"$ "<< std::fixed 
                    << std::setprecision(significant_figures+1)<< thisTypeTotal<<"\n";
                    sum+=thisTypeTotal;
                }
                cout << "---------------------------\n";
                cout <<"\t\t  $ "<< std::fixed << std::setprecision(significant_figures)<<sum<<"\n";
            } 
            else if (menuChoice == 7) {
                mainMenuLoop = false;
            } 
            else if (menuChoice < 1 || menuChoice > 7 ) {
                cout << "\nError: number was outside of range.\n";
            }
    }

    return EXIT_SUCCESS;
    
 
}


    


    


// Assuming each data input are unique
std::map<std::string, std::shared_ptr<Node>> readFoodDataFile(const std::string& fileName){
    /***
     * @brief This function reads the data file, then create a pair which has food name as key and a shared_ptr to the FoodItem object as value
     * then the pair will be inserted into a map
     * @param fileName The file name
     * @cond Only if isFoodFileValid returns True (this function check if the food file follows a set format or not) 
    ***/

    std::string line;
    std::fstream openfile(fileName);
    std::map<std::string ,std::shared_ptr<Node>> foodNodeMap;

    try {
        if (!isFoodFileValid(openfile)) {
            throw std::runtime_error("Invalid food data file!");
        }

        std::fstream openfile(fileName); // re-open file data
        if (openfile.is_open()) {
            while(std::getline(openfile, line)) {
                // check for empty line -> skip
                if (!line.empty()) {
                    // reading each line in the file
                    std::vector<std::string> dataVector;
                    // splitting data with "|" delimiter
                    Helper::splitString(line, dataVector, FOODITEM_DELIM);

                    // a shared_ptr for each FoodItem object
                    std::shared_ptr<FoodItem> newObject = std::make_shared<FoodItem>(dataVector[0], dataVector[1], dataVector[2], std::stod(dataVector[3]));
                    std::shared_ptr<Node> newNode = std::make_shared<Node>(newObject);

                    // inserting the pair into the map
                    foodNodeMap.insert({dataVector[1], newNode});

                    dataVector.clear();
                }  
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
    // for (auto& pair : foodNodeMap) {
    //     cout << pair.first << endl;
    //     pair.second->dataFood->printInfo();
    // }

    // return a map with FoodItem name as key and the value containing shared_ptr pointing to each Object
    return foodNodeMap;
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
            while(std::getline(openfile, line)) { // reading each line in the file
                // skip empty line
                if (!line.empty()) {
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
    // for (long unsigned int i = 0; i < coinVector.size(); i++) {
    //     coinVector[i]->printInfo();
    // }

    // return a vector containing shared_ptr pointing to each Coin
    return coinVector;
}


// since there's a fileReader function, this verification only needs to pass in the reference file
bool isFoodFileValid(std::fstream& fileStream) {
        bool success = false;
        string currentLine = "";
        vector<string> lineSplit;
        vector<string> price;

        try {
            if (fileStream.is_open()) {
                while (getline(fileStream, currentLine)) {    
                    // skip empty line
                    if (!currentLine.empty()) {
                        // splitting data
                        Helper::splitString(currentLine, lineSplit, FOODITEM_DELIM); // "|"

                        // check if the data is sufficient
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
                        
                        else { // If there aren't exactly 4 pieces of data per line
                            throw std::invalid_argument("Invalid number of data arguments!");
                        }
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
                if (!currentLine.empty()) {
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
            }
            fileStream.close();
        }
    } catch (const std::invalid_argument& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    return success;
}