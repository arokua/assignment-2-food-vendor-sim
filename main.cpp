#include <limits>
#include <algorithm>
#include "Node.h"
#include "LinkedList.h"
#include "Helper.h"
#include "Coin.h"
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <map>
#include <memory>
#include <stdexcept>

#define MENU_DESC "Main Menu:\n1. Display Meal Options\n2. Purchase Meal\n3. Save and Exit\n\
Administrator-Only Menu:\n4. Add Food\n5. Remove Food\n6. Display Balance\n7. Abort Program\n\
Select your option (1-7) :\n"

using std::cin;
using std::cout;
using std::endl;
using std::fstream;
using std::make_shared;
using std::map;
using std::ofstream;
using std::ostream;
using std::shared_ptr;
using std::stoi;
using std::string;
using std::to_string;
using std::vector;

// Define the first 3 basic coin types
#define fiveCents 5
#define tenCents 10
#define twentyCents 20
#define totalDenomsTypes 10
#define definedDenoms 3
#define decimalMax 9 // value of maximum single digit in decimal base
// Formatting for balance output printing
#define significant_figures 2
#define numeroUno 1       // Number one, for no magic number
#define maxFoodID "F9999" // Maximum available food ID

// Demo run for a linked list of simple node type (containing only integers)
void LinkedListDemo(int argc);
// Verify data in food file is correct, if correct then create a map to store the values in alphabetical orders
// Then insert that into the food LinkedList by iterating over the map key-value pairs
bool verifyFoodFile(char **argv, LinkedList &foodList, map<string, shared_ptr<Node>> &refMap);
// Verify coin file, should the file be valid, populate one map and two vectors
bool verifyCoinsFile(char **argv, map<Coin, int> &coinMap);

