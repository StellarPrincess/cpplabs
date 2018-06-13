#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <ostream>
#include <vector>
#include <stack>

class BinaryTree {
private:
	// Элемент дерева
    struct Node {
    
        int value;
        
        Node* left;
       
        Node* right;
        // Конструктор по значению, потомки инициализируются как нулевые
        explicit Node (int value) { this->value = value; left = nullptr; right = nullptr; }
    };
    // Рекурсивная очистка дерева
    void clear(Node* n) {
        if (n)	{
        	// Очищаем левое поддерево
            clear(n->left);
            n->left = nullptr;
            // Очищаем правое поддерево
            clear(n->right);
            n->right = nullptr;
            // Очищаем память
            delete n;
        }
    }
	// Рекурсивное копирование дерева
    void copy(Node* thisNode, Node* otherNode) {
    	// Выход из рекурсии
        if (!otherNode) {
            return;
        }
       
        if (otherNode->left) {
            thisNode->left = new Node(otherNode->left->value);
            copy(thisNode->left, otherNode->left);
        }
       
        if (otherNode->right) {
            thisNode->right = new Node(otherNode->right->value);
            copy(thisNode->right, otherNode->right);
        }
    }
	// Рекурсивный вывод
    friend std::ostream& print(std::ostream& os, const Node* n, int level) {
        if (!n) {
            return os;
        }
        // Проставляем табуляцию в зависимости от глубины
        for (int i = 0; i < level; i++) {
            os << "\t";
        }
       
        os << n->value;
        ++level;
        
        if (n->left) {
            os << std::endl;
            print(os, n->left, level);
        }
       
        if (n->right) {
            os << std::endl;
            print(os, n->right, level);
        }
        return os;
    }
	// Количество чётных (рекурсивный подсчёт)
    void evenCount(Node* n, int& count) {
        if (!n) {
            return;
        }
        if (n->value % 2 == 0) {
            ++count;
        }
       
        evenCount(n->left, count);
        
        evenCount(n->right, count);
    }
    // Все ли числа положительны (рекурсивная проверка)
    void isAllPositive(Node* n, bool& res) {
    	// Нечего проверять
        if (!n) {
            return;
        }
        
        if (n->value <= 0) {
            res = false;
            return;
        }
        // Проверка поддеревьев
        isAllPositive(n->left, res);
        isAllPositive(n->right, res);
    }
    // Удаление всех листьев
    void deleteAllLeafs(Node* n) {
        if (!n) {
            return;
        }
        // Если справа есть элемент и он является листом
        if (n->right && !(n->right->left) && !(n->right->left)) {
           delete n->right;
		   n->right = nullptr;
        } 
		else {
            deleteAllLeafs(n->right);
        }
        // Симметрично для левого поддерева
        if (n->left && !(n->left->right) && !(n->left->left)) {
            delete n->left;
            n->left = nullptr;
        } 
		else {
            deleteAllLeafs(n->left);
        }
    }
    // Нахождение среднего значения
    void average(Node* n, int& sum, int& count) {
        if (!n) {
            return;
        }
        // Накапливаем общую сумму
        sum += n->value;
        ++count;
        // Продолжаем подсчёт в поддеревьях
        average(n->left, sum, count);
        average(n->right, sum, count);
    }

	// Корень дерева
    Node* root;
public:
	// Конструктор по умолчанию
    BinaryTree() { root = nullptr; }
    // Конструктор копирования
	BinaryTree(const BinaryTree& other) {
        if (this != &other) {
            root = new Node(other.root->value);
            copy(root, other.root);
        }
    }
    // Конструктор перемещения
    BinaryTree(BinaryTree&& other) noexcept {
        if (this != &other) {
            root = other.root;
            other.root = nullptr;
        }
    }
    // Деструктор
    ~BinaryTree() {
        clear();
    }
    // Оператор присваивания
    BinaryTree& operator=(const BinaryTree& right) {
        if (this != &right) {
        	// Очищаем текущее дерево
            clear();
            // Делаем полную копию
            root = new Node(right.root->value);
            copy(root, right.root);
            return *this;
        }
    }
    // Оператор перемешения
    BinaryTree& operator=(BinaryTree&& right) noexcept {
        if (this != &right) {
        	// Очищаем текущее дерево
        	clear();
            root = right.root;
            right.root = nullptr;
            return *this;
        }
    }
    // Оператор вывода
    friend std::ostream& operator<<(std::ostream& os, const BinaryTree& tree) {
    	// Вызов рекурсивной функции вывода от корня
        return print(os, tree.root, 0);
    }
    // Очистка дерева
    void clear() {
        clear(this->root);
        root = nullptr;
    }
    // Добавление элемента
    void put(int x, std::vector<bool> way) {
        if (way.empty()) {
        	if (root) {
        		root->value = x;
        		return;
			}
            root = new Node(x);
            return;
        }
        Node* prev = root;
        Node* pointer = prev;
        // Итерирование по вектору
        for (auto &&i : way) {
            if (pointer == nullptr) {
                throw "Can't put anything here";
            }
            // Сдвигаем указатель на предыдущий элемент
            prev = pointer;
            if (i) {
                pointer = pointer->right;
            } 
			else {
                pointer = pointer->left;
            }
        }
        if (pointer) {
            pointer->value = x;
        } 
        
		else if (way[way.size() - 1]) {
            prev->right = new Node(x);
        } 
		else {
            prev->left = new Node(x);
        }
    }
    // Количество чётных
    int evenCount() {
        int res = 0;
        evenCount(root, res);
        return res;
    }
    // Количество положительных
    bool isAllPositive() {
        if (!root)
            return true;
        bool res = true;
        isAllPositive(this->root, res);
        return res;
    }
    // Удаление всех листьев
    void deleteAllLeafs() {
        deleteAllLeafs(root);
    }
    // Нахождение среднего значения
    double average() {
        if (!root)
            return 0;
        int sum = 0;
        int count = 0;
        average(root, sum, count);
        return (double) sum / (double) count;
    }
    // Поиск элемента
    std::vector<bool> find(int x) {
    	// Результирующий массив
        std::vector<bool> res = std::vector<bool>();
        // Вспомогательный стэк с указателями
        std::stack<Node*> way = std::stack<Node*>();
        if (!root)
            return res;
        Node* pointer = root;
        while (pointer != nullptr && pointer->value != x) {
        	// Поиск в левой ветке
            while (pointer != nullptr) {
                if (pointer->value == x)
                    return res;
                way.push(pointer);
                res.push_back(false);
                pointer = pointer->left;
            }
            
            pointer = way.top();
            way.pop();
            res.pop_back();
            while (pointer->right == nullptr) {
                pointer = way.top();
                way.pop();
                res.pop_back();
            }
            // Поиск в правой ветке
            while (pointer != nullptr) {
                if (pointer->value == x) {
                    return res;
                }
                way.push(pointer);
                res.push_back(true);
                pointer = pointer->right;
            }
            // Поднимаемся до узла, из которого попали в правую ветку
            pointer = way.top();
            way.pop();
            res.pop_back();
            while (pointer->left == nullptr) {
                pointer = way.top();
                way.pop();
                res.pop_back();
            }
        }

        return res;
    }
};

#endif
