#ifndef PERSISTENCE_H
#define PERSISTENCE_H

#include <string>
#include <vector>

template <typename T, typename U>
class DataStore
{
    public:
        DataStore() = default;
        virtual T get(bool today_only=true, std::string date="") = 0;
        virtual std::vector<std::string> get_column_headers() const = 0;
        virtual void write(U, bool new_data=true) = 0;
        virtual ~DataStore() = default;

    protected:

    private:
};

#endif // PERSISTENCE_H
