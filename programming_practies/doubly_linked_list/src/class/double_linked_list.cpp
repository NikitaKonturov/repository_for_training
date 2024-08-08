
#include "double_linked_list.hpp"


template<typename T>
struct double_linked_list<T>::Node 
{
    T value;
    Node* next;
    Node* previous;
};

template<typename T>
double_linked_list<T>::double_linked_list()
{   
    this->first = nullptr;
    this->last = nullptr;
    size = 0;
}

template<typename T>
double_linked_list<T>::double_linked_list(size_t _Size, T _Value)
{
    this->size = _Size;
    this->first = new Node();
    Node* iter = first;
    iter->next = _Value;
    for (size_t i = 0; i < _Size; ++i) {
        iter->next = new Node;
        iter->next->previous = iter;
        iter = iter->next;
        iter->value = _Value;
    }
    this->last = iter;
}

template<typename T>
double_linked_list<T>::double_linked_list(const double_linked_list<T>& _Source)
{
    this->size = _Source.size;
    this->first = new Node();
    Node* iter = first;
    iter->next = _Value;
    for (size_t i = 0; i < _Source.size; ++i) {
        iter->next = new Node;
        iter->next->previous = iter;
        iter = iter->next;
        iter->value = Source[i];
    }
    this->last = iter;    
}

template<typename T>
double_linked_list<T>::~double_linked_list()
{
    Node* iter = this->last;
    while(iter != this->first) {
        iter = iter->previous
        delete (iter->next)
    }
    delete iter;
}

template<typename T>
T &double_linked_list<T>::operator[](size_t i)
{
    if(i >= size) {
        throw std::out_of_range();
    }
    Node* iter = this->first;
    for (size_t j = 0; j < i; ++j) {
        
    }
    


}
