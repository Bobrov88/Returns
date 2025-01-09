#pragma once

#include "summing_segment_tree.h"
#include <iostream>
#include <cmath>

struct BulkMoneyAdder
{
    double delta = {};
};

struct BulkMoneySpender
{
    double delta = {};
};

struct BulkTaxApplier
{
    double count = 1.0;
};

class BulkLinearUpdater
{
public:
    BulkLinearUpdater() = default;

    BulkLinearUpdater(const BulkMoneyAdder &add) : add_(add) {}

    BulkLinearUpdater(const BulkTaxApplier &tax) : tax_(tax) {}

    BulkLinearUpdater(const BulkMoneySpender &spend) : spend_(spend) {}

    void CombineWith(const BulkLinearUpdater &other)
    {
        tax_.count *= other.tax_.count;
        add_.delta = add_.delta * other.tax_.count + other.add_.delta;
        spend_.delta += other.spend_.delta;
    }

    DayInfo Collapse(DayInfo origin, IndexSegment segment) const
    {
        return DayInfo{origin.income_ * tax_.count, origin.outcome_} +
               DayInfo{add_.delta * static_cast<double>(segment.length()), spend_.delta * static_cast<double>(segment.length())};
    }

private:
    // Apply tax first, then add.
    BulkTaxApplier tax_;
    BulkMoneyAdder add_;
    BulkMoneySpender spend_;
};