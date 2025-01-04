#pragma once
#include "budget_manager.h"

class Query {
    public:
    virtual ~Query() = 0;
};

class ReadQuery : public Query {
    
};

class ModifyQuery : public Query {
};

void Parser(std::string_view line);

// Напишите в этом файле код, ответственный за чтение запросов.