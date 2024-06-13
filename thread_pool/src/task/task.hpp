#ifndef TASK_HPP
#define TASK_HPP
#include<mutex>
#include<string>
#include<sstream>
#include<iostream>
#include<optional>
#include<exception>
#include<functional>


namespace Thread_Pool 
{

// Мьютекс для вывода ошибки в поток 
    std::mutex cerrMutex;
    static size_t tempID = 0;
// Преобразование в string
    std::string thread_id_to_string(const std::thread::id& source);

    /*==================================================*/
    /*================ Базовая задача ==================*/
    /*==================================================*/


    class BaseTask
    {
    protected:
        std::optional<std::runtime_error> taskError;
    public:
        BaseTask() = default;
        virtual ~BaseTask() = default;
        virtual size_t getID() const = 0;
        virtual void start() = 0;
        std::optional<std::runtime_error> showError() const;
    };


    /*==================================================*/
    /*================ Основной шаблон =================*/
    /*==================================================*/

    template<typename Result, typename ...TypeArgs>
    class Task : public BaseTask
    {
    private:
        const size_t ID;
        Result res;
        std::tuple<TypeArgs...> args;
        std::function<Result(TypeArgs...)> func;

        template<size_t... index>
        Result callFunc(std::index_sequence<index...>) {
            return func(std::get<index>(args)...);
        }

    public:
    /*======================== Конструкторы ========================*/
        Task(TypeArgs... sArgs, std::function<Result(TypeArgs...)> sFunc);
        Task(const Task<Result, TypeArgs...>& source);
        ~Task() = default;
    /*=========================== Методы ===========================*/
        void start() override;
        Result getResult() const;
        size_t getID() const override;
    };


    /*==================================================*/
    /*============= Специализация для void =============*/
    /*==================================================*/


    template<typename ...TypeArgs>
    class Task<void, TypeArgs...> : public BaseTask
    {
    private:
        const size_t ID;
        std::tuple<TypeArgs...> args;
        std::function<void(TypeArgs...)> func;

        template<size_t... index>
        void callFunc(std::index_sequence<index...>) {
            return func(std::get<index>(args)...);
        }

    public: 
    /*======================= Конструкторы =======================*/
        Task(TypeArgs..., std::function<void(TypeArgs...)>);
        Task(const Task<void, TypeArgs...>& source);
        ~Task() = default;

    /*========================== Методы ==========================*/
        void start();
        size_t getID() const;
    };
}

#include"task.inl"

#endif // TASK_HPP
