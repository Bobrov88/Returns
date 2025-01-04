#include "budget_manager.h"
#include "date.h"
#include <numeric>
#include <iostream>
#include <algorithm>

using namespace std::literals;

const Date BudgetManager::START_DATE = Date("2000-01-01"s);
const Date BudgetManager::END_DATE = Date("2100-01-01"s);
const double BudgetManager::TAX = 0.87;

BudgetManager::BudgetManager()
{
    day_incomes.resize(static_cast<size_t>(Date::ComputeDistance(START_DATE, END_DATE)));
}

void BudgetManager::ComputeIncome(Date from, Date to) const
{
    std::cout << std::accumulate(day_incomes.begin() + Date::ComputeDistance(START_DATE, from),
                                 day_incomes.begin() + Date::ComputeDistance(START_DATE, to) + 1,
                                 0.0,
                                 [](double sum, const DayInfo &dayinfo)
                                 { return sum + dayinfo.money; });
}

void BudgetManager::PayTax(Date from, Date to)
{
    std::transform(day_incomes.begin() + Date::ComputeDistance(START_DATE, from),
                   day_incomes.begin() + Date::ComputeDistance(START_DATE, to) + 1,
                   day_incomes.begin() + Date::ComputeDistance(START_DATE, from),
                   [](const DayInfo &dayinfo)
                   {
                       return DayInfo{dayinfo.money * TAX};
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
                       return DayInfo{dayinfo.money + everyday_income};
                   });
}
