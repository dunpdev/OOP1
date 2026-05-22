#include <iostream>
#include <string>
using namespace std;

// ===== OSNOVNA SABLONSKА FUNKCIJA =====
// Template - zamenjuje T sa bilo kojim tipom
template <typename T>
T maksimum(T a, T b) {
    return (a > b) ? a : b;
}

template <typename T>
T minimum(T a, T b) {
    return (a < b) ? a : b;
}

// ===== ZAMENA VREDNOSTI =====
template <typename T>
void zameni(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

// ===== ISPIS NIZA =====
template <typename T>
void ispisNiz(T niz[], int velicina) {
    cout << "[ ";
    for (int i = 0; i < velicina; i++) {
        cout << niz[i];
        if (i < velicina - 1) cout << ", ";
    }
    cout << " ]" << endl;
}

// ===== SORTIRANJE NIZA =====
template <typename T>
void sortiraj(T niz[], int velicina) {
    for (int i = 0; i < velicina - 1; i++) {
        for (int j = 0; j < velicina - i - 1; j++) {
            if (niz[j] > niz[j + 1]) {
                zameni(niz[j], niz[j + 1]);
            }
        }
    }
}

// ===== ZBRAJANJE ELEMENATA =====
template <typename T>
T zbrajanje(T niz[], int velicina) {
    T zbir = 0;
    for (int i = 0; i < velicina; i++) {
        zbir += niz[i];
    }
    return zbir;
}

// ===== PRONALAZENJE ELEMENTA =====
template <typename T>
int pronadjElement(T niz[], int velicina, T element) {
    for (int i = 0; i < velicina; i++) {
        if (niz[i] == element) {
            return i;
        }
    }
    return -1;  // Nije pronađen
}

int main() {
    cout << "=== PRIMER 1: Sablonskе Funkcije ===" << endl << endl;

    // ===== TESTIRANJE SA INTEGERIMA =====
    cout << "--- Rad sa INTEGER vrednostima ---" << endl;
    int a = 10, b = 20;
    cout << "Maksimum(" << a << ", " << b << ") = " << maksimum(a, b) << endl;
    cout << "Minimum(" << a << ", " << b << ") = " << minimum(a, b) << endl;

    cout << "\nZamena: a=" << a << ", b=" << b;
    zameni(a, b);
    cout << " -> a=" << a << ", b=" << b << endl;

    int niz_int[] = {5, 2, 8, 1, 9, 3};
    cout << "\nNiz pre sortiranja: ";
    ispisNiz(niz_int, 6);
    sortiraj(niz_int, 6);
    cout << "Niz posle sortiranja: ";
    ispisNiz(niz_int, 6);

    cout << "Zbrajanje svih elemenata: " << zbrajanje(niz_int, 6) << endl;

    int indeks = pronadjElement(niz_int, 6, 8);
    if (indeks != -1) {
        cout << "Element 8 je pronaden na poziciji: " << indeks << endl;
    }

    // ===== TESTIRANJE SA DOUBLE =====
    cout << "\n--- Rad sa DOUBLE vrednostima ---" << endl;
    double x = 3.14, y = 2.71;
    cout << "Maksimum(" << x << ", " << y << ") = " << maksimum(x, y) << endl;
    cout << "Minimum(" << x << ", " << y << ") = " << minimum(x, y) << endl;

    double niz_double[] = {3.5, 1.2, 4.8, 2.3, 5.1};
    cout << "\nNiz pre sortiranja: ";
    ispisNiz(niz_double, 5);
    sortiraj(niz_double, 5);
    cout << "Niz posle sortiranja: ";
    ispisNiz(niz_double, 5);
    cout << "Zbrajanje: " << zbrajanje(niz_double, 5) << endl;

    // ===== TESTIRANJE SA STRING =====
    cout << "\n--- Rad sa STRING vrednostima ---" << endl;
    string s1 = "jabuka", s2 = "banana";
    cout << "Maksimum('" << s1 << "', '" << s2 << "') = '"
         << maksimum(s1, s2) << "'" << endl;

    string niz_str[] = {"zebra", "apple", "dog", "cat"};
    cout << "\nNiz stringova pre sortiranja: ";
    ispisNiz(niz_str, 4);
    sortiraj(niz_str, 4);
    cout << "Niz stringova posle sortiranja: ";
    ispisNiz(niz_str, 4);

    indeks = pronadjElement(niz_str, 4, string("dog"));
    if (indeks != -1) {
        cout << "String 'dog' je pronaden na poziciji: " << indeks << endl;
    }

    return 0;
}
