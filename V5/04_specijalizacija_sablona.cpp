#include <iostream>
#include <string>
using namespace std;

// ===== OPŠTA SABLONSKА KLASA =====
template <typename T>
class Ispis {
public:
    static void ispis_info(T vrednost) {
        cout << "Osnovna verzija: " << vrednost << endl;
    }
};

// ===== SPECIJALIZACIJA ZA INT =====
template <>
class Ispis<int> {
public:
    static void ispis_info(int vrednost) {
        cout << "[INT] Vrednost: " << vrednost;
        cout << " | Binarni: ";

        // Ispis u binarnom formatu
        for (int i = 31; i >= 0; i--) {
            if ((vrednost >> i) & 1) cout << "1";
            else cout << "0";
        }
        cout << " | Heksadecimalni: 0x" << hex << vrednost << dec << endl;
    }
};

// ===== SPECIJALIZACIJA ZA STRING =====
template <>
class Ispis<string> {
public:
    static void ispis_info(const string& str) {
        cout << "[STRING] '" << str << "'";
        cout << " | Duzina: " << str.length();
        cout << " | Karakteri: ";
        for (size_t i = 0; i < str.length(); i++) {
            cout << str[i] << " ";
        }
        cout << endl;
    }
};

// ===== SPECIJALIZACIJA ZA DOUBLE =====
template <>
class Ispis<double> {
public:
    static void ispis_info(double vrednost) {
        cout << "[DOUBLE] Vrednost: " << vrednost;
        cout << " | Ceo deo: " << (int)vrednost;
        cout << " | Decimalni deo: " << (vrednost - (int)vrednost) << endl;
    }
};

// ===== SABLONSKА FUNKCIJA ZA POREĐENJE =====
template <typename T>
bool veci(T a, T b) {
    cout << "Opšta verzija: poređenje " << a << " sa " << b << endl;
    return a > b;
}

// ===== SPECIJALIZACIJA FUNKCIJE ZA STRING =====
template <>
bool veci<string>(string a, string b) {
    cout << "Specijalizovana verzija: poređenje stringova (leksikografski)" << endl;
    cout << "'" << a << "' > '" << b << "'? " << (a > b ? "DA" : "NE") << endl;
    return a > b;
}

// ===== SABLONSKА KLASA ZA NUMERIČKE OPERACIJE =====
template <typename T>
class Matematika {
public:
    static double stepenovanje(T a, int n) {
        double rezultat = 1;
        for (int i = 0; i < n; i++) {
            rezultat *= a;
        }
        return rezultat;
    }
};

// ===== SPECIJALIZACIJA ZA STRINGOVE - SPECIFIČNI PRIMENA =====
template <>
class Matematika<string> {
public:
    static string stepenovanje(string s, int n) {
        string rezultat = "";
        for (int i = 0; i < n; i++) {
            rezultat += s;
        }
        return rezultat;
    }
};

// ===== SABLONSKА KLASA - SORT SA SPECIJALIZACIJOM =====
template <typename T>
class Sortiranje {
public:
    static void sortiraj(T* niz, int velicina, bool opadajuce = false) {
        cout << "Sortiranje (opšta verzija)" << endl;
        for (int i = 0; i < velicina - 1; i++) {
            for (int j = 0; j < velicina - i - 1; j++) {
                if (opadajuce) {
                    if (niz[j] < niz[j + 1]) {
                        T temp = niz[j];
                        niz[j] = niz[j + 1];
                        niz[j + 1] = temp;
                    }
                } else {
                    if (niz[j] > niz[j + 1]) {
                        T temp = niz[j];
                        niz[j] = niz[j + 1];
                        niz[j + 1] = temp;
                    }
                }
            }
        }
    }

    static void prikaziNiz(T* niz, int velicina) {
        cout << "[ ";
        for (int i = 0; i < velicina; i++) {
            cout << niz[i];
            if (i < velicina - 1) cout << ", ";
        }
        cout << " ]" << endl;
    }
};

