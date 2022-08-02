#include "persistence/SqlitePersistence.h"

#include <cstring>
#include <string>

int sqlite_callback(void* p, int count, char** data, char** columns)
{
    SqlitePersistence* persistence = static_cast<SqlitePersistence*>(p);
    for(int i=0; i < count; ++i)
    {
        if(strcmp(columns[i], "amount") == 0 && data[i])
        {
            persistence->write(std::stoi(data[i]), false);
        }
    }
    return 0;
}

SqlitePersistence::SqlitePersistence()
{
    sqlite3_open("income.db", &db);
    sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS income(amount INT);", nullptr, NULL, NULL);
    //sqlite3_exec(db, "INSERT INTO income(amount) VALUES(1000), (2500), (1250);", nullptr, NULL, NULL);
}

std::vector<int> SqlitePersistence::get()
{
    values.clear();
    sqlite3_exec(db, "SELECT amount FROM income;", sqlite_callback, this, NULL);
    return values;
}

void SqlitePersistence::write(int value, bool new_data)
{
    values.push_back(value);
    if(new_data)
    {
        std::string command = "INSERT INTO income(amount) VALUES("+std::to_string(value)+");";
        sqlite3_exec(db, command.c_str(), nullptr, NULL, NULL);
    }
}

SqlitePersistence::~SqlitePersistence()
{
    sqlite3_close(db);
}
