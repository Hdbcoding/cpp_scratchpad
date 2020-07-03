#pragma once
#include <string>

class Account {
    std::string _name;
    int _accountNumber;
    static int _generator;

protected:
    float _balance;

public:
    Account(const std::string &name, float balance);
    ~Account();
    
    const std::string& GetName() const;
    float GetBalance() const;
    int GetAccountNo() const;
    virtual float GetInterestRate() const;

    virtual void AccumulateInterest();
    virtual void Withdraw(float amount);
    void Deposit(float amount);
};