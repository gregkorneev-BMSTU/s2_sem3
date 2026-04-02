# Семинар 3. Вариант 15: **Банковская система**.

Проект написан в максимально простом учебном стиле:
- без `shared_ptr` и фабрик,
- с понятными методами,
- с прямой демонстрацией всех связей в `main.cpp`.

## Классы
- `Bank`
- `Department`
- `Client`
- `Account` (базовый)
- `SavingsAccount`
- `CreditAccount`
- `DepositAccount`
- `Card`
- `Transaction`
- `CommissionCalculator`

## Где показаны связи
- **Наследование**: `Account -> SavingsAccount, CreditAccount, DepositAccount`.
- **Ассоциация**: `Card` хранит `Account*`.
- **Агрегация**: `Client` хранит `std::vector<Account*>`.
- **Композиция**: `Bank` содержит `Department` и `CommissionCalculator`; `Account` содержит `Transaction`.
- **Делегирование**: `Bank::transfer` делегирует расчет комиссии `CommissionCalculator`.

## Сборка
```bash
cmake -B build && cmake --build build && ./build/project_bank
```
