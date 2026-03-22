#include "SavingsAccount.h"

SavingsAccount::SavingsAccount(std::string number,
                               std::string ownerName,
                               double openingBalance,
                               double annualRatePercent)
    : Account(std::move(number), std::move(ownerName), openingBalance),
      annualRatePercent_(annualRatePercent) {}

std::string SavingsAccount::getType() const {
    return "SavingsAccount";
}

double SavingsAccount::getAnnualRatePercent() const {
    return annualRatePercent_;
}

void SavingsAccount::accrueMonthlyInterest() {
    const double monthlyInterest = balance_ * (annualRatePercent_ / 100.0) / 12.0;
    if (monthlyInterest > 0.0) {
        deposit(monthlyInterest, "Начисление месячных процентов");
    }
}
