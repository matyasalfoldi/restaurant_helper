#include "view/OrderView.h"

namespace View
{
    void OrderView::add_to_order_callback(Fl_Widget *w, void *view)
    {
        OrderView* order_view = static_cast<OrderView*>(view);
        // Check the amount given
        std::string samount = order_view->amount->value();
        int amount = -1;
        if(!samount.empty())
        {
            amount = std::stoi(samount);
        }
        if(amount <= 0)
        {
            fl_message("Incorrect amount given!");
            return;
        }
        std::string choice = order_view->choices->value();
        if(choice.empty())
        {
            fl_message("No food/drink was chosen!");
            return;
        }
        std::string table = order_view->tables->value();

        Model::Order chosen_order;
        for(auto& order : order_view->all_possible_orders)
        {
            if(order.name == choice && order.amount == amount)
            {
                chosen_order = order;
            }
        }

        Model::Order current_order =
            Model::Order(
                amount,
                choice,
                amount*chosen_order.price
            );
        order_view->model->add_order(current_order);

        order_view->update_prepared_order(current_order);

        order_view->row_to_delete->clear();
        int number_of_orders = order_view->model->tmp_order_count();
        for(std::size_t i = 0; i < number_of_orders; ++i)
        {
            order_view->row_to_delete->add(std::to_string(i).c_str());
        }

    }

    void OrderView::finnish_order_callback(Fl_Widget *w, void *view)
    {
        OrderView* order_view = static_cast<OrderView*>(view);
    }

    void OrderView::remove_from_order_callback(Fl_Widget *w, void *view)
    {
        OrderView* order_view = static_cast<OrderView*>(view);
    }

    void OrderView::update_prepared_order(Model::Order order, bool add)
    {
        std::string old_order = prepared_order->value();
        std::string new_order = "";
        if(add)
        {
            if(!old_order.empty())
            {
                new_order = old_order + "\n";
            }
            new_order = old_order+std::to_string(order.amount)+" "+
                        order.name;
        }
        prepared_order->value(new_order.c_str());
    }

    OrderView::OrderView(std::unique_ptr<Model::OrderModel>&& m, int x, int y, int w, int h)
    {
        model = std::move(m);

        Fl_Group* group = new Fl_Group(x, y, w, h, "Order page");
        {
            amount = new Fl_Int_Input(75, 200, 150, 30, "Amount:");

            choices = new Fl_Input_Choice(300, 200, 200, 30, "Choices:");
            all_possible_orders = model->get_all_possible_orders();
            for(auto& order : all_possible_orders)
            {
                choices->add(order.name.c_str());
            }

            tables = new Fl_Input_Choice(75, 250, 200, 30, "Tables:");
            tables->add("1");
            tables->add("2");
            tables->value(0);

            add_to_order = new Fl_Button(250, 125, 100, 40, "Add to order");
            add_to_order->callback(add_to_order_callback, this);

            row_to_delete = new Fl_Input_Choice(100, 400, 200, 30, "Select a row:");

            remove_from_order = new Fl_Button(350, 400, 150, 30, "Remove from order");
            remove_from_order->callback(remove_from_order_callback, this);

            prepared_order = new Fl_Multiline_Output(525, 100, 250, 300, "Current order:");

            sum_buffer = new Fl_Text_Buffer();
            sum = new Fl_Text_Display(575, 450, 150, 30, "Sum:");
            sum->buffer(sum_buffer);
            sum_buffer->text("0");

            finnish_order = new Fl_Button(575, 500, 150, 40, "Finnish order");
            finnish_order->callback(finnish_order_callback, this);
        }
        group->end();
    }

    OrderView::~OrderView()
    {
        //dtor
    }
}
