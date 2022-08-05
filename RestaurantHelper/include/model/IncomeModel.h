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
            IncomeModel(std::shared_ptr<DataStore<std::vector<Model::IncomeRow>, int, Model::IncomeRow>>&& p);
            void connect(Update_Func_Income update_func);
            std::vector<Model::IncomeRow> fetch_all_income(bool show_all, std::string date);
            std::string get_date();
            std::shared_ptr<DataStore<std::vector<Model::IncomeRow>, int, Model::IncomeRow>> get_persistence();
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
            std::shared_ptr<DataStore<std::vector<IncomeRow>, int, IncomeRow>> persistence;
    };
}

#endif // INCOMEMODEL_H
