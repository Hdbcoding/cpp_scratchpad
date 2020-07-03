#include "account.h"
#include <iostream>

int Account::_generator = 1;

Account::Account(const std::string &name, float balance) : _name(name), _balance(balance)
{
    _accountNumber = _generator++;
    std::cout << "Account(const std::string &name, float balance)" << std::endl;
}

Account::~Account()
{
    std::cout << "~Account()" << std::endl;
}

const std::string &Account::GetName() const
{
    return _name;
}

float Account::GetBalance() const
{
    return _balance;
}

int Account::GetAccountNo() const
{
    return _accountNumber;
}

float Account::GetInterestRate() const
{
    return 0;
}

void Account::AccumulateInterest() {}

void Account::Withdraw(float amount)
{
    if (amount > _balance)
        std::cout << "Whoah buddy, overdraw!" << std::endl;
    else
        _balance -= amount;
}

void Account::Deposit(float amount)
{
    if (amount < 0)
        std::cout << "What? don't you mean withdraw?" << std::endl;
    else
        _balance += amount;
}