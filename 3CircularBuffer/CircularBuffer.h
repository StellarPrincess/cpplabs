#ifndef CIRCULARBUFFER_CIRCULARBUFFER_H
#define CIRCULARBUFFER_CIRCULARBUFFER_H

class CircularBuffer {
	friend class Iterator;
private:
	// Массив
    int *arr;
    // Размер
    int size;
    // Количество элементов
    int engaged;
public:
	class Iterator {
	private:
		// Позиция итератора
	    int pos;
	    // Указатель на итерируемый буфер
	    CircularBuffer *buffer;
	public:
		// Конструктор: позиция на ноль, указатель указывает на передаваемый по ссылке буфер
	    explicit Iterator(CircularBuffer & buf) : pos(0), buffer(&buf) {}
	    // Деструктор пустой, т.к. удалять нечего
	    virtual ~Iterator() {}
	    // Устанавливаем итератор на начало
	    void start() {
		    pos = 0;
		}
		// Сдвигаем позицию вперёд
	    void next() {
		    ++pos;
		}
		// Проверка на конец: если позиция вышла за пределы массива - конец
	    bool finished() {
		    return pos == buffer->engaged;
		}
	    int getValue() {
	    	// Нельзя брать из места за пределами массива
	    	if (pos == buffer->engaged) {
	    		throw "Can't get from outside of engaged";
			}
		    return buffer->arr[pos];
		}
	};
    explicit CircularBuffer(int);
    explicit CircularBuffer(CircularBuffer&);
    virtual ~CircularBuffer();
    void pushBack(int);
    int pop();
    int head();
    int getSize();
    void erase();
    bool isEmpty();
};


#endif //CIRCULARBUFFER_CIRCULARBUFFER_H
