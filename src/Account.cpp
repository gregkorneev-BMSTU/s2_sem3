#include "Account.h"

#include <sstream>

Account::Account(std::string number, std::string ownerName, double openingBalance)
    : accountNumber_(std::move(number)), ownerName_(std::move(ownerName)), balance_(openingBalance) {
    if (openingBalance > 0.0) {
        addTransaction(TransactionType::Deposit, openingBalance, "Начальное пополнение");
    }
}

const std::string& Account::getNumber() const {
    return accountNumber_;
}

const std::string& Account::getOwnerName() const {
    return ownerName_;
}

double Account::getBalance() const {
    return balance_;
}

bool Account::canDebit(double amount) const {
    return canWithdraw(amount);
}

bool Account::deposit(double amount, const std::string& description) {
    if (amount <= 0.0) {
        return false;
    }

    balance_ += amount;
    addTransaction(TransactionType::Deposit, amount, description);
    return true;
}

bool Account::withdraw(double amount, const std::string& description) {
    if (amount <= 0.0 || !canWithdraw(amount)) {
        return false;
    }

    balance_ -= amount;
    addTransaction(TransactionType::Withdrawal, amount, description);
    return true;
}

bool Account::transferOut(double amount, const std::string& toAccountNumber) {
    if (amount <= 0.0 || !canWithdraw(amount)) {
        return false;
    }

    balance_ -= amount;
    addTransaction(TransactionType::TransferOut, amount, "На счет " + toAccountNumber);
    return true;
}

void Account::transferIn(double amount, const std::string& fromAccountNumber) {
    if (amount <= 0.0) {
        return;
    }

    balance_ += amount;
    addTransaction(TransactionType::TransferIn, amount, "Со счета " + fromAccountNumber);
}

bool Account::chargeFee(double fee, const std::string& reason) {
    if (fee <= 0.0) {
        return true;
    }

    if (!canWithdraw(fee)) {
        return false;
    }

    balance_ -= fee;
    addTransaction(TransactionType::Fee, fee, reason);
    return true;
}

const std::vector<Transaction>& Account::getHistory() const {
    return history_;
}

bool Account::canWithdraw(double amount) const {
    return amount >= 0.0 && balance_ >= amount;
}

void Account::addTransaction(TransactionType type, double amount, const std::string& description) {
    history_.emplace_back(type, amount, description);
}
