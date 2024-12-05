#include "funcs.hpp"


using namespace Thread_Pool;

size_t LCD(size_t first, size_t second) 
{
    while (first > 0 && second > 0) {
        if(second > first) {
            second %= first;
        }
        else {
            first %= second;
        }
    }
    
    return first | second;
}


size_t EulerFunction(size_t number)
{

    std::function<size_t(size_t, size_t, size_t)> calcuteEulerFunckForRange ([](size_t first, size_t second, size_t controlNumber) {
        size_t countMutuallyPrime = 0;
        for(;first <= second; ++first) {
            if(LCD(first, second) == 1) {
                ++countMutuallyPrime;
            }            
        }
        return countMutuallyPrime;
    });

    ThreadPool pool(10);

    size_t tempNumber = 0;


    std::queue<size_t> ids;

    while(number - tempNumber >= 100) {
        ids.push(pool.addTask(Task<size_t, size_t, size_t, size_t>(tempNumber + 1, tempNumber += 100, number, calcuteEulerFunckForRange)));
    }

    if(number - tempNumber < 0) {
        ids.push(pool.addTask(Task<size_t, size_t, size_t, size_t>(tempNumber + 1, number, number, calcuteEulerFunckForRange)));
    }

    pool.start();

    while(!pool.unfulfilledTasksEmty()) {}

    pool.stop();

    size_t result = 0;

    while (!ids.empty())
    {
        result += (pool.getCompletedTask<size_t, size_t, size_t, size_t>(ids.front())->getResult());
        ids.pop();
    }
    
    return result;
}
