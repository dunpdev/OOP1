#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

// ===== PRIMER 1: VECTOR - DINAMIČKI NIZ =====

class Proizvod {
private:
    int id;
    string naziv;
    double cena;
    int kolicina;

public:
    Proizvod(int i, const string& n, double c, int k)
        : id(i), naziv(n), cena(c), kolicina(k) {}

    int getId() const { return id; }
    string getNaziv() const { return naziv; }
    double getCena() const { return cena; }
    int getKolicina() const { return kolicina; }
    double getUkupno() const { return cena * kolicina; }

    void prikaziInfo() const {
        cout << "ID: " << id << " | " << naziv
             << " | " << cena << " RSD × " << kolicina
             << " = " << getUkupno() << " RSD" << endl;
    }

    void postaviKolicinu(int k) { kolicina = k; }
    void dodajKolicinu(int k) { kolicina += k; }
    bool uzmiKolicinu(int k) {
        if (k <= kolicina) {
            kolicina -= k;
            return true;
        }
        return false;
    }
};

class Skladiste {
private:
    vector<Proizvod> proizvodi;

public:
    // ===== DODAVANJE =====
    void dodajProizvod(const Proizvod& p) {
        proizvodi.push_back(p);
        cout << "Dodat proizvod: " << p.getNaziv() << endl;
    }

    // ===== PRONALAŽENJE =====
    Proizvod* pronajdiProizvod(int id) {
        auto it = find_if(proizvodi.begin(), proizvodi.end(),
                         [id](const Proizvod& p) { return p.getId() == id; });
        return (it != proizvodi.end()) ? &(*it) : nullptr;
    }

    // ===== SORTIRANJE =====
    void sortirajPoCeni() {
        sort(proizvodi.begin(), proizvodi.end(),
             [](const Proizvod& a, const Proizvod& b) {
                 return a.getCena() < b.getCena();
             });
    }

    void sortirajPoNazivu() {
        sort(proizvodi.begin(), proizvodi.end(),
             [](const Proizvod& a, const Proizvod& b) {
                 return a.getNaziv() < b.getNaziv();
             });
    }

    // ===== FILTRIRANJE =====
    vector<Proizvod> pronajdiJeftine(double max_cena) {
        vector<Proizvod> rezultat;
        copy_if(proizvodi.begin(), proizvodi.end(),
                back_inserter(rezultat),
                [max_cena](const Proizvod& p) { return p.getCena() <= max_cena; });
        return rezultat;
    }

    // ===== STATISTIKA =====
    double ukupnaVrednostSkladsita() const {
        return accumulate(proizvodi.begin(), proizvodi.end(), 0.0,
                         [](double suma, const Proizvod& p) {
                             return suma + p.getUkupno();
                         });
    }

    int ukupnaKolicina() const {
        return accumulate(proizvodi.begin(), proizvodi.end(), 0,
                         [](int suma, const Proizvod& p) {
                             return suma + p.getKolicina();
                         });
    }

    // ===== PRIKAZ =====
    void prikaziSveProizvode() const {
        if (proizvodi.empty()) {
            cout << "Skladiste je prazno!" << endl;
            return;
        }
        cout << "\n=== PROIZVODI U SKLADISTU ===" << endl;
        for (const auto& p : proizvodi) {
            p.prikaziInfo();
        }
        cout << "================================" << endl;
    }

    int getBrojProizvoda() const { return proizvodi.size(); }
    bool jePrazno() const { return proizvodi.empty(); }
};

int main() {
    cout << "=== PRIMER 1: VECTOR - Skladiste Proizvoda ===" << endl << endl;

    Skladiste skladiste;

    // ===== DODAVANJE PROIZVODA =====
    cout << "--- Dodavanje Proizvoda ---" << endl;
    skladiste.dodajProizvod(Proizvod(1, "Laptop", 80000, 5));
    skladiste.dodajProizvod(Proizvod(2, "Monitor", 15000, 12));
    skladiste.dodajProizvod(Proizvod(3, "Miš", 1500, 50));
    skladiste.dodajProizvod(Proizvod(4, "Tastatura", 3000, 30));
    skladiste.dodajProizvod(Proizvod(5, "Slušalice", 5000, 20));

    skladiste.prikaziSveProizvode();

    // ===== PRONALAŽENJE =====
    cout << "\n--- Pronalaženje Proizvoda ---" << endl;
    Proizvod* p = skladiste.pronajdiProizvod(3);
    if (p) {
        cout << "Pronaden proizvod:" << endl;
        p->prikaziInfo();
    }

    // ===== SORTIRANJE PO CENI =====
    cout << "\n--- Sortiranje po Ceni (od najmanje) ---" << endl;
    skladiste.sortirajPoCeni();
    skladiste.prikaziSveProizvode();

    // ===== SORTIRANJE PO NAZIVU =====
    cout << "\n--- Sortiranje po Nazivu ---" << endl;
    skladiste.sortirajPoNazivu();
    skladiste.prikaziSveProizvode();

    // ===== FILTRIRANJE - JEFTINI PROIZVODI =====
    cout << "\n--- Proizvodi Manji od 5000 RSD ---" << endl;
    vector<Proizvod> jeftini = skladiste.pronajdiJeftine(5000);
    cout << "Pronađeno: " << jeftini.size() << " proizvoda" << endl;
    for (const auto& p : jeftini) {
        p.prikaziInfo();
    }

    // ===== STATISTIKA =====
    cout << "\n--- Statistika ---" << endl;
    cout << "Broj proizvoda: " << skladiste.getBrojProizvoda() << endl;
    cout << "Ukupna kolicina: " << skladiste.ukupnaKolicina() << " komada" << endl;
    cout << "Ukupna vrednost skladista: " << skladiste.ukupnaVrednostSkladsita() << " RSD" << endl;

    // ===== MODIFIKACIJA =====
    cout << "\n--- Modifikacija Kolicina ---" << endl;
    p = skladiste.pronajdiProizvod(2);
    if (p) {
        cout << "Miš pre: ";
        p->prikaziInfo();
        if (p->uzmiKolicinu(10)) {
            cout << "Prodato 10 komada" << endl;
        }
        cout << "Miš posle: ";
        p->prikaziInfo();
    }

    cout << "\n--- Finalna vrednost skladista ---" << endl;
    cout << "Ukupna vrednost: " << skladiste.ukupnaVrednostSkladsita() << " RSD" << endl;

    return 0;
}
