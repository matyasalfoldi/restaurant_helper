#ifndef INCOMETABLE_H
#define INCOMETABLE_H

#include <memory>
#include <vector>

#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Table.H>

#include "model/IncomeTableModel.h"
#include "persistence/DataStore.h"

namespace View
{
    class IncomeTable : public Fl_Table
    {
        public:
            IncomeTable(std::unique_ptr<Model::IncomeTableModel>&& m, int X, int Y, int W, int H, const char *L=0);
            void initialize();
            void DrawHeader(const char *s, int X, int Y, int W, int H);
            void DrawData(const char *s, int X, int Y, int W, int H);
            void draw_cell(TableContext context, int row=0, int col=0, int x=0, int y=0, int w=0, int h=0);
            void draw_everything(bool show_all, std::string date="");
            virtual ~IncomeTable();

        protected:

        private:
            std::unique_ptr<Model::IncomeTableModel> model;
    };
}

#endif // INCOMETABLE_H
