#include "model/OrderModel.h"

namespace Model
{
    OrderModel::OrderModel(std::unique_ptr<Persistence<std::vector<Order>, std::vector<Order>>>&& p)
    {
        persistence = std::move(p);
    }

    void OrderModel::add_order(Order order)
    {
        prepared_order.push_back(order);
    }

    void OrderModel::remove_order(int index)
    {
        prepared_order.erase(prepared_order.begin() + index);
    }

    Order OrderModel::get_order(int index) const
    {
        return prepared_order[index];
    }

    std::vector<Order> OrderModel::get_all_possible_orders() const
    {
        return persistence->get();
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

    OrderModel::~OrderModel()
    {
        //dtor
    }
}
