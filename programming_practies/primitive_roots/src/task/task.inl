#include "task.hpp"


/*=============================================================*/
/*======================= Констркукторы =======================*/
/*=============================================================*/


template<typename Result, typename ...TypeArgs>
inline Thread_Pool::Task<Result, TypeArgs...>::Task(TypeArgs... sArgs, std::function<Result(TypeArgs...)> sFunc) : ID(++tempID),
                                                                                                            res(Result()), 
                                                                                                            func(sFunc)
{                                                                                                           
    this->args = std::make_tuple(sArgs...);
}

template<typename Result, typename ...TypeArgs>
inline Thread_Pool::Task<Result, TypeArgs...>::Task(const Thread_Pool::Task<Result, TypeArgs...>& source) : args(source.args),
                                                                                                     func(source.func),
                                                                                                     res(source.res), 
                                                                                                     ID(source.ID)
{
    taskError = source.taskError;

}

template<typename ...TypeArgs>
inline Thread_Pool::Task<void, TypeArgs...>::Task(TypeArgs... sArgs, std::function<void(TypeArgs...)> sFunc) : ID(++tempID),
                                                                                                        func(sFunc)
{
    this->args = std::make_tuple(sArgs...);
}

template<typename ...TypeArgs>
inline Thread_Pool::Task<void,TypeArgs...>::Task(const Thread_Pool::Task<void, TypeArgs...>& source) : args(source.args),
                                                                                                func(source.func),
                                                                                                ID(source.ID)
{
    taskError = source.taskError;
}


/*=============================================================*/
/*==================== Получение резуьтата ====================*/
/*=============================================================*/

template<typename Result, typename ...TypeArgs>
inline Result Thread_Pool::Task<Result, TypeArgs...>::getResult() const
{
    if(this->showError().has_value()) {
        throw *this->showError();
    } 

    if (!res) { 
        throw std::runtime_error("Result is not set.");
    }

    return res;
}


/*=============================================================*/
/*======================= Запуск фукции =======================*/
/*=============================================================*/

template<typename Result, typename ...TypeArgs>
inline void Thread_Pool::Task<Result, TypeArgs...>::start() 
{
    try {
        this->res = callFunc(std::index_sequence_for<TypeArgs...>{});   
        this->taskError = std::nullopt;
    }
    catch(std::exception& err) {
        std::string errorMessage = "Thread error: ";
        errorMessage += std::string(err.what()) + " [Thread id: " + thread_id_to_string(std::this_thread::get_id()) + "; Task id: " + std::to_string(this->ID) + "]";
        
        std::lock_guard<std::mutex> outError(cerrMutex);
        {
            std::cerr << "\033[0m" << "\033[33m"<< "[WARNING]" << errorMessage << "\033[0m" << std::endl;
        }
        this->taskError.emplace(errorMessage);
    }
}

template<typename ...TypeArgs>
inline void Thread_Pool::Task<void, TypeArgs...>::start()
{
    try {
        std::cout << "Starting task ID: " << std::this_thread::get_id() << std::endl;
        callFunc(std::index_sequence_for<TypeArgs...>{});
        this->taskError = std::nullopt;
        std::cout << "Completed task ID: " << std::this_thread::get_id() << std::endl; 
    }
    catch(std::exception& err) {
        std::string errorMessage = err.what();
        errorMessage += " [Thread id: " + thread_id_to_string(std::this_thread::get_id()) + "; Task id: " + std::to_string(this->ID) + "]";
        std::lock_guard<std::mutex> outError(cerrMutex);
        std::cerr << "\\033[31m" << errorMessage << "\\033[0m" << std::endl;
        this->taskError.emplace(errorMessage);
    }
}


/*=============================================================*/
/*======================= Получение ID ========================*/
/*=============================================================*/

template<typename Result, typename ...TypeArgs>
inline size_t Thread_Pool::Task<Result, TypeArgs...>::getID() const
{
    return this->ID;
}

template<typename ...TypeArgs>
inline size_t Thread_Pool::Task<void, TypeArgs...>::getID() const
{
    return this->ID;
}


/*=============================================================*/
/*===================== Получение Ошибки ======================*/
/*=============================================================*/

inline std::optional<std::runtime_error> Thread_Pool::BaseTask::showError() const
{
    return this->taskError;
}


/*=============================================================*/
/*================= Конвертер для thread::id ==================*/
/*=============================================================*/

inline std::string Thread_Pool::thread_id_to_string(const std::thread::id& source) 
{
    std::ostringstream idStream;    
    idStream << source;
    
    return idStream.str();
}