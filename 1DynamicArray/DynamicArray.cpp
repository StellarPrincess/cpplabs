#include "DynamicArray.h"

// Конструктор по умолчанию
DynamicArray::DynamicArray():
		capacity(100),
		size(100),
		arr(new int[100])
{
	for (int i = 0; i < size; i++) {
		arr[i] = 0;
	}
}
// Конструктор по размеру
DynamicArray::DynamicArray(int size):
		capacity(size),
		size(size),
		arr(new int[size])
{
	for (int i = 0; i < size; i++) {
		arr[i] = 0;
	}
}
// Конструктор по размеру и значению элемента
DynamicArray::DynamicArray(int size, int n):
		capacity(size),
		size(size),
		arr(new int[size])
{
	for (int i = 0; i < size; i++) {
		arr[i] = n;
	}
}
// Конструктор по размеру, значению элемента и вместимости
DynamicArray::DynamicArray(int size, int n, int capacity):
		capacity(capacity),
		size(size),
		arr(new int[capacity])
{
	for (int i = 0; i < size; i++) {
		arr[i] = n;
	}
}
// Конструктор копирования
DynamicArray::DynamicArray(const DynamicArray& src):
    capacity(src.capacity),
	size(src.size),
	arr(new int[capacity])
{
	for (int i = 0; i < size; i++) {
		arr[i] = src.arr[i];
	}
}
// Конструктор перемещения
DynamicArray::DynamicArray(DynamicArray&& src) noexcept :
    capacity(0),
	size(0),
	arr(nullptr)
{
	// Переносим значения из оригинала
    capacity = src.capacity;
	size = src.size;
	arr = src.arr;
	// Обнуляем указатель на массив и все остальные переменные в оригинале
	src.arr = nullptr;
	src.size = 0;
	src.capacity = 0;
}
// Деструктор высвобождает память, выделенную под массив
DynamicArray::~DynamicArray() {
    delete[] arr;
}
// Оператор доступа к элементу
int& DynamicArray::operator[](const int n) {
	if (n < 0 || n >= size) {
		throw "n is out of array access";
	}
	return arr[n];
}
// Оператор присваивания
DynamicArray& DynamicArray::operator=(const DynamicArray& right) {
	if (this != &right) {
		size = right.size;
		capacity = right.capacity;
		arr = new int[right.capacity];
		for (int i = 0; i < size; i++) {
			arr[i] = right.arr[i];
		}
	}
	return *this;
}
// Оператор перемещения
DynamicArray& DynamicArray::operator=(DynamicArray&& right) noexcept {
	if (this != &right) {
		delete[] arr;
		size = right.size;
		arr = right.arr;
		capacity = right.capacity;
		right.arr = nullptr;
		right.size = 0;
		right.capacity = 0;
	}
	return *this;
}
// Оператор сравнения на равенство
bool operator==(const DynamicArray& left, const DynamicArray& right) {
	// Если адреса равны - значит, сравниваем с самим собой
	if (&left == &right) {
		return true;
	}
	// Если размеры различны, выбрасываем исключение
	if (left.size != right.size) {
		throw "Sizes of arrays are not equal";
	}
	for (int i = 0; i < left.size; i++) {
		// Если хоть один элемент не совпадает - возвращаем false
		if (left.arr[i] != right.arr[i]) {
			return false;
		}
	}
	return true;
}
// Оператор сравнения на неравенство
bool operator!=(const DynamicArray& left, const DynamicArray& right) {
	// Вызываем оператор сравнения на равенство и возвращаем обратный результат
	return !(left == right);
}
// Оператор "меньше"
bool operator<(const DynamicArray& left, const DynamicArray& right) {
	// Если адреса равны - значит, сравниваем с самим собой
	if (&left == &right) {
		return false;
	}
	// Выбираем минимальный размер
	int min = (left.size < right.size) ? left.size : right.size;
	for (int i = 0; i < min; i++) {
		// Если какие-то два элемента не совпадают, возвращаем результат их сравнения
		if (left.arr[i] != right.arr[i]) {
        	return left.arr[i] < right.arr[i];
		}
	}
    return left.size < right.size;
}
// Оператор "больше"
bool operator>(const DynamicArray& left, const DynamicArray& right) {
	if (&left == &right) {
		return false;
	}
	int min = (left.size < right.size) ? left.size : right.size;
	for (int i = 0; i < min; i++) {
		if (left.arr[i] != right.arr[i]) {
        	return left.arr[i] > right.arr[i];
		}
	}
    return left.size > right.size;
}
// Оператор "меньше или равно"
bool operator<=(const DynamicArray& left, const DynamicArray& right) {
	// Отрицание оператора "больше"
	return !(left > right);
}
// Оператор "больше или равно"
bool operator>=(const DynamicArray& left, const DynamicArray& right) {
	// Отрицание оператора "меньше"
	return !(left < right);
}
// Конкатенация массивов
const DynamicArray operator+(const DynamicArray& left, const DynamicArray& right) {
	// Вспомогательный массив, его размер и вместимость - сумма размеров двух массивов
	DynamicArray temp(left.size + right.size);
	// Записываем в вспомогательный массив элементы первого
	for (int i = 0; i < left.size; i++) {
		temp.arr[i] = left.arr[i];
	}
	// Затем элементы второго
	for (int i = 0; i < right.size; i++) {
		temp.arr[left.size + i] = right.arr[i];
	}
	return temp;
}
// Получить количество элементов
int DynamicArray::length() {
	return size;
}
// Получить значение элемента на месте n
int DynamicArray::elemAt(const int n) {
	if (n < 0 || n >= size) {
		throw "n is out of range of array";
	}
	return arr[n];
}
// Изменить размер
void DynamicArray::resize(const int newSize) {
	// Если вместимость позволяет - забиваем нужное количество элементов нулями
    if (capacity >= newSize) {
        for (int i = size; i < newSize; i++) {
            arr[i] = 0;
        }
        // И меняем размер на новый
        size = newSize;
    } else {
    	// Иначе создаём новый массив с новым размером
        int* temp = new int[newSize];
        // Копируем в него элементы старого
        for (int i = 0; i < size; i++) {
            temp[i] = arr[i];
        }
        // Освобождаем память от старого
        delete[] arr;
        // Добиваем свободное место в новом массиве нулями
        for (int i = size; i < newSize; i++) {
            temp[i] = 0;
        }
        // Перекидываем указатель на новый массив
        arr = temp;
        size = newSize;
        capacity = newSize;
    }
}
// Вывод в поток в виде [a, b, c, d]
std::ostream& operator<<(std::ostream& os, const DynamicArray& arr) {
	os << "[";
	for (int i = 0; i < arr.size; i++) {
		os << arr.arr[i] << (i == arr.size - 1 ? "]" : ", ");
	}
	return os;
}
// Ввод из потока
std::istream& operator>>(std::istream& is, DynamicArray& arr) {
	for (int i = 0; i < arr.size; i++) {
		is >> arr.arr[i];
	}
	return is;
}
// Выделение дополнительных n ячеек памяти без изменения размера
void DynamicArray::reserve(const int n) {
	// Новая вместимость на n элементов больше старой
    capacity += n;
    // Если под массив выделена память
	if (arr) {
		// Создаём новый
        int* temp = new int[capacity];
        // Копируем элементы старого массива в новый
		for (int i = 0; i < size; i++) {
			temp[i] = arr[i];
		}
		// Высвобождаем память из-под старого
		delete[] arr;
		// Перебрасываем указатель
        arr = temp;
        return;
	}
	// Иначе просто выделяем память 
    arr = new int[capacity];
}
// Получить текущую вместимость массива
int DynamicArray::getCapacity() {
    return capacity;
}
// Вставить элемент в конец
void DynamicArray::pushBack(const int x) {
	// Если вместимости не хватает, резервируем ещё 16 элементов
    if (capacity <= size) {
        reserve(16);
    }
    // Добавляем элемент на следующую за последней позицию и увеличиваем размер на 1
    arr[size++] = x;
}
// Получить элемент с конца и удалить его
int DynamicArray::popBack() {
	if (size == 0) {
		throw "Array is empty";
	}
	// Возвращаем элемент на позиции size - 1 (последней) и уменьшаем размер на 1
    return arr[--size];
}
