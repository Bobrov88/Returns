#include "parser.h"

// Напишите в этом файле код, ответственный за чтение запросов.

void Parser(std::string_view line)
{
    std::istringstream iss{std::move(std::string{line})};
    std::string word;
    iss >> word;
    std::string query = std::move(word);
    iss >> word;
    Date from(std::move(word));
    iss >> word;
    Date to(std::move(word));
    if (iss)
    {
        iss >> word;
        double money = std::stod(std::move(word));
    }
}
