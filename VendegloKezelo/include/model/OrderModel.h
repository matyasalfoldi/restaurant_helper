#ifndef ORDERMODEL_H
#define ORDERMODEL_H

#include <memory>
#include <vector>

#include "model/Order.h"
#include "persistence/Persistence.h"

namespace Model
{
    class OrderModel
    {
        public:
            OrderModel(std::unique_ptr<Persistence<std::vector<Order>, std::vector<Order>>>&& p);
            void add_order(Order order);
            void remove_order(int index);
            Order get_order(int index) const;
            std::vector<Order> get_all_possible_orders() const;
            int tmp_order_count() const;
            int tmp_order_sum() const;
            ~OrderModel();

        protected:

        private:
            std::unique_ptr<Persistence<std::vector<Order>, std::vector<Order>>> persistence;
            std::vector<Order> prepared_order;
    };
}

#endif // ORDERMODEL_H
