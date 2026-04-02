#pragma once

#include "Account.h"

class DepositAccount : public Account {
public:
    DepositAccount(const std::string& number,
                   const std::string& ownerName,
                   double startBalance,
                   int termMonths);

    std::string getType() const override;
    void unlock();

protected:
    bool canWithdraw(double amount) const override;

private:
    int termMonths_;
    bool locked_;
};
