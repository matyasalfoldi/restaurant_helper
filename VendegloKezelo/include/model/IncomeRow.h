#ifndef INCOMEROW_H_INCLUDED
#define INCOMEROW_H_INCLUDED

#include <string>

namespace Model
{
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
