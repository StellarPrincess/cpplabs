#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <ostream>
#include <vector>
#include <stack>

class BinaryTree {
private:
	// ������� ������
    struct Node {
    
        int value;
        
        Node* left;
       
        Node* right;
        // ����������� �� ��������, ������� ���������������� ��� �������
        explicit Node (int value) { this->value = value; left = nullptr; right = nullptr; }
    };
    // ����������� ������� ������
    void clear(Node* n) {
        if (n)	{
        	// ������� ����� ���������
            clear(n->left);
            n->left = nullptr;
            // ������� ������ ���������
            clear(n->right);
            n->right = nullptr;
            // ������� ������
            delete n;
        }
    }
	// ����������� ����������� ������
    void copy(Node* thisNode, Node* otherNode) {
    	// ����� �� ��������
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
	// ����������� �����
    friend std::ostream& print(std::ostream& os, const Node* n, int level) {
        if (!n) {
            return os;
        }
        // ����������� ��������� � ����������� �� �������
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
	// ���������� ������ (����������� �������)
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
    // ��� �� ����� ������������ (����������� ��������)
    void isAllPositive(Node* n, bool& res) {
    	// ������ ���������
        if (!n) {
            return;
        }
        
        if (n->value <= 0) {
            res = false;
            return;
        }
        // �������� �����������
        isAllPositive(n->left, res);
        isAllPositive(n->right, res);
    }
    // �������� ���� �������
    void deleteAllLeafs(Node* n) {
        if (!n) {
            return;
        }
        // ���� ������ ���� ������� � �� �������� ������
        if (n->right && !(n->right->left) && !(n->right->left)) {
           delete n->right;
		   n->right = nullptr;
        } 
		else {
            deleteAllLeafs(n->right);
        }
        // ����������� ��� ������ ���������
        if (n->left && !(n->left->right) && !(n->left->left)) {
            delete n->left;
            n->left = nullptr;
        } 
		else {
            deleteAllLeafs(n->left);
        }
    }
    // ���������� �������� ��������
    void average(Node* n, int& sum, int& count) {
        if (!n) {
            return;
        }
        // ����������� ����� �����
        sum += n->value;
        ++count;
        // ���������� ������� � �����������
        average(n->left, sum, count);
        average(n->right, sum, count);
    }

	// ������ ������
    Node* root;
public:
	// ����������� �� ���������
    BinaryTree() { root = nullptr; }
    // ����������� �����������
	BinaryTree(const BinaryTree& other) {
        if (this != &other) {
            root = new Node(other.root->value);
            copy(root, other.root);
        }
    }
    // ����������� �����������
    BinaryTree(BinaryTree&& other) noexcept {
        if (this != &other) {
            root = other.root;
            other.root = nullptr;
        }
    }
    // ����������
    ~BinaryTree() {
        clear();
    }
    // �������� ������������
    BinaryTree& operator=(const BinaryTree& right) {
        if (this != &right) {
        	// ������� ������� ������
            clear();
            // ������ ������ �����
            root = new Node(right.root->value);
            copy(root, right.root);
            return *this;
        }
    }
    // �������� �����������
    BinaryTree& operator=(BinaryTree&& right) noexcept {
        if (this != &right) {
        	// ������� ������� ������
        	clear();
            root = right.root;
            right.root = nullptr;
            return *this;
        }
    }
    // �������� ������
    friend std::ostream& operator<<(std::ostream& os, const BinaryTree& tree) {
    	// ����� ����������� ������� ������ �� �����
        return print(os, tree.root, 0);
    }
    // ������� ������
    void clear() {
        clear(this->root);
        root = nullptr;
    }
    // ���������� ��������
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
        // ������������ �� �������
        for (auto &&i : way) {
            if (pointer == nullptr) {
                throw "Can't put anything here";
            }
            // �������� ��������� �� ���������� �������
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
    // ���������� ������
    int evenCount() {
        int res = 0;
        evenCount(root, res);
        return res;
    }
    // ���������� �������������
    bool isAllPositive() {
        if (!root)
            return true;
        bool res = true;
        isAllPositive(this->root, res);
        return res;
    }
    // �������� ���� �������
    void deleteAllLeafs() {
        deleteAllLeafs(root);
    }
    // ���������� �������� ��������
    double average() {
        if (!root)
            return 0;
        int sum = 0;
        int count = 0;
        average(root, sum, count);
        return (double) sum / (double) count;
    }
    // ����� ��������
    std::vector<bool> find(int x) {
    	// �������������� ������
        std::vector<bool> res = std::vector<bool>();
        // ��������������� ���� � �����������
        std::stack<Node*> way = std::stack<Node*>();
        if (!root)
            return res;
        Node* pointer = root;
        while (pointer != nullptr && pointer->value != x) {
        	// ����� � ����� �����
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
            // ����� � ������ �����
            while (pointer != nullptr) {
                if (pointer->value == x) {
                    return res;
                }
                way.push(pointer);
                res.push_back(true);
                pointer = pointer->right;
            }
            // ����������� �� ����, �� �������� ������ � ������ �����
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
