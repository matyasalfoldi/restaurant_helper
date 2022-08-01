#ifndef SQLITEPERSISTENCE_H
#define SQLITEPERSISTENCE_H

#include <string>
#include <map>

#include <3rdparty/sqlite3.h>

#include "persistence/Persistence.h"

class SqlitePersistence : public Persistence<std::vector<int>, int>
{
public:
    SqlitePersistence();
    virtual std::vector<int> get() override;
    virtual void write(int value, bool new_data=true) override;
    virtual ~SqlitePersistence();

protected:

private:
    sqlite3* db;
    std::vector<int> values;
};

#endif // SQLITEPERSISTENCE_H
