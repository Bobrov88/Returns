#pragma once

struct DayInfo
{
    double income_ = {};
    double outcome_ = {};
    DayInfo() = default;
    DayInfo(double income, double outcome) : income_(income), outcome_(outcome) {}
    DayInfo operator+(const DayInfo &rhs) const
    {
        return DayInfo{income_ + rhs.income_,
                       outcome_ + rhs.outcome_};
    }
    DayInfo operator*(double factor) const
    {
        return DayInfo{income_ * factor,
                       outcome_ * factor};
    }
};
