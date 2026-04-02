#include <iomanip>
#include <iostream>

#include "Account.h"
#include "Bank.h"
#include "Card.h"
#include "Client.h"
#include "CreditAccount.h"
#include "DepositAccount.h"
#include "SavingsAccount.h"

void printAccount(const Account& account) {
    std::cout << account.getType() << " [" << account.getNumber() << "]"
              << " | владелец: " << account.getOwnerName() << " | баланс: " << std::fixed
              << std::setprecision(2) << account.getBalance() << " RUB\n";
}

void printHistory(const Account& account) {
    std::cout << "\nИстория счета " << account.getNumber() << ":\n";
    const std::vector<Transaction>& history = account.getHistory();
    for (std::size_t i = 0; i < history.size(); i++) {
        std::cout << "  - " << history[i].toString() << "\n";
    }
}

int main() {
    std::cout << "Учебный проект: Банковская система (вариант 15)\n\n";

    Bank bank("BMSTU Bank");
    bank.addDepartment("Центральное", "Москва, ул. Бауманская, 5");
    bank.addDepartment("Северное", "Москва, ул. Лобненская, 12");

    Client alice(1, "Алиса Иванова");
    Client bob(2, "Боб Петров");
    bank.registerClient(alice);
    bank.registerClient(bob);

    // Наследование: три наследника от Account.
    SavingsAccount aliceSavings("ACC-1001", alice.getFullName(), 50000, 6);
    CreditAccount bobCredit("ACC-2001", bob.getFullName(), 15000, 30000);
    DepositAccount aliceDeposit("ACC-3001", alice.getFullName(), 120000, 12);

    // Агрегация: клиент хранит ссылки на внешние счета.
    alice.addAccount(&aliceSavings);
    alice.addAccount(&aliceDeposit);
    bob.addAccount(&bobCredit);

    // Ассоциация: карта связана со счетом.
    Card aliceCard("2200 1000 0000 0001", aliceSavings);

    std::cout << "Отделения банка:\n";
    const std::vector<Department>& deps = bank.getDepartments();
    for (std::size_t i = 0; i < deps.size(); i++) {
        std::cout << "  - " << deps[i].getName() << " (" << deps[i].getAddress() << ")\n";
    }

    std::cout << "\nНачальные балансы:\n";
    printAccount(aliceSavings);
    printAccount(bobCredit);
    printAccount(aliceDeposit);

    std::cout << "\nОперации:\n";
    std::cout << "  * Оплата картой 1500 RUB: "
              << (aliceCard.pay(1500, "Книжный") ? "успех" : "ошибка") << "\n";

    std::cout << "  * Пополнение Savings +3000 RUB: "
              << (aliceSavings.deposit(3000, "Внесение наличных") ? "успех" : "ошибка") << "\n";

    std::cout << "  * Снятие Credit -20000 RUB: "
              << (bobCredit.withdraw(20000, "Покупка техники") ? "успех" : "ошибка") << "\n";

    std::cout << "  * Попытка снять Deposit -1000 RUB (до разблокировки): "
              << (aliceDeposit.withdraw(1000, "Попытка досрочного снятия") ? "успех" : "ошибка") << "\n";

    aliceDeposit.unlock();
    std::cout << "  * Снятие Deposit -1000 RUB (после разблокировки): "
              << (aliceDeposit.withdraw(1000, "Снятие после разблокировки") ? "успех" : "ошибка")
              << "\n";

    // Делегирование в Bank::transfer -> CommissionCalculator.
    std::cout << "  * Перевод 5000 RUB со Savings на Credit: "
              << (bank.transfer(aliceSavings, bobCredit, 5000) ? "успех" : "ошибка") << "\n";

    aliceSavings.addMonthlyInterest();

    std::cout << "\nИтоговые балансы:\n";
    printAccount(aliceSavings);
    printAccount(bobCredit);
    printAccount(aliceDeposit);

    std::cout << "\nСуммарный баланс Алисы: " << alice.totalBalance() << " RUB\n";

    printHistory(aliceSavings);
    printHistory(bobCredit);
    printHistory(aliceDeposit);

    return 0;
}
