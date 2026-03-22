#pragma once

#include "Account.h"

class DepositAccount : public Account {
public:
    DepositAccount(std::string number, std::string ownerName, double openingBalance, int termMonths);

    std::string getType() const override;
    int getTermMonths() const;
    bool isLocked() const;

    void unlockTerm();

protected:
    bool canWithdraw(double amount) const override;

private:
    int termMonths_;
    bool locked_;
};