int main(int argc, char **argv)
{
    int menuChoice = 0;
    bool mainMenuLoop = false;
    bool verifyFiles = true;

    string foodIdSelection = "";

    if (argc != 3)
    {
        cout << "Incorrect number of arguments supplied.\n";
        mainMenuLoop = false;
        verifyFiles = false;
    }

    // Correct number of arguments, initialize an empty food linked list
    LinkedList foods;
    map<string, shared_ptr<Node>> refMap;

    // // Assume the type of denominations are set // Old coin balance idea
    // // Create an empty map of coin denominations to their amount
    // vector<int> denominations = {fiveCents, tenCents, twentyCents};
    // vector<int> coinCounts;

    // // Populate the denominations using the pattern
    // for (int i = 0; i < totalDenomsTypes - definedDenoms; i++) {
    //     denominations.push_back(denominations[i] * 10);
    // }

    map<Coin, int> coinMap;

    if (verifyFiles)
    {
        // First, verify if food file is correct, if correct populate
        // Then start verifying coin files
        bool correctFoodFile = verifyFoodFile(argv, foods, refMap);
        if (correctFoodFile)
        {
            bool success = verifyCoinsFile(argv, coinMap);
            if (success)
            {
                mainMenuLoop = true;
                //cout << "Success\n";
            }
        }
        verifyFiles = false;
        //cout << "Done verifying files!\n";
    }
    vector<shared_ptr<Coin>> cashRegister;
    for (auto &entry : coinMap)
    {
        cashRegister.push_back(make_shared<Coin>(entry.first));
    }

    Helper helperObject; // Create an instance of helper to call some of its functions
    string dumbInput = "";
    while (mainMenuLoop)
    {
        // foods.getItemDetails(8);

        cout << MENU_DESC;

        dumbInput = helperObject.processInput();
        if (dumbInput == "||")
        {
            cout << "\nError in input. Please try again.\n";
            cin.clear();
            mainMenuLoop = false;
        }
        else
        {
            try
            {
                // If input is not EOF or '\n' and is a number
                menuChoice = stoi(dumbInput);
                if (menuChoice == 1)
                {
                    cout << "\nFood Menu";
                    cout << "\n---------";
                    cout << "\nID |Name                                                |Length";
                    cout << "\n------------------------------------------------------------------\n";
                    foods.printItems(); // Print the food out
                    cout << "\n";
                }
                else if (menuChoice == 2)
                {
                    cout << "\nPurchase Meal";
                    cout << "\n-------------\n";
                    bool purchaseSuccess = Coin::purchaseMeal(foods, cashRegister);
                    if (purchaseSuccess)
                    {
                        // Update the original coin map based on the new coin counts
                        coinMap.clear();
                        for (auto &coin : cashRegister)
                        {
                            coinMap[*coin] = coin->getCount();
                        }
                    }
                }

                // Save and exit
                else if (menuChoice == 3)
                {
                    cout << "\nSaving data.";
                    string currentLine = "";
                    ofstream foodSaveFile("food.dat");

                    /*
                        Go through each linked list item
                        Get all details of current item/node in the linked list, in a format suitable for saving as a string
                        Append that to the new save file
                    */
                    if (foodSaveFile.is_open())
                    {
                        for (int i = 0; i < foods.getSize(); i++)
                        {
                            currentLine = foods.getItemDetails(i);
                            // cout << currentLine;
                            foodSaveFile << currentLine;
                        }
                    }
                    foodSaveFile.close();

                    cout << "\nSave completed. Now exiting...\n\n";
                    // Once save completed, exit so
                    mainMenuLoop = false;
                }
                else if (menuChoice == 4)
                {
                    string addFoodId = "";
                    string addFoodName = "";
                    string addFoodDesc = "";
                    string addFood = "";
                    string addFoodPrice = "";
                    bool freeSlotAvailable = true;
                    bool inputtingPrice = false;

                    cout << "\n\n\nFoods size: " << "\n"
                         << to_string(foods.getSize()) << "\n\n";

                    /*  (Chris)
                        Stupid brute force way to get a proper food ID because I couldn't figure out our specific LL implementation in time
                        (I hate this so fucking much)

                        Check the range of the next food ID to be added (current list size + 1) and append to end of appropriate ID
                        Eg: if next ID 1 digit long, append to an ID string that is missing 1 digit
                        If next is 2 digits long, append to ID that is missing 2 digits, etc
                        Caps at 4 digits. If next ID is 5 digits, display error message and cancel adding a new item.
                    */
                    if (foods.getSize() + 1 <= 9)
                    {
                        addFoodId = "F000";
                    }
                    else if (foods.getSize() + 1 > 9 && foods.getSize() + 1 < 100)
                    {
                        addFoodId = "F00";
                    }
                    else if (foods.getSize() + 1 > 99 && foods.getSize() + 1 < 1000)
                    {
                        addFoodId = "F0";
                    }
                    else if (foods.getSize() + 1 > 999 && foods.getSize() + 1 < 10000)
                    {
                        addFoodId = "F";
                    }
                    else
                    {
                        cout << "Maximum number of food items reached!\n";
                        freeSlotAvailable = false;
                    }

                    if (freeSlotAvailable)
                    {
                        // Still able to add food
                        addFoodId.append(to_string(foods.getSize() + 1));
                        cout << "\n\n"
                             << addFoodId;

                        cout << "\nThe new meal item will have the item id of " << addFoodId;
                        cout << "\nEnter the item name: ";
                        addFoodName = helperObject.processInput();
                        if (addFoodName != "||" && addFoodName != "|")
                        {

                            // Exit option when pressed enter
                            cout << "\nEnter the item description: ";
                            addFoodDesc = helperObject.processInput();
                            if (addFoodDesc != "||" && addFoodDesc != "|")
                                inputtingPrice = true;
                            else
                            {
                                freeSlotAvailable = false;
                                cin.clear();
                                menuChoice = 0;
                            }
                        }
                        else
                        {
                            freeSlotAvailable = false;
                            cin.clear();
                            menuChoice = 0;
                        }

                        while (inputtingPrice)
                        {
                            cout << "\nEnter the item price: ";
                            getline(cin, addFoodPrice);

                            if (addFoodPrice.find('.') > addFoodPrice.length())
                            {
                                cout << "Error: money is not formatted correctly";
                            }
                            else
                            {
                                auto newFood = make_shared<FoodItem>(addFoodId, addFoodName, addFoodDesc, stod(addFoodPrice));
                                foods.insert(newFood, refMap); // Orderly insertion with use of refMap

                                inputtingPrice = false;
                            }
                        }
                    }
                }
                else if (menuChoice == 5)
                {
                    cout << "Please enter the ID of the food to remove from the menu: ";
                    foodIdSelection = helperObject.processInput();
                    while (foodIdSelection == "||")
                    {
                        cout << "Invalid input. Please try again: ";
                        cin.clear();
                        foodIdSelection = helperObject.processInput();
                    }
                    foods.deleteFood(foodIdSelection, refMap);
                }
                else if (menuChoice == 6)
                {
                    cout << "\n\nBalance Summary";
                    cout << "\n---------------";
                    cout << "\nDenom  | Quantity | Value";
                    cout << "\n---------------------------\n";
                    double sum = 0;
                    for (auto &k : coinMap)
                    {
                        double thisTypeTotal = k.first.denom * (k.second / 100.0);
                        cout << k.first.denom << "|\t" << k.second << "|\t" << "$ " << std::fixed
                             << std::setprecision(significant_figures + 1) << thisTypeTotal << "\n";
                        sum += thisTypeTotal;
                    }
                    cout << "---------------------------\n";
                    cout << "\t\t  $ " << std::fixed << std::setprecision(significant_figures) << sum << "\n";
                }
                else if (menuChoice == 7)
                {
                    mainMenuLoop = false;
                }
                else if (menuChoice < 1 || menuChoice > 9)
                {
                    cout << "\nError: number was outside of range.\n";
                }
            }
            catch (std::invalid_argument &e)
            {
                cout << "\nError: " << e.what() << "\n";
                cout << "Not a number!\n";
            }
        }
    }

    return EXIT_SUCCESS;
}

