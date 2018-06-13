#ifndef DYNAMICARRAYH
#define DYNAMICARRAYH
#include <iostream>
#include <stdexcept>
class DynamicArray {
private:
    int capacity;
	int size;
	int *arr;
public:
	DynamicArray();
	explicit DynamicArray(int);
	DynamicArray(int, int);
    DynamicArray(int, int, int);
	DynamicArray(const DynamicArray&);
	DynamicArray(DynamicArray&&) noexcept;
	virtual ~DynamicArray();

	int& operator[](int);
	DynamicArray& operator=(const DynamicArray&);
	DynamicArray& operator=(DynamicArray&&) noexcept;
	friend bool operator==(const DynamicArray&, const DynamicArray&);
	friend bool operator!=(const DynamicArray&, const DynamicArray&);
	friend bool operator<(const DynamicArray&, const DynamicArray&);
	friend bool operator<=(const DynamicArray&, const DynamicArray&);
	friend bool operator>=(const DynamicArray&, const DynamicArray&);
	friend bool operator>(const DynamicArray&, const DynamicArray&);
	friend std::ostream& operator<<(std::ostream&, const DynamicArray&);
	friend std::istream& operator>>(std::istream&, DynamicArray&);
	friend const DynamicArray operator+(const DynamicArray&, const DynamicArray&);

	int length();
	int elemAt(int);
	void resize(int);
	void reserve(int);
	int getCapacity();
	void pushBack(int x);
	int popBack();
};
#endif
