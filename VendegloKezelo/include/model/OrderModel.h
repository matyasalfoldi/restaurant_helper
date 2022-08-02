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
            OrderModel(std::unique_ptr<Persistence<std::vector<Order>, std::vector<Order>>>&& p,
                       std::shared_ptr<Persistence<std::vector<int>, int>> db_conn);
            void add_order(Order order);
            Order remove_order(int index);
            Order get_order(const std::string& order) const;
            std::vector<std::string> fetch_all_possible_orders();
            int tmp_order_count() const;
            int tmp_order_sum() const;
            void finalize_order();
            // TODO: Get from persistence
            std::size_t get_table_count() const{return 3;};
            ~OrderModel();

        protected:

        private:
            std::unique_ptr<Persistence<std::vector<Order>, std::vector<Order>>> persistence;
            std::shared_ptr<Persistence<std::vector<int>, int>> db;
            std::vector<Order> prepared_order;
            std::vector<Model::Order> all_possible_orders;
    };
}

#endif // ORDERMODEL_H
