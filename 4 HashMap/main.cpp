#include "HashMap.h"
#include <iostream>
#include <string>

// ����� ����� ��������, ������ �������� �� nullptr
std::string toString(char** v) {
	return v ? *v : "nullptr";
}

int main()
{
	// ������ ����� ���-������� � ������� ���-������� ��� int � ���� ������ h(x) = x
	HashMap<int, char*> map = HashMap<int, char*>( [=] (int x) -> int { return x; } );
	// ��������� ��������� ���������
	map.put(1, "aa");
	map.put(2, "bb");
	map.put(3, "ab");
	// ������ ��������
    HashMap<int, char*>::HashMapIterator it = map.begin();
    // ���� ���� ���������, ������� �������� �� �����
    while (it.hasNext()) {
        std::cout << toString(it.getValue()) << std::endl;
        it.next();
    }
    // ��������� ������� ��������� ��������
    std::cout << toString(it.getValue()) << std::endl;
	// �������� ������ get() ��� ������������ ������
	std::cout << "key: 1" << " value: " << toString(map.get(1)) << std::endl;
	std::cout << "key: 2" << " value: " << toString(map.get(2)) << std::endl;
	std::cout << "key: 3" << " value: " << toString(map.get(3)) << std::endl;
	// ������ �������� � ������ 2
	map.put(2, "d");
	std::cout << "key: 1" << " value: " << toString(map.get(1)) << std::endl;
	std::cout << "key: 2" << " value: " << toString(map.get(2)) << std::endl;
	std::cout << "key: 3" << " value: " << toString(map.get(3)) << std::endl;
	// �������� ��������
	map.remove(1);
	std::cout << "key: 1" << " value: " << toString(map.get(1)) << std::endl;
	std::cout << "key: 2" << " value: " << toString(map.get(2)) << std::endl;
	std::cout << "key: 3" << " value: " << toString(map.get(3)) << std::endl;
	// get() ��� ��������������� �����
	std::cout << "key: 5" << " value: " << toString(map.get(5)) << std::endl;

	system("pause");

    return 0;
}

