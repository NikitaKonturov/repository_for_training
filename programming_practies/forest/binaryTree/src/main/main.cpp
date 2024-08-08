
#include "../class/Three.hpp"


int main()
{
    Three<int> obj;
    obj.insert(5);
    obj.insert(2);
    obj.insert(8);
    obj.insert(0);
    obj.insert(4);
    obj.insert(6);
    obj.insert(9);
    obj.insert(1);
    obj.insert(3);
    obj.insert(7);
    obj.insert(10);
    obj.deleteItem(10);
    obj.print();
    std::cout << std::endl << obj.find(1) << std::endl;
    return 0;
}
