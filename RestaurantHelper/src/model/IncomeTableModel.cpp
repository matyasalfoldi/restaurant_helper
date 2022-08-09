#include <algorithm>
#include <sstream>

#include "model/IncomeTableModel.h"
#include "model/utils.h"

namespace Model
{
    IncomeTableModel::IncomeTableModel(DataStore<Model::IncomeRows, int, Model::IncomeRow>::Shared_Ptr&& p)
    {
        persistence = std::move(p);
        IncomeCriteria income_criteria;
        std::string date = get_current_date();
        income_criteria.predicate =
            [&date](const IncomeRow& income_row)
            {
                return date_comparer(date, income_row);
            };
        incomes = persistence->get(income_criteria);
        headers = persistence->get_column_headers();
        notify();
    }

    void IncomeTableModel::connect(Update_Func_IncomeTable update_func)
    {
        listeners.push_back(update_func);
    }

    std::size_t IncomeTableModel::get_column_count() const
    {
        return headers.size();
    }

    std::string IncomeTableModel::get_column_header(int col) const
    {
        return headers[col];
    }

    std::string IncomeTableModel::get_data(int row, int col) const
    {
        if(col == 0)
        {
            return std::to_string(incomes[row].income);
        }
        else
        {
            return incomes[row].date;
        }
    }

    std::size_t IncomeTableModel::get_number_of_rows() const
    {
        return incomes.size();
    }

    void IncomeTableModel::notify()
    {
        int i = 0;
        for(auto& listener : listeners)
        {
            listener(*this);
        }
    }

    void IncomeTableModel::reload_data(bool show_all, std::string date)
    {
        IncomeCriteria income_criteria;
        if(show_all)
        {
            income_criteria.predicate =
                [](const IncomeRow& income_row)
                {
                    return true;
                };
        }
        else
        {
            if(date.empty())
            {
                date = get_current_date();
            }
            income_criteria.predicate =
                [&date](const IncomeRow& income_row)
                {
                    return date_comparer(date, income_row);
                };
        }
        incomes = persistence->get(income_criteria);
        headers = persistence->get_column_headers();
        notify();
    }

    IncomeTableModel::~IncomeTableModel()
    {
        //dtor
    }
}
