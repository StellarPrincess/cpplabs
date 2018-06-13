#include "HashMap.h"
#include <iostream>
#include <string>

// Чтобы проще выводить, делаем проверку на nullptr
std::string toString(char** v) {
	return v ? *v : "nullptr";
}

int main()
{
	// Создаём новую хэш-таблицу и передаём хэш-функцию для int в виде лямбды h(x) = x
	HashMap<int, char*> map = HashMap<int, char*>( [=] (int x) -> int { return x; } );
	// Добавляем несколько элементов
	map.put(1, "aa");
	map.put(2, "bb");
	map.put(3, "ab");
	// Создаём итератор
    HashMap<int, char*>::HashMapIterator it = map.begin();
    // Пока есть следующий, выводим значения на экран
    while (it.hasNext()) {
        std::cout << toString(it.getValue()) << std::endl;
        it.next();
    }
    // Последний элемент выводится отдельно
    std::cout << toString(it.getValue()) << std::endl;
	// Проверка метода get() для существующих ключей
	std::cout << "key: 1" << " value: " << toString(map.get(1)) << std::endl;
	std::cout << "key: 2" << " value: " << toString(map.get(2)) << std::endl;
	std::cout << "key: 3" << " value: " << toString(map.get(3)) << std::endl;
	// Замена элемента с ключом 2
	map.put(2, "d");
	std::cout << "key: 1" << " value: " << toString(map.get(1)) << std::endl;
	std::cout << "key: 2" << " value: " << toString(map.get(2)) << std::endl;
	std::cout << "key: 3" << " value: " << toString(map.get(3)) << std::endl;
	// Удаление элемента
	map.remove(1);
	std::cout << "key: 1" << " value: " << toString(map.get(1)) << std::endl;
	std::cout << "key: 2" << " value: " << toString(map.get(2)) << std::endl;
	std::cout << "key: 3" << " value: " << toString(map.get(3)) << std::endl;
	// get() для несуществующего ключа
	std::cout << "key: 5" << " value: " << toString(map.get(5)) << std::endl;

	system("pause");

    return 0;
}

