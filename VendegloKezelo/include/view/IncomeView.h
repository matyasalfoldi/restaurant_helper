#ifndef INCOMEVIEW_H
#define INCOMEVIEW_H

#include <memory>
#include <vector>

#include <FL/Fl.H>
#include <FL/Fl_ask.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Text_Buffer.H>

#include "persistence/Persistence.h"
#include "view/IncomeTable.h"
#include "model/IncomeModel.h"

namespace View
{
    class IncomeView
    {
        public:
            IncomeView(std::unique_ptr<Model::IncomeModel>&& m, int x, int y, int w, int h);
            static void calculate_sum_callback(Fl_Widget *w, void *view);
            static void reload_table_callback(Fl_Widget *w, void *view);
            ~IncomeView();

        protected:

        private:
            std::unique_ptr<Model::IncomeModel> model;
            IncomeTable* income_table;

            Fl_Button* calculate_sum;
            Fl_Button* reload_table;
            Fl_Text_Buffer* sum_buffer;
            Fl_Text_Display* sum;
    };
}

#endif // INCOMEVIEW_H
