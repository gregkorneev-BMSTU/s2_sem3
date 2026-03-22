#pragma once

#include <string>

class Account;

class Card {
public:
    Card(std::string cardNumber, Account& linkedAccount);

    const std::string& getCardNumber() const;

    bool pay(double amount, const std::string& merchant);
    bool cashWithdraw(double amount);

private:
    std::string cardNumber_;

    // Ассоциация: карта лишь ссылается на счет, не владеет им.
    Account* linkedAccount_;
};
