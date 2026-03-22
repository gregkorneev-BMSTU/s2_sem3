#pragma once

#include <string>
#include <vector>

#include "Transaction.h"

class Account {
public:
    Account(std::string number, std::string ownerName, double openingBalance);
    virtual ~Account() = default;

    const std::string& getNumber() const;
    const std::string& getOwnerName() const;
    double getBalance() const;

    virtual std::string getType() const = 0;

    bool canDebit(double amount) const;
    bool deposit(double amount, const std::string& description = "Пополнение");
    bool withdraw(double amount, const std::string& description = "Снятие");

    bool transferOut(double amount, const std::string& toAccountNumber);
    void transferIn(double amount, const std::string& fromAccountNumber);
    bool chargeFee(double fee, const std::string& reason);

    const std::vector<Transaction>& getHistory() const;

protected:
    virtual bool canWithdraw(double amount) const;
    void addTransaction(TransactionType type, double amount, const std::string& description);

    std::string accountNumber_;
    std::string ownerName_;
    double balance_;

private:
    std::vector<Transaction> history_;
};
