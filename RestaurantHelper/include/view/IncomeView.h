#ifndef INCOMEVIEW_H
#define INCOMEVIEW_H

#include <memory>
#include <vector>

#include <FL/Fl.H>
#include <FL/Fl_ask.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Text_Display.H>

#include "controller/CallbackStore.h"
#include "controller/IncomeController.h"
#include "view/IncomeTable.h"

namespace View
{
    class IncomeView
    {
        public:
            IncomeTable* income_table;

            Fl_Button* reload_table;
            Fl_Check_Button* show_all;
            Fl_Text_Buffer* sum_buffer;
            Fl_Text_Display* sum;
            Fl_Input* date_to_filter;

            IncomeView(std::shared_ptr<Controller::IncomeController>&& c, int x, int y, int w, int h);
            void update(Model::IncomeModel& model);
            ~IncomeView();

        protected:

        private:
            Controller::CallbackStore* callback_store;
            bool initialized = false;
            std::shared_ptr<Controller::IncomeController> controller;
    };
}

#endif // INCOMEVIEW_H
