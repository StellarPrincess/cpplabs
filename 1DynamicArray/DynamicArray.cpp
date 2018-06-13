#include "DynamicArray.h"

// ����������� �� ���������
DynamicArray::DynamicArray():
		capacity(100),
		size(100),
		arr(new int[100])
{
	for (int i = 0; i < size; i++) {
		arr[i] = 0;
	}
}
// ����������� �� �������
DynamicArray::DynamicArray(int size):
		capacity(size),
		size(size),
		arr(new int[size])
{
	for (int i = 0; i < size; i++) {
		arr[i] = 0;
	}
}
// ����������� �� ������� � �������� ��������
DynamicArray::DynamicArray(int size, int n):
		capacity(size),
		size(size),
		arr(new int[size])
{
	for (int i = 0; i < size; i++) {
		arr[i] = n;
	}
}
// ����������� �� �������, �������� �������� � �����������
DynamicArray::DynamicArray(int size, int n, int capacity):
		capacity(capacity),
		size(size),
		arr(new int[capacity])
{
	for (int i = 0; i < size; i++) {
		arr[i] = n;
	}
}
// ����������� �����������
DynamicArray::DynamicArray(const DynamicArray& src):
    capacity(src.capacity),
	size(src.size),
	arr(new int[capacity])
{
	for (int i = 0; i < size; i++) {
		arr[i] = src.arr[i];
	}
}
// ����������� �����������
DynamicArray::DynamicArray(DynamicArray&& src) noexcept :
    capacity(0),
	size(0),
	arr(nullptr)
{
	// ��������� �������� �� ���������
    capacity = src.capacity;
	size = src.size;
	arr = src.arr;
	// �������� ��������� �� ������ � ��� ��������� ���������� � ���������
	src.arr = nullptr;
	src.size = 0;
	src.capacity = 0;
}
// ���������� ������������ ������, ���������� ��� ������
DynamicArray::~DynamicArray() {
    delete[] arr;
}
// �������� ������� � ��������
int& DynamicArray::operator[](const int n) {
	if (n < 0 || n >= size) {
		throw "n is out of array access";
	}
	return arr[n];
}
// �������� ������������
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
// �������� �����������
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
// �������� ��������� �� ���������
bool operator==(const DynamicArray& left, const DynamicArray& right) {
	// ���� ������ ����� - ������, ���������� � ����� �����
	if (&left == &right) {
		return true;
	}
	// ���� ������� ��������, ����������� ����������
	if (left.size != right.size) {
		throw "Sizes of arrays are not equal";
	}
	for (int i = 0; i < left.size; i++) {
		// ���� ���� ���� ������� �� ��������� - ���������� false
		if (left.arr[i] != right.arr[i]) {
			return false;
		}
	}
	return true;
}
// �������� ��������� �� �����������
bool operator!=(const DynamicArray& left, const DynamicArray& right) {
	// �������� �������� ��������� �� ��������� � ���������� �������� ���������
	return !(left == right);
}
// �������� "������"
bool operator<(const DynamicArray& left, const DynamicArray& right) {
	// ���� ������ ����� - ������, ���������� � ����� �����
	if (&left == &right) {
		return false;
	}
	// �������� ����������� ������
	int min = (left.size < right.size) ? left.size : right.size;
	for (int i = 0; i < min; i++) {
		// ���� �����-�� ��� �������� �� ���������, ���������� ��������� �� ���������
		if (left.arr[i] != right.arr[i]) {
        	return left.arr[i] < right.arr[i];
		}
	}
    return left.size < right.size;
}
// �������� "������"
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
// �������� "������ ��� �����"
bool operator<=(const DynamicArray& left, const DynamicArray& right) {
	// ��������� ��������� "������"
	return !(left > right);
}
// �������� "������ ��� �����"
bool operator>=(const DynamicArray& left, const DynamicArray& right) {
	// ��������� ��������� "������"
	return !(left < right);
}
// ������������ ��������
const DynamicArray operator+(const DynamicArray& left, const DynamicArray& right) {
	// ��������������� ������, ��� ������ � ����������� - ����� �������� ���� ��������
	DynamicArray temp(left.size + right.size);
	// ���������� � ��������������� ������ �������� �������
	for (int i = 0; i < left.size; i++) {
		temp.arr[i] = left.arr[i];
	}
	// ����� �������� �������
	for (int i = 0; i < right.size; i++) {
		temp.arr[left.size + i] = right.arr[i];
	}
	return temp;
}
// �������� ���������� ���������
int DynamicArray::length() {
	return size;
}
// �������� �������� �������� �� ����� n
int DynamicArray::elemAt(const int n) {
	if (n < 0 || n >= size) {
		throw "n is out of range of array";
	}
	return arr[n];
}
// �������� ������
void DynamicArray::resize(const int newSize) {
	// ���� ����������� ��������� - �������� ������ ���������� ��������� ������
    if (capacity >= newSize) {
        for (int i = size; i < newSize; i++) {
            arr[i] = 0;
        }
        // � ������ ������ �� �����
        size = newSize;
    } else {
    	// ����� ������ ����� ������ � ����� ��������
        int* temp = new int[newSize];
        // �������� � ���� �������� �������
        for (int i = 0; i < size; i++) {
            temp[i] = arr[i];
        }
        // ����������� ������ �� �������
        delete[] arr;
        // �������� ��������� ����� � ����� ������� ������
        for (int i = size; i < newSize; i++) {
            temp[i] = 0;
        }
        // ������������ ��������� �� ����� ������
        arr = temp;
        size = newSize;
        capacity = newSize;
    }
}
// ����� � ����� � ���� [a, b, c, d]
std::ostream& operator<<(std::ostream& os, const DynamicArray& arr) {
	os << "[";
	for (int i = 0; i < arr.size; i++) {
		os << arr.arr[i] << (i == arr.size - 1 ? "]" : ", ");
	}
	return os;
}
// ���� �� ������
std::istream& operator>>(std::istream& is, DynamicArray& arr) {
	for (int i = 0; i < arr.size; i++) {
		is >> arr.arr[i];
	}
	return is;
}
// ��������� �������������� n ����� ������ ��� ��������� �������
void DynamicArray::reserve(const int n) {
	// ����� ����������� �� n ��������� ������ ������
    capacity += n;
    // ���� ��� ������ �������� ������
	if (arr) {
		// ������ �����
        int* temp = new int[capacity];
        // �������� �������� ������� ������� � �����
		for (int i = 0; i < size; i++) {
			temp[i] = arr[i];
		}
		// ������������ ������ ��-��� �������
		delete[] arr;
		// ������������� ���������
        arr = temp;
        return;
	}
	// ����� ������ �������� ������ 
    arr = new int[capacity];
}
// �������� ������� ����������� �������
int DynamicArray::getCapacity() {
    return capacity;
}
// �������� ������� � �����
void DynamicArray::pushBack(const int x) {
	// ���� ����������� �� �������, ����������� ��� 16 ���������
    if (capacity <= size) {
        reserve(16);
    }
    // ��������� ������� �� ��������� �� ��������� ������� � ����������� ������ �� 1
    arr[size++] = x;
}
// �������� ������� � ����� � ������� ���
int DynamicArray::popBack() {
	if (size == 0) {
		throw "Array is empty";
	}
	// ���������� ������� �� ������� size - 1 (���������) � ��������� ������ �� 1
    return arr[--size];
}