// ===== SPECIJALIZACIJA SORTIRANJA ZA STRING =====
template <>
class Sortiranje<string> {
public:
    static void sortiraj(string* niz, int velicina, bool opadajuce = false) {
        cout << "Sortiranje stringova (specijalizovana verzija)" << endl;
        for (int i = 0; i < velicina - 1; i++) {
            for (int j = 0; j < velicina - i - 1; j++) {
                if (opadajuce) {
                    if (niz[j] < niz[j + 1]) {
                        string temp = niz[j];
                        niz[j] = niz[j + 1];
                        niz[j + 1] = temp;
                    }
                } else {
                    if (niz[j] > niz[j + 1]) {
                        string temp = niz[j];
                        niz[j] = niz[j + 1];
                        niz[j + 1] = temp;
                    }
                }
            }
        }
    }

    static void prikaziNiz(string* niz, int velicina) {
        cout << "[ ";
        for (int i = 0; i < velicina; i++) {
            cout << "'" << niz[i] << "'";
            if (i < velicina - 1) cout << ", ";
        }
        cout << " ]" << endl;
    }
};

int main() {
    cout << "=== PRIMER 4: Specijalizacija Sablona ===" << endl << endl;

    // ===== ISPIS SPECIJALIZOVANE KLASE =====
    cout << "--- Ispis sa specijalizacijom ---" << endl;
    Ispis<int>::ispis_info(42);
    Ispis<string>::ispis_info("Sablon");
    Ispis<double>::ispis_info(3.14159);
    Ispis<char>::ispis_info('A');  // Koristi opštu verziju

    // ===== POREĐENJE SA SPECIJALIZACIJOM =====
    cout << "\n--- Poređenje sa specijalizacijom ---" << endl;
    cout << "Poređenje integera:" << endl;
    veci<int>(10, 5);

    cout << "\nPoređenje stringova:" << endl;
    veci<string>("zebra", "apple");

    cout << "\nPoređenje double:" << endl;
    veci<double>(3.14, 2.71);

    // ===== MATEMATIKA SA SPECIJALIZACIJOM =====
    cout << "\n--- Matematika sa specijalizacijom ---" << endl;
    cout << "3 na stepen 4 = " << Matematika<int>::stepenovanje(3, 4) << endl;
    cout << "2.5 na stepen 3 = " << Matematika<double>::stepenovanje(2.5, 3) << endl;

    cout << "\nString stepenovanje (ponavljanje):" << endl;
    cout << "'ABC' x3 = '" << Matematika<string>::stepenovanje("ABC", 3) << "'" << endl;
    cout << "'*' x5 = '" << Matematika<string>::stepenovanje("*", 5) << "'" << endl;

    // ===== SORTIRANJE SA SPECIJALIZACIJOM =====
    cout << "\n--- Sortiranje sa specijalizacijom ---" << endl;

    int niz_int[] = {5, 2, 8, 1, 9};
    cout << "Originalni niz integera: ";
    Sortiranje<int>::prikaziNiz(niz_int, 5);
    Sortiranje<int>::sortiraj(niz_int, 5);
    cout << "Sortirani niz: ";
    Sortiranje<int>::prikaziNiz(niz_int, 5);

    cout << "\nSortirani niz (opadajuce): ";
    Sortiranje<int>::sortiraj(niz_int, 5, true);
    Sortiranje<int>::prikaziNiz(niz_int, 5);

    string niz_str[] = {"zebra", "apple", "dog", "cat", "banana"};
    cout << "\nOriginalni niz stringova: ";
    Sortiranje<string>::prikaziNiz(niz_str, 5);
    Sortiranje<string>::sortiraj(niz_str, 5);
    cout << "Sortirani niz: ";
    Sortiranje<string>::prikaziNiz(niz_str, 5);

    cout << "\nSortirani niz (opadajuce): ";
    Sortiranje<string>::sortiraj(niz_str, 5, true);
    Sortiranje<string>::prikaziNiz(niz_str, 5);

    return 0;
}
