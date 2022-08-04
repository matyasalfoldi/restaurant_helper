#include "model/IncomeTableModel.h"

namespace Model
{
    IncomeTableModel::IncomeTableModel(std::shared_ptr<DataStore<std::vector<Model::IncomeRow>, int>> p)
    {
        persistence = std::move(p);
        incomes = persistence->get();
        headers = persistence->get_column_headers();
        notify();
    }

    void IncomeTableModel::connect(Update_Func_IncomeTable update_func)
    {
        listeners.push_back(update_func);
    }

    std::size_t IncomeTableModel::get_column_count() const
    {
        return headers.size();
    }

    std::string IncomeTableModel::get_column_header(int col) const
    {
        return headers[col];
    }

    std::string IncomeTableModel::get_data(int row, int col) const
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

    std::size_t IncomeTableModel::get_number_of_rows() const
    {
        return incomes.size();
    }

    void IncomeTableModel::notify()
    {
        int i = 0;
        for(auto& listener : listeners)
        {
            listener(*this);
        }
    }

    void IncomeTableModel::reload_data(bool show_all, std::string date)
    {
        incomes = persistence->get(!show_all, date);
        notify();
    }

    IncomeTableModel::~IncomeTableModel()
    {
        //dtor
    }
}
