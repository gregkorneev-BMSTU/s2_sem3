#include "CommissionCalculator.h"

#include "Account.h"

#include <algorithm>

double CommissionCalculator::calculateTransferFee(const Account& from, const Account& to, double amount) const {
    if (amount <= 0.0) {
        return 0.0;
    }

    double rate = 0.01;  // базовая комиссия 1%

    if (from.getType() == to.getType()) {
        rate = 0.005;
    }

    if (from.getType() == "CreditAccount") {
        rate = 0.015;
    }

    const double fee = amount * rate;
    return std::max(0.0, fee);
}
