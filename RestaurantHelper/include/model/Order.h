#ifndef ORDER_H_INCLUDED
#define ORDER_H_INCLUDED

#include <string>

namespace Model
{
    struct Order
    {
        Order()
        : amount(-1), name(""), price(-1), table(-1)
        {}
        Order(int a, std::string n, int p, int t) // =-1
        : amount(a), name(n), price(p), table(t)
        {}
        int amount;
        std::string name;
        int price;
        int table;
    };
}

#endif // ORDER_H_INCLUDED
