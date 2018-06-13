#ifndef HASHMAP_H
#define HASHMAP_H

#include "Iterator.h"

// K - ��� �����, V - ��� �������� ��������
template<typename K, typename V>
class HashMap
{
private:
	// ��������� ��������
	template<typename KE, typename VE>
	struct Elem {
		// ���-��� �����
		int hash;
		// ��������� �� ��������� �������
		Elem* next;
		// ����
		KE key;
		// ��������
		VE value;
		// �����������. h - ���, k - ����, v - ��������, n - ��������� �� ��������� �������
		Elem(int h, KE k, VE v, Elem<KE, VE>* n) { hash = h; key = k; next = n; value = v; }
	};
public:
	// ����������� ������ �������
	static const int DEFAULT_CAPACITY = 16;
	// ��������
	class HashMapIterator : public Iterator<V> {
	    friend class HashMap;
	private:
		// ��������� �� ����������� ���-�������
        HashMap<K, V>* map;
        // ��������� �� ������� �������
        Elem<K, V>* curr;
        // ����� ������� ������ � �������
        int bucket;
		// �����������
        explicit HashMapIterator(HashMap<K, V> * map)
        {
        	this->map = map;
			curr = map->arr[0];
			bucket = 0;
			// ����� ���������� �� �������� �������
            start();
        };
	public:
		// ����������� �����������
		HashMapIterator(const HashMapIterator& it) { map = it.map; curr = it.curr; bucket = it.bucket; }
		// ����� �� ������ �������� �������
        void start() override {
        	// �������� � ������ �������
            curr = map->arr[0];
            // ���� ������� ���� � �� ����� �� ������� �������
		    while (curr == nullptr && bucket < map->capacity) {
		    	// ��������� �� �������
		        curr = map->arr[++bucket];
            }
		}
		// �������� ��������� �� �������� ��������, �� ������� ����� ��������
        V* getValue() override {
            return &curr->value;
		}
		// ����� ��������� �����
        void next() override {
        	// ���� ������� ��������� �������, �� ���-�� ����� �� ���
            if (!curr)
                throw "No such element";
            // ���� ���� ��������� ������� � ������
            if (curr->next != nullptr) {
            	// �������� ��������� �� ����
                curr = curr->next;
                return;
            }
            // ����� ���� � �������
            curr = map->arr[++bucket];
            while (curr == nullptr && bucket < map->capacity)
			    curr = map->arr[++bucket];
		}
		// ��������, ���� �� ��������� �������
        bool hasNext() override {
        	// ���������� ������ ���������
            if (!curr) 
				return false;
            if (curr->next)
                return true;
            // �� ������������ ��������������� ����������, ����� �� �������� ��������
            int tBucket = bucket;
            Elem<K, V>* tPointer = map->arr[++tBucket];
            while (tPointer == nullptr && tBucket < map->capacity) {
                ++tBucket;
                tPointer = map->arr[tBucket];
            }
            return tPointer != nullptr;
		}
	};
	// ��������� ��������� �� ������ �������� �������
	HashMapIterator begin() {
		return HashMapIterator(this);
	}
	// �����������. ��������� - ���-������� � ����������� �������
	HashMap(int (*hasher)(K), int capacity = DEFAULT_CAPACITY) {
		// ������ ���� ��� ���� ������
		if (capacity <= 0) {
			throw "Illegal capacity";
		}
		this->capacity = capacity;
		size = 0;
		// ������ ����� ������
		arr = new Elem<K, V>*[capacity];	
		// ��������� ������
		for (int i = 0; i < capacity; i++) {
			arr[i] = nullptr;
		}
	}
	// ���������� ��������
	void put(const K& key, const V& value) {
		// ��������� ���-���
		int hash = hasher(key);
		// ��������� ������ � �������
		int i = indexFor(hash, capacity);
		// ���� ����� ��� ������� � ������ �� ������� i
		Elem<K, V>* e = arr[i];
		while (e != nullptr) {
			// ���� ������ ������� � ����� �� ������
			if (key == e->key) {
				// �������������� ��� ��������
				e->value = value;
				return;
			}
			e = e->next;
		}
		// ������� � ������ ������
		addElem(hash, key, value, i);
	}
	// �������� ��������
	void remove(const K& key) {
		// ��������
		int hash = hasher(key);
		int i = indexFor(hash, capacity);
		// ��������������� ���������
		Elem<K, V>* prev = arr[i];
		Elem<K, V>* e = prev;
		// ���� ������� � ������ ��� ��������
		while (e != nullptr) {
			// ���������� ��������� ������� � ������
			Elem<K, V>* next = e->next;
			// ���� ����� ������ ����
			if (e->key == key) {
				--size;
				// ���� ��������� �� ���������� ������� ��������� � ���������� �� �������
				// ��������� � ������ ������
				if (prev == e) {
					// ������������� ��������� � �����
					arr[i] = next;
					// ������� ������
					delete e;
				}
				// ����� ��������� � �������� ������
				else {
					// ������������� ��������� � ����� � ������� ������
					prev->next = next;
					delete e;
				}
				return;
			}
			// �������� ��������� ������
			prev = e;
			e = next;
		}
	}
	// ��������� ��������� �� �������� ��������
	V* get(const K& key) {
		// ��������
		int hash = hasher(key);
		int i = indexFor(hash, capacity);
		// ��������������� ���������
		Elem<K, V>* e = arr[i];
		// ���� ������ ����
		while (e != nullptr) {
			if (e->key == key) {
				return &(e->value);
			}
			e = e->next;
		}
		// ���� �� ����� - ���������� nullptr
		return nullptr;
	}
	// ������� �������
	void erase() {
		// ��� ������ ������ ������� ���������� ������������ ������� ������
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
		// � ���������� ���������� ��������� � ����
		size = 0;
	}
	// �������� �� �������
	bool isEmpty() {
		return size == 0;
	}
	// ����������
	virtual ~HashMap() {
		erase();
		delete[] arr;
	}
	
private:
	// ������ �������
	Elem<K, V>** arr;
	// ���-�������
	int (*hasher)(K);
	// ���������� ���������
	int size;
	// ������ �������
	int capacity;
	// ��������� ������� � �������
	int indexFor(int h, int c) {
		return h % c;
	}
	// ������� ������ �������� � ������ ������
	void addElem(int hash, const K& key, const V& value, int bucketIndex) {
		// ���������� ������ ��������
		Elem<K, V>* e = arr[bucketIndex];
		// ���������� � ������ ����� �������, ��� ���� next == e
		arr[bucketIndex] = new Elem<K, V>(hash, key, value, e);
	}
};

#endif // HASHMAP_H
