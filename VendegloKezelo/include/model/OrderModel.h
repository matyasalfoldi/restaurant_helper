#ifndef ORDERMODEL_H
#define ORDERMODEL_H

#include <functional>
#include <list>
#include <memory>
#include <vector>

#include "model/IncomeRow.h"
#include "model/Order.h"
#include "persistence/DataStore.h"

namespace Model
{
    class OrderModel;
    using Update_Func = std::function<void(OrderModel&)>;

    class OrderModel
    {
        public:
            OrderModel(std::unique_ptr<DataStore<std::vector<Order>, std::vector<Order>>>&& p,
                       std::shared_ptr<DataStore<std::vector<Model::IncomeRow>, int>> db_conn);
            void add_order(Order order);
            void connect(Update_Func update_func);
            std::vector<std::string> fetch_all_possible_orders();
            void finalize_order();
            Order get_chosen_order(const std::string& order) const;
            std::string get_order_string(const Order& order) const;
            std::vector<Order> get_prepared_order() const;
            // TODO: Get from persistence
            std::size_t get_table_count() const{return 3;};
            void notify();
            Order remove_order(int index);
            int tmp_order_count() const;
            int tmp_order_sum() const;
            ~OrderModel();

            bool is_valid_amount(const std::string& amount) const;
            bool is_valid_choice(std::string choice) const;
            bool is_valid_order_number(const std::string& order_number) const;
            bool is_valid_positive_number(const std::string& number) const;
            bool is_valid_table_number(const std::string& table_number) const;

        protected:

        private:
            std::vector<Update_Func> listeners;
            std::unique_ptr<DataStore<std::vector<Order>, std::vector<Order>>> persistence;
            std::shared_ptr<DataStore<std::vector<Model::IncomeRow>, int>> db;
            std::vector<Order> prepared_order;
            std::vector<Model::Order> all_possible_orders;
    };
}

#endif // ORDERMODEL_H
