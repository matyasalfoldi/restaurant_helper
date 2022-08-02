#include "model/IncomeTableModel.h"

namespace Model
{
    IncomeTableModel::IncomeTableModel(std::shared_ptr<Persistence<std::vector<int>, int>> p)
    {
        persistence = std::move(p);
        incomes = persistence->get();
    }

    IncomeTableModel::~IncomeTableModel()
    {
        //dtor
    }
}
