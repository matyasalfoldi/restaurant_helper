#ifndef PERSISTENCE_H
#define PERSISTENCE_H

#include <memory>
#include <string>
#include <vector>

#include "persistence/Criteria.h"

template <typename T, typename U, typename V>
class DataStore
{
    public:
        using Shared_Ptr = std::shared_ptr<DataStore<T, U, V>>;
        using Unique_Ptr = std::shared_ptr<DataStore<T, U, V>>;

        DataStore() = default;
        virtual T get(const Criteria<V>& criteria) = 0;
        virtual std::vector<std::string> get_column_headers() const = 0;
        virtual void write(U, bool new_data=true) = 0;
        virtual ~DataStore() = default;

    protected:

    private:
};

#endif // PERSISTENCE_H
