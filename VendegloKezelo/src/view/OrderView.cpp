#include <algorithm>
#include <numeric>
#include <sstream>

#include <iterator>
#include <ostream>

#include "view/OrderView.h"

namespace View
{
    OrderView::OrderView(std::unique_ptr<Controller::OrderController>&& c, int x, int y, int w, int h)
    {
        controller = std::move(c);

        Fl_Group* group = new Fl_Group(x, y, w, h, "Order page");
        {
            amount = new Fl_Int_Input(75, 200, 150, 30, "Amount:");

            choices = new Fl_Input_Choice(300, 200, 200, 30, "Choices:");

            tables = new Fl_Input_Choice(75, 250, 200, 30, "Tables:");

            callback_store = new Controller::CallbackStore(this, controller.get());
            add_to_order = new Fl_Button(250, 125, 100, 40, "Add to order");
            add_to_order->callback(controller->add_to_order_callback, callback_store);

            row_to_delete = new Fl_Input_Choice(100, 400, 200, 30, "Select a row:");

            remove_from_order = new Fl_Button(350, 400, 150, 30, "Remove from order");
            remove_from_order->callback(controller->remove_from_order_callback, callback_store);

            prepared_order = new Fl_Multiline_Output(525, 100, 250, 300, "Current order:");

            sum_buffer = new Fl_Text_Buffer();
            sum = new Fl_Text_Display(575, 450, 150, 30, "Sum:");
            sum->buffer(sum_buffer);
            sum_buffer->text("0");

            finnish_order = new Fl_Button(575, 500, 150, 40, "Finnish order");
            finnish_order->callback(controller->finnish_order_callback, callback_store);

            controller->update();
        }
        group->end();
    }

    void OrderView::update(Model::OrderModel* model)
    {
        if(!initialized)
        {
            std::size_t table_count = model->get_table_count();
            for(std::size_t i = 1; i <= table_count; ++i)
            {
                tables->add(std::to_string(i).c_str());
            }
            tables->value(0);

            std::vector<std::string> all_possible_orders = model->fetch_all_possible_orders();
            for(auto& order : all_possible_orders)
            {
                choices->add(order.c_str());
            }
            if(all_possible_orders.size() > 0)
            {
                choices->value(0);
            }
            initialized = true;
        }
        update_prepared_order(model);
        update_prepared_order_count(model);
        update_prepared_order_sum(model);
    }

    void OrderView::update_prepared_order(Model::OrderModel* model)
    {
        auto curr_order = model->get_prepared_order();
        std::string new_order = "";
        std::for_each(
            curr_order.begin(),
            curr_order.end(),
            [&new_order,model](const Model::Order& order)
            {
                auto formatted_order = model->get_order_string(order);
                if(!new_order.empty())
                {
                    new_order = new_order+"\n";
                }
                new_order += formatted_order;
            });
        prepared_order->value(new_order.c_str());
    }

    void OrderView::update_prepared_order_count(Model::OrderModel* model)
    {
        row_to_delete->clear();
        int number_of_orders = model->tmp_order_count();
        for(std::size_t i = 0; i < number_of_orders; ++i)
        {
            row_to_delete->add(std::to_string(i).c_str());
        }
        if(number_of_orders > 0)
        {
            row_to_delete->value(0);
        }
    }

    void OrderView::update_prepared_order_sum(Model::OrderModel* model)
    {
        sum_buffer->text(std::to_string(model->tmp_order_sum()).c_str());
    }

    OrderView::~OrderView()
    {
        //dtor
    }
}
