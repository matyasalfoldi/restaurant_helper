#include "model/IncomeModel.h"

namespace Model
{
    IncomeModel::IncomeModel(std::shared_ptr<DataStore<std::vector<Model::IncomeRow>, int>>&& p)
    {
        persistence = std::move(p);
    }

    std::shared_ptr<DataStore<std::vector<Model::IncomeRow>, int>> IncomeModel::get_persistence()
    {
        return persistence;
    }

    IncomeModel::~IncomeModel()
    {
        //dtor
    }
}
