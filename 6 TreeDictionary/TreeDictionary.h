#ifndef TREE_DICTIONARY_H
#define TREE_DICTIONARY_H

#include <cstring>
#include <iostream>

class TreeDictionary {
private:
	// ���� ������
	struct Node {
		char* word;
		unsigned count;
		Node* left;
		Node* right;
		Node(char* w) { word = w; left = right = 0; count = 1; }
		Node(char* w, unsigned count) { word = w; left = right = 0; this->count = count; }
	};
	// ������� ��������� ����������� �������
	void clear(Node* n) {
        if (n)	{
            clear(n->left);
            n->left = nullptr;
            clear(n->right);
            n->right = nullptr;
            delete n;
        }
    }
	// ����������� ���������� ����������� �������
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
    // ����������� ����� ���� � ���������� �������
	friend std::ostream& print(std::ostream& os, const Node* n) {
	    if (!n) {
	        return os;
	    }
	    // ������� ����� ���������
	    print(os, n->left);
	    // ������� ������� �������
	    os << n->word << " " << n->count << std::endl;
	    // ������� ������ ���������
	    print(os, n->right);
	    return os;
	}
	// ������� ��������
	Node* insert(Node* p, char* w) {
		// ���� ���� ����, ������ �����
		if (!p) {
			return new Node(w);
		}
		// ���� ������� ����� "������" ���������, ��� � ����� ���������
		if (strcmp(w, p->word) < 0)
			p->left = insert(p->left, w);
		// ���� ������ - � ������
		else if (strcmp(w, p->word) > 0)
			p->right = insert(p->right, w);
		// ���� ��������� - ���������� 1 � ����������
		else {
			p->count++;
		}
		return p;
	}
	// �������� ��������
	Node* remove(Node* p, char* w) {
		// ������� ������
		if (!p) return nullptr;
		// ���� �������� ����� ������ �������� - ��� � ����� ���������
		if (strcmp(w, p->word) < 0)
			p->left = remove(p->left, w);
		// ���� ������ - � ������
		else if (strcmp(w, p->word) > 0)
			p->right = remove(p->right, w);	
		// ���� ���������
		else {
			// ���� ���������� > 1, �������� 1
			if (p->count > 1) {
				p->count--;
			}
			// ����� ������� ����
			else {
				// ���������� �������
				Node* q = p->left;
				Node* r = p->right;
				// ������� ����
				delete p;
				p = nullptr;
				// ���� �� ������ ������� ��� - ���������� p = nullptr
				if (!r && !q) return p;
				// ���� ��� ������ - ���������� �������
				if (!r) return q;
				if (!q) return r;
				// ���� ���� ��� - ������ ������ ������� ����� �������� ������� � ���������� �������
				r->left = q;
				return r;
			}
		}
	}
	// ����� ��������
	unsigned find(Node* p, char* w) {
		if (!p) return 0;
		if (strcmp(w, p->word) < 0)
			return find(p->left, w);
		if (strcmp(w, p->word) > 0)
			return find(p->right, w);	
		return p->count;
	}
	// ������� ���������� ����
	void wordCount(Node* p, unsigned& count) {
		if (!p) {
			return;
		}
		count += p->count;
		wordCount(p->left, count);
		wordCount(p->right, count);
	}
	// ������ ������
	Node* root;
public:
	// �����������
	TreeDictionary() { root = nullptr; }
	// ����������� �����������
    TreeDictionary(const TreeDictionary& other) {
        if (this != &other) {
            root = new Node(other.root->word, other.root->count);
            copy(root, other.root);
        }
    }
    // ����������� �����������
    TreeDictionary(TreeDictionary&& other) noexcept {
        if (this != &other) {
            root = other.root;
            other.root = nullptr;
        }
    }
    // ����������
    ~TreeDictionary() {
        clear();
    }
    // �������� ������������
    TreeDictionary& operator=(const TreeDictionary& right) {
        if (this != &right) {
            clear();
            root = new Node(right.root->word, right.root->count);
            copy(root, right.root);
            return *this;
        }
    }
    // �������� �����������
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