bool verifyFoodFile(char **argv, LinkedList &foodList, map<string, shared_ptr<Node>> &refMap)
{
    bool success = false;

    string foodFile = argv[1];
    string currentLine = "";
    vector<string> lineSplit;
    vector<string> price;

    fstream file;
    file.open(foodFile);
    int foodCounter = 0;

    // Ordered-map, so then
    // If the whole file is valid, the foods will be add to
    // linked list in an order ordered by name
    map<string, vector<string>> nameAndFoodData;

    if (file.is_open())
    {
        while (getline(file, currentLine))
        {
            Helper::splitString(currentLine, lineSplit, "|");

            if (lineSplit.size() == 4)
            {
                Helper::splitString(lineSplit[3], price, ".");
            }

            // If there aren't exactly 4 pieces of data per line
            if (lineSplit.size() != 4)
            {
                success = false;
                file.close();
            }
            // If the first letter of the food code isn't F
            else if (lineSplit[0][0] != 'F')
            {
                success = false;
                file.close();
            }
            // If the price is not a decimal number
            else if (!lineSplit[3].find("."))
            {
                success = false;
                file.close();
            }
            // If there is no cents place
            else if (price.size() != 2)
            {
                cout << "\nIs not a full decimal number!";
                success = false;
                file.close();
            }
            else
            {
                success = true;
                foodCounter++;
                nameAndFoodData[lineSplit[1]] = lineSplit; // Store data mapping to map
            }
        }
        if (success)
        {
            // Only initialize food linked list if the whole process is success
            for (auto &key : nameAndFoodData)
            {
                auto newFoodItem = make_shared<FoodItem>(key.second[0], key.second[1], key.second[2], stod(key.second[3]));
                refMap[key.second[0]] = foodList.addEnd(newFoodItem);
            }
        }
        file.close();
    }
    cout << "\n\n";
    return success;
}

bool verifyCoinsFile(char **argv, map<Coin, int> &coinMap)
{
    bool success = false;
    string coinFile = argv[2];
    string currentLine = "";
    vector<string> coinsSplit;

    fstream file;

    //cout << coinFile << "\n";

    file.open(coinFile);
    if (file.is_open())
    {
        while (getline(file, currentLine))
        {
            Helper::splitString(currentLine, coinsSplit, ",");

            if (coinsSplit.size() != 2)
            {
                cout << "Invalid coin line, invalid number of commas!\n";
                success = false;
                file.close();
            }
            else if (!Helper::isNumber(coinsSplit[0]) || !Helper::isNumber(coinsSplit[1]))
            {
                cout << "Non-numerical arguments!\n";
                cout << coinsSplit[0] << " " << coinsSplit[1] << endl; // Debugging
                success = false;
                file.close();
            }
            else
            {
                int coinType = stoi(coinsSplit[0]);
                int amount = stoi(coinsSplit[1]);
                Denomination denom = static_cast<Denomination>(coinType);

                Coin coin(denom, 0); // Temporary Coin object with count 0

                if (coinMap.find(coin) != coinMap.end())
                {
                    coinMap[coin] += amount; // Update existing coin count
                }
                else
                {
                    coinMap[coin] = amount; // Add new coin with count
                }
                success = true;
            }
        }
        file.close();
    }
    //cout << "Check coin file is success: " << success << "\n";
    return success;
}


