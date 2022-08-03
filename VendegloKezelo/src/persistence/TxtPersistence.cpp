#include <fstream>

#include "persistence/TxtPersistence.h"

TxtPersistence::TxtPersistence()
{

}

std::vector<Model::Order> TxtPersistence::get(bool today_only, std::string date)
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
        Model::Order order;
        order.amount = 1;
        bool found_price = false;
        while(!found_price)
        {
            std::string order_part = "";
            config >> order_part;
            if(is_number(order_part))
            {
                found_price = true;
                order.price = std::stoi(order_part);
                possible_orders.push_back(order);
            }
            else
            {
                if(order.name.empty())
                {
                    order.name = order_part;
                }
                else
                {
                    order.name = order.name + " " + order_part;
                }
            }
        }
    }
    return possible_orders;
}

void TxtPersistence::write(std::vector<Model::Order>, bool new_data)
{

}

TxtPersistence::~TxtPersistence()
{
    //dtor
}
