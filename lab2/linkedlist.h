#include <iostream>
#include <stdexcept>
#include <random>

#pragma once

template<typename T>
struct Node {
	T _data;
	Node<T>* _next;

	Node(T data);
};

template<typename T>
class List {
	Node<T>* _tail { nullptr };

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

	size_t size() const {
		if (!_tail) return 0;

		size_t size = 0;
		Node<T>* current = _tail->_next;
		do {
			++size;
			current = current->_next;
		} while (current != _tail->_next);

		return size;
	}

	T& operator[](size_t idx);
	const T& operator[](size_t idx) const;

	friend std::ostream& operator<<(std::ostream& stream, const List& list) {
		for (size_t i = 0; i < list.size(); ++i) {
			stream << list[i] << " ";
		}
		stream << "\n";

		return stream;
	}
};


//Node:
template<typename T>
Node<T>::Node(T data) : _data(data), _next(nullptr) {}

//List:
template<typename T>
List<T>::List(const List<T>& other) : _tail(nullptr) {
	if (!other._tail) return;

	Node<T>* node = other._tail->_next;
	do {
		push_tail(node->_data);
		node = node->_next;
	} while (node != other._tail->_next);
}
template<typename T>
List<T>::List(size_t size) : _tail(nullptr) {
	std::random_device rd;
	std::mt19937 gen(rd());

	for (size_t i = 0; i < size; ++i) {
		int value;
		value = std::uniform_int_distribution<>(0, 127)(gen);
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
	if (this == &other) return *this;
	if (!other._tail) return *this;

	while (_tail && _tail->_next != _tail) {
		pop_head();
	}
	if (_tail) {
		delete _tail;
		_tail = nullptr;
	}

	Node<T>* current = other._tail->_next;
	do {
		push_tail(current->_data);
		current = current->_next;
	} while (current != other._tail->_next);

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

	Node<T>* current = _tail->_next;
	while (current->_next != _tail) {
		current = current->_next;
	}

	current->_next = _tail->_next;
	delete _tail;
	_tail = current;
}

template<typename T>
void List<T>::delete_node(T data) {
	if (!_tail) return;

	Node* current = _tail->_next;
	Node* prev = _tail;

	bool modified = false;

	do {
		if (current->_data == data) {
			Node* toDelete = current;
			prev->_next = current->_next;

			if (current == _tail) {
				_tail = (current == current->_next) ? nullptr : prev;
			}

			current = prev->_next;
			delete toDelete;
			modified = true;
		}
		else {
			prev = current;
			current = current->_next;
		}
	} while (modified ? current != _tail : current != _tail->_next);

	if (_tail && _tail->_data == data) {
		Node* toDelete = _tail;
		if (_tail == _tail->_next) {
			_tail = nullptr;
		}
		else {
			prev->_next = _tail->_next;
			_tail = prev;
		}
		delete toDelete;
	}
}

template<typename T>
T& List<T>::operator[](size_t idx) {
	size_t size = this->size();
	if (idx >= size) {
		throw std::out_of_range("Index out of range!");
	}

	Node<T>* current = _tail->_next;
	for (size_t i = 0; i < idx; ++i) {
		current = current->_next;
	}

	return current->_data;
}
template<typename T>
const T& List<T>::operator[](size_t idx) const {
	size_t size = this->size();
	if (idx >= size) {
		throw std::out_of_range("Index out of range!");
	}

	Node<T>* current = _tail->_next;
	for (size_t i = 0; i < idx; ++i) {
		current = current->_next;
	}

	return current->_data;
}

template<typename T>
List<T> sorted_union(const List<T>& first, const List<T>& second) {
	List<T> result;
	size_t size1 = 0;
	size_t size2 = 0;

	if (first.size() == 0) {
		result = second;
		return result;
	}
	if (second.size() == 0) {
		result = first;
		return result;
	}

	do {
		if (first[size1] == second[size2]) {
			result.push_tail(first[size1]);
			++size1;
			++size2;
		}
		else if (first[size1] > second[size2]) {
			result.push_tail(second[size2]);
			++size2;
		}
		else {
			result.push_tail(first[size1]);
			++size1;
		}
		std::cout << result;
	} while (size1 < first.size() && size2 < second.size());

	while (size1 < first.size()) {
		result.push_tail(first[size1]);
		++size1;
		std::cout << result;
	}

	while (size2 < second.size()) {
		result.push_tail(second[size2]);
		++size2;
		std::cout << result;
	}

	return result;
}