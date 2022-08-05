#include <algorithm>
#include <ctime>
#include <sstream>

#include "model/IncomeTableModel.h"

namespace Model
{
    IncomeTableModel::IncomeTableModel(std::shared_ptr<DataStore<std::vector<Model::IncomeRow>, int, IncomeRow>> p)
    {
        persistence = std::move(p);
        IncomeCriteria income_criteria;
        std::time_t time = std::time(nullptr);
        std::tm* const time_info = std::localtime(&time);
        std::string date = std::to_string(1900+time_info->tm_year) + "-" +
                           std::to_string(1+time_info->tm_mon) + "-" +
                           std::to_string(time_info->tm_mday);

        income_criteria.predicate =
            [&](const IncomeRow& income_row)
            {
                std::stringstream input_date(date);
                std::string input_val;
                std::stringstream pred_date(income_row.date);
                std::string pred_val;
                auto remove_leading_zeros =
                    [](std::string& input_val)
                    {
                        input_val.erase(
                            input_val.begin(),
                            std::find_if(
                                input_val.begin(),
                                input_val.end(),
                                [](unsigned char ch)
                                {
                                    return ch != '0';
                                }
                            )
                        );
                    };
                auto get_date_part =
                    [&]()
                    {
                        std::getline(input_date, input_val, '-');
                        // Remove leading 0-s
                        remove_leading_zeros(input_val);
                        std::getline(pred_date, pred_val, '-');
                        remove_leading_zeros(pred_val);
                    };
                //Compare year
                get_date_part();
                if(input_val != pred_val)
                {
                    return false;
                }
                //Compare month
                get_date_part();
                if(input_val != pred_val)
                {
                    return false;
                }
                //Compare day
                get_date_part();
                if(input_val != pred_val)
                {
                    return false;
                }
                return true;
            };
        delete time_info;
        incomes = persistence->get(income_criteria);
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
        IncomeCriteria income_criteria;
        if(show_all)
        {
            income_criteria.predicate =
                [](const IncomeRow& income_row)
                {
                    return true;
                };
        }
        else
        {
            if(date.empty())
            {
                std::time_t time = std::time(nullptr);
                std::tm* const time_info = std::localtime(&time);
                date = std::to_string(1900+time_info->tm_year) + "-" +
                       std::to_string(1+time_info->tm_mon) + "-" +
                       std::to_string(time_info->tm_mday);
                delete time_info;
            }
            income_criteria.predicate =
                [&](const IncomeRow& income_row)
                {
                    std::stringstream input_date(date);
                    std::string input_val;
                    std::stringstream pred_date(income_row.date);
                    std::string pred_val;
                    auto remove_leading_zeros =
                        [](std::string& input_val)
                        {
                            input_val.erase(
                                input_val.begin(),
                                std::find_if(
                                    input_val.begin(),
                                    input_val.end(),
                                    [](unsigned char ch)
                                    {
                                        return ch != '0';
                                    }
                                )
                            );
                        };
                    auto get_date_part =
                        [&]()
                        {
                            std::getline(input_date, input_val, '-');
                            // Remove leading 0-s
                            remove_leading_zeros(input_val);
                            std::getline(pred_date, pred_val, '-');
                            remove_leading_zeros(pred_val);
                        };
                    //Compare year
                    get_date_part();
                    if(input_val != pred_val)
                    {
                        return false;
                    }
                    //Compare month
                    get_date_part();
                    if(input_val != pred_val)
                    {
                        return false;
                    }
                    //Compare day
                    get_date_part();
                    if(input_val != pred_val)
                    {
                        return false;
                    }
                    return true;
                };
        }
        incomes = persistence->get(income_criteria);
        notify();
    }

    IncomeTableModel::~IncomeTableModel()
    {
        //dtor
    }
}
