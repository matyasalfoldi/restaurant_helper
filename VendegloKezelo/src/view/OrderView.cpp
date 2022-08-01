#include <sstream>

#include "view/OrderView.h"

namespace View
{
    bool OrderView::is_valid_amount(const std::string& amount) const
    {
        return !amount.empty() && std::stoi(amount) > 0;
    }

    Model::Order OrderView::get_chosen_order(const std::string& choice) const
    {
        return model->get_order(choice);
    }

    bool OrderView::is_valid_choice(std::string choice) const
    {
        if(choice.empty())
        {
            return false;
        }
        //else if(std::find(
        //            all_possible_orders.begin(),
        //            all_possible_orders.end(),
        //            choice) != all_possible_orders.end())
        int index = 0;
        while(index < all_possible_orders.size())
        {
            if(choice == all_possible_orders[index])
            {
                break;
            }
            ++index;
        };
        if(index == all_possible_orders.size())
        {
            return false;
        }
        return true;
    }

    bool OrderView::is_valid_table_number(const std::string& table_number) const
    {
        if(table_number.empty())
        {
            return false;
        }
        if(!is_valid_positive_number(table_number))
        {
            return false;
        }
        if(std::stoi(table_number) > model->get_table_count())
        {
            return false;
        }
        return true;
    }

    void OrderView::add_to_order_callback(Fl_Widget *w, void *view)
    {
        OrderView* order_view = static_cast<OrderView*>(view);
        std::string samount = order_view->amount->value();
        int amount = -1;
        if(order_view->is_valid_amount(samount))
        {
            amount = std::stoi(samount);
        }
        else
        {
            fl_message("Incorrect amount given!");
            return;
        }
        std::string choice = order_view->choices->value();
        if(!order_view->is_valid_choice(choice))
        {
            fl_message("No food/drink was chosen!");
            return;
        }
        std::string table = order_view->tables->value();
        if(!order_view->is_valid_table_number(table))
        {
            fl_message("Invalid table number!");
            return;
        }

        Model::Order current_order =
            Model::Order(
                amount,
                choice,
                amount*order_view->get_chosen_order(choice).price
            );
        // Update Model
        order_view->model->add_order(current_order);
        // Update GUI
        order_view->add_to_prepared_order(current_order, table);
        order_view->update_prepared_order_count();
        order_view->update_prepared_order_sum();
    }

    void OrderView::update_prepared_order_sum()
    {
        sum_buffer->text(std::to_string(model->tmp_order_sum()).c_str());
    }

    void OrderView::update_prepared_order_count()
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

    void OrderView::finnish_order_callback(Fl_Widget *w, void *view)
    {
        OrderView* order_view = static_cast<OrderView*>(view);
        order_view->model->finalize_order();
        order_view->set_to_zero();
    }

    void OrderView::set_to_zero()
    {
        prepared_order->value("");
        update_prepared_order_count();
        update_prepared_order_sum();
    }

    bool OrderView::is_valid_order_number(const std::string& order_number) const
    {
        if(order_number.empty())
        {
            return false;
        }
        // This should get negative numbers aswell
        if(!is_valid_positive_number(order_number))
        {
            return false;
        }
        if(std::stoi(order_number) >= model->tmp_order_count())
        {
            return false;
        }
        return true;
    }

    bool OrderView::is_valid_positive_number(const std::string& number) const
    {
        for(const auto& c : number)
        {
            if(!std::isdigit(c))
            {
                return false;
            }
        }
        return true;
    }

    void OrderView::remove_from_order_callback(Fl_Widget *w, void *view)
    {
        OrderView* order_view = static_cast<OrderView*>(view);
        std::string sorder_number = order_view->row_to_delete->value();
        if(!order_view->is_valid_order_number(sorder_number))
        {
            fl_message("Invalid order number!");
            return;
        }
        int order_number = std::stoi(sorder_number);
        order_view->remove_from_prepared_order(order_number);
        // returns the deleted order, if needed later on
        order_view->model->remove_order(order_number);
        order_view->update_prepared_order_count();
        order_view->update_prepared_order_sum();
    }

    void OrderView::remove_from_prepared_order(std::size_t index)
    {
        std::stringstream ss{prepared_order->value()};
        std::string new_order = "";
        for(std::size_t i = 0; i < model->tmp_order_count(); ++i)
        {
            std::string order_part = "";
            std::getline(ss, order_part, '\n');
            if(i != index)
            {
                if(new_order.empty())
                {
                    new_order = order_part;
                }
                else
                {
                    new_order = new_order+"\n"+order_part;
                }
            }
        }
        prepared_order->value(new_order.c_str());
    }

    void OrderView::add_to_prepared_order(Model::Order order, const std::string& table)
    {
        std::string old_order = prepared_order->value();
        std::string new_order = "";
        if(!old_order.empty())
        {
            new_order = old_order + "\n";
        }
        new_order = new_order+"Table: "+table+", "+
                    std::to_string(order.amount)+". "+order.name;
        prepared_order->value(new_order.c_str());
    }

    OrderView::OrderView(std::unique_ptr<Model::OrderModel>&& m, int x, int y, int w, int h)
    {
        model = std::move(m);

        Fl_Group* group = new Fl_Group(x, y, w, h, "Order page");
        {
            amount = new Fl_Int_Input(75, 200, 150, 30, "Amount:");

            choices = new Fl_Input_Choice(300, 200, 200, 30, "Choices:");
            all_possible_orders = model->fetch_all_possible_orders();
            if(all_possible_orders.size() > 0)
            {
                for(auto& order : all_possible_orders)
                {
                    choices->add(order.c_str());
                }
                choices->value(0);
            }

            tables = new Fl_Input_Choice(75, 250, 200, 30, "Tables:");
            std::size_t table_count = model->get_table_count();
            for(std::size_t i = 1; i <= table_count; ++i)
            {
                tables->add(std::to_string(i).c_str());
            }
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
