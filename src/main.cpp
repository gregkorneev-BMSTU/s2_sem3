#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "Account.h"
#include "Bank.h"
#include "Card.h"
#include "Client.h"
#include "CreditAccount.h"
#include "DepositAccount.h"
#include "SavingsAccount.h"


namespace {

const std::string RESET  = "\033[0m";
const std::string BOLD   = "\033[1m";
const std::string CYAN   = "\033[36m";
const std::string GREEN  = "\033[32m";
const std::string RED    = "\033[31m";
const std::string YELLOW = "\033[33m";

std::string formatMoney(double value) {
    std::ostringstream out;
    out << std::fixed << std::setprecision(2) << value << " RUB";
    return out.str();
}

void printLine(char ch = '=', int width = 72) {
    for (int i = 0; i < width; i++) {
        std::cout << ch;
    }
    std::cout << '\n';
}

void printSection(const std::string& title) {
    std::cout << '\n'
              << CYAN << BOLD;
    printLine('=');
    std::cout << title << '\n';
    printLine('=');
    std::cout << RESET;
}

void printSubsection(const std::string& title) {
    std::cout << '\n'
              << YELLOW << BOLD << title << RESET << '\n';
    printLine('-');
}

void printAccountCard(const Account& account) {
    printLine('-');
    std::cout << std::left
              << std::setw(14) << "Тип:"      << account.getType() << '\n'
              << std::setw(14) << "Номер:"    << account.getNumber() << '\n'
              << std::setw(14) << "Владелец:" << account.getOwnerName() << '\n'
              << std::setw(14) << "Баланс:"   << formatMoney(account.getBalance()) << '\n';
    printLine('-');
}

void printDepartments(const Bank& bank) {
    const std::vector<Department>& deps = bank.getDepartments();

    std::cout << std::left
              << std::setw(5)  << "№"
              << std::setw(25) << "Отделение"
              << std::setw(35) << "Адрес"
              << '\n';
    printLine('-');

    for (std::size_t i = 0; i < deps.size(); i++) {
        std::cout << std::left
                  << std::setw(5)  << (i + 1)
                  << std::setw(25) << deps[i].getName()
                  << std::setw(35) << deps[i].getAddress()
                  << '\n';
    }
}

void printOperationResult(const std::string& text, bool success) {
    std::cout << std::left << std::setw(52) << text;

    if (success) {
        std::cout << GREEN << "[OK]" << RESET;
    } else {
        std::cout << RED << "[ERROR]" << RESET;
    }

    std::cout << '\n';
}

std::string transactionTypeToText(TransactionType type) {
    if (type == TransactionType::Deposit) {
        return "Пополнение";
    }
    if (type == TransactionType::Withdrawal) {
        return "Снятие";
    }
    if (type == TransactionType::TransferIn) {
        return "Входящий перевод";
    }
    if (type == TransactionType::TransferOut) {
        return "Исходящий перевод";
    }
    if (type == TransactionType::Fee) {
        return "Комиссия";
    }
    return "Операция";
}

void printHistoryTable(const Account& account) {
    printSubsection("История счета " + account.getNumber());

    const std::vector<Transaction>& history = account.getHistory();

    if (history.empty()) {
        std::cout << "История операций пуста.\n";
        return;
    }

    std::cout << std::left
              << std::setw(6)  << "ID"
              << std::setw(22) << "Тип"
              << std::setw(14) << "Сумма"
              << std::setw(28) << "Комментарий"
              << '\n';
    printLine('-');

    for (std::size_t i = 0; i < history.size(); i++) {
        const Transaction& tx = history[i];

        std::cout << std::left
                  << std::setw(6)  << tx.getId()
                  << std::setw(22) << transactionTypeToText(tx.getType())
                  << std::setw(14) << formatMoney(tx.getAmount())
                  << std::setw(28) << tx.getComment()
                  << '\n';
    }
}

void printClientSummary(const Client& client) {
    printLine('-');
    std::cout << std::left
              << std::setw(14) << "Клиент:"   << client.getFullName() << '\n'
              << std::setw(14) << "ID:"       << client.getId() << '\n'
              << std::setw(14) << "Счетов:"   << client.getAccounts().size() << '\n'
              << std::setw(14) << "Итого:"    << formatMoney(client.totalBalance()) << '\n';
    printLine('-');
}

} // namespace

int main() {
    printSection("УЧЕБНЫЙ ПРОЕКТ: БАНКОВСКАЯ СИСТЕМА (ВАРИАНТ 15)");

    Bank bank("BMSTU Bank");
    bank.addDepartment("Центральное", "Москва, ул. Бауманская, 5");
    bank.addDepartment("Северное", "Москва, ул. Лобненская, 12");

    Client alice(1, "Алиса Иванова");
    Client bob(2, "Боб Петров");

    bank.registerClient(alice);
    bank.registerClient(bob);

    SavingsAccount aliceSavings("ACC-1001", alice.getFullName(), 50000, 6);
    CreditAccount bobCredit("ACC-2001", bob.getFullName(), 15000, 30000);
    DepositAccount aliceDeposit("ACC-3001", alice.getFullName(), 120000, 12);

    alice.addAccount(&aliceSavings);
    alice.addAccount(&aliceDeposit);
    bob.addAccount(&bobCredit);

    Card aliceCard("2200 1000 0000 0001", aliceSavings);

    printSection("1. ОТДЕЛЕНИЯ БАНКА");
    printDepartments(bank);

    printSection("2. НАЧАЛЬНОЕ СОСТОЯНИЕ СЧЕТОВ");
    printAccountCard(aliceSavings);
    printAccountCard(bobCredit);
    printAccountCard(aliceDeposit);

    printSection("3. ВЫПОЛНЕНИЕ ОПЕРАЦИЙ");
    printOperationResult("Оплата картой 1500 RUB (магазин: Книжный)",
                         aliceCard.pay(1500, "Книжный"));

    printOperationResult("Пополнение Savings на 3000 RUB",
                         aliceSavings.deposit(3000, "Внесение наличных"));

    printOperationResult("Снятие с Credit 20000 RUB",
                         bobCredit.withdraw(20000, "Покупка техники"));

    printOperationResult("Попытка снять с Deposit 1000 RUB до разблокировки",
                         aliceDeposit.withdraw(1000, "Попытка досрочного снятия"));

    aliceDeposit.unlock();

    printOperationResult("Снятие с Deposit 1000 RUB после разблокировки",
                         aliceDeposit.withdraw(1000, "Снятие после разблокировки"));

    printOperationResult("Перевод 5000 RUB со Savings на Credit",
                         bank.transfer(aliceSavings, bobCredit, 5000));

    aliceSavings.addMonthlyInterest();
    std::cout << GREEN << "[INFO]" << RESET
              << " На сберегательный счет начислены месячные проценты.\n";

    printSection("4. ИТОГОВОЕ СОСТОЯНИЕ СЧЕТОВ");
    printAccountCard(aliceSavings);
    printAccountCard(bobCredit);
    printAccountCard(aliceDeposit);

    printSection("5. СВОДКА ПО КЛИЕНТАМ");
    printClientSummary(alice);
    printClientSummary(bob);

    printSection("6. ИСТОРИЯ ОПЕРАЦИЙ");
    printHistoryTable(aliceSavings);
    printHistoryTable(bobCredit);
    printHistoryTable(aliceDeposit);

    printSection("РАБОТА ПРОГРАММЫ ЗАВЕРШЕНА");
    return 0;
}
