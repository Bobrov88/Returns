#pragma once

#include "date.h"

class BudgetManager
{

    struct DayInfo
    {
        double money;
    };

    std::vector<DayInfo> day_incomes;

public:
    static const Date START_DATE;
    static const Date END_DATE;
    static const double TAX;

    BudgetManager();
    void ComputeIncome(Date from, Date to) const;
    void PayTax(Date from, Date to);
    void Earn(Date from, Date to, double income);
};