#ifndef INCOMEMODEL_H
#define INCOMEMODEL_H

#include <memory>
#include <string>
#include <vector>
#include <set>

#include "model/IncomeRow.h"
#include "persistence/DataStore.h"

namespace Model
{
    class IncomeModel
    {
        public:
            IncomeModel(std::shared_ptr<DataStore<std::vector<Model::IncomeRow>, int>>&& p);
            ~IncomeModel();
            std::vector<Model::IncomeRow> fetch_all_income(bool show_all, std::string date);
            bool is_valid_date(std::string date) const;
            std::shared_ptr<DataStore<std::vector<Model::IncomeRow>, int>> get_persistence();
        protected:

        private:
            std::vector<Model::IncomeRow> incomes;
            std::shared_ptr<DataStore<std::vector<Model::IncomeRow>, int>> persistence;
    };
}

#endif // INCOMEMODEL_H
