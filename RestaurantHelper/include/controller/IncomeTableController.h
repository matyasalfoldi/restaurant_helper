#ifndef INCOMETABLECONTROLLER_H
#define INCOMETABLECONTROLLER_H

#include <memory>
#include <string>

#include <FL/Fl.H>
#include <FL/Fl_Widget.H>

#include "model/IncomeTableModel.h"

namespace Controller
{
    class IncomeTableController
    {
        public:
            IncomeTableController(std::unique_ptr<Model::IncomeTableModel>&& m);
            void connect(Model::Update_Func_IncomeTable update_func);
            std::string get_column_header(int col) const;
            std::size_t get_column_count() const;
            std::string get_data(int row, int col) const;
            std::size_t get_number_of_rows() const;
            void reload_data(bool show_all, std::string date);
            void update();
            ~IncomeTableController();

        protected:

        private:
            std::unique_ptr<Model::IncomeTableModel> model;
    };
}

#endif // INCOMETABLECONTROLLER_H
