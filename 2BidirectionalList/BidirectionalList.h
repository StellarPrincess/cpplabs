#ifndef BIDIRECTIONAL_LIST_H
#define BIDIRECTIONAL_LIST_H

#include <type_traits>
#include "List.h"

// Шаблонный класс, наследуется от абстрактного List
template<typename T>
class BidirectionalList : public List<T> {
private:
	// Итератор, тоже шаблонный, наследуется от абстрактного Iterator
	template<typename TI>
	class ListIterator : public Iterator<T> {
		// Чтобы список имел доступ к private полям итератора
		friend class BidirectionalList<TI>;
	private:
		// Указатель на буферный элемент списка
		Node<TI>* buffer;
		// Указатель на текущий элемент
		Node<TI>* p;
		// Конструктор приватный, чтобы нельзя было создать итератор можно было только методом begin() списка
		explicit ListIterator(Node<TI>* p) : buffer(p), p(p->next) {}
		// Получить указатель на текущий элемент
		Node<TI>* getNode() {
			return p;
		}
	public:
		// Сбросить итератор в начало
		void start() override {
			p = buffer->next;
		}
		// Получить значение элемента
		T getValue() override {
			if (p == buffer) {
				throw "can't get value from buffer";
			}
			return p->value;
		}
		// Передвинуть итератор на элемент вперёд
		void next() override {
			// Если указатель нулевой, сбросить его в начало
			if (p == nullptr) {
				p = buffer->next;
			}
			p = p->next;
		}
		// Проверка всё ли проитерировано
		bool isFinished() override {
			return p == buffer;
		}
	};
	// Буферный элемент
	Node<T> *buffer;
	// Размер списка
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

// Конструктор по умолчанию
template<typename T>
BidirectionalList<T>::BidirectionalList() {
	// Создаём только буферный элемент
	buffer = new Node<T>();
	buffer->next = buffer;
	buffer->prev = buffer;
	size = 0;
}

// Деструктор
template<typename T>
inline BidirectionalList<T>::~BidirectionalList()
{
	// Вызываем метод очистки
	erase();
	// Удаляем буферный элемент
	delete buffer;
}

// Вставить элемент перед итератором
template<typename T>
void BidirectionalList<T>::insert(Iterator<T> *pos, T value) {
	// Чтобы получить доступ к полям p и buffer и методу getNode() итератора списка
	iterator* tPos = static_cast<iterator*>(pos);
	// Если размер списка = 0, сбрасываем указатель итератора на буфер
	if (size == 0) {
		tPos->p = tPos->buffer;
	}
	// Получаем элемент, на который указывает итератор
	Node<T> *current = tPos->getNode();
	// Создаём новый элемент
	Node<T> *ins = new Node<T>(current->prev, current, value);
	// Перебрасываем указатели
	ins->prev->next = ins;
	ins->next->prev = ins;
	++size;
}

// Удалить элемент, на который указывает итератор
template<typename T>
void BidirectionalList<T>::remove(Iterator<T> *pos) {
	iterator* tPos = static_cast<iterator*>(pos);
	Node<T> *current = tPos->getNode();
	if (current == buffer) {
		throw "Can't remove buffer element.";
	}
	// Перебрасываем указатели в обход текущего элемента
	current->prev->next = current->next;
	current->next->prev = current->prev;
	--size;
	// Очищаем память
	delete current;
}

// Поиск первого элемента с указанным значением
template<typename T>
Iterator<T>* BidirectionalList<T>::find(T value) {
	// С помощью итератора
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

// Очистка списка
template<typename T>
void BidirectionalList<T>::erase() {
	// Вспомогательный указатель
	Node<T> *curr = buffer->next;
	// Пока не обошли всё, кроме буфера
	while (curr != buffer) {
		// Запоминаем следующий элемент
		Node<T> *temp = curr->next;
		// Удаляем текущий
		delete curr;
		// Сдвигаем указатель
		curr = temp;
	}
	// Устанавливаем указатели буфера на сам буфер
	buffer->next = buffer;
	buffer->prev = buffer;
	// Обнуляем размер
	size = 0;
}

// Проверка на пустоту
template<typename T>
bool BidirectionalList<T>::isEmpty() {
	return size == 0;
}

// Получить размер списка
template<typename T>
size_t BidirectionalList<T>::length() {
	return size;
}

// Получить итератор на первый элемент
template<typename T>
Iterator<T> *BidirectionalList<T>::begin() {
	return new ListIterator<T>(this->buffer);
}

#endif //BIDIRECTIONAL_LIST_H
