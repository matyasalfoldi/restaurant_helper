#include "model/IncomeModel.h"

namespace Model
{
    IncomeModel::IncomeModel(std::shared_ptr<Persistence<int, int>>&& p)
    {
        persistence = std::move(p);
    }

    std::weak_ptr<Persistence<int, int>> IncomeModel::get_persistence()
    {
        return persistence;
    }

    IncomeModel::~IncomeModel()
    {
        //dtor
    }
}
