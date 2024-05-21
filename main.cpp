#include <fstream>

#include "Node.h"
#include "LinkedList.h"
#include "Helper.h"
#include "Coin.h"

#define MENU_DESC "\nMain Menu:\n1. Display Meal Options\n2. Purchase Meal\n3. Save and Exit\n\
Administrator-Only Menu:\n4. Add Food\n5. Remove Food\n6. Display Balance\n7. Abort Program\n\
Select your option (1-7): "

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

bool isFoodFileValid(std::fstream& fileStream);
bool isCoinFileValid(std::fstream& fileStream);

std::map<std::string ,std::shared_ptr<Node>> readFoodDataFile(const std::string& fileName);
std::vector<std::shared_ptr<Coin>> readCoinDataFile(const std::string& fileName);

std::map<Denomination, int> readCoinDataFileintoMap(const std::string& fileName);

void updateFoodFile(LinkedList& foodsLinkedList, const string& fileName);
void updateCoinFile(vector<std::shared_ptr<Coin>>& coinsVector, const string& fileName);

// this sorting function is used to specifically sort coin vector
void insertionSortIncrementally(std::vector<std::shared_ptr<Coin>>& coinsVector);


int main(int argc, char ** argv){
    int menuChoice = 0;
    bool mainMenuLoop = false;
    string foodIdSelection = "";

    if (argc != 3) {
        cout << "Incorrect number of arguments supplied." << endl;
        cout << "./ftt <food file> <coin file>" << endl;
        mainMenuLoop = false;

    }

    std::vector<std::shared_ptr<Coin>> coinVector = readCoinDataFile(argv[2]);
    std::map<std::string, std::shared_ptr<Node>> refMap = readFoodDataFile(argv[1]);
    LinkedList foodsLinkedList(refMap);

    std::map<Denomination, int> coinMap = readCoinDataFileintoMap(argv[2]);


    cout << "Coin Vector" << endl;
    for (auto coin : coinVector) {
        coin->printInfo();
    }
    cout << endl;
    cout << "Linked List\t" << foodsLinkedList.getSize() << endl;
    foodsLinkedList.printMenuFood();
    cout << endl;


    mainMenuLoop = true;

    while(mainMenuLoop) {

        cout << MENU_DESC;
        cin.clear();
        cin >> menuChoice;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore();
            cout << "\nError in input. Please try again.\n";
            menuChoice = 0;
        }

        else if (cin.eof()) {
            cin.clear();
            cin.ignore();
            cout << "\nEOF has been detected. Exiting the program\n";
            menuChoice = 0;
            mainMenuLoop = false;
        }
        
        else if (menuChoice == 1) {
            foodsLinkedList.printMenuFood();
        } 
        else if (menuChoice == 2) {
            // bool payingForItem = false;
            cout << "\nPurchase Meal";
            cout << "\n-------------\n";
            Coin::purchaseMeal(foodsLinkedList, coinVector);
        } 
        else if (menuChoice == 3) {
            // argv[1] is food file, argv [2] is coin file
            updateFoodFile(foodsLinkedList, argv[1]);
            updateCoinFile(coinVector, argv[2]);
            mainMenuLoop = false;
        } 
        else if (menuChoice == 4) {
            string addFoodId = "";
            string addFoodName = "";
            string addFoodDesc = "";
            string addFood="";
            string addFoodPrice = "";
            bool freeSlotAvailable = true;
            bool inputtingPrice = false;

            cout << "\n\n\nFoods size: " << "\n" << foodsLinkedList.getSize() << "\n\n";
                
            /*  Check the range of the next food ID to be added (current list size + 1) and append to end of appropriate ID
                Eg: if next ID 1 digit long, append to an ID string that is missing 1 digit
                If next is 2 digits long, append to ID that is missing 2 digits, etc
                Caps at 4 digits. If next ID is 5 digits, display error message and cancel adding a new item.
            */
            if (foodsLinkedList.getSize() + 1 <= 9) {
                addFoodId = "F000";
            }
            else if (foodsLinkedList.getSize() + 1 > 9 && foodsLinkedList.getSize() + 1 < 100) {
                addFoodId = "F00";
            }
            else if (foodsLinkedList.getSize() + 1 > 99 && foodsLinkedList.getSize() + 1 < 1000) {
                addFoodId = "F0";
            }
            else if (foodsLinkedList.getSize() + 1 > 999 && foodsLinkedList.getSize() + 1 < 10000) {
                addFoodId = "F";
            }
            else {
                cout << "Maximum number of food items reached!\n";
                freeSlotAvailable = false;
            }

            if (freeSlotAvailable) {
                // Still able to add food
                addFoodId.append(to_string(foodsLinkedList.getSize() + 1));
                cout << "\n\n" << addFoodId;

                cout << "\nThe new meal item will have the item id of " << addFoodId;
                cout << "\nEnter the item name: ";
                getline(cin, addFoodName);
                cout << "\nEnter the item description: ";
                getline(cin, addFoodDesc);

                inputtingPrice = true;

                while (inputtingPrice) {
                    cout << "\nEnter the item price: ";
                    getline(cin, addFoodPrice);

                    if (addFoodPrice.find('.') > addFoodPrice.length()) {
                        cout << "Error: money is not formatted correctly";
                    }
                    else {
                        auto newFood = make_shared<FoodItem>(addFoodId, addFoodName, addFoodDesc, stod(addFoodPrice));
                        foodsLinkedList.insert(newFood, refMap); // Orderly insertion with use of refMap
                        
                        inputtingPrice = false;
                    }
                }
            }
        } 

        else if (menuChoice == 5) {
            cout << "Please enter the ID of the food to remove from the menu: ";
            cin >> foodIdSelection;
            foodsLinkedList.deleteFood(foodIdSelection, refMap);
        } 
        else if (menuChoice == 6) {
            Coin::displayBalance(coinVector);
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

                    // check if the data is unique or not
                    if (foodNodeMap.find(dataVector[1]) != foodNodeMap.end()) {
                        throw std::invalid_argument("Data has already existed!");
                    }

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
    } catch (const std::invalid_argument& e) {
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


std::vector<std::shared_ptr<Coin>> readCoinDataFile(const std::string& fileName){
    /***
     * @brief This function reads the data file, then create a shared_ptr which points to the Coin object
     * @param fileName The file name
     * @cond Only if isCoinFileValid returns True (this function check if the coin file follows a set format or not) 
    ***/

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

                    if (std::stoi(dataVector[1]) >= 0) {
                        bool duplication = false;

                        for (auto& coinptr : coinVector) { // if the Denom exists, increase the counts on the existed Denom
                            if (coinptr->getDenom() == std::stoi(dataVector[0])) {
                                duplication = true;
                                coinptr->setCount(coinptr->getCount() + std::stoi(dataVector[1]));  
                            }
                        }

                        // if not, create new ptr to the new object
                        if (!duplication) {
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
                                throw std::invalid_argument("Invalid data arguments!"); // invalid Denom
                            }
                        }
                        
                    } else {
                        throw std::invalid_argument("Invalid data arguments!"); // invalid counts 
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
    // for (size_t i = 0; i < coinVector.size(); i++) {
    //     coinVector[i]->printInfo();
    // }

    // return a vector containing shared_ptr pointing to each Coin
    return coinVector;
}


void updateFoodFile(LinkedList& foodsLinkedList, const string& fileName){
    /***
     * @brief Updating the food file by iterating through the vector and overwrite
     * existing file
     * @param foodsLinkedList Linked list that holds food information
     * @param fileName File name that was passed in the command line argument
    ***/
    cout << "\nSaving data...." << endl;
    string currentLine = "";
    std::ofstream foodSaveFile(fileName);
    /*
        Go through each linked list item
        Get all details of current item/node in the linked list, in a format suitable for saving as a string
        Append that to the new save file
    */
    if (foodSaveFile.is_open()) {
        for (int i = 0; i < foodsLinkedList.getSize(); i++) {
            currentLine = foodsLinkedList.getItemDetails(i);
            // cout << currentLine;
            foodSaveFile << currentLine;
        }
    }
    foodSaveFile.close();

    cout << "\nSave completed. Now exiting...\n\n";
    // Once save completed, exit so
}


void updateCoinFile(vector<std::shared_ptr<Coin>>& coinsVector, const string& fileName){
    /***
     * @brief Updating the coin file by iterating through the vector and overwrite
     * existing file
     * @param coinsVector Vector that contains coins information
     * @param fileName File name that was passed in the command line argument
    ***/
    cout << "\nSaving data....." << endl;
    string currentLine = "";
    std::ofstream coinSaveFile(fileName);
    
    if (coinSaveFile.is_open()) {
        for (auto& denom : coinsVector) {
            currentLine = denom->getDenom() + "," + denom->getCount();
            // cout << currentLine;
            coinSaveFile << currentLine;
        }
    }
    coinSaveFile.close();

    cout << "\nSave completed. Now exiting...\n\n";
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
                                for (size_t i = 1; i < lineSplit[0].size(); i++) {
                                    if (!isdigit(lineSplit[0][i])) {
                                        throw std::invalid_argument("The ID does not follow the correct format!");
                                    }
                                }
                            }

                            // validating each data length
                            if (lineSplit[0].length() > IDLEN) {
                                throw std::invalid_argument("An error in ID detected!");
                            }

                            if (lineSplit[1].length() > NAMELEN) {
                                throw std::invalid_argument("An error in Name detected!");
                            }

                            if (lineSplit[2].length() > DESCLEN) {
                                throw std::invalid_argument("An error in Description detected!");
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
    vector<string> coinsSplit;
    vector<string> price;

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


// map version of the readCoinDataFile function
std::map<Denomination, int> readCoinDataFileintoMap(const std::string& fileName) {
    std::string line;
    std::fstream openfile(fileName);
    std::map<Denomination, int> coinMap;

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

                    if (std::stoi(dataVector[1]) >= 0) {
                        bool duplication = false;

                        for (auto& coin : coinMap) { // if the Denom exists, increase the counts on the existed Denom
                            if (coin.first == std::stoi(dataVector[0])) {
                                duplication = true;
                                coin.second += std::stoi(dataVector[1]);  
                            }
                        }

                        // if not, create new pair in the map
                        if (!duplication) {
                            if (std::stoi(dataVector[0]) == 5) {
                                coinMap.insert({Denomination::FIVE_CENTS, std::stoi(dataVector[1])});

                            } else if (std::stoi(dataVector[0]) == 10) {
                                coinMap.insert({Denomination::TEN_CENTS, std::stoi(dataVector[1])});

                            } else if (std::stoi(dataVector[0]) == 20) {
                                coinMap.insert({Denomination::TWENTY_CENTS, std::stoi(dataVector[1])});

                            } else if (std::stoi(dataVector[0]) == 50) {
                                coinMap.insert({Denomination::FIFTY_CENTS, std::stoi(dataVector[1])});

                            } else if (std::stoi(dataVector[0]) == 100) {
                                coinMap.insert({Denomination::ONE_DOLLAR, std::stoi(dataVector[1])});

                            } else if (std::stoi(dataVector[0]) == 200) {
                                coinMap.insert({Denomination::TWO_DOLLARS, std::stoi(dataVector[1])});

                            } else if (std::stoi(dataVector[0]) == 500) {
                                coinMap.insert({Denomination::FIVE_DOLLARS, std::stoi(dataVector[1])});

                            } else if (std::stoi(dataVector[0]) == 1000) {
                                coinMap.insert({Denomination::TEN_DOLLARS, std::stoi(dataVector[1])});

                            } else if (std::stoi(dataVector[0]) == 2000) {
                                coinMap.insert({Denomination::TWENTY_DOLLARS, std::stoi(dataVector[1])});

                            } else if (std::stoi(dataVector[0]) == 5000) {
                                coinMap.insert({Denomination::FIFTY_DOLLARS, std::stoi(dataVector[1])});
                            }
                        }
                            
                    } else {
                        throw std::invalid_argument("Invalid data arguments!"); // invalid counts 
                    }
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

    return coinMap;
}


void insertionSortIncrementally(std::vector<std::shared_ptr<Coin>>& coinsVector) {
    // this sorting function is used to specifically sort coin vector
    for (size_t i = 1; i < coinsVector.size(); ++i) {
        auto key = coinsVector[i];
        int j = i - 1;

        // Move elements of vec[0..i-1], that are greater than key->denom, to one position ahead of their current position
        while (j >= 0 && coinsVector[j]->denom > key->denom) {
            coinsVector[j + 1] = coinsVector[j];
            --j;
        }
        coinsVector[j + 1] = key;
    }
}