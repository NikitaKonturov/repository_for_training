#include <fstream>
#include <vector>
#include <iostream>
#include <functional>
#include <cmath>
#include <sstream>
#include<iterator>
#include <set>


class Base 
{
public:
    Base() = default;
    virtual void print() const = 0;
    ~Base() = default;
};


class Child : public Base
{
protected:
    int a;
    std::string mes;
public:
    Child() 
    {}
    void print() const override
    {
        std::cout << "Hellow world!!!" << std::endl;
    }
};





union Test
    {
        int a;
        double d;
        char c;
    };

typedef void(*FuncPointer)();

int main()
{
    
    Base* s = new Child();
    
    FuncPointer* vtable = *reinterpret_cast<FuncPointer**>(s);

    vtable[0]();

    Test test;

    test.a = 5;

    std::cout << test.a <<  std::endl;


    test.c = 'D';

    std::cout << test.c << std::endl;


    std::vector<int> v1 {1, 2, 3, 3, 4, 4, 3, 5, 6, 0};

    std::set<int> s1(v1.begin(), v1.end());    

    std::sort(v1.begin(), v1.end(), std::function<bool(const int&, const int&)>([](const int& f, const int& s){return s > f;}));

    std::copy(v1.begin(), v1.end(), std::ostream_iterator<int>(std::cout, " "));
   
    


    std::istringstream is("12 32 434 534");
    

    std::vector<int> v3 {std::istream_iterator<int>(is), std::istream_iterator<int>()};

    std::cout << std::endl;

    std::copy(v3.begin(), v3.end(), std::ostream_iterator<int>(std::cout, " "));







    std::vector<int> v2;

   // std::transform(v1.begin(), v1.end(), s1.begin(), std::function<int(const int&)>([](const int& f){return (int)std::pow(f, 2);}));






    // for(int i : s1) {
    //     std::cout << i << " "; 
    // }


    return 0;
}
