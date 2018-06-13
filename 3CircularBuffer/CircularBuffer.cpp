#include "CircularBuffer.h"

// Конструктор по максимальному размеру
CircularBuffer::CircularBuffer(const int size) {
    this->size = size;
    this->engaged = 0;
    this->arr = new int[size];
}

// Конструктор копирования
CircularBuffer::CircularBuffer(CircularBuffer &src) {
    this->size = src.size;
    this->engaged = src.engaged;
    this->arr = new int[this->size];
    for (int i = 0; i < this->engaged; i++) {
        this->arr[i] = src.arr[i];
    }
}

// Деструктор
CircularBuffer::~CircularBuffer() {
    this->engaged = 0;
    this->size = 0;
    delete[] this->arr;
}

// Вставка в конец
void CircularBuffer::pushBack(const int elem) {
    if (engaged >= size) {
        throw "There is no place to push";
    }
    // Вставляем на последнее место и прибавляем 1 к количеству элементов
    arr[engaged++] = elem;
}

// Получаем первый элемент без его удаления
int CircularBuffer::head() {
    if (isEmpty()) {
        throw "Queue is empty";
    }
    return arr[0];
}

// Получаем первый элемент с его удалением
int CircularBuffer::pop() {
    int temp = head();
    for (int i = 0; i < engaged - 1; i++) {
    	arr[i] = arr[i + 1];
	}
    --engaged;
    return temp;
}

int CircularBuffer::getSize() {
    return engaged;
}

void CircularBuffer::erase() {
    engaged = 0;
}

bool CircularBuffer::isEmpty() {
    return engaged == 0;
}
