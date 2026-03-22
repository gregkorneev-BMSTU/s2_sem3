#pragma once

#include "Account.h"

class SavingsAccount : public Account {
public:
    SavingsAccount(std::string number, std::string ownerName, double openingBalance, double annualRatePercent);

    std::string getType() const override;
    double getAnnualRatePercent() const;

    void accrueMonthlyInterest();

private:
    double annualRatePercent_;
};
