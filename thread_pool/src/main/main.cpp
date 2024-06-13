#include "../thread_pool/thread_pool.hpp"
#include "../taskQueue/taskQueue.hpp"
#include "../task/task.hpp"
#include <chrono>

int main()
{
    try {
        Thread_Pool::ThreadPool pool;

        size_t firstTaskID = 0;
        firstTaskID = pool.addTask(Thread_Pool::Task<int, int, int>(5, 0, [](int first, int second){
            throw std::exception();
            return first + second;}));
        size_t secondTaskID = pool.addTask(Thread_Pool::Task<void, std::string>("Hellow world!", [](std::string mes){std::cout << mes << std::endl;}));
        pool.start();

        pool.stop();

        std::cout << pool.getCompletedTask<int, int, int>(firstTaskID)->getResult() << std::endl;
  
    }
    catch(std::exception &err) {
        std::cerr << "\033[31m" << "[FATAL]" << err.what() << "\033[0m" << std::endl;
    }
    return 0;
}
