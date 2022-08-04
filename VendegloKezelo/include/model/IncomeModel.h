#ifndef INCOMEMODEL_H
#define INCOMEMODEL_H

#include <functional>
#include <memory>
#include <numeric>
#include <set>
#include <string>
#include <vector>

#include "model/IncomeRow.h"
#include "persistence/DataStore.h"

namespace Model
{
    class IncomeModel;
    using Update_Func_Income = std::function<void(IncomeModel&)>;

    class IncomeModel
    {
        public:
            IncomeModel(std::shared_ptr<DataStore<std::vector<Model::IncomeRow>, int>>&& p);
            void connect(Update_Func_Income update_func);
            std::vector<Model::IncomeRow> fetch_all_income(bool show_all, std::string date);
            std::shared_ptr<DataStore<std::vector<Model::IncomeRow>, int>> get_persistence();
            std::string get_date()
            {
                return date;
            }
            int get_sum()
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
            bool is_show_all_on()
            {
                return show_all;
            }
            bool is_valid_date(std::string date) const;
            void set_date(std::string d)
            {
                date = d;
                if(!date.empty())
                {
                    show_all = false;
                }
                notify();
            }
            void set_show_all(bool s)
            {
                show_all = s;
                if(show_all)
                {
                    date = "";
                }
                notify();
            }
            void notify();
            ~IncomeModel();
        protected:

        private:
            bool show_all;
            std::string date;
            std::vector<Update_Func_Income> listeners;
            std::vector<Model::IncomeRow> incomes;
            std::shared_ptr<DataStore<std::vector<Model::IncomeRow>, int>> persistence;
    };
}

#endif // INCOMEMODEL_H
