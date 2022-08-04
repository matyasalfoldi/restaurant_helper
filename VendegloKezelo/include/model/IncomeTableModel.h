#ifndef INCOMETABLEMODEL_H
#define INCOMETABLEMODEL_H

#include <memory>
#include <string>
#include <vector>

#include "model/IncomeRow.h"
#include "persistence/DataStore.h"

namespace Model
{
    class IncomeTableModel;
    using Update_Func_IncomeTable = std::function<void(IncomeTableModel&)>;

    class IncomeTableModel
    {
        public:
            IncomeTableModel(std::shared_ptr<DataStore<std::vector<Model::IncomeRow>, int>> p);
            void connect(Update_Func_IncomeTable update_func);
            std::string get_column_header(int col) const;
            std::size_t get_column_count() const;
            std::string get_data(int row, int col) const;
            std::size_t get_number_of_rows() const;
            void notify();
            void reload_data(bool show_all, std::string date="");
            ~IncomeTableModel();

        protected:

        private:
            std::vector<Update_Func_IncomeTable> listeners;
            std::vector<Model::IncomeRow> incomes;
            std::vector<std::string> headers;
            std::shared_ptr<DataStore<std::vector<Model::IncomeRow>, int>> persistence;
    };
}

#endif // INCOMETABLEMODEL_H
