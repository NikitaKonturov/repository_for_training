
#include "../funcs/funcs.hpp"

#include <algorithm>
#include <numeric>
#include <queue>
#include <thread>
#include <chrono>
#include <mutex>
#include <time.h>
#include <atomic>
#include <functional>

template<typename Result, typename ...TypeArgs>
class Task 
{
private:
    Result res;
    std::tuple<TypeArgs...> args;
    std::function<Result(TypeArgs...)> func;

    template<size_t... index>
    Result callFunc(std::index_sequence<index...>) {
        return func(std::get<index>(args)...);
    }

public:
    Task(TypeArgs..., std::function<Result(TypeArgs...)>);
    void start();
    Result getResult() const;
    ~Task() = default;
};

template<typename Result, typename ...TypeArgs>
Task<Result, TypeArgs...>::Task(TypeArgs... sArgs, std::function<Result(TypeArgs...)> sFunc) : res(Result()) 
{
    this->args = std::make_tuple(sArgs...);
    this->func = sFunc;
}

template<typename Result, typename ...TypeArgs>
Result Task<Result, TypeArgs...>::getResult() const
{
    return res;
}

template<typename Result, typename ...TypeArgs>
void Task<Result, TypeArgs...>::start()
{
    this->res = callFunc(std::index_sequence_for<TypeArgs...>{});   
}

int sum(int a, int b) 
{
    return a + b;
}


// template<typename ...Types>
// class ThreadPull
// {
// private:
//     std::queue<std::thread> pull;
//     std::queue<>

// };


int main()
{
    
    Task<int, int, int> test(5,5, sum);
    test.start();

    std::cout << test.getResult() << std::endl;
    return 0;
}
