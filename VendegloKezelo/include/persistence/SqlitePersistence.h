#ifndef SQLITEPERSISTENCE_H
#define SQLITEPERSISTENCE_H

#include <3rdparty/sqlite3.h>

#include "model/IncomeRow.h"
#include "persistence/DataStore.h"

class SqlitePersistence : public DataStore<std::vector<Model::IncomeRow>, int>
{
public:
    SqlitePersistence();
    virtual std::vector<Model::IncomeRow> get(bool today_only=true, std::string date="") override;
    virtual void write(int value, bool new_data=true) override;
    virtual std::vector<std::string> get_column_headers() const override;
    virtual ~SqlitePersistence();

protected:

private:
    sqlite3* db;
    std::vector<Model::IncomeRow> values;
    std::vector<std::string> headers;

    void write(std::string date);
    void write_headers(std::string header);
    static int sqlite_callback(void* p, int count, char** data, char** columns);
};

#endif // SQLITEPERSISTENCE_H
