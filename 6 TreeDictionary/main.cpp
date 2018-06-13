#include <iostream>
#include "TreeDictionary.h"

int main(int argc, char** argv) {	
	TreeDictionary td1;
	// Вставляем несколько элементов
    td1.insert("123");
    td1.insert("456");
    td1.insert("4567");
    td1.insert("45");
    td1.insert("4567");
    // Ищем элементы
    std::cout << "find 4567: " << td1.find("4567") << std::endl;
    std::cout << "find 45: " << td1.find("45") << std::endl;
    std::cout << "find 0: " << td1.find("0") << std::endl;
    // Вставляем ещё элемент
    td1.insert("4567");
    std::cout << "insert/find 4567: " << td1.find("4567") << std::endl;
    std::cout << "tree: " << std::endl << td1 << std::endl;
    std::cout << "wordCount: " << td1.wordCount() << std::endl;
    // Удаляе некоторые элементы
    td1.remove("4567");
    std::cout << "remove/find 4567: " << td1.find("4567") << std::endl;
    td1.remove("456");
    std::cout << "remove/find 456: " << td1.find("456") << std::endl;
    td1.remove("456");
    std::cout << "remove/find 456: " << td1.find("456") << std::endl;
    std::cout << "tree: " << std::endl << td1 << std::endl;
    std::cout << "wordCount: " << td1.wordCount() << std::endl;
    std::cout << "===============" << std::endl;

	// Вставляем много элементов, чтобы проверить, что порядок сохраняется
	TreeDictionary td2;
	td2.insert("50");
	td2.insert("70");
	td2.insert("90");
	td2.insert("40");
	std::cout << "tree: " << std::endl << td2 << std::endl;
	td2.insert("30");
	td2.insert("45");
	td2.insert("60");
	td2.insert("65");
	std::cout << "tree: " << std::endl << td2 << std::endl;
	td2.insert("64");
	td2.insert("59");
	td2.insert("58");
	td2.insert("57");
	std::cout << "tree: " << std::endl << td2 << std::endl;
	std::cout << "===============" << std::endl;
	td2.remove("60");
	td2.remove("50");
	td2.remove("70");
	td2.remove("65");
	td2.remove("64");
	// Удаляем, чтобы проверить, что порядок сохраняется
	std::cout << "remove 60, 50, 70, 65, 64: " << std::endl << td2 << std::endl;

    return 0;
}
