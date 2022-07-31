#ifndef ORDER_H_INCLUDED
#define ORDER_H_INCLUDED

#include <string>

namespace Model
{
    struct Order
    {
        int amount;
        std::string name;
        int price;
    };
}

#endif // ORDER_H_INCLUDED
