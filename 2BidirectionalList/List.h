#ifndef LIST_H
#define LIST_H
#include "Iterator.h"

template<typename T>
class Node {
public:
	T value;
	Node<T> *next;
	Node<T> *prev;
	Node() : prev(nullptr), next(nullptr) {}
	Node(Node<T> *prev, Node<T> *next, T value) :
		prev(prev), next(next), value(value) {}
	Node(Node<T> *prev, Node<T> *next) :
		prev(prev), next(next) {}
};

template<typename T>
class List {
public:
	virtual void insert(Iterator<T> *iter, T elem) = 0;
	virtual void remove(Iterator<T> *iter) = 0;
	virtual Iterator<T> *find(T elem) = 0;
	virtual void erase() = 0;
	virtual bool isEmpty() = 0;
	virtual size_t length() = 0;
	virtual Iterator<T> *begin() = 0;
	virtual ~List() {};
};
#endif
