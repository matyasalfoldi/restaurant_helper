#include <string>
#include <vector>
#include <memory>

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Tabs.H>

#include "persistence/Persistence.h"
#include "persistence/SqlitePersistence.h"
#include "persistence/TxtPersistence.h"
#include "view/OrderView.h"
#include "view/IncomeView.h"
#include "model/IncomeModel.h"
#include "model/OrderModel.h"

int main (int argc, char ** argv)
{
    std::unique_ptr<Model::IncomeModel> income_model = std::make_unique<Model::IncomeModel>(std::make_shared<SqlitePersistence>());
    std::unique_ptr<Model::OrderModel> order_model =
        std::make_unique<Model::OrderModel>(std::make_unique<TxtPersistence>());
    Fl_Window *window;

    window = new Fl_Window (Fl::w(), Fl::h(), "Restaurant Helper");

    Fl_Tabs* tabs = new Fl_Tabs(0, 0, Fl::w(), Fl::h());
    {
        View::OrderView* order_view =
            new View::OrderView(std::move(order_model),
                0, 100, Fl::w(), Fl::h()-100);
        View::IncomeView* income_view =
            new View::IncomeView(std::move(income_model),
                0, 100, Fl::w(), Fl::h()-100);
    }
    tabs->end();

    window->end ();
    window->show (argc, argv);

    return(Fl::run());
}
