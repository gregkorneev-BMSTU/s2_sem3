#include "CreditAccount.h"

CreditAccount::CreditAccount(const std::string& number,
                             const std::string& ownerName,
                             double startBalance,
                             double creditLimit)
    : Account(number, ownerName, startBalance), creditLimit_(creditLimit) {}

std::string CreditAccount::getType() const {
    return "CreditAccount";
}

bool CreditAccount::canWithdraw(double amount) const {
    return amount >= 0 && (balance_ + creditLimit_) >= amount;
}
