#include "view/OrderView.h"

namespace View
{
    void add_to_order_callback(Fl_Widget *w, void *view)
    {
        OrderView* order_view = static_cast<OrderView*>(view);
    }

    void finnish_order_callback(Fl_Widget *w, void *view)
    {
        OrderView* order_view = static_cast<OrderView*>(view);
    }

    void remove_from_order_callback(Fl_Widget *w, void *view)
    {
        OrderView* order_view = static_cast<OrderView*>(view);
    }

    OrderView::OrderView(std::unique_ptr<Model::OrderModel>&& m, int x, int y, int w, int h)
    {
        model = std::move(m);

        Fl_Group* group = new Fl_Group(x, y, w, h, "Order page");
        {
            Fl_Int_Input* amount = new Fl_Int_Input(75, 200, 150, 30, "Amount:");

            Fl_Input_Choice* choices = new Fl_Input_Choice(300, 200, 200, 30, "Choices:");

            Fl_Input_Choice* tables = new Fl_Input_Choice(75, 250, 200, 30, "Tables:");
            tables->add("1");
            tables->value(0);

            Fl_Button* add_to_order = new Fl_Button(250, 125, 100, 40, "Add to order");
            add_to_order->callback(add_to_order_callback, this);

            Fl_Input_Choice* row_to_delete = new Fl_Input_Choice(100, 400, 200, 30, "Select a row:");

            Fl_Button* remove_from_order = new Fl_Button(350, 400, 150, 30, "Remove from order");
            remove_from_order->callback(remove_from_order_callback, this);

            Fl_Multiline_Output* prepared_order = new Fl_Multiline_Output(525, 100, 250, 300, "Current order:");

            Fl_Text_Buffer* sum_buffer = new Fl_Text_Buffer();
            Fl_Text_Display* sum = new Fl_Text_Display(575, 450, 150, 30, "Sum:");
            sum->buffer(sum_buffer);
            sum_buffer->text("0");

            Fl_Button* finnish_order = new Fl_Button(575, 500, 150, 40, "Finnish order");
            finnish_order->callback(finnish_order_callback, this);
        }
        group->end();
    }

    OrderView::~OrderView()
    {
        //dtor
    }
}
