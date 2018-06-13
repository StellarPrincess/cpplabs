#include <iostream>
#include "CircularBuffer.h"

int main() {
	// Создаём новый буфер
    CircularBuffer buffer(15);
    // Заполняем числами от 0 до 14
    for (int i = 0; i < 15; i++) {
        buffer.pushBack(i);
    }
	
	// Выводим информацию о размере и головном элементе
    std::cout << "queue size: " << buffer.getSize() << std::endl;
    std::cout << "queue head: " << buffer.head() << std::endl;
    // Пробуем добавить элемент в полностью заполненный буфер
    try {
        buffer.pushBack(0);
    } catch (char const* e) {
    	// Ловим исключение и выводим сообщение об ошибке
        std::cout << "tried to push into full buffer: " << e << std::endl;
    }

	// Создаём итератор по буферу
    CircularBuffer::Iterator iterator = CircularBuffer::Iterator(buffer);
    std::cout << "queue written 3 times using an iterator: " << std::endl;
	// Выводим содержимое буфера три раза, чтобы показать, что очередь не разрушается итератором
    for (int i = 0; i < 3; i++) {
        iterator.start();
        while (!iterator.finished()) {
            std::cout << iterator.getValue() << " ";
            iterator.next();
		}
        std::cout << std::endl;
    }

	// Достаём головной элемент
    std::cout << std::endl << "queue after popping one element: " << std::endl;
    std::cout << "popped: " << buffer.pop() << std::endl;
    // И выводим очередь на экран
    iterator.start();
    while (!iterator.finished()) {
        std::cout << iterator.getValue() << " ";
        iterator.next();
    }
    // Стираем все элементы
    std::cout << std::endl << "queue after erasing: " << std::endl;
    buffer.erase();
    // Выводим пустую очередь
    iterator.start();
    while (!iterator.finished()) {
        std::cout << iterator.getValue() << " ";
        iterator.next();
    }
    // Пытаемся удалить элемент из пустой очереди
    try {
        buffer.pop();
    } catch (char const* e) {
    	// Ловим исключение и выводим информацию об ошибке
        std::cout << "tried to pop from empty queue: " << e << std::endl;
    }

    return 0;
}
