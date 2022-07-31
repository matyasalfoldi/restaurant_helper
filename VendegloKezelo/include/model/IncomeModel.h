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
            IncomeModel(std::shared_ptr<Persistence<int, int>>&& p);
            ~IncomeModel();
            std::weak_ptr<Persistence<int, int>> get_persistence();
        protected:

        private:
            std::shared_ptr<Persistence<int, int>> persistence;
    };
}

#endif // INCOMEMODEL_H