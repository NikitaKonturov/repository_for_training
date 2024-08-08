
#ifndef DOUBLE_LINKED_LIST_HPP
#define DOUBLE_LINKED_LIST_HPP
#include<iostream>


template<typename T>
class double_linked_list
{
private:
    struct Node;
    Node* first;
    Node* last;
    size_t size;
public:
    double_linked_list();
    double_linked_list(const double_linked_list<T>& );
    double_linked_list(size_t, T);

    ~double_linked_list();
    
	void push_back(T); // добавление эллемента в конец списка
	void push_front(T); // добавление элемента в начало списка
	void delete_item(size_t); // удаление элемента из списка по индексу
	void insert(size_t, T); // вставка элемента в спимсо по индексу
	void merge(const List<T>&, size_t); // вставка списка в другой список
	void print_list(); // вывод списка в косоль
	void revers(); // инвертирование списка 
	void revers(const void func_to_swap(T&, T&)); // инвертирование списка для абстрактных типов
	void clear(); // очистка списка
	bool empty(); // проверка списка на пустоту


	size_t get_size(); // получение размера списка
	T &operator[](size_t); // оператор индексации списка
	List& operator=(const List<T>&); // оператор приравнивания
	List& operator+(const List<T>&); // оператор слияния двух списков
	bool operator==(const List<T>&); // оператор сравнивания двух списков
	bool operator!=(const List<T>&); 
};


#endif // DOUBLE_LINKED_LIST_HPP
