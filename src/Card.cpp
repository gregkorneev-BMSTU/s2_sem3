#include "Card.h"

#include "Account.h"

Card::Card(std::string cardNumber, Account& linkedAccount)
    : cardNumber_(std::move(cardNumber)), linkedAccount_(&linkedAccount) {}

const std::string& Card::getCardNumber() const {
    return cardNumber_;
}

bool Card::pay(double amount, const std::string& merchant) {
    if (linkedAccount_ == nullptr) {
        return false;
    }

    return linkedAccount_->withdraw(amount, "Оплата картой: " + merchant);
}

bool Card::cashWithdraw(double amount) {
    if (linkedAccount_ == nullptr) {
        return false;
    }

    return linkedAccount_->withdraw(amount, "Снятие наличных по карте");
}
