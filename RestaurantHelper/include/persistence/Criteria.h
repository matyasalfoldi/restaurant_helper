#ifndef CRITERIA_H_INCLUDED
#define CRITERIA_H_INCLUDED

#include <functional>

#include "model/IncomeRow.h"
#include "model/Order.h"

template <typename T>
struct Criteria
{
    std::function<bool(const T&)> predicate;
};

struct IncomeCriteria : public Criteria<Model::IncomeRow>
{
};

struct OrderCriteria : public Criteria<Model::Order>
{
};

#endif // CRITERIA_H_INCLUDED
