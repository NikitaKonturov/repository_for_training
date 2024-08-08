#include "class.hpp"


template <typename T>
Item<T>::Item(T info) : data(info)
{}

template <typename T>
Item<T>::Item(const Item<T> &source) : data(source.data)
{}

template <typename T>
T Item<T>::getData() const
{
    return this->data;
}

template <typename T>
void TypeContainer::add(Item<T> value)
{
    this->data.insert();   
}
