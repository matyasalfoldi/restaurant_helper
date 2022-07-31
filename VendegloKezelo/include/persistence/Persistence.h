#ifndef PERSISTENCE_H
#define PERSISTENCE_H

#include <vector>

template <typename T, typename U>
class Persistence
{
    public:
        Persistence() = default;
        virtual std::vector<T> get() = 0;
        virtual void write(U, bool new_data=true) = 0;
        virtual ~Persistence() = default;

    protected:

    private:
};

#endif // PERSISTENCE_H
