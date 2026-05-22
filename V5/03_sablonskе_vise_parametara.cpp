#include <iostream>
#include <string>
using namespace std;

// ===== TEMPLATE CLASS WITH TWO TYPE PARAMETERS =====
template <typename K, typename V>
class Par {
private:
    K kljuc;
    V vrednost;

public:
    // Constructor
    Par(K k, V v) : kljuc(k), vrednost(v) {
        cout << "Par je kreiran" << endl;
    }

    // Getters
    K getKljuc() const { return kljuc; }
    V getVrednost() const { return vrednost; }

    // Setters
    void setVrednost(V nova_vrednost) {
        vrednost = nova_vrednost;
    }

    // Display
    void prikaziPar() const {
        cout << "Kljuc: " << kljuc << " => Vrednost: " << vrednost << endl;
    }
};

// ===== TEMPLATE CLASS - SIMPLE MAP =====
template <typename K, typename V>
class Mapa {
private:
    struct Stavka {
        K kljuc;
        V vrednost;
    };

    Stavka* stavke;
    int kapacitet;
    int velicina;

public:
    // Constructor
    Mapa(int kap = 10) : kapacitet(kap), velicina(0) {
        stavke = new Stavka[kapacitet];
        cout << "Mapa je kreirana sa kapacitetom " << kapacitet << endl;
    }

    // Destructor
    ~Mapa() {
        delete[] stavke;
        cout << "Mapa je obrisana" << endl;
    }

    // Add key-value pair
    void dodaj(K kljuc, V vrednost) {
        // Check if key already exists
        for (int i = 0; i < velicina; i++) {
            if (stavke[i].kljuc == kljuc) {
                stavke[i].vrednost = vrednost;
                cout << "Vrednost za kljuc '" << kljuc << "' je azurirana" << endl;
                return;
            }
        }

        // Add new pair
        if (velicina < kapacitet) {
            stavke[velicina].kljuc = kljuc;
            stavke[velicina].vrednost = vrednost;
            velicina++;
            cout << "Dodan par: " << kljuc << " => " << vrednost << endl;
        } else {
            cout << "GRESKA: Mapa je puna!" << endl;
        }
    }

    // Find value by key
    V pronadi(K kljuc) const {
        for (int i = 0; i < velicina; i++) {
            if (stavke[i].kljuc == kljuc) {
                return stavke[i].vrednost;
            }
        }
        throw out_of_range("Kljuc nije pronaden!");
    }

    // Check if key exists
    bool sadrzi(K kljuc) const {
        for (int i = 0; i < velicina; i++) {
            if (stavke[i].kljuc == kljuc) {
                return true;
            }
        }
        return false;
    }

    // Remove by key
    void ukloni(K kljuc) {
        for (int i = 0; i < velicina; i++) {
            if (stavke[i].kljuc == kljuc) {
                for (int j = i; j < velicina - 1; j++) {
                    stavke[j] = stavke[j + 1];
                }
                velicina--;
                cout << "Kljuc '" << kljuc << "' je uklonjen" << endl;
                return;
            }
        }
        cout << "GRESKA: Kljuc nije pronaden!" << endl;
    }

    // Display all pairs
    void prikaziSve() const {
        cout << "\n--- Sadrzaj mape ---" << endl;
        for (int i = 0; i < velicina; i++) {
            cout << "  " << stavke[i].kljuc << " => " << stavke[i].vrednost << endl;
        }
        cout << "Broj stavki: " << velicina << endl;
    }

    // Getters
    int getVelicina() const { return velicina; }
    bool jePrazan() const { return velicina == 0; }
};

// ===== TEMPLATE CLASS - STACK =====
template <typename T>
class Stack {
private:
    T* elementi;
    int kapacitet;
    int vrh;

public:
    Stack(int kap = 10) : kapacitet(kap), vrh(-1) {
        elementi = new T[kapacitet];
        cout << "Stack je kreiran" << endl;
    }

    ~Stack() {
        delete[] elementi;
        cout << "Stack je obrisan" << endl;
    }

    // Push - add to top
    void push(T element) {
        if (vrh < kapacitet - 1) {
            elementi[++vrh] = element;
            cout << "Push: " << element << endl;
        } else {
            cout << "GRESKA: Stack je pun!" << endl;
        }
    }

