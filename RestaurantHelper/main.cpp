#include <memory>
#include <string>
#include <vector>

#include <FL/Fl.H>
#include <FL/Fl_Tabs.H>
#include <FL/Fl_Window.H>

#include "controller/IncomeController.h"
#include "controller/OrderController.h"
#include "model/IncomeModel.h"
#include "model/IncomeTableModel.h"
#include "model/OrderModel.h"
#include "persistence/SqlitePersistence.h"
#include "persistence/TxtPersistence.h"
#include "view/IncomeView.h"
#include "view/OrderView.h"

int main (int argc, char** argv)
{
    std::shared_ptr<SqlitePersistence> db_conn = std::make_shared<SqlitePersistence>();
    std::unique_ptr<Model::IncomeModel> income_model = std::make_unique<Model::IncomeModel>(db_conn);
    std::unique_ptr<Model::OrderModel> order_model =
        std::make_unique<Model::OrderModel>(std::make_unique<TxtPersistence>(), db_conn);

    std::unique_ptr<Controller::OrderController> order_controller = std::make_unique<Controller::OrderController>(std::move(order_model));
    std::unique_ptr<Controller::IncomeController> income_controller = std::make_unique<Controller::IncomeController>(std::move(income_model));

    // Based on the comments during destruction it deletes child pointers
    // thus not manually deleting child elements is not a problem
    Fl_Window* window = new Fl_Window (Fl::w()-100, Fl::h()-100, "Restaurant Helper");

    Fl_Tabs* tabs = new Fl_Tabs(0, 0, Fl::w(), Fl::h());
    {
        View::OrderView* order_view =
            new View::OrderView(std::move(order_controller),
                0, 100, Fl::w()-100, Fl::h()-200);

        View::IncomeView* income_view =
            new View::IncomeView(std::move(income_controller),
                0, 100, Fl::w()-100, Fl::h()-200);
    }
    tabs->end();

    window->end ();
    window->show(argc, argv);
    Fl::run();
    delete window;
    return 0;
}
