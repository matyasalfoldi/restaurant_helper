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

    void IncomeController::calculate_sum_callback(Fl_Widget* w, void* c_s)
    {
        CallbackStore* callback_store = (CallbackStore*)c_s;
        View::IncomeView* income_view = static_cast<View::IncomeView*>(callback_store->view);
        IncomeController* income_controller = static_cast<IncomeController*>(callback_store->controller);
        bool show_all = income_view->show_all->value();
        // TODO: validate input
        std::string date = income_view->date_to_filter->value();
        if(!date.empty() && !income_controller->model->is_valid_date(date))
        {
            fl_message("Invalid date. Example format: 2022-01-02");
        }
        std::vector<Model::IncomeRow> incomes = income_controller->model->fetch_all_income(show_all, date);
        income_view->sum_buffer->text(
            std::to_string(
                std::accumulate(
                    incomes.begin(),
                    incomes.end(),
                    0,
                    [](int accumulated_income, Model::IncomeRow next_income)
                    {
                        return accumulated_income + next_income.income;
                    })
            ).c_str()
        );
        income_view->income_table->draw_everything(show_all, date);
    }

    void IncomeController::reload_table_callback(Fl_Widget* w, void* c_s)
    {
        CallbackStore* callback_store = (CallbackStore*)c_s;
        View::IncomeView* income_view = static_cast<View::IncomeView*>(callback_store->view);
        IncomeController* income_controller = static_cast<IncomeController*>(callback_store->controller);
        bool show_all = income_view->show_all->value();
        std::string date = income_view->date_to_filter->value();
        if(!date.empty() && !income_controller->model->is_valid_date(date))
        {
            fl_message("Invalid date. Example format: 2022-01-02");
        }
        income_view->income_table->draw_everything(show_all, date);
    }

    void IncomeController::show_all_callback(Fl_Widget* w, void* c_s)
    {
        CallbackStore* callback_store = (CallbackStore*)c_s;
        View::IncomeView* income_view = static_cast<View::IncomeView*>(callback_store->view);
        IncomeController* income_controller = static_cast<IncomeController*>(callback_store->controller);
        income_view->date_to_filter->value("");
    }

    IncomeController::~IncomeController()
    {
        //dtor
    }
}
