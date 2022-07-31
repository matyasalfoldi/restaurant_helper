#include "view/IncomeView.h"
#include "model/IncomeTableModel.h"

#include <FL/Fl.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Text_Display.H>

namespace View
{
    void calculate_sum_callback(Fl_Widget *w, void *view)
    {
        IncomeView* order_view = static_cast<IncomeView*>(view);
    }

    IncomeView::IncomeView(std::unique_ptr<Model::IncomeModel>&& m, int x, int y, int w, int h)
    {
        model = std::move(m);

        Fl_Group* group = new Fl_Group(x, y, w, h, "Income page");
        {
            Fl_Button* calculate_sum = new Fl_Button(100, 150, 100, 30, "Calculate sum");
            calculate_sum->callback(calculate_sum_callback, this);

            Fl_Text_Buffer* sum_buffer = new Fl_Text_Buffer();
            Fl_Text_Display* sum = new Fl_Text_Display(250, 150, 150, 30);
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
