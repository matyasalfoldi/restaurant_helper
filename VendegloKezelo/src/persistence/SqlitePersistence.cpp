#include "persistence/SqlitePersistence.h"

#include <algorithm>
#include <cstring>
#include <string>

int SqlitePersistence::sqlite_callback(void* p, int count, char** data, char** columns)
{
    SqlitePersistence* persistence = static_cast<SqlitePersistence*>(p);
    for(int i=0; i < count; ++i)
    {
        persistence->write_headers(columns[i]);
        if(strcmp(columns[i], "Amount") == 0 && data[i])
        {
            persistence->write(std::stoi(data[i]), false);
        }
        else if(strcmp(columns[i], "OrderDate") == 0 && data[i])
        {
            persistence->write(data[i]);
        }
    }
    return 0;
}

void SqlitePersistence::write(std::string date)
{
    values[values.size()-1].date = date;
}

void SqlitePersistence::write_headers(std::string header)
{
    if(std::find(headers.begin(), headers.end(), header) == headers.end())
    {
        headers.push_back(header);
    }
}

SqlitePersistence::SqlitePersistence()
{
    sqlite3_open("income.db", &db);
    sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS incomes(Amount INT, OrderDate TEXT);", nullptr, NULL, NULL);
    // Test data
    /*sqlite3_exec(db, "INSERT INTO incomes(Amount, OrderDate) VALUES(1000, date());", nullptr, NULL, NULL);
    sqlite3_exec(db, "INSERT INTO incomes(Amount, OrderDate) VALUES(1300, date('now','-1 day'));", nullptr, NULL, NULL);
    sqlite3_exec(db, "INSERT INTO incomes(Amount, OrderDate) VALUES(1500, date());", nullptr, NULL, NULL);*/
}

std::vector<Model::IncomeRow> SqlitePersistence::get(bool today_only, std::string date)
{
    values.clear();
    std::string stmt = "SELECT Amount, OrderDate FROM incomes";
    if(!date.empty())
    {
        stmt += " WHERE OrderDate = date('"+date+"')";
    }
    else if(today_only)
    {
        stmt += " WHERE OrderDate = date()";
    }

    stmt += ";";
    sqlite3_exec(db, stmt.c_str(), sqlite_callback, this, NULL);
    return values;
}

std::vector<std::string> SqlitePersistence::get_column_headers() const
{
    return headers;
}

void SqlitePersistence::write(int value, bool new_data)
{
    Model::IncomeRow order_row();
    values.push_back(value);
    if(new_data)
    {
        std::string command = "INSERT INTO incomes(Amount, OrderDate) VALUES("+std::to_string(value)+", date());";
        sqlite3_exec(db, command.c_str(), nullptr, NULL, NULL);
    }
}

SqlitePersistence::~SqlitePersistence()
{
    sqlite3_close(db);
}
