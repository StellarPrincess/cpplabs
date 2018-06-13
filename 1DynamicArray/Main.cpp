#include <iostream>
#include <vector>
#include "DynamicArray.h"

int main() {
	// Создаём массив размера 10
    DynamicArray arr(10);
    DynamicArray arr3(2,2);
    std::cout << "arr3: " << arr3 << std::endl;
	try {
        for (int i = 0; i<3; i++) 
    		std::cout << "arr3.popBack(): " << arr3.popBack() << std::endl;
    } catch (const char* e) {
    	std::cout << e << std::endl; 
    }

    // Создаём массив размера 10, заполненный пятёрками
    DynamicArray arr2(10, 5);
    // Выводим их на экран
    std::cout << "arr: " << arr << std::endl
              << "arr2: " << arr2 << std::endl;
	// Пробуем получить элемент за пределами массива
    try {
        int a = arr[10];
    } catch (const char* e) {
    	// Ловим исключение и выводим информацию об ошибке
        std::cout << "Tried to get arr[10]. Exception caught!";
    }
	// Конкатенируем массивы и выводим полученный на экран
    std::cout << std::endl << "(after arr + arr2) arr: ";
    arr = arr + arr2;
    std::cout << arr << std::endl;
	// Проверяем работу операторов "больше" и "меньше"
    std::cout << std::endl << "arr < arr2? " << ((arr < arr2) ? "yes" : "no");
    std::cout << std::endl << "arr > arr2? " << ((arr > arr2) ? "yes" : "no");
	// Изменяем размер второго массива до 50 и выводим его на экран
    arr2.resize(50);
    std::cout << std::endl << "(after resizing) arr2: " << arr2 << std::endl;
	// Заполняем массив пятёрками для проверки оператора доступа к элементу
    for (int i = 0; i < arr.length(); i++) {
        arr[i] = 5;
    }
    // Выводим полученный массив на экран и сравниваем со вторым
    std::cout << std::endl << "(after reassigning) arr: " << arr << std::endl;
    std::cout << std::endl << "arr < arr2? " << ((arr < arr2) ? "yes" : "no");
    std::cout << std::endl << "arr > arr2? " << ((arr > arr2) ? "yes" : "no") << std::endl;
    // Пытаемся сравнить на равенство
    try {
        std::cout << std::endl << "arr == arr2? " << ((arr == arr2) ? "yes" : "no");
    } catch (const char* e) {
    	// Ловим исключение и выводим сообщение об ошибке
        std::cout << e << std::endl; 
    }
    // Уменьшаем размер до 20 (чтобы он совпадал с размером первого массива)
	arr2.resize(20);
	// И заполняем пятёрками
    for (int i = 0; i < arr2.length(); i++) {
        arr2[i] = 5;
    }
    std::cout << std::endl << "(after reassigning) arr2: ";
    std::cout << arr2;
	// Различные сравнения
    std::cout << std::endl << "arr < arr2? " << ((arr < arr2) ? "yes" : "no");
    std::cout << std::endl << "arr > arr2? " << ((arr > arr2) ? "yes" : "no");
    std::cout << std::endl << "arr >= arr2? " << ((arr >= arr2) ? "yes" : "no");
    std::cout << std::endl << "arr <= arr2? " << ((arr <= arr2) ? "yes" : "no");
    std::cout << std::endl << "arr == arr2? " << ((arr == arr2) ? "yes" : "no");
    std::cout << std::endl << "arr != arr2? " << ((arr != arr2) ? "yes" : "no");
    // Сравниваем массив сам с собой
    std::cout << std::endl << "arr == arr? " << ((arr == arr) ? "yes" : "no") << std::endl;
    std::cout << "Pushed 2 in the end of array" << std::endl;
	// Добавляем 2 в конец первого массива, выводим его и информацию о его вместимости и размере на экран
    arr.pushBack(2);
    std::cout << std::endl << arr << std::endl
              << "arr.capacity: " << arr.getCapacity() << std::endl
              << "arr.size: " << arr.length() << std::endl;
    // Забираем элемент из конца, выводим информацию о вместимости и размере массива на экран

    std::cout << "arr.popBack(): " << arr.popBack() << std::endl; 
    std::cout << arr << std::endl
              << "arr.capacity: " << arr.getCapacity() << std::endl
              << "arr.size: " << arr.length() << std::endl;
    // Резервируем ещё 30 элементов в первом массиве, выводим его и информацию о его вместимости и размере на экран
    arr.reserve(30);
    std::cout << arr << std::endl
              << "arr.capacity: " << arr.getCapacity() << std::endl
              << "arr.size: " << arr.length() << std::endl;

    return 0;
}
