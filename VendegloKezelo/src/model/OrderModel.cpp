#include "model/OrderModel.h"

#include <numeric>

namespace Model
{
    OrderModel::OrderModel(
        std::unique_ptr<Persistence<std::vector<Order>, std::vector<Order>>>&& p,
        std::shared_ptr<Persistence<std::vector<int>, int>> d)
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
        for(const auto& order : prepared_order)
        {
            db->write(order.price);
        }
        prepared_order.clear();
    }

    OrderModel::~OrderModel()
    {
        //dtor
    }
}
