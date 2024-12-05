#ifndef TASKQUEUE_HPP
#define TASKQUEUE_HPP
#include <queue>
#include <memory>
#include <algorithm>
#include <functional>
#include "../task/task.hpp"


namespace Thread_Pool 
{
    class TaskQueue 
    {
    private:
        std::queue<std::shared_ptr<BaseTask>> tasks;
    public:

    /*============== Конструкторы ==============*/

        TaskQueue() = default;
        ~TaskQueue() = default;

    /*================= Сетеры =================*/

        // Добавление задачи
        template<typename Result, typename ...TypeArgs>
        size_t put(const Task<Result, TypeArgs...>& sourceTask);

    /*================= Гетеры =================*/
        
        // Получение задачи 
        std::shared_ptr<BaseTask> get();
        // Получение размера
        size_t size() const;
        // Проверка на пустоту
        bool empty() const;
    };
}

#include "taskQueue.inl"

#endif // TASKLIST_HPP
