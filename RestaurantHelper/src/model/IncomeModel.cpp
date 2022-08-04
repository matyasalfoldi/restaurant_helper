#include <numeric>
#include <set>

#include "model/IncomeModel.h"

namespace Model
{
    IncomeModel::IncomeModel(std::shared_ptr<DataStore<std::vector<Model::IncomeRow>, int>>&& p)
    {
        persistence = std::move(p);
        show_all = false;
        date = "";
    }

    void IncomeModel::connect(Update_Func_Income update_func)
    {
        listeners.push_back(update_func);
    }

    std::vector<Model::IncomeRow> IncomeModel::fetch_all_income(bool show_all, std::string date)
    {
        incomes = persistence->get(!show_all, date);
        return incomes;
    }

    std::string IncomeModel::get_date()
    {
        return date;
    }

    int IncomeModel::get_sum()
    {
        incomes = fetch_all_income(show_all, date);
        return std::accumulate(
            incomes.begin(),
            incomes.end(),
            0,
            [](int accumulated_income, Model::IncomeRow next_income)
            {
                return accumulated_income + next_income.income;
            }
        );
    }

    std::shared_ptr<DataStore<std::vector<Model::IncomeRow>, int>> IncomeModel::get_persistence()
    {
        return persistence;
    }

    bool IncomeModel::is_show_all_on()
    {
        return show_all;
    }

    bool IncomeModel::is_valid_date(std::string date) const
    {
        // YYYY-MM-DD
        if(date.length() != 4+1+2+1+2)
        {
            return false;
        }
        std::set<int> number_indexes = {0, 1, 2, 3, 5, 6, 8, 9};
        std::set<int> dash_indexes = {4, 7};
        for(std::size_t i = 0; i < date.length(); ++i)
        {
            if(number_indexes.find(i) != number_indexes.end() &&
               !std::isdigit(date[i]))
            {
                return false;
            }
            else if(dash_indexes.find(i) != dash_indexes.end() &&
                    date.at(i) != '-')
            {
                return false;
            }
        }
        return true;
    }

    void IncomeModel::notify()
    {
        int i = 0;
        for(auto& listener : listeners)
        {
            listener(*this);
        }
    }

    void IncomeModel::set_date(std::string d)
    {
        date = d;
        if(!date.empty())
        {
            show_all = false;
        }
        notify();
    }

    void IncomeModel::set_show_all(bool s)
    {
        show_all = s;
        if(show_all)
        {
            date = "";
        }
        notify();
    }

    IncomeModel::~IncomeModel()
    {
        //dtor
    }
}
