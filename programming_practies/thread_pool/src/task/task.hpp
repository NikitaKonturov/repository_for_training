#ifndef TASK_HPP
#define TASK_HPP
#include<iostream>
#include<functional>


/*==================================================*/
/*================ Базовая задача ==================*/
/*==================================================*/

class BaseTask
{
public:
    BaseTask() = default;
    virtual ~BaseTask() = default;
    virtual size_t getID() const = 0;
    virtual void start() = 0;
};


/*==================================================*/
/*================ Основной шаблон =================*/
/*==================================================*/

template<typename Result, typename ...TypeArgs>
class Task : public BaseTask
{
private:
    size_t ID;
    static size_t tempID;
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
    size_t ID;
    static size_t tempID;
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


#include"task.inl"

#endif // TASK_HPP
