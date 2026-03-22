#include "Client.h"

#include "Account.h"

Client::Client(int id, std::string fullName) : id_(id), fullName_(std::move(fullName)) {}

int Client::getId() const {
    return id_;
}

const std::string& Client::getFullName() const {
    return fullName_;
}

void Client::addAccount(const std::shared_ptr<Account>& account) {
    accounts_.push_back(account);
}

const std::vector<std::shared_ptr<Account>>& Client::getAccounts() const {
    return accounts_;
}

double Client::totalBalance() const {
    double sum = 0.0;
    for (const auto& account : accounts_) {
        sum += account->getBalance();
    }
    return sum;
}
