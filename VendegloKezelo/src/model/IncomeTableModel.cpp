#include "model/IncomeTableModel.h"

namespace Model
{
    IncomeTableModel::IncomeTableModel(std::shared_ptr<DataStore<std::vector<Model::IncomeRow>, int>> p)
    {
        persistence = std::move(p);
        incomes = persistence->get();
    }

    IncomeTableModel::~IncomeTableModel()
    {
        //dtor
    }
}
