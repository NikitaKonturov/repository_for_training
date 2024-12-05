#ifndef LIST_CPP
#define LIST_CPP

#include <iostream>
#include <exception>
#include "List.hpp"


template<typename T>
struct List<T>::Node {
	T item;
	Node* next;
};

template<typename T>
List<T>::List()
{
	root = nullptr;
	size = 0;
}

template<typename T>
List<T>::List(const List<T> &_Source)
{
	root = nullptr;
	size = 0;
	for (size_t i = 0; i < _Source.get_size(); ++i) {
		push_back(_Source[i]);
	}
}

template<typename T>
List<T>::List(const size_t _Size, const T func())
{
	for (size_t i = 0; i < _Size; ++i) {
		push_back(func());
	}
}

template<typename T>
List<T>::List(const size_t _Size, T _Item)
{
	for (size_t i = 0; i < _Size; ++i) {
		push_back(_Item);
	}
}

template<typename T>
List<T>::~List()
{
	for (size_t i = size - 1; i > 0; --i) {
		delete_item(i);
	}
	delete_item(0);
}

template<typename T>
void List<T>::push_back(T _Item) 
{
	if (root == nullptr) {
		root = new Node;
		root->item = _Item;
		root->next = nullptr;
		++size;
	}
	else {
		Node* node = root;
		while (node->next != nullptr) {
			node = node->next;
		}
		node->next = new Node;
		node = node->next;
		node->item = _Item;
		node->next = nullptr;
		++size;
	}
}

template<typename T>
void List<T>::push_front(T _Item)
{
	if (root == nullptr) {
		root = new Node;
		root->item = _Item;
		root->next = nullptr;
		++size;
	}
	else {
		Node* tempNode = root;
		root = new Node;
		root->item = _Item;
		root->next = tempNode;
		++size;
	}
}

template<typename T>
void List<T>::delete_item(size_t _Pos)
{
	if (_Pos >= size) {
		throw std::out_of_range("Going beyond the list...");
	}
	if (root == nullptr || root->next == nullptr) {
		return;
	}
	Node* node = root;
	if (_Pos == 0) {
		Node* tempRoot = root->next;
		delete root;
		root = tempRoot;
		--size;
	}
	else
	{
		for (size_t i = 0; i < _Pos  - 1; ++i) {
			node = node->next;
		}
		Node* tempNode;
		tempNode = node->next->next;
		delete node->next;
		node->next = tempNode;
		--size;
	}
}

template<typename T>
void List<T>::insert(size_t _Pos, T _Item)
{
	if (_Pos >= size) {
		throw std::out_of_range("Going beyond the list...");
	}
	if (_Pos == 0) {
		Node* tempNode = root;
		root = new Node;
		root->item = _Item;
		root->next = tempNode;
		++size;
	}
	else {
		Node* node = root;
		for (size_t i = 0; i < _Pos - 1; ++i) {
			node = node->next;
		}
		Node* tempNode = node->next;
		node->next = new Node;
		node = node->next;
		node->item = _Item;
		node->next = tempNode;
		++size;
	}
}

template<typename T>
void List<T>::merge(const List<T>& _Source, size_t _Pos)
{
	if (_Source.empty()) {
		throw std::logic_error("_Source is empty...");
	}
	if (_Pos > size) {
		throw std::out_of_range("Going beyond the list...");
	}

	if (_Pos == 0) {
		Node* tempNode = root;
		root = new Node;
		Node* node = root;
		for (size_t i = 0; i < _Source.get_size(); ++i) {
			node->item = _Source[i];
			node->next = new Node;
			if (i == _Source.get_size() - 1) {
				break;
			}
			node = node->next;
		}
		node->next = tempNode;
	}
	else {
		Node* tempNode = root;
		Node* node = root;
		for (size_t i = 0; i < _Pos - 1; ++i) {
			node = node->next;
		}
		tempNode = node->next;
		node->next = new Node;
		for (size_t i = 0; i < _Source.get_size(); ++i) {
			node = node->next;
			node->item = _Source[i];
			if (i == _Source.get_size() - 1) {
				break;
			}
			node->next = new Node;
		}
		node->next = tempNode;
	}
	size += _Source.get_size();
}

template<typename T>
void List<T>::revers()
{
	Node* firstNode = root;
	Node* secondNode = root;
	for (size_t i = 0, j = size - 1; i < j; ++i, --j) {
		firstNode = root;
		secondNode = root;
		for (size_t k = 0; k < i; ++k) {
			firstNode = firstNode->next;
		}
		for (size_t k = 0; k < j; ++k) {
			secondNode = secondNode->next;
		}
		T tempItem = firstNode->item;
		firstNode->item = secondNode->item;
		secondNode->item = tempItem;
	}
}

template<typename T>
void List<T>::revers(const void func_to_swap(T& _FirstItem, T& _SecondItem)) 
{
	Node* firstNode = root;
	Node* secondNode = root;
	for (size_t i = 0, j = size - 1; i < j; ++i, --j) {
		firstNode = root;
		secondNode = root;
		for (size_t k = 0; k < i; ++k) {
			firstNode = firstNode->next;
		}
		for (size_t k = 0; k < j; ++k) {
			secondNode = secondNode->next;
		}
		func_to_swap(firstNode->item, secondNode->item);
	}
}

template<typename T>
void List<T>::clear()
{
	for (size_t i = size - 1; i > 0; --i) {
		delete_item(i);
	}
	delete_item(0);
}

template<typename T>
bool List<T>::empty()
{
	return root == nullptr;
}

template<typename T>
void List<T>::print_list()
{
	Node* node = root;
	if (root == nullptr) {
		throw std::logic_error("List is empty...");
	}
	while (node != nullptr) {
		std::cout << node->item << " ";
		node = node->next;
	}
	std::cout << std::endl;
} 

template<typename T>
size_t List<T>::get_size()
{
	return size;
}

template<typename T>
T &List<T>::operator[](size_t _Pos)
{
	if (_Pos >= size) {
		throw std::out_of_range("The element at this position is undefined...");
	}
	Node* node = root;
	for (size_t i = 0; i < _Pos; ++i) {
		node = node->next;
	}
	return node->item;
}

template<typename T>
List<T>& List<T>::operator=(const List<T>& _Source)
{
	this->root = _Source.root;
	this->size = _Source.size;
	return *this;
}

template<typename T>
List<T>& List<T>::operator+(const List<T>& _Source)
{
	this->merge(_Source, size);
	return *this;
}

template<typename T>
bool List<T>::operator==(const List<T>& _Source)
{
	if (size != _Source.get_size()) {
		return false;
	}
	Node* node = root;
	for (size_t i = 0; i < size; ++i) {
		if (node->item != _Source[i]) {
			return false;
		}
		node = node->next;
	}
	return true;
}

template<typename T>
bool List<T>::operator!=(const List<T>& _Source)
{
	return !(*this == _Source);
}

#endif // LIST_CPP
