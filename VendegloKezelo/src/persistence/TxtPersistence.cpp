#include <fstream>

#include "persistence/TxtPersistence.h"

TxtPersistence::TxtPersistence()
{

}

std::vector<Model::Order> TxtPersistence::get()
{
    possible_orders.clear();
    std::ifstream config(config_file);
    Model::Order order;
    order.amount = 1;
    while(!config.eof())
    {
        config >> order.name >> order.price;
        possible_orders.push_back(order);
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
