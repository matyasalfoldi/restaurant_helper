#ifndef INCOMEVIEW_H
#define INCOMEVIEW_H

#include <memory>
#include <vector>

#include <FL/Fl.H>
#include <FL/Fl_ask.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Text_Buffer.H>

#include "persistence/DataStore.h"
#include "view/IncomeTable.h"
#include "model/IncomeModel.h"

namespace View
{
    class IncomeView
    {
        public:
            IncomeView(std::unique_ptr<Model::IncomeModel>&& m, int x, int y, int w, int h);
            ~IncomeView();

        protected:

        private:
            std::unique_ptr<Model::IncomeModel> model;
            IncomeTable* income_table;

            Fl_Button* calculate_sum;
            Fl_Button* reload_table;
            Fl_Check_Button* show_all;
            Fl_Text_Buffer* sum_buffer;
            Fl_Text_Display* sum;
            Fl_Input* date_to_filter;

            static void calculate_sum_callback(Fl_Widget* w, void* view);
            static void reload_table_callback(Fl_Widget* w, void* view);
            static void filter_callback(Fl_Widget* w, void* view);
            static void show_all_callback(Fl_Widget* w, void* view);
    };
}

#endif // INCOMEVIEW_H
