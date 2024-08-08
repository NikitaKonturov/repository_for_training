#ifndef CLASS_HPP
#define CLASS_HPP
#include<map>
#include<iostream>
#include<typeindex>
#include<functional>
#include<unordered_map>


class Base 
{
public:
    Base* next;

    Base() : next(nullptr) {}
    virtual ~Base() = default;
    virtual std::type_index getType() const = 0;
};


template<typename T>
class Item : public Base
{
public:
    T data;
    Item(T info);
    Item(const Item<T>& source);
    ~Item() = default;
    std::type_index getType() const override;
    T getData() const;
};


class TypeContainer
{
private:
    std::multimap<std::type_index, std::shared_ptr<Base>> data;
public:
    TypeContainer() = default;
    TypeContainer(const TypeContainer& source) = default;
    ~TypeContainer() = default;

    template<typename T>
    void add(Item<T> value);

    template<typename T>
    Item<T>* get();
};


#include "class.inl"

#endif //CLASS_HPP
