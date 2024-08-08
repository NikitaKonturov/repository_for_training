
#ifndef THREE_HPP
#define THREE_HPP
#include<iostream>

template<typename T>
struct Node {
    Node(Node* = nullptr, Node* = nullptr, Node* = nullptr);
    // Полезная нагрузка
    T value;
    // Указател  на правого потомка 
    Node<T>* right;
    // Указатель на левого потомка
    Node<T>* left;
    // Указатель на родителя[у корня всего дерева он nullptr]
    Node<T>* parent;
};


template<typename T>
class Three
{
private:
    Node<T>* root;
    /*============== Обходы дерева ==============*/

    // Прямой обход
    void directBypass(std::ostream&, Node<T>*);
    // Центральный обход
    void centralBypass(void (Node<T>*), Node<T>*);
    // Обратный обход
    void reverseBypass(void (Node<T>*), Node<T>*);
    // Поиск
    Node<T>* find(T, Node<T>*);
    // Вставка
    Node<T>* insert(T, Node<T>*);
public:
/*nj============== Конструктоы ==============*/
// По умолчанию
    Three();
// Деструктор 
    ~Three();

/*============== Методы ==============*/
    // Удаление эллемента
    bool deleteItem(T);
    // Поиск
    bool find(T);
    // Обёртка для вставки
    bool insert(T);

/*============= Операторы =============*/

void print();


};

#include"Three.inl";


#endif //FUNCS_HPP
