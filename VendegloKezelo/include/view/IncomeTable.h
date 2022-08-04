#ifndef INCOMETABLE_H
#define INCOMETABLE_H

#include <memory>
#include <vector>

#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Table.H>

#include "controller/IncomeTableController.h"
#include "model/IncomeTableModel.h"

namespace View
{
    class IncomeTable : public Fl_Table
    {
        public:
            IncomeTable(std::unique_ptr<Controller::IncomeTableController>&& c, int X, int Y, int W, int H, const char *L=0);
            void DrawHeader(const char *s, int X, int Y, int W, int H);
            void DrawData(const char *s, int X, int Y, int W, int H);
            void draw_cell(TableContext context, int row=0, int col=0, int x=0, int y=0, int w=0, int h=0);
            void draw_everything(bool show_all, std::string date="");
            void update(Model::IncomeTableModel& model);
            virtual ~IncomeTable();

        protected:

        private:
            std::unique_ptr<Controller::IncomeTableController> controller;
            bool initialized = false;

            void initialize();
    };
}

#endif // INCOMETABLE_H
