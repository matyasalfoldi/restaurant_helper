#ifndef INCOMETABLEMODEL_H
#define INCOMETABLEMODEL_H

#include <memory>
#include <vector>

#include "persistence/Persistence.h"

namespace Model
{
    class IncomeTableModel
    {
        public:
            IncomeTableModel(std::weak_ptr<Persistence<std::vector<int>, int>>&& p);
            ~IncomeTableModel();

        protected:

        private:
            std::weak_ptr<Persistence<std::vector<int>, int>> persistence;
    };
}

#endif // INCOMETABLEMODEL_H
