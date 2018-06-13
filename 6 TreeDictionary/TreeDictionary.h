#ifndef TREE_DICTIONARY_H
#define TREE_DICTIONARY_H

#include <cstring>
#include <iostream>

class TreeDictionary {
private:
	// Узел дерева
	struct Node {
		char* word;
		unsigned count;
		Node* left;
		Node* right;
		Node(char* w) { word = w; left = right = 0; count = 1; }
		Node(char* w, unsigned count) { word = w; left = right = 0; this->count = count; }
	};
	// Очистка идентична предыдущему заданию
	void clear(Node* n) {
        if (n)	{
            clear(n->left);
            n->left = nullptr;
            clear(n->right);
            n->right = nullptr;
            delete n;
        }
    }
	// Копирование аналогично предыдущему заданию
    void copy(Node* thisNode, Node* otherNode) {
        if (otherNode == nullptr)
            return;
        if (otherNode->left) {
            thisNode->left = new Node(otherNode->left->word, otherNode->left->count);
            copy(thisNode->left, otherNode->left);
        }
        if (otherNode->right) {
            thisNode->right = new Node(otherNode->right->word, otherNode->right->count);
            copy(thisNode->right, otherNode->right);
        }
    }
    // Рекурсивный вывод слов в алфавитном порядке
	friend std::ostream& print(std::ostream& os, const Node* n) {
	    if (!n) {
	        return os;
	    }
	    // Выводим левое поддерево
	    print(os, n->left);
	    // Выводим текущий элемент
	    os << n->word << " " << n->count << std::endl;
	    // Выводим правое поддерево
	    print(os, n->right);
	    return os;
	}
	// Вставка элемента
	Node* insert(Node* p, char* w) {
		// Если узел пуст, создаём новый
		if (!p) {
			return new Node(w);
		}
		// Если текущее слово "меньше" заданного, идём в левое поддерево
		if (strcmp(w, p->word) < 0)
			p->left = insert(p->left, w);
		// Если больше - в правое
		else if (strcmp(w, p->word) > 0)
			p->right = insert(p->right, w);
		// Если совпадает - прибавляем 1 к количеству
		else {
			p->count++;
		}
		return p;
	}
	// Удаление элемента
	Node* remove(Node* p, char* w) {
		// Удалять нечего
		if (!p) return nullptr;
		// Если заданное слово меньше текущего - идём в левое поддерево
		if (strcmp(w, p->word) < 0)
			p->left = remove(p->left, w);
		// Если больше - в правое
		else if (strcmp(w, p->word) > 0)
			p->right = remove(p->right, w);	
		// Если совпадает
		else {
			// Если количество > 1, отнимаем 1
			if (p->count > 1) {
				p->count--;
			}
			// Иначе удаляем узел
			else {
				// Запоминаем потомки
				Node* q = p->left;
				Node* r = p->right;
				// Удаляем узел
				delete p;
				p = nullptr;
				// Если ни одного потомка нет - возвращаем p = nullptr
				if (!r && !q) return p;
				// Если нет одного - возвращаем другого
				if (!r) return q;
				if (!q) return r;
				// Если есть оба - делаем левого потомка левым потомком правого и возвращаем правого
				r->left = q;
				return r;
			}
		}
	}
	// Поиск элемента
	unsigned find(Node* p, char* w) {
		if (!p) return 0;
		if (strcmp(w, p->word) < 0)
			return find(p->left, w);
		if (strcmp(w, p->word) > 0)
			return find(p->right, w);	
		return p->count;
	}
	// Подсчёт количества слов
	void wordCount(Node* p, unsigned& count) {
		if (!p) {
			return;
		}
		count += p->count;
		wordCount(p->left, count);
		wordCount(p->right, count);
	}
	// Корень дерева
	Node* root;
public:
	// Конструктор
	TreeDictionary() { root = nullptr; }
	// Конструктор копирования
    TreeDictionary(const TreeDictionary& other) {
        if (this != &other) {
            root = new Node(other.root->word, other.root->count);
            copy(root, other.root);
        }
    }
    // Конструктор перемещения
    TreeDictionary(TreeDictionary&& other) noexcept {
        if (this != &other) {
            root = other.root;
            other.root = nullptr;
        }
    }
    // Деструктор
    ~TreeDictionary() {
        clear();
    }
    // Оператор присваивания
    TreeDictionary& operator=(const TreeDictionary& right) {
        if (this != &right) {
            clear();
            root = new Node(right.root->word, right.root->count);
            copy(root, right.root);
            return *this;
        }
    }
    // Оператор перемещения
    TreeDictionary& operator=(TreeDictionary&& right) noexcept {
        if (this != &right) {
        	clear();
            root = right.root;
            right.root = nullptr;
            return *this;
        }
    }
	Node* remove(char* w) {
		root = remove(root, w);
	}
	Node* insert(char* w) {
		return root = insert(root, w);	
	}
	unsigned find(char* w) {
		return find(root, w);
	}
	unsigned wordCount() {
		unsigned count = 0;
		wordCount(root, count);
		return count;
	}
	friend std::ostream& operator<<(std::ostream& os, const TreeDictionary& td) {
		return print(os, td.root);
	}
	void clear() {
        clear(this->root);
        root = nullptr;
    }
};

#endif
