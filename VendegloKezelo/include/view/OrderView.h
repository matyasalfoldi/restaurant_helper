#ifndef ORDERVIEW_H
#define ORDERVIEW_H

#include <memory>
#include <string>
#include <vector>

#include <FL/Fl.H>
#include <FL/Fl_ask.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Input_Choice.H>
#include <FL/Fl_Int_Input.H>
#include <FL/Fl_Multiline_Output.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Text_Display.H>


#include "model/Order.h"
#include "controller/CallbackStore.h"
#include "controller/OrderController.h"

namespace View
{
    class OrderView
    {
        public:
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

            OrderView(std::shared_ptr<Controller::OrderController>&& c, int x, int y, int w, int h);
            void update(Model::OrderModel& model);
            ~OrderView();

        protected:

        private:
            std::shared_ptr<Controller::OrderController> controller;
            Controller::CallbackStore* callback_store;
            bool initialized = false;

            void update_prepared_order(Model::OrderModel& model);
            void update_prepared_order_sum(Model::OrderModel& model);
            void update_prepared_order_count(Model::OrderModel& model);
    };
}

#endif // ORDERVIEW_H
