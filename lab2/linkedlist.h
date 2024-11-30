#include <iostream>

#pragma once

struct Node {
	double _data;
	Node* _next;

	Node(double data);
};

class List {
	Node* _tail { nullptr };

public:
	List() = default;
	List(const List& other);
	List(size_t size);
	~List();

	List& operator=(const List& other);

	void push_tail();
	void push_head();

	void pop_head();
	void pop_tail();

	void delete_node(double data);

	Node* get(size_t idx);
	void insert(size_t idx, double data);
};


//Node:
Node::Node(double data) : _data(data), _next(nullptr) {}

//List:
List::List(const List& other) {

}
List::List(size_t size) {

}
List::~List() {

}

List& List::operator=(const List& other) {

}

void List::pop_head() {
	if (!_tail) return;

	if (_tail->_next == _tail) {
		delete _tail;
		_tail = nullptr;
		return;
	}

	_tail->_next = _tail->_next->_next;
	delete _tail->_next;
}

void List::pop_tail() {
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