    // Pop - remove from top
    T pop() {
        if (!jePrazan()) {
            cout << "Pop: " << elementi[vrh] << endl;
            return elementi[vrh--];
        } else {
            throw out_of_range("Stack je prazan!");
        }
    }

    // Peek - look at top without removing
    T peek() const {
        if (!jePrazan()) {
            return elementi[vrh];
        } else {
            throw out_of_range("Stack je prazan!");
        }
    }

    bool jePrazan() const { return vrh == -1; }
    bool jePun() const { return vrh == kapacitet - 1; }
    int getVelicina() const { return vrh + 1; }

    void prikaziSve() const {
        cout << "[ ";
        for (int i = 0; i <= vrh; i++) {
            cout << elementi[i];
            if (i < vrh) cout << ", ";
        }
        cout << " ]" << endl;
    }
};

int main() {
    cout << "=== PRIMER 3: Sablonskе Klase sa Vise Parametara ===" << endl << endl;

    // ===== PAR =====
    cout << "--- Par Kljuc-Vrednost ---" << endl;
    Par<int, string> p1(1, "Marko");
    Par<string, double> p2("cena", 99.99);
    Par<int, int> p3(10, 20);

    p1.prikaziPar();
    p2.prikaziPar();
    p3.prikaziPar();

    // ===== MAPA =====
    cout << "\n--- Jednostavna Mapa ---" << endl;
    Mapa<string, int> telefonska_knjiga;

    telefonska_knjiga.dodaj("Marko", 1001);
    telefonska_knjiga.dodaj("Ana", 1002);
    telefonska_knjiga.dodaj("Petar", 1003);
    telefonska_knjiga.dodaj("Jovana", 1004);

    telefonska_knjiga.prikaziSve();

    cout << "\nPronalazenje:" << endl;
    cout << "Broj za 'Marko': " << telefonska_knjiga.pronadi("Marko") << endl;
    cout << "Broj za 'Ana': " << telefonska_knjiga.pronadi("Ana") << endl;

    cout << "\nProvera da li kljuc postoji:" << endl;
    cout << "Postoji 'Petar'? " << (telefonska_knjiga.sadrzi("Petar") ? "DA" : "NE") << endl;
    cout << "Postoji 'Dusan'? " << (telefonska_knjiga.sadrzi("Dusan") ? "DA" : "NE") << endl;

    cout << "\nAzuriranje vrednosti:" << endl;
    telefonska_knjiga.dodaj("Marko", 2001);
    telefonska_knjiga.prikaziSve();

    cout << "\nUklanjanje:" << endl;
    telefonska_knjiga.ukloni("Ana");
    telefonska_knjiga.prikaziSve();

    // ===== MAPA SA DOUBLE =====
    cout << "\n--- Mapa sa Double vrednostima ---" << endl;
    Mapa<string, double> proizvodi;

    proizvodi.dodaj("Jabuka", 50.0);
    proizvodi.dodaj("Kruska", 75.0);
    proizvodi.dodaj("Narandza", 60.0);

    proizvodi.prikaziSve();

    cout << "Cena 'Jabuke': " << proizvodi.pronadi("Jabuka") << " RSD" << endl;

    // ===== STACK SA INTEGERIMA =====
    cout << "\n--- Stack sa INTEGER vrednostima ---" << endl;
    Stack<int> stack_int;

    stack_int.push(10);
    stack_int.push(20);
    stack_int.push(30);
    stack_int.push(40);

    cout << "Stack: ";
    stack_int.prikaziSve();
    cout << "Vrh: " << stack_int.peek() << endl;
    cout << "Velicina: " << stack_int.getVelicina() << endl;

    cout << "\nIskid (Pop):" << endl;
    stack_int.pop();
    stack_int.pop();
    cout << "Stack posle 2 popa: ";
    stack_int.prikaziSve();

    // ===== STACK SA STRINGOVIMA =====
    cout << "\n--- Stack sa STRING vrednostima ---" << endl;
    Stack<string> stack_str;

    stack_str.push("python");
    stack_str.push("java");
    stack_str.push("cpp");
    stack_str.push("javascript");

    cout << "Stack: ";
    stack_str.prikaziSve();

    cout << "\nIskid svih elementa:" << endl;
    while (!stack_str.jePrazan()) {
        stack_str.pop();
    }
    cout << "Stack je prazan? " << (stack_str.jePrazan() ? "DA" : "NE") << endl;

    return 0;
}
