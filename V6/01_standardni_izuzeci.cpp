#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <cctype>
using namespace std;

// ===== PRIMER 1: STANDARDNI IZUZECI =====

// Funkcija sa deljenje
double deli(double a, double b) {
    if (b == 0) {
        throw invalid_argument("Ne mogu da delim sa nulom!");
    }
    return a / b;
}

// Funkcija sa pristupom nizu
int pristupNizu(int niz[], int velicina, int indeks) {
    if (indeks < 0 || indeks >= velicina) {
        throw out_of_range("Indeks je van opsega niza!");
    }
    return niz[indeks];
}

// Funkcija za konverziju
int konvertujiUInt(const string& str) {
    if (str.empty()) {
        throw invalid_argument("String ne sme biti prazan!");
    }

    for (char c : str) {
        if (!isdigit(c)) {
            throw invalid_argument("String '" + str + "' nije validan broj!");
        }
    }

    return stoi(str);
}

// Funkcija sa more_generalized_catch
void obradi_broj(int broj) {
    if (broj < 0) {
        throw out_of_range("Broj ne sme biti negativan!");
    }
    if (broj == 0) {
        throw logic_error("Broj ne sme biti nula!");
    }
    if (broj > 1000) {
        throw overflow_error("Broj je prevelik!");
    }

    cout << "Broj " << broj << " je validan!" << endl;
}

int main() {
    cout << "=== PRIMER 1: Standardni Izuzeci ===" << endl << endl;

    // ===== PRIMERIO 1: DELJENJE SA NULOM =====
    cout << "--- Deljenje sa Nulom ---" << endl;
    try {
        cout << "10 / 2 = " << deli(10, 2) << endl;
        cout << "10 / 0 = " << deli(10, 0) << endl;  // IZUZETAK!
    } catch (invalid_argument& e) {
        cout << "UHVACEN IZUZETAK: " << e.what() << endl;
    } catch (exception& e) {
        cout << "OPŠTI IZUZETAK: " << e.what() << endl;
    }

    // ===== PRIMER 2: PRISTUP NIZU =====
    cout << "\n--- Pristup Nizu ---" << endl;
    int niz[] = {10, 20, 30, 40, 50};
    int velicina = 5;

    try {
        cout << "Niz[2] = " << pristupNizu(niz, velicina, 2) << endl;
        cout << "Niz[10] = " << pristupNizu(niz, velicina, 10) << endl;  // IZUZETAK!
    } catch (out_of_range& e) {
        cout << "UHVACEN IZUZETAK: " << e.what() << endl;
    }

    // ===== PRIMER 3: KONVERZIJA STRINGA =====
    cout << "\n--- Konverzija Stringa ---" << endl;
    vector<string> stringovi = {"123", "abc", "456", "", "789"};

    for (const auto& str : stringovi) {
        try {
            int broj = konvertujiUInt(str);
            cout << "'" << str << "' -> " << broj << endl;
        } catch (invalid_argument& e) {
            cout << "GRESKA: " << e.what() << endl;
        }
    }

    // ===== PRIMER 4: VISE TIPOVA IZUZETAKA =====
    cout << "\n--- Vise Tipova Izuzetaka ---" << endl;
    vector<int> testni_brojevi = {5, -10, 0, 100, 2000};

    for (int broj : testni_brojevi) {
        try {
            cout << "Proveravao: " << broj << " ... ";
            obradi_broj(broj);
        } catch (out_of_range& e) {
            cout << "OUT_OF_RANGE: " << e.what() << endl;
        } catch (logic_error& e) {
            cout << "LOGIC_ERROR: " << e.what() << endl;
        } catch (overflow_error& e) {
            cout << "OVERFLOW_ERROR: " << e.what() << endl;
        } catch (exception& e) {
            cout << "OPŠTI IZUZETAK: " << e.what() << endl;
        }
    }

    // ===== PRIMER 5: FINALLY SIMULACIJA (sa dodatnim scopeom) =====
    cout << "\n--- Izvršavanje sa Osiguranjem ---" << endl;
    try {
        cout << "Počinje operacija..." << endl;
        throw runtime_error("Nešto je pošlo naopako!");
        cout << "Ova linija se nece izvršiti" << endl;
    } catch (runtime_error& e) {
        cout << "Uhvacen runtime_error: " << e.what() << endl;
    }
    cout << "Program nastavlja posle izuzetka" << endl;

    cout << "\n--- Kraj programa ---" << endl;
    return 0;
}
