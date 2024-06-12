#include "../thread_pool/thread_pool.hpp"
#include "../taskQueue/taskQueue.hpp"
#include "../task/task.hpp"
#include <chrono>

int main()
{
    ThreadPool pool;

    size_t firstTaskID = 0;
    firstTaskID = pool.addTask(Task<int, int, int>(5, 5, [](int first, int second){return first + second;}));
    size_t secondTaskID = pool.addTask(Task<void, std::string>("Hellow world!", [](std::string mes){std::cout << mes << std::endl;}));
    pool.start();

    std::this_thread::sleep_for(std::chrono::seconds(3));

    pool.stop();

    std::cout << pool.getCompletedTask<int, int, int>(firstTaskID)->getResult() << std::endl;

//    std::cout << "Hello world!" << std::endl;
    return 0;
}
