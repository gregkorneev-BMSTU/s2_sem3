#include "Bank.h"

#include "Account.h"
#include "Client.h"
#include "CreditAccount.h"
#include "DepositAccount.h"
#include "SavingsAccount.h"

Bank::Bank(std::string name) : name_(std::move(name)) {}

const std::string& Bank::getName() const {
    return name_;
}

Department& Bank::addDepartment(std::string name, std::string address) {
    departments_.emplace_back(std::move(name), std::move(address));
    return departments_.back();
}

void Bank::registerClient(const std::shared_ptr<Client>& client) {
    clients_.push_back(client);
}

std::shared_ptr<SavingsAccount> Bank::createSavingsAccount(const std::string& number,
                                                           const std::string& ownerName,
                                                           double openingBalance,
                                                           double annualRatePercent) {
    auto account = std::make_shared<SavingsAccount>(number, ownerName, openingBalance, annualRatePercent);
    accounts_.push_back(account);
    return account;
}

std::shared_ptr<CreditAccount> Bank::createCreditAccount(const std::string& number,
                                                         const std::string& ownerName,
                                                         double openingBalance,
                                                         double creditLimit) {
    auto account = std::make_shared<CreditAccount>(number, ownerName, openingBalance, creditLimit);
    accounts_.push_back(account);
    return account;
}

std::shared_ptr<DepositAccount> Bank::createDepositAccount(const std::string& number,
                                                           const std::string& ownerName,
                                                           double openingBalance,
                                                           int termMonths) {
    auto account = std::make_shared<DepositAccount>(number, ownerName, openingBalance, termMonths);
    accounts_.push_back(account);
    return account;
}

bool Bank::transfer(Account& from, Account& to, double amount) {
    if (&from == &to || amount <= 0.0) {
        return false;
    }

    // Делегирование: расчет комиссии передается отдельному объекту.
    const double fee = commissionCalculator_.calculateTransferFee(from, to, amount);

    if (!from.canDebit(amount + fee)) {
        return false;
    }

    if (!from.transferOut(amount, to.getNumber())) {
        return false;
    }

    if (fee > 0.0 && !from.chargeFee(fee, "Комиссия за перевод")) {
        return false;
    }

    to.transferIn(amount, from.getNumber());
    return true;
}

const std::vector<Department>& Bank::getDepartments() const {
    return departments_;
}

const std::vector<std::shared_ptr<Account>>& Bank::getAccounts() const {
    return accounts_;
}
