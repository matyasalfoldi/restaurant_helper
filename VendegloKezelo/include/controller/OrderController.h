#ifndef ORDERCONTROLLER_H
#define ORDERCONTROLLER_H

#include <memory>

#include <FL/Fl.H>
#include <FL/Fl_Widget.H>

#include "model/OrderModel.h"

namespace Controller
{
    class OrderController
    {
        public:
            OrderController(std::unique_ptr<Model::OrderModel>&& m);
            void update();
            ~OrderController();
            void connect(Model::Update_Func update_func)
            {
                model->connect(update_func);
            }

            // Callbacks
            static void add_to_order_callback(Fl_Widget* w, void* callback_store);
            static void finnish_order_callback(Fl_Widget* w, void* callback_store);
            static void remove_from_order_callback(Fl_Widget* w, void* callback_store);
        protected:

        private:
            std::unique_ptr<Model::OrderModel> model;
    };
}

#endif // ORDERCONTROLLER_H
