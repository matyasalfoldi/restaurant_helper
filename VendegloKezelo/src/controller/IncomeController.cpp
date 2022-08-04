#include <numeric>

#include "controller/CallbackStore.h"
#include "controller/IncomeController.h"
#include "view/IncomeView.h"

namespace Controller
{
    IncomeController::IncomeController(std::unique_ptr<Model::IncomeModel>&& m)
    {
        model = std::move(m);
    }

    void IncomeController::reload_table_callback(Fl_Widget* w, void* c_s)
    {
        CallbackStore* callback_store = (CallbackStore*)c_s;
        View::IncomeView* income_view = static_cast<View::IncomeView*>(callback_store->view);
        IncomeController* income_controller = static_cast<IncomeController*>(callback_store->controller);
        std::string date = income_view->date_to_filter->value();
        if(!date.empty() && !income_controller->model->is_valid_date(date))
        {
            fl_message("Invalid date. Example format: 2022-01-02");
        }
        income_controller->set_date(date);
    }

    void IncomeController::show_all_callback(Fl_Widget* w, void* c_s)
    {
        CallbackStore* callback_store = (CallbackStore*)c_s;
        View::IncomeView* income_view = static_cast<View::IncomeView*>(callback_store->view);
        IncomeController* income_controller = static_cast<IncomeController*>(callback_store->controller);
        income_controller->set_show_all(static_cast<bool>(income_view->show_all->value()));
    }

    void IncomeController::update()
    {
        model->notify();
    }

    IncomeController::~IncomeController()
    {
        //dtor
    }
}
