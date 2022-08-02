#ifndef INCOMEMODEL_H
#define INCOMEMODEL_H

#include <memory>
#include <vector>

#include "persistence/Persistence.h"

namespace Model
{
    class IncomeModel
    {
        public:
            IncomeModel(std::shared_ptr<Persistence<std::vector<int>, int>>&& p);
            ~IncomeModel();
            std::vector<int> fetch_all_income()
            {
                incomes = persistence->get();
                return incomes;
            }
            std::shared_ptr<Persistence<std::vector<int>, int>> get_persistence();
        protected:

        private:
            std::vector<int> incomes;
            std::shared_ptr<Persistence<std::vector<int>, int>> persistence;
    };
}

#endif // INCOMEMODEL_H
