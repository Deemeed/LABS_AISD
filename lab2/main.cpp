#include <iostream>

#include "linkedlist.h"

int main(void) {
	List<int> first;
	List<int> second;

	first.push_tail(1);
	first.push_tail(3);
	first.push_tail(5);

	second.push_tail(2);
	second.push_tail(4);
	second.push_tail(5);
	second.push_tail(6);
	second.push_tail(8);

	std::cout << "First list: " << first;
	std::cout << "Second list: " << second;

	List<int> result(sorted_union(first, second));
	std::cout << "Union result: " << result;

	return 0;
}