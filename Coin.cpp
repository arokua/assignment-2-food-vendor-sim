#include "Coin.h"
#include "Helper.h"


Coin::Coin(Denomination denom, unsigned count) {
    this->denom = denom;
    this->count = count;
}

void Coin::printInfo(){
    if (count > 0) {
        std::cout << denom << "," << count << std::endl;
    }    
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

void Coin::displayBalance(std::vector<std::shared_ptr<Coin>>& coinVector) {
    cout << "\n\nBalance Summary";
    cout << "\n---------------";
    cout << "\nDenom  | Quantity | Value";
    cout << "\n----------------------------\n";
    double sum=0;
    for (auto& denom : coinVector){
        double thisTypeTotal = denom->getCount() * (denom->getDenom() / 100.0);

        std::ostringstream priceStream;
        priceStream << std::fixed << std::setprecision(2) << thisTypeTotal;

        cout << std::left << std::setw(7) << denom->getDenom() << "|"
             << std::setw(10) << denom->getCount() << "|"  
             << "$" << std::right << std::setw(7) << priceStream.str() << endl;
        sum+=thisTypeTotal;
    }
    cout << "----------------------------\n";
    cout << std::right << std::setw(20) << "$"
         << std::right << std::setw(7) << std::fixed << std::setprecision(2) << sum << endl;
};



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


bool Coin::purchaseMeal(LinkedList& list, std::vector<std::shared_ptr<Coin>>& cashRegister, std::vector<int> currentPayment) {
    /***
    * @brief Purchasing meal function that finds the FoodItem based on ID and will return change
    * to users after several procedure steps
    * @param list Linkedlist containing the Food Items
    * @param currentBalance The shop's current coin/note vector
    * @param currentPayment records user's current FoodItem/Payment (not yet finalised) 
    ***/

    bool done = false;

    try {
        cout << "Please enter Ctrl-D or Enter on a new line to cancel this purchase." << endl;
        cout << "\nPlease enter the ID of the food you wish to purchase: ";
        string foodIdSelection;
        getline(std::cin, foodIdSelection);
        if (std::cin.eof() || foodIdSelection.empty()) { 
            done = true;
            throw std::invalid_argument("Cancelling purchase");
        } 
        // search and create a pointer to the object
        std::shared_ptr<FoodItem> chosenFoodItem = list.searchFoodItemByID(foodIdSelection);

        if (chosenFoodItem == nullptr) {
            throw std::invalid_argument("Sorry, this item does not exist!");
        }

        // checking for stock
        if (chosenFoodItem->getOnHand() <= 0) { 
            throw std::invalid_argument("Sorry, this item is currently out of stock!");
        }
        unsigned int inputValue = 0; // used to hold current int input by the user

        std::cout << std::endl;
        std::cout << "You have selected \"" << chosenFoodItem->getName() << " - " 
                  << chosenFoodItem->getDesc() << "\"." << "\nThis will cost you $"
                  << chosenFoodItem->getPrice() << "." << std::endl;
        std::cout << "Please hand over the money - type in the value of each note/coin in cents.\n"
                  << "Please enter Ctrl-D or Enter on a new line to cancel this purchase." << endl;
        
        double currentBalance = chosenFoodItem->getPrice() - (inputValue / 100.0);
        while (!done) {
            std::string line; // only used for checking empty line

            std::cout << "You still need to give us $" << currentBalance << ": ";
            getline(std::cin, line);
            
            // check for ctrl+D or empty line -> exiting the function
            if (std::cin.eof() || line.empty()) { 
                currentPayment.clear(); // deleting current payment
                done = true;
                chosenFoodItem.reset();
                throw std::invalid_argument("Cancelling purchase");
            } 

            // check if user's input is a double
            if (line.find('.') != std::string::npos) {  
                throw std::invalid_argument("Please enter an int value similar to the following example: 850 (8 dollars and 50 cents)");
            }
            
            // correct input format
            else {
                // incorrect coin denomination
                inputValue = std::stoi(line);
                if (!isMoneyValidforPurchase(inputValue)) {
                    throw std::runtime_error("Invalid denomination encountered");
                }

                // Insufficient amount of money -> skip
                
                if ((inputValue / 100.0) > currentBalance) { // returning change 
                    // return an updated cashRegister (with deducted coin amount)
                    Coin::change_making(cashRegister, static_cast<int>(inputValue - (currentBalance * 100)));
                }

                currentBalance -= (inputValue / 100.0);
                currentPayment.push_back(inputValue);
                
                if (currentBalance <= 0) {
                    done = true;
                    if (done){
                        chosenFoodItem->sold();
                    }
                    updateCoinVector(cashRegister, currentPayment);
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

    return done;
}


void Coin::updateCoinVector(std::vector<std::shared_ptr<Coin>> originalCoinVector, std::vector<int> userPayment) {
    /***
    * @brief Function to update the original coin vector with the used coin vector
    * 
    * @param originalCoinVector The original coin vector
    * @param usedCoinVector Used coin/note vector (empty by default)
    ***/

    int currentCoinDenom; // hold the current Denom
    // receive coins/notes from the user's payment
    if (userPayment.size() != 0) {
        for (size_t i = 0; i < userPayment.size(); i++) {
            currentCoinDenom = userPayment[i];
            for (size_t j = 0; j < originalCoinVector.size(); j++) {
                if (originalCoinVector[j]->getDenom() == currentCoinDenom) {
                    originalCoinVector[j]->setCount(originalCoinVector[j]->getCount() + 1);
                }
            }
        }
    }

    // is there an exception to check for?
}


// Modified function based on wikipedia.org/wiki/Change-making_problem
// This function return the minimum number of coins used to make the amount paymentAmount
// If no solution exists, it returns -1
// The additional part to the original algorithm is that the coins set is finite
// Thus, additional comparision is made to see if the original optimal denom is suitable
// Then, a tracking matrix is used to keep track of all possible solutions
// This function needs a vector that have the denomination of the coins in numerical values
// And a vector that contain the current amount of each denomination

// vector<int>& coins, vector<int>& counts
int Coin::change_making(std::vector<std::shared_ptr<Coin>>& cashRegister, int paymentAmount) {
    /***
     * @brief
     * 
     * @param coins containing a vector of denominations in int value
     * @param counts containing a vector of each denomination counts
     * @param paymentAmount is the amount of money that this algorithm needs to reach
    ***/

    int numCoins = cashRegister.size();
    
    vector<int> m(paymentAmount + 1, numeric_limits<int>::max());
    // Use 2D vector of size (n+1) for tracking used coins 
    vector<vector<int>> used_coins(paymentAmount + 1);

    // Initialize the zero amount case
    m[0] = 0;

    // Fill the DP table
    for (int amount = 1; amount <= paymentAmount; ++amount) {
        for (int c = 0; c < numCoins; ++c) {
            int coin = cashRegister[c]->getDenom();
            if (coin <= amount) {
                if (m[amount - coin] + 1 < m[amount] && cashRegister[c]->getCount() > 0) {
                    m[amount] = m[amount - coin] + 1;
                    used_coins[amount] = used_coins[amount - coin];
                    used_coins[amount].push_back(c);
                }
            }
        }
    }

    // Check if a solution exists
    if (m[paymentAmount] == numeric_limits<int>::max() || m[paymentAmount] == numeric_limits<int>::min()) {
        cout << "Not possible to do transaction" << endl;
        return -1;
    }   

    // Compute the count of each coin used
    vector<int> coinUsage(numCoins, 0);
    for (int idx : used_coins[paymentAmount]) {
        coinUsage[idx]++;
    }

    // Update counts directly within the loop for efficiency
    cout << "Your change is ";
    for (int i = 0; i < numCoins; ++i) {
        if (coinUsage[i] > 0) {
            for (int j = 0; j < coinUsage[i]; j++) {
                if (cashRegister[i]->getDenom() >= 100) {
                    cout << "$" << cashRegister[i]->getDenom() / 100 << " ";
                } else {
                    cout << cashRegister[i]->getDenom() << "c" << " ";
                }
            }
            
            cashRegister[i]->setCount(cashRegister[i]->getCount() - coinUsage[i]);
        }
    }
    cout<<endl;

    // // Print remaining counts conditionally to avoid unnecessary output
    // std::cout << "Remaining Denomination: " << endl;
    // for (size_t i = 0; i < cashRegister.size(); i++) {
    //     cashRegister[i]->printInfo();
    // }
    
    return 0;
}

Coin::~Coin(){};