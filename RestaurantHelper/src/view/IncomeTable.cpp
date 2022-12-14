#include "view/IncomeTable.h"

namespace View
{
    IncomeTable::IncomeTable(std::unique_ptr<Controller::IncomeTableController>&& c, int X, int Y, int W, int H, const char *L)
        :Fl_Table(X,Y,W,H,L)
    {
        controller = std::move(c);
        initialize();
        controller->connect([&](Model::IncomeTableModel& mo)
        {
            update(mo);
        });
        //controller->update();
    }

    void IncomeTable::initialize()
    {
        begin();
        auto num_of_rows = controller->get_number_of_rows();
        rows(num_of_rows);
        row_header(1);
        row_height_all(20);
        row_resize(0);

        auto num_of_cols = controller->get_column_count();
        cols(num_of_cols);
        col_header(1);
        col_width_all(100);
        col_resize(1);
        col_resize_min(100);
        end(); // end the Fl_Table group
    }

    void IncomeTable::DrawHeader(const char *s, int X, int Y, int W, int H)
    {
        fl_push_clip(X,Y,W,H);
        fl_draw_box(FL_THIN_UP_BOX, X,Y,W,H, row_header_color());
        fl_color(FL_BLACK);
        fl_draw(s, X,Y,W,H, FL_ALIGN_CENTER);
        fl_pop_clip();
    }

    void IncomeTable::DrawData(const char *s, int X, int Y, int W, int H)
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

    void IncomeTable::draw_cell(TableContext context, int row, int col, int x, int y, int w, int h)
    {
        switch ( context ) {
          case CONTEXT_STARTPAGE:
            fl_font(FL_HELVETICA, 16);
            return;
          case CONTEXT_COL_HEADER:
            DrawHeader(controller->get_column_header(col).c_str(), x, y, w, h);
            return;
          case CONTEXT_ROW_HEADER:
            DrawHeader(std::to_string(row).c_str(), x, y, w, h);
            return;
          case CONTEXT_CELL:
            DrawData(controller->get_data(row, col).c_str(), x, y, w, h);
            return;
          default:
            return;
        }
    }

    void IncomeTable::draw_everything(bool show_all, std::string date)
    {
        controller->reload_data(show_all, date);
        clear();
        initialize();
    }

    void IncomeTable::update(Model::IncomeTableModel& model)
    {
        clear();
        initialize();
    }

    IncomeTable::~IncomeTable()
    {
        //dtor
    }
}
