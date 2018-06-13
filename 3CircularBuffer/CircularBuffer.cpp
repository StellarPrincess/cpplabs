#include "CircularBuffer.h"

// ����������� �� ������������� �������
CircularBuffer::CircularBuffer(const int size) {
    this->size = size;
    this->engaged = 0;
    this->arr = new int[size];
}

// ����������� �����������
CircularBuffer::CircularBuffer(CircularBuffer &src) {
    this->size = src.size;
    this->engaged = src.engaged;
    this->arr = new int[this->size];
    for (int i = 0; i < this->engaged; i++) {
        this->arr[i] = src.arr[i];
    }
}

// ����������
CircularBuffer::~CircularBuffer() {
    this->engaged = 0;
    this->size = 0;
    delete[] this->arr;
}

// ������� � �����
void CircularBuffer::pushBack(const int elem) {
    if (engaged >= size) {
        throw "There is no place to push";
    }
    // ��������� �� ��������� ����� � ���������� 1 � ���������� ���������
    arr[engaged++] = elem;
}

// �������� ������ ������� ��� ��� ��������
int CircularBuffer::head() {
    if (isEmpty()) {
        throw "Queue is empty";
    }
    return arr[0];
}

// �������� ������ ������� � ��� ���������
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
