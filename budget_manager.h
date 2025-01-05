#pragma once

#include "parser.h"

class BudgetManager : public ReadQuery, public ModifyQuery
{

    struct DayInfo
    {
        double money;
    };

    std::vector<DayInfo> day_incomes;

    void ComputeIncome(Date from, Date to) const override;
    void PayTax(Date from, Date to) override;
    void Earn(Date from, Date to, double income) override;

public:
    static const Date START_DATE;
    static const Date END_DATE;
    static const double TAX;

    BudgetManager();
    ~BudgetManager() override;
    void InvokeQuery(ParsedValues);
};