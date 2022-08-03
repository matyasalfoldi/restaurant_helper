#ifndef INCOMEMODEL_H
#define INCOMEMODEL_H

#include <memory>
#include <vector>

#include "model/IncomeRow.h"
#include "persistence/Persistence.h"

namespace Model
{
    class IncomeModel
    {
        public:
            IncomeModel(std::shared_ptr<Persistence<std::vector<Model::IncomeRow>, int>>&& p);
            ~IncomeModel();
            std::vector<Model::IncomeRow> fetch_all_income(bool show_all)
            {
                incomes = persistence->get(!show_all);
                return incomes;
            }
            std::shared_ptr<Persistence<std::vector<Model::IncomeRow>, int>> get_persistence();
        protected:

        private:
            std::vector<Model::IncomeRow> incomes;
            std::shared_ptr<Persistence<std::vector<Model::IncomeRow>, int>> persistence;
    };
}

#endif // INCOMEMODEL_H
