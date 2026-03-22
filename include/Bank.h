#pragma once

#include <memory>
#include <string>
#include <vector>

#include "CommissionCalculator.h"
#include "Department.h"

class Account;
class Client;
class CreditAccount;
class DepositAccount;
class SavingsAccount;

class Bank {
public:
    explicit Bank(std::string name);

    const std::string& getName() const;

    Department& addDepartment(std::string name, std::string address);
    void registerClient(const std::shared_ptr<Client>& client);

    std::shared_ptr<SavingsAccount> createSavingsAccount(const std::string& number,
                                                         const std::string& ownerName,
                                                         double openingBalance,
                                                         double annualRatePercent);

    std::shared_ptr<CreditAccount> createCreditAccount(const std::string& number,
                                                       const std::string& ownerName,
                                                       double openingBalance,
                                                       double creditLimit);

    std::shared_ptr<DepositAccount> createDepositAccount(const std::string& number,
                                                         const std::string& ownerName,
                                                         double openingBalance,
                                                         int termMonths);

    bool transfer(Account& from, Account& to, double amount);

    const std::vector<Department>& getDepartments() const;
    const std::vector<std::shared_ptr<Account>>& getAccounts() const;

private:
    std::string name_;

    // Композиция: банк владеет калькулятором комиссии и управляет его жизненным циклом.
    CommissionCalculator commissionCalculator_;

    // Композиция: отделения создаются и уничтожаются вместе с банком.
    std::vector<Department> departments_;

    std::vector<std::shared_ptr<Client>> clients_;
    std::vector<std::shared_ptr<Account>> accounts_;
};
