#ifndef ORDERVIEW_H
#define ORDERVIEW_H

#include <memory>
#include <string>
#include <vector>

#include <FL/Fl.H>
#include <FL/Fl_ask.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Multiline_Output.H>
#include <FL/Fl_Input_Choice.H>
#include <FL/Fl_Int_Input.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Group.H>

#include "model/Order.h"
#include "model/OrderModel.h"

namespace View
{
    class OrderView
    {
        public:
            OrderView(std::unique_ptr<Model::OrderModel>&& m, int x, int y, int w, int h);
            ~OrderView();

        protected:

        private:
            std::unique_ptr<Model::OrderModel> model;
    };
}

#endif // ORDERVIEW_H
