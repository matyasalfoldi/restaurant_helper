#include <numeric>

#include "view/IncomeView.h"

namespace View
{
    IncomeView::IncomeView(std::shared_ptr<Controller::IncomeController>&& c, int x, int y, int w, int h)
    {
        controller = std::move(c);

        Fl_Group* group = new Fl_Group(x, y, w, h, "Income page");
        {
            callback_store = new Controller::CallbackStore(this, controller.get());
            reload_table = new Fl_Button(250, 200, 100, 30, "Reload");
            reload_table->callback(controller->reload_table_callback, callback_store);

            show_all = new Fl_Check_Button(450, 200, 150, 30, "Show all income");
            show_all->callback(controller->show_all_callback, callback_store);

            sum_buffer = new Fl_Text_Buffer();
            sum = new Fl_Text_Display(250, 150, 150, 30, "Sum:");
            sum->buffer(sum_buffer);
            sum_buffer->text("0");

            date_to_filter = new Fl_Input(100, 200, 100, 30, "Filter for date:");

            // Since IncomeTable inherits from Fl_Table it will become
            // most likely a child widget to group, which causes it
            // to be automatically deleted.
            income_table = new IncomeTable(
                std::make_unique<Controller::IncomeTableController>(
                    std::make_unique<Model::IncomeTableModel>(
                        controller->get_persistence()
                    )
                ),
                x, y+200, w, h+100, "Income"
            );

            controller->connect([&](Model::IncomeModel& mo)
                    {
                        update(mo);
                    });
            controller->update();
        }
        group->end();
    }

    void IncomeView::update(Model::IncomeModel& model)
    {
        bool show_all_state = model.is_show_all_on();
        sum_buffer->text(
            std::to_string(
                model.get_sum()
            ).c_str()
        );
        std::string date = model.get_date();
        date_to_filter->value(date.c_str());
        show_all->value(show_all_state);
        income_table->draw_everything(show_all_state, date);
    }

    IncomeView::~IncomeView()
    {
        delete callback_store;
        sum->buffer(nullptr);
        delete sum_buffer;
    }
}
