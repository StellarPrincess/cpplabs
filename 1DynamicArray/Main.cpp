#include <iostream>
#include <vector>
#include "DynamicArray.h"

int main() {
	// ������ ������ ������� 10
    DynamicArray arr(10);
    DynamicArray arr3(2,2);
    std::cout << "arr3: " << arr3 << std::endl;
	try {
        for (int i = 0; i<3; i++) 
    		std::cout << "arr3.popBack(): " << arr3.popBack() << std::endl;
    } catch (const char* e) {
    	std::cout << e << std::endl; 
    }

    // ������ ������ ������� 10, ����������� ��������
    DynamicArray arr2(10, 5);
    // ������� �� �� �����
    std::cout << "arr: " << arr << std::endl
              << "arr2: " << arr2 << std::endl;
	// ������� �������� ������� �� ��������� �������
    try {
        int a = arr[10];
    } catch (const char* e) {
    	// ����� ���������� � ������� ���������� �� ������
        std::cout << "Tried to get arr[10]. Exception caught!";
    }
	// ������������� ������� � ������� ���������� �� �����
    std::cout << std::endl << "(after arr + arr2) arr: ";
    arr = arr + arr2;
    std::cout << arr << std::endl;
	// ��������� ������ ���������� "������" � "������"
    std::cout << std::endl << "arr < arr2? " << ((arr < arr2) ? "yes" : "no");
    std::cout << std::endl << "arr > arr2? " << ((arr > arr2) ? "yes" : "no");
	// �������� ������ ������� ������� �� 50 � ������� ��� �� �����
    arr2.resize(50);
    std::cout << std::endl << "(after resizing) arr2: " << arr2 << std::endl;
	// ��������� ������ �������� ��� �������� ��������� ������� � ��������
    for (int i = 0; i < arr.length(); i++) {
        arr[i] = 5;
    }
    // ������� ���������� ������ �� ����� � ���������� �� ������
    std::cout << std::endl << "(after reassigning) arr: " << arr << std::endl;
    std::cout << std::endl << "arr < arr2? " << ((arr < arr2) ? "yes" : "no");
    std::cout << std::endl << "arr > arr2? " << ((arr > arr2) ? "yes" : "no") << std::endl;
    // �������� �������� �� ���������
    try {
        std::cout << std::endl << "arr == arr2? " << ((arr == arr2) ? "yes" : "no");
    } catch (const char* e) {
    	// ����� ���������� � ������� ��������� �� ������
        std::cout << e << std::endl; 
    }
    // ��������� ������ �� 20 (����� �� �������� � �������� ������� �������)
	arr2.resize(20);
	// � ��������� ��������
    for (int i = 0; i < arr2.length(); i++) {
        arr2[i] = 5;
    }
    std::cout << std::endl << "(after reassigning) arr2: ";
    std::cout << arr2;
	// ��������� ���������
    std::cout << std::endl << "arr < arr2? " << ((arr < arr2) ? "yes" : "no");
    std::cout << std::endl << "arr > arr2? " << ((arr > arr2) ? "yes" : "no");
    std::cout << std::endl << "arr >= arr2? " << ((arr >= arr2) ? "yes" : "no");
    std::cout << std::endl << "arr <= arr2? " << ((arr <= arr2) ? "yes" : "no");
    std::cout << std::endl << "arr == arr2? " << ((arr == arr2) ? "yes" : "no");
    std::cout << std::endl << "arr != arr2? " << ((arr != arr2) ? "yes" : "no");
    // ���������� ������ ��� � �����
    std::cout << std::endl << "arr == arr? " << ((arr == arr) ? "yes" : "no") << std::endl;
    std::cout << "Pushed 2 in the end of array" << std::endl;
	// ��������� 2 � ����� ������� �������, ������� ��� � ���������� � ��� ����������� � ������� �� �����
    arr.pushBack(2);
    std::cout << std::endl << arr << std::endl
              << "arr.capacity: " << arr.getCapacity() << std::endl
              << "arr.size: " << arr.length() << std::endl;
    // �������� ������� �� �����, ������� ���������� � ����������� � ������� ������� �� �����

    std::cout << "arr.popBack(): " << arr.popBack() << std::endl; 
    std::cout << arr << std::endl
              << "arr.capacity: " << arr.getCapacity() << std::endl
              << "arr.size: " << arr.length() << std::endl;
    // ����������� ��� 30 ��������� � ������ �������, ������� ��� � ���������� � ��� ����������� � ������� �� �����
    arr.reserve(30);
    std::cout << arr << std::endl
              << "arr.capacity: " << arr.getCapacity() << std::endl
              << "arr.size: " << arr.length() << std::endl;

    return 0;
}
