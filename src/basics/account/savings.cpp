#include "savings.h"

Savings::Savings(const std::string &name, float balance, float rate) : Account(name, balance), _rate(rate) {}

Savings::~Savings() {}

float Savings::GetInterestRate() const
{
    return _rate;
}

void Savings::AccumulateInterest()
{
    _balance += _balance * _rate;
}