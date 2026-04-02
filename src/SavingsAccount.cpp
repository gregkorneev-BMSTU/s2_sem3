#include "SavingsAccount.h"

SavingsAccount::SavingsAccount(const std::string& number,
                               const std::string& ownerName,
                               double startBalance,
                               double annualRatePercent)
    : Account(number, ownerName, startBalance), annualRatePercent_(annualRatePercent) {}

std::string SavingsAccount::getType() const {
    return "SavingsAccount";
}

void SavingsAccount::addMonthlyInterest() {
    double monthly = balance_ * (annualRatePercent_ / 100.0) / 12.0;
    if (monthly > 0) {
        deposit(monthly, "Месячные проценты");
    }
}
