#ifndef INCOMEMODEL_H
#define INCOMEMODEL_H

#include <memory>
#include <string>
#include <vector>
#include <set>

#include "model/IncomeRow.h"
#include "persistence/DataStore.h"

namespace Model
{
    class IncomeModel
    {
        public:
            IncomeModel(std::shared_ptr<DataStore<std::vector<Model::IncomeRow>, int>>&& p);
            ~IncomeModel();
            std::vector<Model::IncomeRow> fetch_all_income(bool show_all, std::string date)
            {
                incomes = persistence->get(!show_all, date);
                return incomes;
            }
            bool is_valid_date(std::string date) const
            {
                // YYYY-MM-DD
                if(date.length() != 4+1+2+1+2)
                {
                    return false;
                }
                std::set<int> number_indexes = {0, 1, 2, 3, 5, 6, 8, 9};
                std::set<int> dash_indexes = {4, 7};
                for(std::size_t i = 0; i < date.length(); ++i)
                {
                    if(number_indexes.find(i) != number_indexes.end() &&
                       !std::isdigit(date[i]))
                    {
                        return false;
                    }
                    else if(dash_indexes.find(i) != dash_indexes.end() &&
                            date.at(i) != '-')
                    {
                        return false;
                    }
                }
                return true;
            }
            std::shared_ptr<DataStore<std::vector<Model::IncomeRow>, int>> get_persistence();
        protected:

        private:
            std::vector<Model::IncomeRow> incomes;
            std::shared_ptr<DataStore<std::vector<Model::IncomeRow>, int>> persistence;
    };
}

#endif // INCOMEMODEL_H
