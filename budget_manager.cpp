#include "budget_manager.h"
#include "date.h"
#include <numeric>
#include <iostream>
#include <algorithm>

using namespace std::literals;

const Date BudgetManager::START_DATE = Date("2000-01-01"s);
const Date BudgetManager::END_DATE = Date("2100-01-01"s);

BudgetManager::BudgetManager()
{
    day_incomes.resize(static_cast<size_t>(Date::ComputeDistance(START_DATE, END_DATE)));
}

BudgetManager::~BudgetManager() {}

void BudgetManager::ComputeIncome(Date from, Date to) const
{
    std::cout << std::accumulate(day_incomes.begin() + Date::ComputeDistance(START_DATE, from),
                                 day_incomes.begin() + Date::ComputeDistance(START_DATE, to) + 1,
                                 0.0,
                                 [](double sum, const DayInfo &dayinfo)
                                 { return sum + dayinfo.income - dayinfo.outcome; })
              << "\n";
}

void BudgetManager::PayTax(Date from, Date to, double number)
{
    std::transform(day_incomes.begin() + Date::ComputeDistance(START_DATE, from),
                   day_incomes.begin() + Date::ComputeDistance(START_DATE, to) + 1,
                   day_incomes.begin() + Date::ComputeDistance(START_DATE, from),
                   [number](const DayInfo &dayinfo)
                   {
                       return DayInfo{dayinfo.income * (1. - number / 100), dayinfo.outcome};
                   });
}

void BudgetManager::Earn(Date from, Date to, double income)
{
    double everyday_income = income / (Date::ComputeDistance(from, to) + 1);
    std::transform(day_incomes.begin() + Date::ComputeDistance(START_DATE, from),
                   day_incomes.begin() + Date::ComputeDistance(START_DATE, to) + 1,
                   day_incomes.begin() + Date::ComputeDistance(START_DATE, from),
                   [everyday_income](const DayInfo &dayinfo)
                   {
                       return DayInfo{dayinfo.income + everyday_income, dayinfo.outcome};
                   });
}

void BudgetManager::Spend(Date from, Date to, double money)
{
    double everyday_outcome = money / (Date::ComputeDistance(from, to) + 1);
    std::transform(day_incomes.begin() + Date::ComputeDistance(START_DATE, from),
                   day_incomes.begin() + Date::ComputeDistance(START_DATE, to) + 1,
                   day_incomes.begin() + Date::ComputeDistance(START_DATE, from),
                   [everyday_outcome](const DayInfo &dayinfo)
                   {
                       return DayInfo{dayinfo.income, dayinfo.outcome + everyday_outcome};
                   });
}

void BudgetManager::InvokeQuery(ParsedValues pq)
{
    if (pq.query == Queries::COMPUTEINCOME)
        ComputeIncome(pq.from, pq.to);
    if (pq.query == Queries::EARN)
        Earn(pq.from, pq.to, *pq.number);
    if (pq.query == Queries::PAYTAX)
        PayTax(pq.from, pq.to, *pq.number);
    if (pq.query == Queries::SPEND)
        Spend(pq.from, pq.to, *pq.number);
}