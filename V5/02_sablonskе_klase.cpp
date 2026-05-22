#include <iostream>
#include <string>
using namespace std;

// ===== SABLONSKА KLASA - Generički Niz =====
template <typename T>
class Niz {
private:
    T* elementi;
    int kapacitet;
    int velicina;

public:
    // Konstruktor
    Niz(int kap = 10) : kapacitet(kap), velicina(0) {
        elementi = new T[kapacitet];
        cout << "[Niz] Kreiran niz kapaciteta " << kapacitet << endl;
    }

    // Destruktor
    ~Niz() {
        delete[] elementi;
        cout << "[Niz] Niz je obrisan" << endl;
    }

    // Dodaj element na kraj
    void dodaj(T element) {
        if (velicina < kapacitet) {
            elementi[velicina] = element;
            velicina++;
            cout << "Dodat element. Trenutna velicina: " << velicina << endl;
        } else {
            cout << "GRESKA: Niz je pun!" << endl;
        }
    }

    // Dodaj element na specifičnu poziciju
    void dodajNaPoziciji(int indeks, T element) {
        if (indeks >= 0 && indeks <= velicina && velicina < kapacitet) {
            for (int i = velicina; i > indeks; i--) {
                elementi[i] = elementi[i - 1];
            }
            elementi[indeks] = element;
            velicina++;
            cout << "Element dodat na poziciji " << indeks << endl;
        } else {
            cout << "GRESKA: Nevalidna pozicija!" << endl;
        }
    }

    // Uklanja element sa pozicije
    void ukloniSaPozicije(int indeks) {
        if (indeks >= 0 && indeks < velicina) {
            for (int i = indeks; i < velicina - 1; i++) {
                elementi[i] = elementi[i + 1];
            }
            velicina--;
            cout << "Element sa pozicije " << indeks << " je uklonjen" << endl;
        } else {
            cout << "GRESKA: Nevalidna pozicija!" << endl;
        }
    }

    // Pristup elementu
    T& operator[](int indeks) {
        if (indeks >= 0 && indeks < velicina) {
            return elementi[indeks];
        } else {
            throw out_of_range("Indeks je van opsega!");
        }
    }

    // Get element
    T get(int indeks) const {
        if (indeks >= 0 && indeks < velicina) {
            return elementi[indeks];
        } else {
            throw out_of_range("Indeks je van opsega!");
        }
    }

    // Pronađi element
    int pronadi(T element) const {
        for (int i = 0; i < velicina; i++) {
            if (elementi[i] == element) {
                return i;
            }
        }
        return -1;
    }

    // Sortiraj niz
    void sortiraj() {
        for (int i = 0; i < velicina - 1; i++) {
            for (int j = 0; j < velicina - i - 1; j++) {
                if (elementi[j] > elementi[j + 1]) {
                    T temp = elementi[j];
                    elementi[j] = elementi[j + 1];
                    elementi[j + 1] = temp;
                }
            }
        }
        cout << "Niz je sortiran!" << endl;
    }

    // Prikaži sve elemente
    void prikaziSve() const {
        cout << "[ ";
        for (int i = 0; i < velicina; i++) {
            cout << elementi[i];
            if (i < velicina - 1) cout << ", ";
        }
        cout << " ]" << endl;
    }

    // Inspektori
    int getVelicina() const { return velicina; }
    int getKapacitet() const { return kapacitet; }
    bool jePrazan() const { return velicina == 0; }
    bool jePun() const { return velicina == kapacitet; }

    // Očisti niz
    void ocisti() {
        velicina = 0;
        cout << "Niz je očišćen" << endl;
    }
};

int main() {
    cout << "=== PRIMER 2: Sablonskе Klase ===" << endl << endl;

    // ===== NIZ INTEGERA =====
    cout << "--- Rad sa nizom INTEGER vrednosti ---" << endl;
    Niz<int> niz_int(10);

    niz_int.dodaj(5);
    niz_int.dodaj(3);
    niz_int.dodaj(7);
    niz_int.dodaj(1);
    niz_int.dodaj(9);

    cout << "Niz: ";
    niz_int.prikaziSve();
    cout << "Velicina: " << niz_int.getVelicina() << ", Kapacitet: " << niz_int.getKapacitet() << endl;

    cout << "\nSortiranje niza..." << endl;
    niz_int.sortiraj();
    cout << "Sortirani niz: ";
    niz_int.prikaziSve();

    cout << "\nElement na indeksu 2: " << niz_int[2] << endl;
    int indeks = niz_int.pronadi(7);
    cout << "Pozicija broja 7: " << indeks << endl;

    cout << "\nDodavanje elementa 4 na poziciju 2..." << endl;
    niz_int.dodajNaPoziciji(2, 4);
    niz_int.prikaziSve();

    cout << "\nUklanjanje elementa sa pozicije 0..." << endl;
    niz_int.ukloniSaPozicije(0);
    niz_int.prikaziSve();

    // ===== NIZ DOUBLE =====
    cout << "\n--- Rad sa nizom DOUBLE vrednosti ---" << endl;
    Niz<double> niz_double(5);

    niz_double.dodaj(3.14);
    niz_double.dodaj(2.71);
    niz_double.dodaj(1.41);
    niz_double.dodaj(1.73);

    cout << "Niz: ";
    niz_double.prikaziSve();
    cout << "Da li je niz pun? " << (niz_double.jePun() ? "DA" : "NE") << endl;

    niz_double.sortiraj();
    cout << "Sortirani niz: ";
    niz_double.prikaziSve();

    // ===== NIZ STRINGOVA =====
    cout << "\n--- Rad sa nizom STRING vrednosti ---" << endl;
    Niz<string> niz_str(6);

    niz_str.dodaj("mjauca");
    niz_str.dodaj("pas");
    niz_str.dodaj("ptica");
    niz_str.dodaj("zaba");

    cout << "Niz: ";
    niz_str.prikaziSve();

    niz_str.sortiraj();
    cout << "Sortirani niz: ";
    niz_str.prikaziSve();

    indeks = niz_str.pronadi("pas");
    cout << "Pozicija 'pas': " << indeks << endl;

    cout << "\nDodavanje 'kornjaca' na poziciju 1..." << endl;
    niz_str.dodajNaPoziciji(1, "kornjaca");
    niz_str.prikaziSve();

    cout << "\nOčistka niza stringova..." << endl;
    niz_str.ocisti();
    cout << "Niz je prazан? " << (niz_str.jePrazan() ? "DA" : "NE") << endl;

    return 0;
}
