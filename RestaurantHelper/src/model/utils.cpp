#include "model/utils.h"

namespace Model
{
    std::function<bool(const std::string&, const IncomeRow&)> date_comparer =
        [](const std::string& date, const IncomeRow& income_row)
        {
            std::stringstream input_date(date);
            std::string input_val;
            std::stringstream pred_date(income_row.date);
            std::string pred_val;
            auto remove_leading_zeros =
                [](std::string& input_val)
                {
                    input_val.erase(
                        input_val.begin(),
                        std::find_if(
                            input_val.begin(),
                            input_val.end(),
                            [](unsigned char ch)
                            {
                                return ch != '0';
                            }
                        )
                    );
                };
            auto get_date_part =
                [&]()
                {
                    std::getline(input_date, input_val, '-');
                    // Remove leading 0-s
                    remove_leading_zeros(input_val);
                    std::getline(pred_date, pred_val, '-');
                    remove_leading_zeros(pred_val);
                };
            //Compare year
            get_date_part();
            if(input_val != pred_val)
            {
                return false;
            }
            //Compare month
            get_date_part();
            if(input_val != pred_val)
            {
                return false;
            }
            //Compare day
            get_date_part();
            if(input_val != pred_val)
            {
                return false;
            }
            return true;
        };

    std::string get_current_date()
    {
        std::time_t time = std::time(nullptr);
        std::tm* const time_info = std::localtime(&time);
        std::string date = std::to_string(1900+time_info->tm_year) + "-" +
               std::to_string(1+time_info->tm_mon) + "-" +
               std::to_string(time_info->tm_mday);
        delete time_info;
        return date;
    }
}
