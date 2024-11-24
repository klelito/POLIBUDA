#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Zadanie 1
void print(int* S, int n) {  // wyświetla dane w formie tablicy
    cout << "{ ";
    for (int i = 0; i < n; ++i) {
        cout << S[i];
        if (i < n - 1) {
            cout << ", ";  // Dodajemy przecinek między elementami, jeśli to nie ostatni element
        }
    }
    cout << " }" << endl;
}

void init(int* S, int n) {  // generuje losowe dane
    srand(time(0));  // Inicjalizujemy generator liczb losowych
    for (int i = 0; i < n; ++i) {
        S[i] = rand() % 100;  // Losowe liczby z zakresu 0-99
    }
}

void insertionSort(int* S, int n) {  // Insertion Sort
    for (int i = 1; i < n; ++i) {
        int key = S[i];
        int j = i - 1;
        
        // Przesuwamy elementy S[0..i-1], które są większe od key, o jedno miejsce do przodu
        while (j >= 0 && S[j] > key) {
            S[j + 1] = S[j];
            j = j - 1;
        }
        S[j + 1] = key;
    }
}

void selectionSort(int* S, int n) {  // Selection Sort
    for (int i = 0; i < n - 1; ++i) {
        int minIndex = i;
        
        // Szukamy najmniejszego elementu w pozostałej części tablicy
        for (int j = i + 1; j < n; ++j) {
            if (S[j] < S[minIndex]) {
                minIndex = j;
            }
        }
        
        // Zamieniamy miejscami elementy
        if (minIndex != i) {
            swap(S[i], S[minIndex]);
        }
    }
}

void bubbleSort(int* S, int n) {  // Bubble Sort
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (S[j] > S[j + 1]) {
                // Zamiana elementów
                swap(S[j], S[j + 1]);
            }
        }
    }
}

int main() {
    // Zadanie 1 - test
    cout << "Zadanie 1 - test - sortowanie ..." << endl;
    
    int n = 20;  // przykładowy rozmiar
    int *S = new int[n];
    
    // Generacja losowych danych i wyświetlenie
    init(S, n);
    cout << "Dane przed sortowaniem: ";
    print(S, n);

    // Insertion Sort
    int* S1 = new int[n];
    copy(S, S + n, S1);  // Kopiujemy dane do nowej tablicy
    insertionSort(S1, n);
    cout << "Po Insertion Sort: ";
    print(S1, n);

    // Selection Sort
    int* S2 = new int[n];
    copy(S, S + n, S2);  // Kopiujemy dane do nowej tablicy
    selectionSort(S2, n);
    cout << "Po Selection Sort: ";
    print(S2, n);

    // Bubble Sort
    int* S3 = new int[n];
    copy(S, S + n, S3);  // Kopiujemy dane do nowej tablicy
    bubbleSort(S3, n);
    cout << "Po Bubble Sort: ";
    print(S3, n);

    // Czyszczenie pamięci
    delete[] S;
    delete[] S1;
    delete[] S2;
    delete[] S3;

    return 0;
}
