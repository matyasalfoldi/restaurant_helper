#ifndef TXTPERSISTENCE_H
#define TXTPERSISTENCE_H

#include <string>
#include <vector>

#include "model/Order.h"
#include "persistence/Persistence.h"

class TxtPersistence : public Persistence<std::vector<Model::Order>, std::vector<Model::Order>>
{
    public:
        TxtPersistence();
        virtual std::vector<Model::Order> get(bool today_only=true, std::string date="") override;
        virtual void write(std::vector<Model::Order>, bool new_data=true) override;
        virtual ~TxtPersistence();

    protected:

    private:
        std::string config_file = "config.txt";
        std::vector<Model::Order> possible_orders;
};

#endif // TXTPERSISTENCE_H
