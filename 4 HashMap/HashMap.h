#ifndef HASHMAP_H
#define HASHMAP_H

#include "Iterator.h"

// K - тип ключа, V - тип хранимых значений
template<typename K, typename V>
class HashMap
{
private:
	// Структура элемента
	template<typename KE, typename VE>
	struct Elem {
		// Хэш-код ключа
		int hash;
		// Указатель на следующий элемент
		Elem* next;
		// Ключ
		KE key;
		// Значение
		VE value;
		// Конструктор. h - хэш, k - ключ, v - значение, n - указатель на следующий элемент
		Elem(int h, KE k, VE v, Elem<KE, VE>* n) { hash = h; key = k; next = n; value = v; }
	};
public:
	// Стандартный размер массива
	static const int DEFAULT_CAPACITY = 16;
	// Итератор
	class HashMapIterator : public Iterator<V> {
	    friend class HashMap;
	private:
		// Указатель на итерируемую хэш-таблицу
        HashMap<K, V>* map;
        // Указатель на текущий элемент
        Elem<K, V>* curr;
        // Номер текущей ячейки в массиве
        int bucket;
		// Конструктор
        explicit HashMapIterator(HashMap<K, V> * map)
        {
        	this->map = map;
			curr = map->arr[0];
			bucket = 0;
			// Сразу сдвигаемся на непустой элемент
            start();
        };
	public:
		// Конструктор копирования
		HashMapIterator(const HashMapIterator& it) { map = it.map; curr = it.curr; bucket = it.bucket; }
		// Сдвиг на первый непустой элемент
        void start() override {
        	// Начинаем с самого первого
            curr = map->arr[0];
            // Пока элемент пуст и не вышли за пределы массива
		    while (curr == nullptr && bucket < map->capacity) {
		    	// Двигаемся по массиву
		        curr = map->arr[++bucket];
            }
		}
		// Получить указатель на значение элемента, на котором стоит итератор
        V* getValue() override {
            return &curr->value;
		}
		// Сдвиг итератора вперёд
        void next() override {
        	// Если текущий указатель нулевой, то что-то пошло не так
            if (!curr)
                throw "No such element";
            // Если есть следующий элемент в списке
            if (curr->next != nullptr) {
            	// Сдвигаем указатель на него
                curr = curr->next;
                return;
            }
            // Иначе ищем в массиве
            curr = map->arr[++bucket];
            while (curr == nullptr && bucket < map->capacity)
			    curr = map->arr[++bucket];
		}
		// Проверка, есть ли следующий элемент
        bool hasNext() override {
        	// Аналогично сдвигу указателя
            if (!curr) 
				return false;
            if (curr->next)
                return true;
            // Но используются вспомогательные переменные, чтобы не сдвинуть итератор
            int tBucket = bucket;
            Elem<K, V>* tPointer = map->arr[++tBucket];
            while (tPointer == nullptr && tBucket < map->capacity) {
                ++tBucket;
                tPointer = map->arr[tBucket];
            }
            return tPointer != nullptr;
		}
	};
	// Получение итератора на первый непустой элемент
	HashMapIterator begin() {
		return HashMapIterator(this);
	}
	// Конструктор. Аргументы - хэш-функция и вместимость массива
	HashMap(int (*hasher)(K), int capacity = DEFAULT_CAPACITY) {
		// Меньше нуля или ноль нельзя
		if (capacity <= 0) {
			throw "Illegal capacity";
		}
		this->capacity = capacity;
		size = 0;
		// Создаём новый массив
		arr = new Elem<K, V>*[capacity];	
		// Заполняем нулями
		for (int i = 0; i < capacity; i++) {
			arr[i] = nullptr;
		}
	}
	// Добавление элемента
	void put(const K& key, const V& value) {
		// Вычисляем хэш-код
		int hash = hasher(key);
		// Вычисляем индекс в массиве
		int i = indexFor(hash, capacity);
		// Ищем место для вставки в списке по индексу i
		Elem<K, V>* e = arr[i];
		while (e != nullptr) {
			// Если найден элемент с таким же ключом
			if (key == e->key) {
				// Перезаписываем его значение
				e->value = value;
				return;
			}
			e = e->next;
		}
		// Вставка в начало списка
		addElem(hash, key, value, i);
	}
	// Удаление элемента
	void remove(const K& key) {
		// Очевидно
		int hash = hasher(key);
		int i = indexFor(hash, capacity);
		// Вспомогательные указатели
		Elem<K, V>* prev = arr[i];
		Elem<K, V>* e = prev;
		// Ищем элемент в списке для удаления
		while (e != nullptr) {
			// Запоминаем следующий элемент в списке
			Elem<K, V>* next = e->next;
			// Если нашли нужный ключ
			if (e->key == key) {
				--size;
				// Если указатель на предыдущий элемент совпадает с указателем на текущий
				// находимся в начале списка
				if (prev == e) {
					// Перебрасываем указатель в обход
					arr[i] = next;
					// Очищаем память
					delete e;
				}
				// Иначе находимся в середине списка
				else {
					// Перебрасываем указатель в обход и очищаем память
					prev->next = next;
					delete e;
				}
				return;
			}
			// Сдвигаем указатели дальше
			prev = e;
			e = next;
		}
	}
	// Получение указателя на значение элемента
	V* get(const K& key) {
		// Очевидно
		int hash = hasher(key);
		int i = indexFor(hash, capacity);
		// Вспомогательный указатель
		Elem<K, V>* e = arr[i];
		// Ищем нужный ключ
		while (e != nullptr) {
			if (e->key == key) {
				return &(e->value);
			}
			e = e->next;
		}
		// Если не нашли - возвращаем nullptr
		return nullptr;
	}
	// Очистка таблицы
	void erase() {
		// Для каждой ячейки массива производим классическую очистку списка
		for (int i = 0; i < capacity; i++) {
			Elem<K, V>* e = arr[i];
			Elem<K, V>* next;
			while(e != nullptr) {
				next = e->next;
				delete e;
				e = next;
			}
			arr[i] = nullptr;
		}
		// И сбрасываем количество элементов в ноль
		size = 0;
	}
	// Проверка на пустоту
	bool isEmpty() {
		return size == 0;
	}
	// Деструктор
	virtual ~HashMap() {
		erase();
		delete[] arr;
	}
	
private:
	// Массив списков
	Elem<K, V>** arr;
	// Хэщ-функция
	int (*hasher)(K);
	// Количество элементов
	int size;
	// Размер массива
	int capacity;
	// Получение индекса в массиве
	int indexFor(int h, int c) {
		return h % c;
	}
	// Вставка нового элемента в начало списка
	void addElem(int hash, const K& key, const V& value, int bucketIndex) {
		// Запоминаем старое значение
		Elem<K, V>* e = arr[bucketIndex];
		// Записываем в ячейку новый элемент, его поле next == e
		arr[bucketIndex] = new Elem<K, V>(hash, key, value, e);
	}
};

#endif // HASHMAP_H
