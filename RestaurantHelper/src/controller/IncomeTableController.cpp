#include "controller/IncomeTableController.h"

namespace Controller
{
    IncomeTableController::IncomeTableController(std::unique_ptr<Model::IncomeTableModel>&& m)
    {
        model = std::move(m);
    }

    void IncomeTableController::connect(Model::Update_Func_IncomeTable update_func)
    {
        model->connect(update_func);
    }

    std::string IncomeTableController::get_column_header(int col) const
    {
        return model->get_column_header(col);
    }

    std::size_t IncomeTableController::get_column_count() const
    {
        return model->get_column_count();
    }

    std::string IncomeTableController::get_data(int row, int col) const
    {
        return model->get_data(row, col);
    }

    std::size_t IncomeTableController::get_number_of_rows() const
    {
        return model->get_number_of_rows();
    }

    void IncomeTableController::reload_data(bool show_all, std::string date)
    {
        return model->reload_data(show_all, date);
    }

    void IncomeTableController::update()
    {
        model->notify();
    }

    IncomeTableController::~IncomeTableController()
    {
        //dtor
    }
}
