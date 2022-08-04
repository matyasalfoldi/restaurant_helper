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

    void IncomeController::connect(Model::Update_Func_Income update_func)
    {
        model->connect(update_func);
    }

    std::shared_ptr<DataStore<std::vector<Model::IncomeRow>, int>> IncomeController::get_persistence()
    {
        return model->get_persistence();
    }

    int IncomeController::get_sum() const
    {
        return model->get_sum();
    }

    void IncomeController::set_date(std::string date)
    {
        model->set_date(date);
    }

    void IncomeController::set_show_all(bool show_all)
    {
        model->set_show_all(show_all);
    }

    void IncomeController::update()
    {
        model->notify();
    }

    void IncomeController::reload_table_callback(Fl_Widget* w, void* c_s)
    {
        CallbackStore* callback_store = static_cast<CallbackStore*>(c_s);
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
        CallbackStore* callback_store = static_cast<CallbackStore*>(c_s);
        View::IncomeView* income_view = static_cast<View::IncomeView*>(callback_store->view);
        IncomeController* income_controller = static_cast<IncomeController*>(callback_store->controller);
        income_controller->set_show_all(static_cast<bool>(income_view->show_all->value()));
    }

    IncomeController::~IncomeController()
    {
        //dtor
    }
}
