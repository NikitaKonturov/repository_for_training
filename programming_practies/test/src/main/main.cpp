
#include "../funcs/funcs.hpp"

template<size_t num, size_t degree>
struct Pow {
    static const size_t res = Pow<num, degree - 1>::res * num;
};

template<size_t num>
struct Pow<num, 0> {
    static const size_t res = 1;
};


int main()
{
    Pow<7, 20> test;
    std::cout << test.res << std::endl;
    return 0;
}
