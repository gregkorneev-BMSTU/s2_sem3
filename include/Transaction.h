#pragma once

#include <string>

enum class TransactionType {
    Deposit,
    Withdrawal,
    TransferIn,
    TransferOut,
    Fee
};

class Transaction {
public:
    Transaction(TransactionType type, double amount, std::string description);

    int getId() const;
    const std::string& getTimestamp() const;
    TransactionType getType() const;
    double getAmount() const;
    const std::string& getDescription() const;

    std::string toString() const;

private:
    static std::string makeTimestamp();
    static std::string typeToString(TransactionType type);

    static int nextId_;

    int id_;
    std::string timestamp_;
    TransactionType type_;
    double amount_;
    std::string description_;
};
