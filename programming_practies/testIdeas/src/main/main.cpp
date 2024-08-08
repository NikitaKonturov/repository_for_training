
#include "../class/class.hpp"
#include<deque>
#include<queue>
#include<list>
#include<thread>
#include<locale>
#include<chrono>
#include<regex>
#include<iostream>
#include<spdlog/spdlog.h>
#include<algorithm>
#include"../class/class.hpp"






int main() {

    Base* first = new Item<int>(5);

    TypeContainer test;
    test.add<Item<int>>();



    return 0;
}
