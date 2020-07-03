#include "savings.h"
#include <iostream>

Savings::Savings(const std::string &name, float balance, float rate) : Account(name, balance), _rate(rate) {
    std::cout << "Savings(const std::string &name, float balance, float rate)" << std::endl;
}

Savings::~Savings() {
    std::cout << "~Savings()" << std::endl;
}

float Savings::GetInterestRate() const
{
    return _rate;
}

void Savings::AccumulateInterest()
{
    _balance += _balance * _rate;
}