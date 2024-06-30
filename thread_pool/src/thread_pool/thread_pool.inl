#include "thread_pool.hpp"


/*=============================================================*/
/*===================== Задача для потока =====================*/
/*=============================================================*/

const std::function<void(Thread_Pool::TaskQueue&, 
                         std::map<size_t, std::shared_ptr<Thread_Pool::BaseTask>>&, 
                         std::atomic<bool>&,
                         std::atomic<bool>&
                         )> Thread_Pool::ThreadPool::executeTasks = [](TaskQueue& unfulfilledTasks, 
                                                                        std::map<size_t, std::shared_ptr<BaseTask>>& completedTasks, 
                                                                        std::atomic<bool>& controler,
                                                                        std::atomic<bool>& is_working
                                                                        ) 
{
    while(controler) {    
        is_working = false;
        while (!unfulfilledTasks.empty()) {
            is_working = true;
            unfulfilledTasksMutex.lock();
            std::shared_ptr<BaseTask> executebleTask = unfulfilledTasks.get();
            unfulfilledTasksMutex.unlock();
            executebleTask->start();
            completedTasksMutex.lock();
            completedTasks.insert({executebleTask->getID(), executebleTask});
            completedTasksMutex.unlock();
            is_working = false;
        }
    } 
};


/*=============================================================*/
/*======================= Констркукторы =======================*/
/*=============================================================*/

Thread_Pool::ThreadPool::ThreadPool(size_t threadCount) : threads(threadCount)
{
    threadsStatus.clear();
    threadControllers.clear();
}


Thread_Pool::ThreadPool::~ThreadPool()
{
    this->stop();
}


/*=============================================================*/
/*============== Добавление задачи на выполнение ==============*/
/*=============================================================*/

// Добавление задачи(возвращение ID задачи)
template<typename Result, typename ...TypeArgs>
size_t Thread_Pool::ThreadPool::addTask(const Task<Result, TypeArgs...>& source)
{
    return unfulfilledTasks.put(source);
}


/*=============================================================*/
/*============ Методы для управленя всеми потоками ============*/
/*=============================================================*/

// Запуск всех потоков
void Thread_Pool::ThreadPool::start() 
{
    this->threadsStatus.clear();
    this->threadControllers.clear();
    for (size_t i = 0; i < this->threads.size(); ++i) {
        this->threadsStatus[this->threads[i].get_id()] = false;
        this->threadControllers[this->threads[i].get_id()] = true;
        this->threads[i] = std::thread(std::ref(this->executeTasks), 
                                       std::ref(this->unfulfilledTasks), 
                                       std::ref(this->completedTasks), 
                                       std::ref(this->threadControllers[this->threads[i].get_id()]), 
                                       std::ref(this->threadsStatus[this->threads[i].get_id()]));        
         this->threads[i].detach();
    }
}

// Остановка всех потоков(посылаеться сигнал они заканчивают выполнение уже начатой задачи и больше задачь не берут)
void Thread_Pool::ThreadPool::stop()
{
    bool allStatus = false;
    completedTasksMutex.lock();
    for (auto controller = this->threadControllers.begin(); controller != this->threadControllers.end(); ++controller) {
        (controller->second) = false;
    }
    completedTasksMutex.unlock();
    do {
        allStatus = false;
        for(auto oneStatus = this->threadsStatus.begin(); oneStatus != this->threadsStatus.end(); ++oneStatus) {
            allStatus |= oneStatus->second;
        }
    } while (allStatus);
}

// Остановка одного потока 
void Thread_Pool::ThreadPool::stop(const std::thread::id& sourceID)
{
    auto threadController = this->threadControllers.find(sourceID);
    if(threadController == this->threadControllers.end()) {
        std::cerr << "\033[33m" << "[WARNING] Thread with id: " << sourceID << " was not founded..." << "\033[0m" << std::endl;
        return;
    }

    completedTasksMutex.lock();
    (threadController->second) = false;
    completedTasksMutex.unlock();

    while(this->threadsStatus[sourceID]){}
}


/*=============================================================*/
/*========= Методы для для получения выполненых задач =========*/
/*=============================================================*/

template<typename Result, typename ...TypeArgs>
std::optional<Thread_Pool::Task<Result, TypeArgs...>> Thread_Pool::ThreadPool::getCompletedTask(size_t taskID)
{
    auto foundTaskIter = this->completedTasks.find(taskID);
    if(foundTaskIter == this->completedTasks.end()) {
        return std::nullopt;
    }
    std::shared_ptr<Task<Result, TypeArgs...>> foundTaskPtr = std::dynamic_pointer_cast<Task<Result, TypeArgs...>>(std::move(foundTaskIter->second));
    if(foundTaskPtr == nullptr) {
        return std::nullopt;
    }

    
    return *foundTaskPtr;
}
