#ifndef INCOMETABLEMODEL_H
#define INCOMETABLEMODEL_H

#include <memory>
#include <vector>

#include "model/IncomeRow.h"
#include "persistence/Persistence.h"

namespace Model
{
    class IncomeTableModel
    {
        public:
            IncomeTableModel(std::shared_ptr<Persistence<std::vector<Model::IncomeRow>, int>> p);
            std::size_t get_number_of_rows()
            {
                return incomes.size();
            }

            std::string get_data(int row, int col)
            {
                if(col == 0)
                {
                    return std::to_string(incomes[row].income);
                }
                else
                {
                    return incomes[row].date;
                }
            }

            void reload_data(bool show_all, std::string date="")
            {
                incomes = persistence->get(!show_all, date);
            }

            ~IncomeTableModel();

        protected:

        private:
            std::vector<Model::IncomeRow> incomes;
            std::shared_ptr<Persistence<std::vector<Model::IncomeRow>, int>> persistence;
    };
}

#endif // INCOMETABLEMODEL_H
