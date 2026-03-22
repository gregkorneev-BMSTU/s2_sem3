#include <iomanip>
#include <iostream>
#include <memory>

#include "Bank.h"
#include "Card.h"
#include "Client.h"
#include "CreditAccount.h"
#include "DepositAccount.h"
#include "SavingsAccount.h"

namespace {
void printAccountSummary(const std::shared_ptr<Account>& account) {
    std::cout << account->getType() << " [" << account->getNumber() << "]"
              << " | владелец: " << account->getOwnerName() << " | баланс: " << std::fixed
              << std::setprecision(2) << account->getBalance() << " RUB\n";
}

void printHistory(const std::shared_ptr<Account>& account) {
    std::cout << "\nИстория операций счета " << account->getNumber() << ":\n";
    for (const auto& tx : account->getHistory()) {
        std::cout << "  - " << tx.toString() << "\n";
    }
}
}  // namespace

int main() {
    std::cout << "Учебный проект: Банковская система (вариант 15)\n\n";

    Bank bank("BMSTU Bank");

    // Композиция: отделения принадлежат банку по времени жизни.
    bank.addDepartment("Центральное отделение", "Москва, ул. 2-я Бауманская, 5");
    bank.addDepartment("Северное отделение", "Москва, ул. Лобненская, 12");

    std::cout << "Отделения банка:\n";
    for (const auto& dep : bank.getDepartments()) {
        std::cout << "  - " << dep.getName() << " (" << dep.getAddress() << ")\n";
    }

    auto alice = std::make_shared<Client>(1, "Алиса Иванова");
    auto bob = std::make_shared<Client>(2, "Боб Петров");

    bank.registerClient(alice);
    bank.registerClient(bob);

    // Наследование: Account -> SavingsAccount/CreditAccount/DepositAccount.
    auto aliceSavings = bank.createSavingsAccount("ACC-1001", alice->getFullName(), 50000.0, 6.0);
    auto bobCredit = bank.createCreditAccount("ACC-2001", bob->getFullName(), 15000.0, 30000.0);
    auto aliceDeposit = bank.createDepositAccount("ACC-3001", alice->getFullName(), 120000.0, 12);

    // Агрегация: клиент хранит ссылки на уже созданные счета.
    alice->addAccount(aliceSavings);
    alice->addAccount(aliceDeposit);
    bob->addAccount(bobCredit);

    std::cout << "\nНачальные данные по счетам:\n";
    printAccountSummary(aliceSavings);
    printAccountSummary(bobCredit);
    printAccountSummary(aliceDeposit);

    // Ассоциация: карта ссылается на существующий счет и не владеет им.
    Card aliceCard("2200 1000 0000 0001", *aliceSavings);

    std::cout << "\nОперации:\n";
    std::cout << "  * Оплата картой 1 500 RUB: "
              << (aliceCard.pay(1500.0, "Книжный магазин") ? "успех" : "ошибка") << "\n";
    std::cout << "  * Пополнение сберегательного счета на 3 000 RUB: "
              << (aliceSavings->deposit(3000.0, "Внесение наличных") ? "успех" : "ошибка") << "\n";
    std::cout << "  * Снятие с кредитного счета 20 000 RUB: "
              << (bobCredit->withdraw(20000.0, "Покупка техники") ? "успех" : "ошибка") << "\n";

    std::cout << "  * Попытка снять 1 000 RUB с депозитного счета (до окончания срока): "
              << (aliceDeposit->withdraw(1000.0, "Попытка досрочного снятия") ? "успех" : "ошибка")
              << "\n";

    aliceDeposit->unlockTerm();
    std::cout << "  * Снятие 1 000 RUB с депозитного счета после разблокировки: "
              << (aliceDeposit->withdraw(1000.0, "Снятие после окончания срока") ? "успех" : "ошибка")
              << "\n";

    // Делегирование: Bank::transfer делегирует расчет комиссии CommissionCalculator.
    std::cout << "  * Перевод 5 000 RUB со сберегательного на кредитный счет: "
              << (bank.transfer(*aliceSavings, *bobCredit, 5000.0) ? "успех" : "ошибка") << "\n";

    aliceSavings->accrueMonthlyInterest();

    std::cout << "\nИтоговые балансы:\n";
    printAccountSummary(aliceSavings);
    printAccountSummary(bobCredit);
    printAccountSummary(aliceDeposit);

    std::cout << "\nСуммарный баланс клиента " << alice->getFullName() << ": " << std::fixed
              << std::setprecision(2) << alice->totalBalance() << " RUB\n";

    printHistory(aliceSavings);
    printHistory(bobCredit);
    printHistory(aliceDeposit);

    return 0;
}
