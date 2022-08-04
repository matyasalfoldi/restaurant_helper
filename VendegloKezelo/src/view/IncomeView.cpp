#include <numeric>

#include "view/IncomeView.h"
#include "model/IncomeTableModel.h"
#include "model/IncomeRow.h"

namespace View
{
    IncomeView::IncomeView(std::shared_ptr<Controller::IncomeController>&& c, int x, int y, int w, int h)
    {
        controller = std::move(c);

        Fl_Group* group = new Fl_Group(x, y, w, h, "Income page");
        {
            callback_store = new Controller::CallbackStore(this, controller.get());
            calculate_sum = new Fl_Button(100, 150, 100, 30, "Calculate sum");
            calculate_sum->callback(controller->calculate_sum_callback, callback_store);

            reload_table = new Fl_Button(450, 150, 100, 30, "Reload");
            reload_table->callback(controller->reload_table_callback, callback_store);

            show_all = new Fl_Check_Button(450, 200, 150, 30, "Show all income");
            show_all->callback(controller->show_all_callback, callback_store);

            sum_buffer = new Fl_Text_Buffer();
            sum = new Fl_Text_Display(250, 150, 150, 30);
            sum->buffer(sum_buffer);
            sum_buffer->text("0");

            date_to_filter = new Fl_Input(100, 200, 100, 30, "Filter for date:");

            income_table = new IncomeTable(
                std::make_unique<Model::IncomeTableModel>(
                     controller->get_persistence()),
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
