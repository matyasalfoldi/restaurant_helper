#ifndef INCOMETABLEMODEL_H
#define INCOMETABLEMODEL_H

#include <memory>

#include "persistence/Persistence.h"

namespace Model
{
    class IncomeTableModel
    {
        public:
            IncomeTableModel(std::weak_ptr<Persistence<int, int>>&& p);
            ~IncomeTableModel();

        protected:

        private:
            std::weak_ptr<Persistence<int, int>> persistence;
    };
}

#endif // INCOMETABLEMODEL_H