// Hung stuff
std::map<Denomination, int> readCoinDataFileintoMap(const std::string &fileName)
{
    std::string line;
    std::fstream openfile(fileName);
    std::map<Denomination, int> coinMap;

    try
    {
        if (false)
        {
            throw std::runtime_error("Invalid coin data file!");
        }

        std::fstream openfile(fileName); // re-open file data
        if (openfile.is_open())
        {
            while (std::getline(openfile, line))
            { // reading each line in the file
                // skip empty line
                if (!line.empty())
                {
                    std::vector<std::string> dataVector;
                    // splitting data with "|" delimiter
                    Helper::splitString(line, dataVector, COIN_DELIM);

                    if (std::stoi(dataVector[1]) >= 0)
                    {
                        bool duplication = false;

                        for (auto &coin : coinMap)
                        { // if the Denom exists, increase the counts on the existed Denom
                            if (coin.first == std::stoi(dataVector[0]))
                            {
                                duplication = true;
                                coin.second += std::stoi(dataVector[1]);
                            }
                        }

                        // if not, create new pair in the map
                        if (!duplication)
                        {
                            if (std::stoi(dataVector[0]) == 5)
                            {
                                coinMap.insert({Denomination::FIVE_CENTS, std::stoi(dataVector[1])});
                            }
                            else if (std::stoi(dataVector[0]) == 10)
                            {
                                coinMap.insert({Denomination::TEN_CENTS, std::stoi(dataVector[1])});
                            }
                            else if (std::stoi(dataVector[0]) == 20)
                            {
                                coinMap.insert({Denomination::TWENTY_CENTS, std::stoi(dataVector[1])});
                            }
                            else if (std::stoi(dataVector[0]) == 50)
                            {
                                coinMap.insert({Denomination::FIFTY_CENTS, std::stoi(dataVector[1])});
                            }
                            else if (std::stoi(dataVector[0]) == 100)
                            {
                                coinMap.insert({Denomination::ONE_DOLLAR, std::stoi(dataVector[1])});
                            }
                            else if (std::stoi(dataVector[0]) == 200)
                            {
                                coinMap.insert({Denomination::TWO_DOLLARS, std::stoi(dataVector[1])});
                            }
                            else if (std::stoi(dataVector[0]) == 500)
                            {
                                coinMap.insert({Denomination::FIVE_DOLLARS, std::stoi(dataVector[1])});
                            }
                            else if (std::stoi(dataVector[0]) == 1000)
                            {
                                coinMap.insert({Denomination::TEN_DOLLARS, std::stoi(dataVector[1])});
                            }
                            else if (std::stoi(dataVector[0]) == 2000)
                            {
                                coinMap.insert({Denomination::TWENTY_DOLLARS, std::stoi(dataVector[1])});
                            }
                            else if (std::stoi(dataVector[0]) == 5000)
                            {
                                coinMap.insert({Denomination::FIFTY_DOLLARS, std::stoi(dataVector[1])});
                            }
                        }
                    }
                    else
                    {
                        throw std::invalid_argument("Invalid data arguments!"); // invalid counts
                    }
                    dataVector.clear();
                }
            }

            openfile.close();
        }
        else
        { // if can't locate/open data file
            throw std::ifstream::failure("Failed to open file");
        }
    }
    catch (const std::ifstream::failure &e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }
    catch (const std::invalid_argument &e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }
    catch (const std::runtime_error &e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }

    return coinMap;
}

// since there's a fileReader function, this verification only needs to pass in the reference file
bool isFoodFileValid(std::fstream &fileStream)
{
    bool success = false;
    string currentLine = "";
    vector<string> lineSplit;
    vector<string> price;

    try
    {
        if (fileStream.is_open())
        {
            while (getline(fileStream, currentLine))
            {
                // skip empty line
                if (!currentLine.empty())
                {
                    // splitting data
                    Helper::splitString(currentLine, lineSplit, FOODITEM_DELIM); // "|"

                    // check if the data is sufficient
                    if (lineSplit.size() == FOODITEM_ARGC)
                    { // 4
                        // If the first letter of the food code isn't F
                        if (lineSplit[0][0] != 'F')
                        {
                            throw std::invalid_argument("The ID does not follow the correct format!");
                        }
                        else
                        {
                            // If the rest of the ID char are not ints
                            for (size_t i = 1; i < lineSplit[0].size(); i++)
                            {
                                if (!isdigit(lineSplit[0][i]))
                                {
                                    throw std::invalid_argument("The ID does not follow the correct format!");
                                }
                            }
                        }

                        // If the price is not a double number
                        Helper::splitString(lineSplit[3], price, ".");
                        if (!lineSplit[3].find(".") || price.size() != 2)
                        {
                            throw std::invalid_argument("The price does not follow the correct format!");
                        }

                        success = true;
                    }

                    else
                    { // If there aren't exactly 4 pieces of data per line
                        throw std::invalid_argument("Invalid number of data arguments!");
                    }
                }
            }
            fileStream.close();
        }
        else
        { // if can't locate/open data file
            throw std::ifstream::failure("Failed to open file");
        }
    }
    catch (const std::ifstream::failure &e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }
    catch (const std::invalid_argument &e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }
    return success;
}
