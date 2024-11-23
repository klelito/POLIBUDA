#include <iostream>
using namespace std;
#include <windows.h>
// Definicja klasy Node
class Node {
private:
	int value;
	Node* left;
	Node* right;
	Node* parent;

public:
	Node(int v, Node* l = nullptr, Node* r = nullptr, Node* p = nullptr)
		: value(v), left(l), right(r), parent(p) {}

	int getValue() {
		return value;
	}
	Node* getLeft() {
		return left;
	}
	Node* getRight() {
		return right;
	}
	Node* getParent() {
		return parent;
	}

	void setValue(int v) {
		value = v;
	}
	void setLeft(Node* l) {
		left = l;
	}
	void setRight(Node* r) {
		right = r;
	}
	void setParent(Node* p) {
		parent = p;
	}
};

// Definicja klasy BSTree
class BSTree {
private:
	Node* root;

public:
	BSTree() : root(nullptr) {}

	Node* getRoot() {
		return root;
	}

	bool empty(Node* p) {
		return p == nullptr;
	}

	void inorder(Node* p) {
		if (p == nullptr) return;
		inorder(p->getLeft());
		cout << p->getValue() << " ";
		inorder(p->getRight());
	}

	// Operacja wstawiania
	void insert(int x) {
		if (root == nullptr) {
			root = new Node(x);
		}
		else {
			Node* current = root;
			Node* parent = nullptr;
			while (current != nullptr) {
				parent = current;
				if (x < current->getValue()) {
					current = current->getLeft();
				}
				else {
					current = current->getRight();
				}
			}
			Node* newNode = new Node(x, nullptr, nullptr, parent);
			if (x < parent->getValue()) {
				parent->setLeft(newNode);
			}
			else {
				parent->setRight(newNode);
			}
		}
	}

	// Wyszukiwanie w drzewie
	Node* search(int x) {
		Node* current = root;
		while (current != nullptr && current->getValue() != x) {
			if (x < current->getValue()) {
				current = current->getLeft();
			}
			else {
				current = current->getRight();
			}
		}
		return current;
	}

	// Zwraca minimum w poddrzewie p
	Node* minimum(Node* p) {
		while (p != nullptr && p->getLeft() != nullptr) {
			p = p->getLeft();
		}
		return p;
	}

	// Zwraca maksimum w poddrzewie p
	Node* maximum(Node* p) {
		while (p != nullptr && p->getRight() != nullptr) {
			p = p->getRight();
		}
		return p;
	}

	// Następnik w drzewie p
	Node* successor(Node* p) {
		if (p->getRight() != nullptr) {
			return minimum(p->getRight());
		}
		Node* parent = p->getParent();
		while (parent != nullptr && p == parent->getRight()) {
			p = parent;
			parent = parent->getParent();
		}
		return parent;
	}

	// Poprzednik w drzewie p
	Node* predecessor(Node* p) {
		if (p->getLeft() != nullptr) {
			return maximum(p->getLeft());
		}
		Node* parent = p->getParent();
		while (parent != nullptr && p == parent->getLeft()) {
			p = parent;
			parent = parent->getParent();
		}
		return parent;
	}

	// Usuwanie w drzewie p
	void del(Node* p) {
		if (p == nullptr) return;

		// Jeśli węzeł nie ma dzieci
		if (p->getLeft() == nullptr && p->getRight() == nullptr) {
			if (p->getParent() == nullptr) {
				root = nullptr;
			}
			else if (p == p->getParent()->getLeft()) {
				p->getParent()->setLeft(nullptr);
			}
			else {
				p->getParent()->setRight(nullptr);
			}
			delete p;
		}
		// Jeśli węzeł ma jedno dziecko
		else if (p->getLeft() == nullptr || p->getRight() == nullptr) {
			Node* child = (p->getLeft() != nullptr) ? p->getLeft() : p->getRight();
			if (p->getParent() == nullptr) {
				root = child;
			}
			else if (p == p->getParent()->getLeft()) {
				p->getParent()->setLeft(child);
			}
			else {
				p->getParent()->setRight(child);
			}
			child->setParent(p->getParent());
			delete p;
		}
		// Jeśli węzeł ma dwoje dzieci
		else {
			Node* successorNode = successor(p);
			p->setValue(successorNode->getValue());
			del(successorNode);
		}
	}
};

int main() {
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	cout << "Zadanie 1 - test" << endl;

	BSTree* t = new BSTree();

	// Wstawianie węzłów do drzewa
	t->insert(20);
	t->insert(10);
	t->insert(30);
	t->insert(5);
	t->insert(15);
	t->insert(25);
	t->insert(35);
	t->insert(90);
	t->insert(22);

	// Inorder traversal
	cout << "Inorder: ";
	t->inorder(t->getRoot());
	cout << endl;

	// Wyszukiwanie w drzewie
	Node* foundNode = t->search(15);
	if (foundNode != nullptr) {
		cout << "Znaleziono węzeł o wartości: " << foundNode->getValue() << endl;
	}
	else {
		cout << "Nie znaleziono węzła" << endl;
	}

	// Minimum i Maximum
	cout << "Minimum: " << t->minimum(t->getRoot())->getValue() << endl;
	cout << "Maximum: " << t->maximum(t->getRoot())->getValue() << endl;

	// Następnik i Poprzednik
	Node* successorNode = t->successor(t->search(10));
	if (successorNode != nullptr) {
		cout << "Następnik 10: " << successorNode->getValue() << endl;
	}
	else {
		cout << "Brak następcy dla 10" << endl;
	}

	Node* predecessorNode = t->predecessor(t->search(25));
	if (predecessorNode != nullptr) {
		cout << "Poprzednik 25: " << predecessorNode->getValue() << endl;
	}
	else {
		cout << "Brak poprzednika dla 25" << endl;
	}

	// Usuwanie węzła
	t->del(t->search(15));
	cout << "Po usunięciu węzła 15, inorder: ";
	t->inorder(t->getRoot());
	cout << endl;

	// Test na pustym drzewie
	t->del(t->search(10));
	t->del(t->search(20));
	cout << "Po usunięciu węzłów 10 i 20, inorder: ";
	t->inorder(t->getRoot());
	cout << endl;

	return 0;
}
