#ifndef INCOMETABLE_H
#define INCOMETABLE_H

#include <memory>
#include <vector>

#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Table.H>

#include "model/IncomeTableModel.h"
#include "persistence/Persistence.h"

namespace View
{
    class IncomeTable : public Fl_Table
    {
        public:
            IncomeTable(std::unique_ptr<Model::IncomeTableModel>&& m, int X, int Y, int W, int H, const char *L=0)
                :Fl_Table(X,Y,W,H,L)
            {
                model = std::move(m);
                initialize();
            }

            void initialize()
            {
                begin();
                auto num_of_rows = model->get_number_of_rows();
                rows(num_of_rows);
                row_header(1);
                row_height_all(20);
                row_resize(0);

                // Change it later on if more columns will be
                cols(1);
                col_header(1);
                col_width_all(80);
                col_resize(1);
                col_resize_min(50);
                end(); // end the Fl_Table group
            }

            void DrawHeader(const char *s, int X, int Y, int W, int H)
            {
                fl_push_clip(X,Y,W,H);
                fl_draw_box(FL_THIN_UP_BOX, X,Y,W,H, row_header_color());
                fl_color(FL_BLACK);
                fl_draw(s, X,Y,W,H, FL_ALIGN_CENTER);
                fl_pop_clip();
            }

            void DrawData(const char *s, int X, int Y, int W, int H)
            {
                fl_push_clip(X,Y,W,H);

                // Draw cell bg
                fl_color(FL_WHITE);
                fl_rectf(X,Y,W,H);
                // Draw cell data
                fl_color(FL_GRAY0);
                fl_draw(s, X,Y,W,H, FL_ALIGN_CENTER);
                // Draw box border
                fl_color(color());
                fl_rect(X,Y,W,H);

                fl_pop_clip();
            }

            void draw_cell(TableContext context, int row=0, int col=0, int x=0, int y=0, int w=0, int h=0)
            {
                switch ( context ) {
                  case CONTEXT_STARTPAGE:
                    fl_font(FL_HELVETICA, 16);
                    return;
                  case CONTEXT_COL_HEADER:
                    DrawHeader("income", x, y, w, h);
                    return;
                  case CONTEXT_ROW_HEADER:
                    DrawHeader(std::to_string(row).c_str(), x, y, w, h);
                    return;
                  case CONTEXT_CELL:
                    DrawData(std::to_string(model->get_data(row, col)).c_str(), x, y, w, h);
                    return;
                  default:
                    return;
                }
            }

            void draw_everything()
            {
                model->reload_data();
                clear();
                initialize();
            }

            virtual ~IncomeTable();

        protected:

        private:
            std::unique_ptr<Model::IncomeTableModel> model;
    };
}

#endif // INCOMETABLE_H
