#include <iostream>
#include "CircularBuffer.h"

int main() {
	// ������ ����� �����
    CircularBuffer buffer(15);
    // ��������� ������� �� 0 �� 14
    for (int i = 0; i < 15; i++) {
        buffer.pushBack(i);
    }
	
	// ������� ���������� � ������� � �������� ��������
    std::cout << "queue size: " << buffer.getSize() << std::endl;
    std::cout << "queue head: " << buffer.head() << std::endl;
    // ������� �������� ������� � ��������� ����������� �����
    try {
        buffer.pushBack(0);
    } catch (char const* e) {
    	// ����� ���������� � ������� ��������� �� ������
        std::cout << "tried to push into full buffer: " << e << std::endl;
    }

	// ������ �������� �� ������
    CircularBuffer::Iterator iterator = CircularBuffer::Iterator(buffer);
    std::cout << "queue written 3 times using an iterator: " << std::endl;
	// ������� ���������� ������ ��� ����, ����� ��������, ��� ������� �� ����������� ����������
    for (int i = 0; i < 3; i++) {
        iterator.start();
        while (!iterator.finished()) {
            std::cout << iterator.getValue() << " ";
            iterator.next();
		}
        std::cout << std::endl;
    }

	// ������ �������� �������
    std::cout << std::endl << "queue after popping one element: " << std::endl;
    std::cout << "popped: " << buffer.pop() << std::endl;
    // � ������� ������� �� �����
    iterator.start();
    while (!iterator.finished()) {
        std::cout << iterator.getValue() << " ";
        iterator.next();
    }
    // ������� ��� ��������
    std::cout << std::endl << "queue after erasing: " << std::endl;
    buffer.erase();
    // ������� ������ �������
    iterator.start();
    while (!iterator.finished()) {
        std::cout << iterator.getValue() << " ";
        iterator.next();
    }
    // �������� ������� ������� �� ������ �������
    try {
        buffer.pop();
    } catch (char const* e) {
    	// ����� ���������� � ������� ���������� �� ������
        std::cout << "tried to pop from empty queue: " << e << std::endl;
    }

    return 0;
}
