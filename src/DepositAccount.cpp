#include "DepositAccount.h"

DepositAccount::DepositAccount(const std::string& number,
                               const std::string& ownerName,
                               double startBalance,
                               int termMonths)
    : Account(number, ownerName, startBalance), termMonths_(termMonths), locked_(true) {}

std::string DepositAccount::getType() const {
    return "DepositAccount";
}

void DepositAccount::unlock() {
    locked_ = false;
}

bool DepositAccount::canWithdraw(double amount) const {
    if (locked_) {
        return false;
    }
    return Account::canWithdraw(amount);
}
