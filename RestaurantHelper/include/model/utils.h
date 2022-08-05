#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <algorithm>
#include <ctime>
#include <functional>
#include <sstream>
#include <string>

#include "model/IncomeRow.h"

namespace Model
{
    extern std::function<bool(const std::string&, const IncomeRow&)> date_comparer;
    std::string get_current_date();
}

#endif // UTILS_H_INCLUDED
