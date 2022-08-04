#ifndef INCOMECONTROLLER_H
#define INCOMECONTROLLER_H

#include <memory>

#include <FL/Fl.H>
#include <FL/Fl_Widget.H>

#include "model/IncomeModel.h"
#include "model/IncomeRow.h"

namespace Controller
{
    class IncomeController
    {
        public:
            IncomeController(std::unique_ptr<Model::IncomeModel>&& m);
            void connect(Model::Update_Func_Income update_func)
            {
                model->connect(update_func);
            }
            std::shared_ptr<DataStore<std::vector<Model::IncomeRow>, int>> get_persistence()
            {
                return model->get_persistence();
            }
            int get_sum() const
            {
                return model->get_sum();
            }
            void set_date(std::string date)
            {
                model->set_date(date);
            }
            void set_show_all(bool show_all)
            {
                model->set_show_all(show_all);
            }
            void update();
            ~IncomeController();

            // Callbacks
            static void reload_table_callback(Fl_Widget* w, void* callback_store);
            static void show_all_callback(Fl_Widget* w, void* callback_store);
        protected:

        private:
            std::unique_ptr<Model::IncomeModel> model;
    };
}

#endif // INCOMECONTROLLER_H
