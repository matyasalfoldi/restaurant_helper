#include <algorithm>
#include <numeric>

#include "model/OrderModel.h"
#include "persistence/Criteria.h"

namespace Model
{
    OrderModel::OrderModel(
        DataStore<Model::Orders, Model::Orders, Order>::Unique_Ptr&& p,
        DataStore<Model::IncomeRows, int, Model::IncomeRow>::Shared_Ptr d)
    {
        persistence = std::move(p);
        db = d;
    }

    void OrderModel::add_order(Order order)
    {
        prepared_order.push_back(order);
        notify();
    }

    void OrderModel::connect(Update_Func_Order update_func)
    {
        listeners.push_back(update_func);
    }

    std::vector<std::string> OrderModel::fetch_all_possible_orders()
    {
        OrderCriteria order_criteria;
        order_criteria.predicate =
            [](const Order& order)
            {
                return true;
            };
        all_possible_orders = persistence->get(order_criteria);
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

    void OrderModel::finalize_order()
    {
        // TODO: print out order to printer
        db->write(tmp_order_sum());
        prepared_order.clear();
        notify();
    }

    Order OrderModel::get_chosen_order(const std::string& order) const
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

    std::string OrderModel::get_order_string(const Order& order) const
    {
        return "Table: " + std::to_string(order.table) + ", " +
               std::to_string(order.amount) + ". " + order.name;
    }

    std::vector<Order> OrderModel::get_prepared_order() const
    {
        return prepared_order;
    }

    void OrderModel::notify()
    {
        int i = 0;
        for(auto& listener : listeners)
        {
            listener(*this);
        }
    }

    Order OrderModel::remove_order(int index)
    {
        auto deleted_element = *prepared_order.erase(prepared_order.begin() + index);
        notify();
        return deleted_element;
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

    bool OrderModel::is_valid_amount(const std::string& amount) const
    {
        return !amount.empty() && std::stoi(amount) > 0;
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

    OrderModel::~OrderModel()
    {
        //dtor
    }
}
