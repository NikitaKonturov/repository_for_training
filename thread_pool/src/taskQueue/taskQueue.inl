#include"taskQueue.hpp"


/*==================================================*/
/*===================== Сетеры =====================*/
/*==================================================*/

// Добавление задачи в очередь 
template<typename Result, typename ...TypeArgs>
size_t TaskQueue::put(const Task<Result, TypeArgs...>& sourceTask)
{   
    std::shared_ptr<BaseTask> sourceBaseTask = std::make_shared<Task<Result, TypeArgs...>>(sourceTask);
    this->tasks.push(sourceBaseTask);
    return sourceBaseTask->getID();
}   


/*==================================================*/
/*===================== Гетеры =====================*/
/*==================================================*/

// Получение задачи из очереди
std::shared_ptr<BaseTask> TaskQueue::get()
{
    std::shared_ptr<BaseTask> result = this->tasks.front();
    this->tasks.pop();
    return result;
}

// Получение размера
size_t TaskQueue::size() const
{
    return this->tasks.size();
}

// Проверка на пустоту
bool TaskQueue::empty() const
{
    return this->tasks.empty();
}
