#pragma once
#include <string_view>
#include <optional>
#include "date.h"

class Query
{
public:
    virtual ~Query() = 0;
};

class ReadQuery : public Query
{
public:
    virtual void ComputeIncome(Date from, Date to) const = 0;
    ~ReadQuery() override {};
};

class ModifyQuery : public Query
{
public:
    virtual void PayTax(Date from, Date to) = 0;
    virtual void Earn(Date from, Date to, double income) = 0;
    ~ModifyQuery() override {};
};

enum class Queries { 
    COMPUTEINCOME,
    PAYTAX,
    EARN
};

struct ParsedValues {
    Queries query;
    Date from;
    Date to;
    std::optional<double> money;
};

ParsedValues Parser(std::string_view);

// Напишите в этом файле код, ответственный за чтение запросов