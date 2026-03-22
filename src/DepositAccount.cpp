#include "DepositAccount.h"

DepositAccount::DepositAccount(std::string number,
                               std::string ownerName,
                               double openingBalance,
                               int termMonths)
    : Account(std::move(number), std::move(ownerName), openingBalance),
      termMonths_(termMonths),
      locked_(true) {}

std::string DepositAccount::getType() const {
    return "DepositAccount";
}

int DepositAccount::getTermMonths() const {
    return termMonths_;
}

bool DepositAccount::isLocked() const {
    return locked_;
}

void DepositAccount::unlockTerm() {
    locked_ = false;
}

bool DepositAccount::canWithdraw(double amount) const {
    if (locked_) {
        return false;
    }

    return Account::canWithdraw(amount);
}
