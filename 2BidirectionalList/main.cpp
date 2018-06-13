#include <iostream>
#include "List.h"
#include "BidirectionalList.h"

template<typename T>
void print(List<T> *list) {
	Iterator<int> *iter = list->begin();
	iter->start();
	while (!iter->isFinished()) {
		std::cout << iter->getValue() << " ";
		iter->next();
	}
	std::cout << std::endl;
}

int main() {
	List<int> *list = new BidirectionalList<int>();
	Iterator<int> *iter = list->begin();
	for (int i = 0; i < 5; i++) {
		list->insert(iter, i);
	}
	std::cout << "filled list: ";
	print<int>(list);

	iter = list->find(1);
	list->insert(iter, 1);
	std::cout << "insert in list: " << std::endl;
	print<int>(list);
	iter->next();
	for (int i = 0; i < 5; i++) {
		list->insert(iter, i);
		print<int>(list);
		iter->next();
	}

	iter = list->find(2);
	list->remove(iter);
	std::cout << "removed first 2 from list: ";
	print<int>(list);

	list->erase();
	std::cout << "erased list: ";
	print<int>(list);

	std::cout << "insert 1:\n";
	list->insert(iter, 1);
	print<int>(list);

	return 0;
}
