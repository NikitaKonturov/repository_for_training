#ifndef _LIST_HPP_
#define _LIST_HPP_
#include <iostream>
#include <exception>

template<typename T>
class List {
private:
	struct Node;
	Node* root;
	size_t size;

public:
	List(); // конструктор по умолчанию
	List(const List<T> &_Source); // конструктор копирования
	List(const size_t _Size, const T func()); // конструктор заполнения значениями с внешней функции
	List(const size_t _Size, T _Item); // конструктор заполнения одним значением

	~List(); // деструктор 


	void push_back(T _Item); // добавление эллемента в конец списка
	void push_front(T _Item); // добавление элемента в начало списка
	void delete_item(size_t _Pos); // удаление элемента из списка по индексу
	void insert(size_t _Pos, T _Item); // вставка элемента в спимсо по индексу
	void merge(const List<T>& _Source, size_t _Pos); // вставка списка в другой список
	void print_list(); // вывод списка в косоль
	void revers(); // инвертирование списка 
	void revers(const void func_to_swap(T& _FirstItem, T& _SecondItem)); // инвертирование списка для абстрактных типов
	void clear(); // очистка списка
	bool empty(); // проверка списка на пустоту


	size_t get_size(); // получение размера списка
	T &operator[](size_t _Pos); // оператор индексации списка
	List& operator=(const List<T>& _Source); // оператор создания указателя на один и тот же список
	List& operator+(const List<T>& _Source); // оператор слияния двух списков
	bool operator==(const List<T>& _Source); // оператор сравнивания двух списков
	bool operator!=(const List<T>& _Source); 
};

#endif // LIST_HPP
