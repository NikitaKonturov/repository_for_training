#include "thread_pool.hpp"


/*=============================================================*/
/*===================== Задача для потока =====================*/
/*=============================================================*/

const std::function<void(TaskQueue&, 
                         std::map<size_t, std::shared_ptr<BaseTask>>&, 
                         std::atomic<bool>&,
                         std::unique_ptr<std::atomic<bool>>&
                         )> ThreadPool::executeTasks = [](TaskQueue& unfulfilledTasks, 
                                                                        std::map<size_t, std::shared_ptr<BaseTask>>& completedTasks, 
                                                                        std::atomic<bool>& controler,
                                                                        std::unique_ptr<std::atomic<bool>>& is_working
                                                                        ) 
{
    while(controler) {    
        *is_working = false;
        while (!unfulfilledTasks.empty()) {
            *is_working = true;
            std::lock_guard<std::mutex> getTask(unfulfilledTasksMutex);
            std::shared_ptr<BaseTask> executebleTask = unfulfilledTasks.get();
            executebleTask->start();
            std::lock_guard<std::mutex> putTask(completedTasksMutex);
            completedTasks.insert({executebleTask->getID(), executebleTask});
            *is_working = false;
        }
    }
};


/*=============================================================*/
/*======================= Констркукторы =======================*/
/*=============================================================*/

ThreadPool::ThreadPool(size_t threadCount) : threads(threadCount)
{}


ThreadPool::~ThreadPool()
{
    this->stop();
}


/*=============================================================*/
/*============== Добавление задачи на выполнение ==============*/
/*=============================================================*/

// Добавление задачи(возвращение ID задачи)
template<typename Result, typename ...TypeArgs>
size_t ThreadPool::addTask(const Task<Result, TypeArgs...>& source)
{
    return unfulfilledTasks.put(source);
}


/*=============================================================*/
/*============ Методы для управленя всеми потоками ============*/
/*=============================================================*/

// Запуск всех потоков
void ThreadPool::start()
{
    this->threadsStatus.clear();
    this->controller = true;
    for (size_t i = 0; i < this->threads.size(); ++i) {
        this->threadsStatus[threads[i].get_id()] = std::make_unique<std::atomic<bool>>(false);
        this->threads[i] = std::thread(std::ref(this->executeTasks), 
                                       std::ref(this->unfulfilledTasks), 
                                       std::ref(this->completedTasks), 
                                       std::ref(this->controller), 
                                       std::ref(this->threadsStatus[this->threads[i].get_id()]));        
        this->threads[i].detach();
    }
}

// Остановка всех потоков(посылаеться сигнал они заканчивают выполнение уже начатой задачи и больше задачь не берут)
void ThreadPool::stop()
{
    this->controller = false;
    bool allStatus = false;
    do {
        allStatus = false;
        for(auto oneStatus = this->threadsStatus.begin(); oneStatus != this->threadsStatus.end(); ++oneStatus) {
            allStatus |= *oneStatus->second;
        }
    } while (allStatus);
}


/*=============================================================*/
/*========= Методы для для получения выполненых задачь ========*/
/*=============================================================*/

template<typename Result, typename ...TypeArgs>
std::optional<Task<Result, TypeArgs...>> ThreadPool::getCompletedTask(size_t taskID)
{
    auto foundTaskIter = this->completedTasks.find(taskID);
    if(foundTaskIter == this->completedTasks.end()) {
        return std::nullopt;
    }
    std::shared_ptr<Task<Result, TypeArgs...>> foundTaskPtr = std::dynamic_pointer_cast<Task<Result, TypeArgs...>>((foundTaskIter->second));
    if(foundTaskPtr == nullptr) {
        return std::nullopt;
    }

    return *foundTaskPtr;
}
