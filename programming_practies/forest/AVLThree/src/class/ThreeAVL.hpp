
#ifndef THREEAVL_HPP
#define THREEAVL_HPP
#include<iostream>

template<typename T>
struct Node {
    Node(Node* = nullptr, size_t = 0, Node* = nullptr, Node* = nullptr);
    // Полезная нагрузка
    T value;
    size_t height;
    // Указател  на правого потомка 
    Node<T>* right;
    // Указатель на левого потомка
    Node<T>* left;
    // Указатель на родителя[у корня всего дерева он nullptr]
    Node<T>* parent;
};


template<typename T>
class ThreeAVL {
private:
    /*============== Обходы дерева ==============*/

    // Прямой обход
    void directBypass(std::ostream&, Node<T>*);
    // Центральный обход
    void centralBypass(void (Node<T>*), Node<T>*);
    // Обратный обход
    void reverseBypass(void (Node<T>*), Node<T>*);
    // Метод балансировки
    Node<T>* balanceNode(Node<T>*);
    // Метод получению высоты узла
    int64_t height(Node<T>*);
    // Метод вычисления balace factor
    int64_t balanceFactor(Node<T>*);
    // Методы востановления высот
    void fixHeight(Node<T>*);
    // Метод вращения в право
    Node<T>* rotateToRight(Node<T>*);
    // Метод вращения в лево
    Node<T>* rotateToLeft(Node<T>*); 

    static Node<T>* root;
public:

/*nj============== Конструктоы ==============*/
// По умолчанию
    ThreeAVL();
// Деструктор 
    ~ThreeAVL();

/*============== Методы ==============*/
    // Вставка
    
    Node<T>* insert(T, Node<T>* = root, Node<T>* = nullptr);
    // Удаление эллемента
    Node<T>* deleteItem(T, Node<T>* = root);
    // Поиск
    Node<T>* find(T, Node<T>* = root);


/*============= Операторы =============*/

void print();


};

#include"ThreeAVL.inl";


#endif 
