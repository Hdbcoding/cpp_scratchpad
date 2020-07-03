#include "account.h"
#include "savings.h"
#include "checking.h"
#include <iostream>

void Report(const Account &a)
{
    std::cout << a.GetName() << ": " << a.GetAccountNo() << ": " << a.GetBalance() << std::endl;
}

int main()
{
    Account *a = new Account("account", 25);

    a->Deposit(25);
    Report(*a);
    a->Withdraw(56);
    a->Withdraw(45);
    Report(*a);
    delete a;

    Savings *b = new Savings("savings", 25, 0.25);
    b->AccumulateInterest();
    b->AccumulateInterest();
    Report(*b);
    delete b;

    Checking *c = new Checking("checking", 15);
    c->Withdraw(5);
    c->Deposit(25);
    c->Withdraw(5);
    Report(*c);
    delete c;
}
