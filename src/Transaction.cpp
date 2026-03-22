#include "Transaction.h"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

int Transaction::nextId_ = 1;

Transaction::Transaction(TransactionType type, double amount, std::string description)
    : id_(nextId_++),
      timestamp_(makeTimestamp()),
      type_(type),
      amount_(amount),
      description_(std::move(description)) {}

int Transaction::getId() const {
    return id_;
}

const std::string& Transaction::getTimestamp() const {
    return timestamp_;
}

TransactionType Transaction::getType() const {
    return type_;
}

double Transaction::getAmount() const {
    return amount_;
}

const std::string& Transaction::getDescription() const {
    return description_;
}

std::string Transaction::toString() const {
    std::ostringstream out;
    out << "#" << id_ << " [" << timestamp_ << "] " << typeToString(type_) << ": "
        << std::fixed << std::setprecision(2) << amount_ << " RUB";

    if (!description_.empty()) {
        out << " (" << description_ << ")";
    }

    return out.str();
}

std::string Transaction::makeTimestamp() {
    const auto now = std::chrono::system_clock::now();
    const std::time_t time = std::chrono::system_clock::to_time_t(now);

    std::tm localTm{};
#if defined(_WIN32)
    localtime_s(&localTm, &time);
#else
    localTm = *std::localtime(&time);
#endif

    std::ostringstream out;
    out << std::put_time(&localTm, "%Y-%m-%d %H:%M:%S");
    return out.str();
}

std::string Transaction::typeToString(TransactionType type) {
    switch (type) {
    case TransactionType::Deposit:
        return "Пополнение";
    case TransactionType::Withdrawal:
        return "Снятие";
    case TransactionType::TransferIn:
        return "Перевод входящий";
    case TransactionType::TransferOut:
        return "Перевод исходящий";
    case TransactionType::Fee:
        return "Комиссия";
    }

    return "Неизвестно";
}
