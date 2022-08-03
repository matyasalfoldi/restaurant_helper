#ifndef SQLITEPERSISTENCE_H
#define SQLITEPERSISTENCE_H

#include <string>
#include <map>

#include <3rdparty/sqlite3.h>

#include "model/IncomeRow.h"
#include "persistence/Persistence.h"

class SqlitePersistence : public Persistence<std::vector<Model::IncomeRow>, int>
{
public:
    SqlitePersistence();
    virtual std::vector<Model::IncomeRow> get(bool today_only=true) override;
    virtual void write(int value, bool new_data=true) override;
    virtual ~SqlitePersistence();

protected:

private:
    sqlite3* db;
    std::vector<Model::IncomeRow> values;

    void write(std::string date);
    static int sqlite_callback(void* p, int count, char** data, char** columns);
};

#endif // SQLITEPERSISTENCE_H
