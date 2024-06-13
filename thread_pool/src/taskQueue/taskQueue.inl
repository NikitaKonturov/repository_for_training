#include"taskQueue.hpp"


/*==================================================*/
/*===================== Сетеры =====================*/
/*==================================================*/

// Добавление задачи в очередь 
template<typename Result, typename ...TypeArgs>
size_t Thread_Pool::TaskQueue::put(const Task<Result, TypeArgs...>& sourceTask)
{   
    std::shared_ptr<Thread_Pool::BaseTask> sourceBaseTask = std::make_shared<Task<Result, TypeArgs...>>(sourceTask);
    this->tasks.push(sourceBaseTask);
    return sourceBaseTask->getID();
}   


/*==================================================*/
/*===================== Гетеры =====================*/
/*==================================================*/

// Получение задачи из очереди
std::shared_ptr<Thread_Pool::BaseTask> Thread_Pool::TaskQueue::get()
{
    std::shared_ptr<BaseTask> result = this->tasks.front();
    this->tasks.pop();
    return result;
}

// Получение размера
size_t Thread_Pool::TaskQueue::size() const
{
    return this->tasks.size();
}

// Проверка на пустоту
bool Thread_Pool::TaskQueue::empty() const
{
    return this->tasks.empty();
}
