#include "Coin.h"
#include "LinkedList.h"

#include <iostream>

Coin::Coin(Denomination denom, unsigned count) {
    this->denom = denom;
    this->count = count;
}

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



bool isMoneyValidforPurchase(unsigned int input){
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


void purchaseMeal(std::string foodItemID, LinkedList& list, std::vector<Coin> currentBalance) {
    // search and create a pointer to the object
    std::shared_ptr<FoodItem> chosenFoodItem = std::make_shared<FoodItem>(list.searchFoodItemByID(foodItemID));
    bool done = false;

    try {
        if (chosenFoodItem->getOnHand() <= 0) {
            throw std::logic_error("Sorry, this item is currently out of stock!");
        }
        unsigned int inputValue = 0; // used to hold current input by the user
        std::vector<unsigned> currentPayment; // used to hold the history of input by the user
                                              // could change to Coin object if needed


        std::cout << "You have selected \"" << chosenFoodItem->getName() << " - " 
                  << chosenFoodItem->getDesc() << "\"." << "This will cost you $"
                  << chosenFoodItem->getPrice() / 100.0 << "." << std::endl;
        std::cout << "Please hand over the money - type in the value of each note/coin in cents.\n"
                  << "Please enter ctrl-D or enter on a new line to cancel this purchase." << endl;
        
        while (!done) {
            std::string line; // only used for checking empty line
            
            double currentPrice = (chosenFoodItem->getPrice() / 100.0) - (inputValue / 100.0);
            std::cout << "You still need to give us $" << currentPrice << ": ";
            std::cin >> inputValue >> line;
            
            // check for ctrl + D or empty line
            if (std::cin.eof() || line.empty()) { 
                std::cout << "Cancelling purchase." << std::endl;
                done = true;
                currentPayment.clear();
            } 
            
            // check for invalid input
            else if (std::cin.fail()) { 
                std::cin.clear(); // clear the error state
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore the rest of the line
                std::cout << "Invalid input. Please enter a value similar to the following example:"
                          << " 850 (8 dollars and 50 cents)" << std::endl;
            } 
            
            // correct input format
            else {
                // incorrect coin denomination
                if (!isMoneyValidforPurchase(inputValue)) {
                    throw std::runtime_error("Invalid denomination encountered");
                }

                // Insufficient amount of money -> skip
                if ((inputValue / 100.0) < currentPrice) {
                    currentPayment.push_back(inputValue);
                }

                else if ((inputValue / 100.0) >= currentPrice) {
                    // change making algo comes in here
                    // the change will be (inputValue (ie 500) / 100.0)) - currentPrice (ie 1.50)
                    // = 3.50 == 2$ 1$ 50cents
                }
            }
        }
        
        


        
    } catch (const std::logic_error& e) {
        cout << e.what() << endl;
    } catch (const std::runtime_error& e) {
        cout << "Error: " << e.what() << endl;
    } 
    
}





void displayBalance(std::vector<Coin>& currentBalance) {

}


// a very linear way to convert (can be changed later)
// should take (Coin)->getDenom(); as parameter
int convertDenomtoInt(Denomination denom) {
    int convertedVal = 0;

    if (denom == Denomination::FIVE_CENTS){
        convertedVal = 5;
    } else if (denom == Denomination::TEN_CENTS){
        convertedVal = 10;
    } else if (denom == Denomination::TWENTY_CENTS){
        convertedVal = 20;
    } else if (denom == Denomination::FIFTY_CENTS){
        convertedVal = 50;
    } else if (denom == Denomination::ONE_DOLLAR){
        convertedVal = 100;
    } else if (denom == Denomination::TWO_DOLLARS){
        convertedVal = 200;
    } else if (denom == Denomination::FIVE_DOLLARS){
        convertedVal = 500;
    } else if (denom == Denomination::TEN_DOLLARS){
        convertedVal = 1000;
    } else if (denom == Denomination::TWENTY_DOLLARS){
        convertedVal = 2000;
    } else if (denom == Denomination::FIFTY_DOLLARS){
        convertedVal = 5000;
    } 
    return convertedVal;
}


Coin::~Coin(){};