#ifndef THREAD_POOL_HPP
#define THREAD_POOL_HPP
#include<map>
#include<deque>
#include<mutex>
#include<thread>
#include<atomic>
#include<memory>
#include<vector>
#include<optional>
#include<unordered_map>
#include"../taskQueue/taskQueue.hpp"



std::mutex unfulfilledTasksMutex;
std::mutex completedTasksMutex;

class ThreadPool {
private:
    static const std::function<void(TaskQueue&, 
                               std::map<size_t, std::shared_ptr<BaseTask>>&, 
                               std::atomic<bool>&,
                               std::unique_ptr<std::atomic<bool>>&
                               )> executeTasks;
    std::vector<std::thread> threads;
    TaskQueue unfulfilledTasks;
    std::map<size_t, std::shared_ptr<BaseTask>> completedTasks;
    std::unordered_map<std::thread::id, std::unique_ptr<std::atomic<bool>>> threadsStatus;
    std::atomic<bool> controller;
public:
/*==================== Конструкторы ====================*/
    ThreadPool(size_t threadCount = 5);
    ~ThreadPool();

/*========== Добавление задачи на выполнение ===========*/

    //Возвращает ID задачи
    template<typename Result, typename ...TypeArgs>
    size_t addTask(const Task<Result, TypeArgs...>& source);   

/*======== Методы для управления всеми потоками ========*/

// Запуск всех потоков
    void start();

// Остановка всех потоков
    void stop();

/*====== Методы для получения обработанной задачи ======*/

    template<typename Result, typename ...TypeArgs>
    std::optional<Task<Result, TypeArgs...>> getCompletedTask(size_t taskID);
};


#include "thread_pool.inl"

#endif
