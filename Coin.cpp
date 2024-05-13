#include "Coin.h"
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

Coin::~Coin(){};