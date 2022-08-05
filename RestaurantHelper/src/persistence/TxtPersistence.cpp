#include <algorithm>
#include <fstream>
#include <iterator>

#include "persistence/TxtPersistence.h"

TxtPersistence::TxtPersistence()
{

}

std::vector<Model::Order> TxtPersistence::get(const Criteria<Model::Order>& criteria)
{
    auto is_number = [](const std::string& value)
    {
        for(auto c : value)
        {
            if(!std::isdigit(c))
            {
                return false;
            }
        }
        return true;
    };
    possible_orders.clear();
    std::ifstream config(config_file);

    while(!config.eof())
    {
        parse_input(config, is_number);
    }
    return possible_orders;
}

std::vector<std::string> TxtPersistence::get_column_headers() const
{
    return std::vector<std::string>();
}

void TxtPersistence::parse_input(std::ifstream& config, bool(*predicate)(const std::string&))
{
    Model::Order order;
    order.table = -1;
    order.amount = 1;
    std::for_each(
        std::istream_iterator<std::string>(config),
        std::istream_iterator<std::string>(),
        [&,this](std::string order_part)
        {

            if(predicate(order_part))
            {
                order.price = std::stoi(order_part);
                possible_orders.push_back(order);
                reset_order(order);
            }
            else
            {
                order.name = order.name + " " + order_part;
            }
        });
}

void TxtPersistence::reset_order(Model::Order& order)
{
    order.amount = 1;
    order.name = "";
    order.price = -1;
}

void TxtPersistence::write(std::vector<Model::Order>, bool new_data)
{

}

TxtPersistence::~TxtPersistence()
{
    //dtor
}
