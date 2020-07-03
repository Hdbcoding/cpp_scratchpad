#pragma once
#include "account.h"

class Checking : public Account
{
public:
    Checking(const std::string &name, float balance);
    ~Checking();

    void Withdraw(float amount) override;
};