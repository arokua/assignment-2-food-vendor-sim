#ifndef COIN_H
#define COIN_H

#include <string>
#include <iostream>

#include "LinkedList.h"

// Coin.h defines the coin structure for managing currency in the system. 
#define COIN_DELIM ","  // delimiter

//The number of denominations of currency available in the system 
#define COINS_DENOMS 10

#define COIN_ARGC 2 // Coin data arguments count

// enumeration representing the various types of currency available in the system. 
enum Denomination
{
    FIVE_CENTS = 5, 
    TEN_CENTS = 10, 
    TWENTY_CENTS = 20, 
    FIFTY_CENTS = 50, 
    ONE_DOLLAR = 100, 
    TWO_DOLLARS = 200, 
    FIVE_DOLLARS = 500, 
    TEN_DOLLARS = 1000, 
    TWENTY_DOLLARS = 2000, 
    FIFTY_DOLLARS = 5000
};


// represents a coin type stored in the cash register perhaps. Each demonination
// will have exactly one of these in the cash register.
class Coin
{
public:
    // the denomination type
    enum Denomination denom;
    
    // the count of how many of these are in the cash register
    unsigned count;

    // constructor + destructor
    Coin(Denomination denom, unsigned count);
    ~Coin();

    // Getters & Setters
    Denomination getDenom();
    unsigned getCount();
    void setCount(unsigned count);

    // returns the string representation of the coin
    void printInfo();

    // Functions
    static bool isMoneyValidforPurchase(unsigned int input);
    static bool purchaseMeal(LinkedList& list, std::vector<std::shared_ptr<Coin>>& cashRegister, std::vector<int> currentPayment = {});
    static void displayBalance(std::vector<std::shared_ptr<Coin>>& coinVector);
    static void updateCoinVector(std::vector<std::shared_ptr<Coin>> originalCoinVector, std::vector<int> userPayment = {});
    static int change_making(vector<std::shared_ptr<Coin>>& cashRegister, int paymentAmount);
};

#endif // COIN_H
