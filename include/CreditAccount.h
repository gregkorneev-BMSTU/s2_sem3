#pragma once

#include "Account.h"

class CreditAccount : public Account {
public:
    CreditAccount(std::string number, std::string ownerName, double openingBalance, double creditLimit);

    std::string getType() const override;
    double getCreditLimit() const;
    double getAvailableFunds() const;

protected:
    bool canWithdraw(double amount) const override;

private:
    double creditLimit_;
};
