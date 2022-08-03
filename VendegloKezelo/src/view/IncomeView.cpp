#include <numeric>

#include "view/IncomeView.h"
#include "model/IncomeTableModel.h"
#include "model/IncomeRow.h"

namespace View
{
    void IncomeView::calculate_sum_callback(Fl_Widget *w, void *view)
    {
        IncomeView* income_view = static_cast<IncomeView*>(view);
        bool show_all = income_view->show_all->value();
        // TODO: validate input
        std::string date = income_view->date_to_filter->value();
        if(!date.empty() && !income_view->model->is_valid_date(date))
        {
            fl_message("Invalid date. Example format: 2022-01-02");
        }
        std::vector<Model::IncomeRow> incomes = income_view->model->fetch_all_income(show_all, date);
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

    void IncomeView::reload_table_callback(Fl_Widget *w, void *view)
    {
        IncomeView* income_view = static_cast<IncomeView*>(view);
        bool show_all = income_view->show_all->value();
        std::string date = income_view->date_to_filter->value();
        if(!date.empty() && !income_view->model->is_valid_date(date))
        {
            fl_message("Invalid date. Example format: 2022-01-02");
        }
        income_view->income_table->draw_everything(show_all, date);
    }

    void IncomeView::show_all_callback(Fl_Widget* w, void* view)
    {
        IncomeView* income_view = static_cast<IncomeView*>(view);
        income_view->date_to_filter->value("");
    }

    IncomeView::IncomeView(std::unique_ptr<Model::IncomeModel>&& m, int x, int y, int w, int h)
    {
        model = std::move(m);

        Fl_Group* group = new Fl_Group(x, y, w, h, "Income page");
        {
            calculate_sum = new Fl_Button(100, 150, 100, 30, "Calculate sum");
            calculate_sum->callback(calculate_sum_callback, this);

            reload_table = new Fl_Button(450, 150, 100, 30, "Reload");
            reload_table->callback(reload_table_callback, this);

            show_all = new Fl_Check_Button(450, 200, 150, 30, "Show all income");
            show_all->callback(show_all_callback, this);

            sum_buffer = new Fl_Text_Buffer();
            sum = new Fl_Text_Display(250, 150, 150, 30);
            sum->buffer(sum_buffer);
            sum_buffer->text("0");

            date_to_filter = new Fl_Input(100, 200, 100, 30, "Filter for date:");

            income_table = new IncomeTable(
                std::make_unique<Model::IncomeTableModel>(
                    model->get_persistence()),
                x, y+200, w, h+100, "Income"
            );
        }
        group->end();
    }

    IncomeView::~IncomeView()
    {
        //dtor
    }
}
