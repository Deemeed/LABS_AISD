#include <iostream>
#include <stdexcept>
#include <random>

#pragma once

template<typename T>
struct Node {
	T _data;
	Node* _next;

	Node(T data);
};

template<typename T>
class List {
	Node* _tail { nullptr };

public:
	List() = default;
	List(const List& other);
	List(size_t size);
	~List();

	List& operator=(const List& other);

	void push_tail(T data);
	void push_tail(const List& other);
	void push_head(T data);
	void push_head(const List& other);

	void pop_head();
	void pop_tail();

	void delete_node(T data);

	Node* get(size_t idx);
	void insert(size_t idx, T data);

	void print();
};


//Node:
template<typename T>
Node<T>::Node(T data) : _data(data), _next(nullptr) {}

//List:
template<typename T>
List<T>::List(const List<T>& other) : _tail(nullptr) {
	if (!other._tail) return;

	Node* tmp = other._tail->_next;
	do {
		push_tail(tmp->_data);
		tmp = tmp->_next;
	} while (tmp != other._tail->_next);
}
template<typename T>
List<T>::List(size_t size) : _tail(nullptr) {
	for (size_t i = 0; i < size; ++i) {
		push_tail(value);
	}
}
template<typename T>
List<T>::~List() {
	if (!_tail) return;

	while (_tail->_next != _tail) {
		pop_head();
	}

	delete _tail;
	_tail = nullptr;
}

template<typename T>
List<T>& List<T>::operator=(const List<T>& other) {
	if (*this == other) return *this;
	if (!other._tail) return *this;

	while (_tail->_next != _tail) {
		pop_head();
	}

	delete _tail;
	_tail = nullptr;

	Node* tmp = other._tail->_next;
	do {
		push_tail(tmp->_data);
		tmp = tmp->_next;
	} while (tmp != other._tail->_next);

	return *this;
}

template<typename T>
void List<T>::push_tail(T data) {
	Node<T>* node = new Node<T>(data);
	if (!_tail) {
		_tail = node;
		_tail->_next = _tail;
	}

	node->_next = _tail->_next;
	_tail->_next = node;
	_tail = node;
}
template<typename T>
void List<T>::push_tail(const List<T>& other) {
	if (!other._tail) return;

	if (!_tail) {
		*this = other;
		return;
	}

	Node<T>* otherHead = other._tail->_next;
	Node<T>* otherTail = other._tail;

	otherTail->_next = _tail->_next;
	_tail->_next = otherHead;
	_tail = otherTail;
}

template<typename T>
void List<T>::push_head(T data) {
	Node<T>* node = new Node<T>(data);
	if (!_tail) {
		_tail = node;
		_tail->_next = _tail;
	}

	node->_next = _tail->_next;
	_tail->_next = node;
}
template<typename T>
void List<T>::push_head(const List<T>& other) {
	if (!other._tail) return;

	if (!_tail) {
		*this = other;
		return;
	}

	Node<T>* otherHead = other._tail->_next;
	Node<T>* otherTail = other._tail;

	otherTail->_next = _tail->_next;
	_tail->_next = otherHead;
}

template<typename T>
void List<T>::pop_head() {
	if (!_tail) return;

	if (_tail->_next == _tail) {
		delete _tail;
		_tail = nullptr;
		return;
	}

	_tail->_next = _tail->_next->_next;
	delete _tail->_next;
}
template<typename T>
void List<T>::pop_tail() {
	if (!_tail) return;

	if (_tail->_next == _tail) {
		delete _tail;
		_tail = nullptr;
		return;
	}

	Node* current = _tail->_next;
	while (current->_next != _tail) {
		current = current->_next;
	}

	current->_next = _tail->_next;
	delete _tail;
	_tail = current;
}

template<typename T>
void List<T>::delete_node(T data) {

}

template<typename T>
void List<T>::print() {
	if (!_tail) {
		std::cout << "List is empty." << std::endl;
		return;
	}

	Node<T>* current = _tail->_next;
	do {
		std::cout << current->_data << " ";
		current = current->_next;
	} while (current != _tail->_next);

	std::cout << std::endl;
}