#include <numeric>

#include "view/IncomeView.h"
#include "model/IncomeTableModel.h"

namespace View
{
    void IncomeView::calculate_sum_callback(Fl_Widget *w, void *view)
    {
        IncomeView* order_view = static_cast<IncomeView*>(view);
        std::vector<int> incomes = order_view->model->fetch_all_income();
        order_view->sum_buffer->text(
            std::to_string(
                std::accumulate(
                    incomes.begin(),
                    incomes.end(),
                    0)
            ).c_str()
        );
    }

    void IncomeView::reload_table_callback(Fl_Widget *w, void *view)
    {
        IncomeView* order_view = static_cast<IncomeView*>(view);
        order_view->income_table->draw_everything();
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

            sum_buffer = new Fl_Text_Buffer();
            sum = new Fl_Text_Display(250, 150, 150, 30);
            sum->buffer(sum_buffer);
            sum_buffer->text("0");

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
