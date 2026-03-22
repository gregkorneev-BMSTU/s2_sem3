# Учебный проект по ООП на C++

## Тема
Вариант 15: **Банковская система**.

## Реализованные классы
- `Bank`
- `Department`
- `Client`
- `Account` (базовый класс)
- `SavingsAccount`
- `CreditAccount`
- `DepositAccount`
- `Card`
- `Transaction`
- `CommissionCalculator`

## Где показаны отношения
- **Наследование**: `Account -> SavingsAccount, CreditAccount, DepositAccount`.
- **Ассоциация**: `Card` хранит невладеющий указатель `Account*`.
- **Агрегация**: `Client` хранит `std::vector<std::shared_ptr<Account>>`, счета создаются отдельно.
- **Композиция**:
  - `Bank` содержит `CommissionCalculator` как поле.
  - `Bank` содержит `std::vector<Department>` по значению.
  - `Account` содержит историю `std::vector<Transaction>` по значению.
- **Делегирование**: `Bank::transfer(...)` делегирует расчет комиссии объекту `CommissionCalculator`.

## Что умеет программа
- Создавать клиентов и счета разных типов.
- Пополнять счет и снимать средства.
- Выполнять перевод между счетами с комиссией.
- Вести историю транзакций.
- Демонстрировать работу карты, привязанной к счету.

## Сборка и запуск
```bash
cmake -S . -B build
cmake --build build
./build/project_bank
```
