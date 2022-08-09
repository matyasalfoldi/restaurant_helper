#ifndef INCOMEROW_H_INCLUDED
#define INCOMEROW_H_INCLUDED

#include <string>
#include <vector>

namespace Model
{
    struct IncomeRow;

    using IncomeRows = std::vector<IncomeRow>;

    struct IncomeRow
    {
        IncomeRow(int i = 0, std::string d = "")
        : income(i), date(d)
        {}
        int income;
        std::string date;
    };
}

#endif // INCOMEROW_H_INCLUDED
