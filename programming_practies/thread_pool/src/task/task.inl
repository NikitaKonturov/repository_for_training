#include "task.hpp"


template<typename Resualt, typename ...TypeArgs>
size_t Task<Resualt, TypeArgs...>::tempID = 0;

template<typename ...TypeArgs>
size_t Task<void, TypeArgs...>::tempID = 0;

/*=============================================================*/
/*======================= Констркукторы =======================*/
/*=============================================================*/


template<typename Result, typename ...TypeArgs>
Task<Result, TypeArgs...>::Task(TypeArgs... sArgs, std::function<Result(TypeArgs...)> sFunc) : res(Result()), ID(++(this->tempID))
{
    this->args = std::make_tuple(sArgs...);
    this->func = sFunc;
}

template<typename Result, typename ...TypeArgs>
Task<Result, TypeArgs...>::Task(const Task<Result, TypeArgs...>& source) : res(source.res), 
                                                                           args(source.args),
                                                                           func(source.func),
                                                                           ID(source.ID)
{}

template<typename ...TypeArgs>
Task<void, TypeArgs...>::Task(TypeArgs... sArgs, std::function<void(TypeArgs...)> sFunc) : ID(++(this->tempID))
{
    this->args = std::make_tuple(sArgs...);
    this->func = sFunc;
}

template<typename ...TypeArgs>
Task<void,TypeArgs...>::Task(const Task<void, TypeArgs...>& source) : args(source.args),
                                                                      func(source.func),
                                                                      ID(source.ID)
{}


/*=============================================================*/
/*==================== Получение резуьтата ====================*/
/*=============================================================*/

template<typename Result, typename ...TypeArgs>
Result Task<Result, TypeArgs...>::getResult() const
{
    return res;
}


/*=============================================================*/
/*======================= Запуск фукции =======================*/
/*=============================================================*/

template<typename Result, typename ...TypeArgs>
void Task<Result, TypeArgs...>::start() 
{
    this->res = callFunc(std::index_sequence_for<TypeArgs...>{});   
}

template<typename ...TypeArgs>
void Task<void, TypeArgs...>::start()
{
    callFunc(std::index_sequence_for<TypeArgs...>{});
}


/*=============================================================*/
/*======================= Получение ID ========================*/
/*=============================================================*/

template<typename Result, typename ...TypeArgs>
size_t Task<Result, TypeArgs...>::getID() const
{
    return this->ID;
}

template<typename ...TypeArgs>
size_t Task<void, TypeArgs...>::getID() const
{
    return this->ID;
}
