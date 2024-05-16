#include "Coin.h"
#include "LinkedList.h"
#include "Helper.h"

#include <iostream>

Coin::Coin(Denomination denom, unsigned count) {
    this->denom = denom;
    this->count = count;
}

Coin::Coin() :
    denom(Denomination::FIVE_CENTS), count(0) {}

void Coin::printInfo(){
    std::cout << denom << "," << count << std::endl;
}

Denomination Coin::getDenom() {
    return denom;
}

unsigned Coin::getCount() {
    return count;
}

void Coin::setCount(unsigned count) {
    this->count = count;
}



bool Coin::isMoneyValidforPurchase(unsigned int input){
    /***
    * @brief Function to check if the input is a valid denomination for purchase
    * Since user are not allowed to input a combination of note/coins ie 300 (200 + 100)
    ***/
    return input == Denomination::FIVE_CENTS || 
           input == Denomination::TEN_CENTS || 
           input == Denomination::TWENTY_CENTS || 
           input == Denomination::FIFTY_CENTS || 
           input == Denomination::ONE_DOLLAR || 
           input == Denomination::TWO_DOLLARS || 
           input == Denomination::FIVE_DOLLARS || 
           input == Denomination::TEN_DOLLARS || 
           input == Denomination::TWENTY_DOLLARS || 
           input == Denomination::FIFTY_DOLLARS;
}


void Coin::purchaseMeal(std::string foodItemID, LinkedList& list, std::vector<std::shared_ptr<Coin>> cashRegister, unsigned int currentPayment) {
    /***
    * @brief Purchasing meal function that finds the FoodItem based on ID and will return change
    * to users after several procedure steps
    * @param foodItemID The ID of the food
    * @param list Linkedlist containing the Food Items
    * @param currentBalance The shop's current coin/node vector
    * @param currentPayment records user's current FoodItem/Payment (not yet finalised) 
    ***/

    // search and create a pointer to the object
    std::shared_ptr<FoodItem> chosenFoodItem = std::make_shared<FoodItem>(list.searchFoodItemByID(foodItemID));
    bool done = false;

    try {
        // checking for stock
        if (chosenFoodItem->getOnHand() <= 0) { 
            throw std::invalid_argument("Sorry, this item is currently out of stock!");
        }
        unsigned int inputValue = 0; // used to hold current int input by the user

        std::cout << "You have selected \"" << chosenFoodItem->getName() << " - " 
                  << chosenFoodItem->getDesc() << "\"." << "This will cost you $"
                  << chosenFoodItem->getPrice() / 100.0 << "." << std::endl;
        std::cout << "Please hand over the money - type in the value of each note/coin in cents.\n"
                  << "Please enter ctrl-D or enter on a new line to cancel this purchase." << endl;
        
        double currentBalance = (chosenFoodItem->getPrice() - inputValue) / 100.0;
        while (!done) {
            std::string line; // only used for checking empty line
            

            std::cout << "You still need to give us $" << currentBalance << ": ";
            getline(std::cin, line);
            inputValue = std::stoi(line);
            
            // check for ctrl+D or empty line -> exiting the function
            if (std::cin.eof() || line.empty()) { 
                std::cout << "Cancelling purchase." << std::endl;
                done = true;
                // currentPayment.clear();
            } 

            // CURRENT ERROR
            // when inputting double, it's taking 2 lines instead of 1
            // when convert purchaseMeal and isMoneyValid... to static function
            // memory leak or std::"bad_alloc" error appears
            // 



            // check if user's input is a float/double
            if (line.find('.') != std::string::npos) {
                throw std::invalid_argument("Please enter a value similar to the following example: 850 (8 dollars and 50 cents)");
            }
            
            // correct input format
            else {
                // incorrect coin denomination
                if (!isMoneyValidforPurchase(inputValue)) {
                    throw std::runtime_error("Invalid denomination encountered");
                }

                // Insufficient amount of money -> skip
                if ((inputValue / 100.0) < currentBalance) {
                    currentBalance -= inputValue / 100.0;
                    // currentPayment.push_back(inputValue);
                }

                else if ((inputValue / 100.0) >= currentBalance) {
                    // change making algo comes in here
                    // the change will be (inputValue (ie 500) / 100.0)) - currentPrice (ie 1.50)
                    // = 3.50 == 2$ 1$ 50cents
                    std::vector<int> coins(cashRegister.size() + 1);
                    for (long unsigned int i = 0; i < cashRegister.size(); ++i) {
                        coins[i] = cashRegister[i]->getDenom();
                    }
                    std::vector<int> counts(cashRegister.size() + 1);
                    for (long unsigned int i = 0; i < cashRegister.size(); ++i) {
                        counts[i] = cashRegister[i]->getCount();
                    }
                    Helper::change_making(coins, counts, static_cast<int>(inputValue - (currentBalance * 100)));
                    done = true;
                }
            }
        }
        
        


        
    } 
    catch (const std::runtime_error& e) { // invalid note/coin
        cout << "Error: " << e.what() << endl;
    } 
    catch (const std::invalid_argument& e) { // handling non-int string conversion
        std::cin.clear(); // clear the error state
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore the rest of the line
        if (std::string(e.what()).empty()) {
            std::cout << "Invalid input. Please enter a valid number" << std::endl;
        } else {
            std::cout << e.what() << std::endl;
        }
    } 
    catch (const std::out_of_range& e) { // handling out of int value range conversion
        std::cout << "Input is out of range. Please enter a smaller number." << std::endl;
    }
    
}





void Coin::displayBalance(std::vector<Coin>& currentBalance) {

}


Coin::~Coin(){};