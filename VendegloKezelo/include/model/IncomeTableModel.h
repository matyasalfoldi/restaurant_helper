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
            IncomeTableModel(std::shared_ptr<Persistence<std::vector<int>, int>> p);
            std::size_t get_number_of_rows()
            {
                return incomes.size();
            }
            int get_data(int row, int col)
            {
                return incomes[row];
            }
            void reload_data()
            {
                incomes = persistence->get();
            }

            ~IncomeTableModel();

        protected:

        private:
            std::vector<int> incomes;
            std::shared_ptr<Persistence<std::vector<int>, int>> persistence;
    };
}

#endif // INCOMETABLEMODEL_H
