#include "model/OrderModel.h"

#include <algorithm>
#include <numeric>

namespace Model
{
    OrderModel::OrderModel(
        std::unique_ptr<DataStore<std::vector<Order>, std::vector<Order>>>&& p,
        std::shared_ptr<DataStore<std::vector<Model::IncomeRow>, int>> d)
    {
        persistence = std::move(p);
        db = d;
    }

    void OrderModel::add_order(Order order)
    {
        prepared_order.push_back(order);
    }

    Order OrderModel::remove_order(int index)
    {
        return *prepared_order.erase(prepared_order.begin() + index);
    }

    Order OrderModel::get_order(const std::string& order) const
    {
        Order not_found;
        for(const auto& o : all_possible_orders)
        {
            if(o.name == order)
            {
                return o;
            }
        }
        return not_found;
    }

    std::vector<std::string> OrderModel::fetch_all_possible_orders()
    {
        all_possible_orders = persistence->get();
        return std::accumulate(
            all_possible_orders.begin(),
            all_possible_orders.end(),
            std::vector<std::string>(),
            [](std::vector<std::string> order_names, Order order)
            {
                order_names.push_back(order.name);
                return order_names;
            });
    }

    int OrderModel::tmp_order_count() const
    {
        return prepared_order.size();
    }

    int OrderModel::tmp_order_sum() const
    {
        int sum = 0;
        for(const auto& order : prepared_order)
        {
            sum += order.price;
        }
        return sum;
    }

    void OrderModel::finalize_order()
    {
        // TODO?: Write to file through TxtPersistence
        // (create folder if not exists)
        // TODO: print out order
        db->write(tmp_order_sum());
        prepared_order.clear();
    }

    OrderModel::~OrderModel()
    {
        //dtor
    }


    bool OrderModel::is_valid_choice(std::string choice) const
    {
        if (choice.empty() ||
            std::find_if(
                all_possible_orders.begin(),
                all_possible_orders.end(),
                [&](Order order)
                {
                    return order.name == choice;
                }
                ) == all_possible_orders.end()
            )
        {
            return false;
        }
        return true;
    }

    bool OrderModel::is_valid_table_number(const std::string& table_number) const
    {
        if(table_number.empty() ||
           !is_valid_positive_number(table_number) ||
           std::stoi(table_number) > get_table_count())
        {
            return false;
        }
        return true;
    }

    bool OrderModel::is_valid_amount(const std::string& amount) const
    {
        return !amount.empty() && std::stoi(amount) > 0;
    }


    bool OrderModel::is_valid_order_number(const std::string& order_number) const
    {
        if(order_number.empty() ||
           !is_valid_positive_number(order_number) ||
           std::stoi(order_number) >= tmp_order_count())
        {
            return false;
        }
        return true;
    }

    bool OrderModel::is_valid_positive_number(const std::string& number) const
    {
        for(const auto& c : number)
        {
            if(!std::isdigit(c))
            {
                return false;
            }
        }
        return true;
    }
}
