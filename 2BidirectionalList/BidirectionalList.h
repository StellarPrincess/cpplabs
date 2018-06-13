#ifndef BIDIRECTIONAL_LIST_H
#define BIDIRECTIONAL_LIST_H

#include <type_traits>
#include "List.h"

// ��������� �����, ����������� �� ������������ List
template<typename T>
class BidirectionalList : public List<T> {
private:
	// ��������, ���� ���������, ����������� �� ������������ Iterator
	template<typename TI>
	class ListIterator : public Iterator<T> {
		// ����� ������ ���� ������ � private ����� ���������
		friend class BidirectionalList<TI>;
	private:
		// ��������� �� �������� ������� ������
		Node<TI>* buffer;
		// ��������� �� ������� �������
		Node<TI>* p;
		// ����������� ���������, ����� ������ ���� ������� �������� ����� ���� ������ ������� begin() ������
		explicit ListIterator(Node<TI>* p) : buffer(p), p(p->next) {}
		// �������� ��������� �� ������� �������
		Node<TI>* getNode() {
			return p;
		}
	public:
		// �������� �������� � ������
		void start() override {
			p = buffer->next;
		}
		// �������� �������� ��������
		T getValue() override {
			if (p == buffer) {
				throw "can't get value from buffer";
			}
			return p->value;
		}
		// ����������� �������� �� ������� �����
		void next() override {
			// ���� ��������� �������, �������� ��� � ������
			if (p == nullptr) {
				p = buffer->next;
			}
			p = p->next;
		}
		// �������� �� �� ��������������
		bool isFinished() override {
			return p == buffer;
		}
	};
	// �������� �������
	Node<T> *buffer;
	// ������ ������
	size_t size;
	typedef ListIterator<T> iterator;
public:
	BidirectionalList();
	~BidirectionalList();
	void insert(Iterator<T> *it, T elem);
	void remove(Iterator<T> *it);
	Iterator<T> *find(T elem);
	void erase();
	bool isEmpty();
	size_t length();
	Iterator<T> *begin();
};

// ����������� �� ���������
template<typename T>
BidirectionalList<T>::BidirectionalList() {
	// ������ ������ �������� �������
	buffer = new Node<T>();
	buffer->next = buffer;
	buffer->prev = buffer;
	size = 0;
}

// ����������
template<typename T>
inline BidirectionalList<T>::~BidirectionalList()
{
	// �������� ����� �������
	erase();
	// ������� �������� �������
	delete buffer;
}

// �������� ������� ����� ����������
template<typename T>
void BidirectionalList<T>::insert(Iterator<T> *pos, T value) {
	// ����� �������� ������ � ����� p � buffer � ������ getNode() ��������� ������
	iterator* tPos = static_cast<iterator*>(pos);
	// ���� ������ ������ = 0, ���������� ��������� ��������� �� �����
	if (size == 0) {
		tPos->p = tPos->buffer;
	}
	// �������� �������, �� ������� ��������� ��������
	Node<T> *current = tPos->getNode();
	// ������ ����� �������
	Node<T> *ins = new Node<T>(current->prev, current, value);
	// ������������� ���������
	ins->prev->next = ins;
	ins->next->prev = ins;
	++size;
}

// ������� �������, �� ������� ��������� ��������
template<typename T>
void BidirectionalList<T>::remove(Iterator<T> *pos) {
	iterator* tPos = static_cast<iterator*>(pos);
	Node<T> *current = tPos->getNode();
	if (current == buffer) {
		throw "Can't remove buffer element.";
	}
	// ������������� ��������� � ����� �������� ��������
	current->prev->next = current->next;
	current->next->prev = current->prev;
	--size;
	// ������� ������
	delete current;
}

// ����� ������� �������� � ��������� ���������
template<typename T>
Iterator<T>* BidirectionalList<T>::find(T value) {
	// � ������� ���������
	iterator *iter = static_cast<iterator*>(begin());
	iter->start();
	while (!iter->isFinished()) {
		if (iter->getValue() == value) {
			return iter;
		}
		iter->next();
	}
	return nullptr;
}

// ������� ������
template<typename T>
void BidirectionalList<T>::erase() {
	// ��������������� ���������
	Node<T> *curr = buffer->next;
	// ���� �� ������ ��, ����� ������
	while (curr != buffer) {
		// ���������� ��������� �������
		Node<T> *temp = curr->next;
		// ������� �������
		delete curr;
		// �������� ���������
		curr = temp;
	}
	// ������������� ��������� ������ �� ��� �����
	buffer->next = buffer;
	buffer->prev = buffer;
	// �������� ������
	size = 0;
}

// �������� �� �������
template<typename T>
bool BidirectionalList<T>::isEmpty() {
	return size == 0;
}

// �������� ������ ������
template<typename T>
size_t BidirectionalList<T>::length() {
	return size;
}

// �������� �������� �� ������ �������
template<typename T>
Iterator<T> *BidirectionalList<T>::begin() {
	return new ListIterator<T>(this->buffer);
}

#endif //BIDIRECTIONAL_LIST_H
