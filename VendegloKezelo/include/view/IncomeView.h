#ifndef INCOMEVIEW_H
#define INCOMEVIEW_H

#include <memory>

#include "persistence/Persistence.h"
#include "view/IncomeTable.h"
#include "model/IncomeModel.h"

namespace View
{
    class IncomeView
    {
        public:
            IncomeView(std::unique_ptr<Model::IncomeModel>&& m, int x, int y, int w, int h);
            ~IncomeView();

        protected:

        private:
            std::unique_ptr<Model::IncomeModel> model;
            IncomeTable* income_table;
    };
}

#endif // INCOMEVIEW_H
