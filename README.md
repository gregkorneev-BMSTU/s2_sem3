# Семинар 3. Вариант 15: **Банковская система**.

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
