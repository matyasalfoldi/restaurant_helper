#ifndef INCOMETABLEMODEL_H
#define INCOMETABLEMODEL_H

#include <memory>
#include <string>
#include <vector>

#include "model/IncomeRow.h"
#include "persistence/DataStore.h"

namespace Model
{
    class IncomeTableModel
    {
        public:
            IncomeTableModel(std::shared_ptr<DataStore<std::vector<Model::IncomeRow>, int>> p);
            std::size_t get_number_of_rows() const;
            std::string get_data(int row, int col) const;
            std::string get_column_header(int col) const;
            std::size_t get_column_count() const;
            void reload_data(bool show_all, std::string date="");
            ~IncomeTableModel();

        protected:

        private:
            std::vector<Model::IncomeRow> incomes;
            std::vector<std::string> headers;
            std::shared_ptr<DataStore<std::vector<Model::IncomeRow>, int>> persistence;
    };
}

#endif // INCOMETABLEMODEL_H
