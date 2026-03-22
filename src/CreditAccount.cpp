#include "CreditAccount.h"

CreditAccount::CreditAccount(std::string number,
                             std::string ownerName,
                             double openingBalance,
                             double creditLimit)
    : Account(std::move(number), std::move(ownerName), openingBalance), creditLimit_(creditLimit) {}

std::string CreditAccount::getType() const {
    return "CreditAccount";
}

double CreditAccount::getCreditLimit() const {
    return creditLimit_;
}

double CreditAccount::getAvailableFunds() const {
    return balance_ + creditLimit_;
}

bool CreditAccount::canWithdraw(double amount) const {
    return amount >= 0.0 && (balance_ + creditLimit_) >= amount;
}
