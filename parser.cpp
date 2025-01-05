#include "parser.h"

// Напишите в этом файле код, ответственный за чтение запросов.

Query::~Query() {}

Queries ParseQuery(std::string_view word)
{
    using namespace std::string_view_literals;
    if (word == "ComputeIncome"sv)
        return Queries::COMPUTEINCOME;
    else if (word == "Earn"sv)
        return Queries::EARN;
    else if (word == "PayTax"sv)
        return Queries::PAYTAX;
    else
        return Queries::SPEND;
}

ParsedValues Parser(std::string_view line)
{
    std::istringstream iss{std::move(std::string{line})};
    std::string word;
    iss >> word;
    Queries query = ParseQuery(word);
    iss >> word;
    Date from(std::move(word));
    iss >> word;
    Date to(std::move(word));
    std::optional<double> number = std::nullopt;
    if (iss)
    {
        iss >> word;
        number = std::stod(std::move(word));
    }
    return {query, from, to, number};
}
