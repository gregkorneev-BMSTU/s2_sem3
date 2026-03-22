#pragma once

#include <memory>
#include <string>
#include <vector>

class Account;

class Client {
public:
    Client(int id, std::string fullName);

    int getId() const;
    const std::string& getFullName() const;

    void addAccount(const std::shared_ptr<Account>& account);
    const std::vector<std::shared_ptr<Account>>& getAccounts() const;
    double totalBalance() const;

private:
    int id_;
    std::string fullName_;

    // Агрегация: счета создаются вне клиента и могут жить независимо от него.
    std::vector<std::shared_ptr<Account>> accounts_;
};
