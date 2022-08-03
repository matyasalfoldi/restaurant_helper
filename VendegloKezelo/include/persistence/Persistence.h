#ifndef PERSISTENCE_H
#define PERSISTENCE_H

#include <string>
#include <vector>

template <typename T, typename U>
class Persistence
{
    public:
        Persistence() = default;
        virtual T get(bool today_only=true, std::string date="") = 0;
        virtual void write(U, bool new_data=true) = 0;
        virtual ~Persistence() = default;

    protected:

    private:
};

#endif // PERSISTENCE_H
