#include <iostream>
#include <algorithm>

class Heap {
private:
    int* kopiec;    // tablica przechowuj�ca elementy kopca
    int capacity;   // maksymalna pojemno�� kopca
    int size;       // aktualny rozmiar kopca

public:
    Heap(int c);                      // Konstruktor, tworzy pusty kopiec o pojemno�ci c
    bool empty();                     // Sprawdza, czy kopiec jest pusty
    bool full();                      // Sprawdza, czy kopiec jest pe�ny
    int getLeft(int i);               // Zwraca indeks lewego dziecka
    int getRight(int i);              // Zwraca indeks prawego dziecka
    int getParent(int i);             // Zwraca indeks rodzica
    int getSize();                    // Zwraca rozmiar kopca
    void setSize(int s);              // Ustawia rozmiar kopca
    int getValue(int i);              // Zwraca warto�� na pozycji i
    void setValue(int i, int x);      // Ustawia warto�� x na pozycji i
    void bottomUp(int i);             // Przywraca w�asno�� kopca metod� wynurzania
    void topDown(int i);              // Przywraca w�asno�� kopca metod� zatapiania
    void insert(int x);               // Wstawia element x
    void deleteP();                   // Usuwa element z "maksymaln�" warto�ci�
    void del(int i);                  // Usuwa element na pozycji i
    friend std::ostream& operator<<(std::ostream& out, Heap& h);  // Operator wyj�cia
};

// Konstruktor
Heap::Heap(int c) {
    capacity = c;
    size = 0;
    kopiec = new int[capacity];
}

// Metoda sprawdzaj�ca, czy kopiec jest pusty
bool Heap::empty() {
    return size == 0;
}

// Metoda sprawdzaj�ca, czy kopiec jest pe�ny
bool Heap::full() {
    return size == capacity;
}

// Zwraca indeks lewego dziecka
int Heap::getLeft(int i) {
    return 2 * i + 1;
}

// Zwraca indeks prawego dziecka
int Heap::getRight(int i) {
    return 2 * i + 2;
}

// Zwraca indeks rodzica
int Heap::getParent(int i) {
    return (i - 1) / 2;
}

// Zwraca rozmiar kopca
int Heap::getSize() {
    return size;
}

// Ustawia rozmiar kopca
void Heap::setSize(int s) {
    size = s;
}

// Zwraca warto�� na pozycji i
int Heap::getValue(int i) {
    return kopiec[i];
}

// Ustawia warto�� x na pozycji i
void Heap::setValue(int i, int x) {
    kopiec[i] = x;
}

// Metoda wynurzania (bottom-up) - przywraca w�asno�� kopca
void Heap::bottomUp(int i) {
    while (i > 0 && kopiec[getParent(i)] < kopiec[i]) {
        std::swap(kopiec[i], kopiec[getParent(i)]);
        i = getParent(i);
    }
}

// Metoda zatapiania (top-down) - przywraca w�asno�� kopca
void Heap::topDown(int i) {
    int left = getLeft(i);
    int right = getRight(i);
    int largest = i;

    if (left < size && kopiec[left] > kopiec[largest]) {
        largest = left;
    }

    if (right < size && kopiec[right] > kopiec[largest]) {
        largest = right;
    }

    if (largest != i) {
        std::swap(kopiec[i], kopiec[largest]);
        topDown(largest);
    }
}

// Wstawia nowy element do kopca
void Heap::insert(int x) {
    if (full()) {
        std::cout << "Heap is full!" << std::endl;
        return;
    }
    kopiec[size] = x;
    size++;
    bottomUp(size - 1);  // Przywr�cenie w�asno�ci kopca po dodaniu elementu
}

// Usuwa element z "maksymaln�" warto�ci�
void Heap::deleteP() {
    if (empty()) {
        std::cout << "Heap is empty!" << std::endl;
        return;
    }
    kopiec[0] = kopiec[size - 1];
    size--;
    topDown(0);  // Przywr�cenie w�asno�ci kopca po usuni�ciu elementu
}

// Usuwa element na pozycji i
void Heap::del(int i) {
    if (i >= size || i < 0) {
        std::cout << "Invalid index!" << std::endl;
        return;
    }
    kopiec[i] = kopiec[size - 1];
    size--;
    topDown(i);  // Przywr�cenie w�asno�ci kopca po usuni�ciu elementu
}

// Operator wyj�cia
std::ostream& operator<<(std::ostream& out, Heap& h) {
    for (int i = 0; i < h.getSize(); ++i) {
        out << h.getValue(i) << " ";
    }
    return out;
}

// Testy
int main() {
    std::cout << "Zadanie 1 - test\n";

    Heap h(15);
    std::cout << "empty(): " << h.empty() << std::endl;  // Sprawdza, czy kopiec jest pusty
    std::cout << "full(): " << h.full() << std::endl;    // Sprawdza, czy kopiec jest pe�ny

    h.insert(50);
    h.insert(40);
    h.insert(50);
    h.insert(40);
    h.insert(15);
    h.insert(-30);
    h.insert(20);
    h.insert(-12);
    h.insert(11);
    h.insert(10);
    h.insert(9);

    std::cout << "Po wstawieniu element�w: " << h << std::endl;

    h.deleteP();
    std::cout << "Po usuni�ciu maksymalnej warto�ci: " << h << std::endl;

    h.del(2);
    std::cout << "Po usuni�ciu elementu na pozycji 2: " << h << std::endl;

    return 0;
}
