#include "checking.h"
#include <iostream>

Checking::Checking(const std::string &name, float balance) : Account(name, balance)
{
    std::cout << "Checking(const std::string &name, float balance)" << std::endl;
}

Checking::~Checking()
{
    std::cout << "~Checking()" << std::endl;
}

void Checking::Withdraw(float amount)
{
    if (_balance - amount < 50)
        std::cout << "Whoah man, checking balance can't fall below 50!" << std::endl;
    else
        Account::Withdraw(amount);
}