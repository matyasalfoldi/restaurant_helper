#ifndef INCOMEMODEL_H
#define INCOMEMODEL_H

#include <functional>
#include <memory>
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
            bool is_valid_date(std::string date) const;
            void notify();
            ~IncomeModel();
        protected:

        private:
            std::vector<Update_Func_Income> listeners;
            std::vector<Model::IncomeRow> incomes;
            std::shared_ptr<DataStore<std::vector<Model::IncomeRow>, int>> persistence;
    };
}

#endif // INCOMEMODEL_H
