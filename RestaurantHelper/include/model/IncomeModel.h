#ifndef INCOMEMODEL_H
#define INCOMEMODEL_H

#include <functional>
#include <memory>
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
            IncomeModel(DataStore<Model::IncomeRows, int, Model::IncomeRow>::Shared_Ptr&& p);
            void connect(Update_Func_Income update_func);
            std::vector<Model::IncomeRow> fetch_all_income(bool show_all, std::string date);
            std::string get_date();
            DataStore<Model::IncomeRows, int, Model::IncomeRow>::Shared_Ptr get_persistence();
            int get_sum();
            bool is_show_all_on();
            bool is_valid_date(std::string date) const;
            void notify();
            void set_date(std::string d);
            void set_show_all(bool s);
            ~IncomeModel();

        protected:

        private:
            bool show_all;
            std::string date;
            std::vector<Update_Func_Income> listeners;
            std::vector<Model::IncomeRow> incomes;
            DataStore<Model::IncomeRows, int, Model::IncomeRow>::Shared_Ptr persistence;
    };
}

#endif // INCOMEMODEL_H
