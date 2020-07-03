#include "checking.h"
#include <iostream>

Checking::Checking(const std::string &name, float balance) : Account(name, balance){}

Checking::~Checking(){}

void Checking::Withdraw(float amount){
    if (_balance - amount < 50)
        std::cout << "Whoah man, checking balance can't fall below 50!" << std::endl;
    else
        _balance -= amount;
}