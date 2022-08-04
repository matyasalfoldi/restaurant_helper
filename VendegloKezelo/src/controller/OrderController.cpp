#include "controller/CallbackStore.h"
#include "controller/OrderController.h"
#include "view/OrderView.h"

namespace Controller
{
    OrderController::OrderController(std::unique_ptr<Model::OrderModel>&& m)
    {
        model = std::move(m);
    }

    void OrderController::connect(Model::Update_Func_Order update_func)
    {
        model->connect(update_func);
    }

    void OrderController::update()
    {
        model->notify();
    }

    void OrderController::add_to_order_callback(Fl_Widget* w, void* c_s)
    {
        CallbackStore* callback_store = static_cast<CallbackStore*>(c_s);
        View::OrderView* order_view = static_cast<View::OrderView*>(callback_store->view);
        OrderController* order_controller = static_cast<OrderController*>(callback_store->controller);
        std::string samount = order_view->amount->value();
        int amount = -1;
        if(!order_controller->model->is_valid_amount(samount))
        {
            fl_message("Incorrect amount given!");
            return;
        }
        amount = std::stoi(samount);
        std::string choice = order_view->choices->value();
        if(!order_controller->model->is_valid_choice(choice))
        {
            fl_message("No food/drink was chosen!");
            return;
        }
        std::string table = order_view->tables->value();
        if(!order_controller->model->is_valid_table_number(table))
        {
            fl_message("Invalid table number!");
            return;
        }

        Model::Order current_order =
            Model::Order(
                amount,
                choice,
                amount*order_controller->model->get_chosen_order(choice).price,
                std::stoi(table)
            );
        order_controller->model->add_order(current_order);
    }

    void OrderController::finnish_order_callback(Fl_Widget* w, void* c_s)
    {
        CallbackStore* callback_store = static_cast<CallbackStore*>(c_s);
        View::OrderView* order_view = static_cast<View::OrderView*>(callback_store->view);
        OrderController* order_controller = static_cast<OrderController*>(callback_store->controller);
        order_controller->model->finalize_order();
    }

    void OrderController::remove_from_order_callback(Fl_Widget* w, void* c_s)
    {
        CallbackStore* callback_store = static_cast<CallbackStore*>(c_s);
        View::OrderView* order_view = static_cast<View::OrderView*>(callback_store->view);
        OrderController* order_controller = static_cast<OrderController*>(callback_store->controller);
        std::string sorder_number = order_view->row_to_delete->value();
        if(!order_controller->model->is_valid_order_number(sorder_number))
        {
            fl_message("Invalid order number!");
            return;
        }
        int order_number = std::stoi(sorder_number);

        // returns the deleted order, if needed later on
        order_controller->model->remove_order(order_number);
    }

    OrderController::~OrderController()
    {
        //dtor
    }
}
