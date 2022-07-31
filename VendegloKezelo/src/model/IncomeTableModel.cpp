#include "model/IncomeTableModel.h"

namespace Model
{
    IncomeTableModel::IncomeTableModel(std::weak_ptr<Persistence<int, int>>&& p)
    {
        persistence = std::move(p);
    }

    IncomeTableModel::~IncomeTableModel()
    {
        //dtor
    }
}
