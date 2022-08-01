#ifndef ORDERVIEW_H
#define ORDERVIEW_H

#include <memory>
#include <string>
#include <vector>
#include <map>

#include <FL/Fl.H>
#include <FL/Fl_ask.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Multiline_Output.H>
#include <FL/Fl_Input_Choice.H>
#include <FL/Fl_Int_Input.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Group.H>

#include "model/Order.h"
#include "model/OrderModel.h"

namespace View
{
    class OrderView
    {
        public:
            OrderView(std::unique_ptr<Model::OrderModel>&& m, int x, int y, int w, int h);
            static void add_to_order_callback(Fl_Widget *w, void *view);
            static void finnish_order_callback(Fl_Widget *w, void *view);
            static void remove_from_order_callback(Fl_Widget *w, void *view);
            ~OrderView();

        protected:

        private:
            std::vector<Model::Order> all_possible_orders;
            std::unique_ptr<Model::OrderModel> model;

            Fl_Int_Input* amount;
            Fl_Input_Choice* choices;
            Fl_Input_Choice* tables;
            Fl_Button* add_to_order;
            Fl_Input_Choice* row_to_delete;
            Fl_Button* remove_from_order;
            Fl_Multiline_Output* prepared_order;
            Fl_Text_Buffer* sum_buffer;
            Fl_Text_Display* sum;
            Fl_Button* finnish_order;

            void update_prepared_order(Model::Order order, bool add=true);
            void update_prepared_order_count();
    };
}

#endif // ORDERVIEW_H
