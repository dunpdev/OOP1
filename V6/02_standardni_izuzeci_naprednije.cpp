#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
using namespace std;

// ===== PRIMER 2: STANDARDNI IZUZECI SA KONTEJNERIMA =====

class Bankovni_Racun {
private:
    string broj_racuna;
    double stanje;
    int broj_transakcija;

public:
    Bankovni_Racun(string br, double s)
        : broj_racuna(br), stanje(s), broj_transakcija(0) {
        if (s < 0) {
            throw invalid_argument("Stanje ne sme biti negativno!");
        }
        cout << "Racun " << broj_racuna << " je kreiran sa stanjem " << stanje << " RSD" << endl;
    }

    void uplata(double iznos) {
        if (iznos <= 0) {
            throw invalid_argument("Iznos uplate mora biti pozitivan!");
        }
        stanje += iznos;
        broj_transakcija++;
        cout << "Uplacen iznos: " << iznos << " RSD. Novo stanje: " << stanje << " RSD" << endl;
    }

    void isplata(double iznos) {
        if (iznos <= 0) {
            throw invalid_argument("Iznos isplate mora biti pozitivan!");
        }
        if (iznos > stanje) {
            throw out_of_range("Nedovoljno sredstava! Dostupno: " + to_string(stanje));
        }
        stanje -= iznos;
        broj_transakcija++;
        cout << "Isplacen iznos: " << iznos << " RSD. Novo stanje: " << stanje << " RSD" << endl;
    }

    void promeniRacun(string novi_broj) {
        if (novi_broj.empty()) {
            throw invalid_argument("Broj racuna ne sme biti prazan!");
        }
        if (novi_broj.length() != 18) {
            throw length_error("Broj racuna mora imati 18 karaktera!");
        }
        broj_racuna = novi_broj;
        cout << "Broj racuna je promenjen na: " << broj_racuna << endl;
    }

    string getBrojRacuna() const { return broj_racuna; }
    double getStanje() const { return stanje; }
    int getBrojTransakcija() const { return broj_transakcija; }

    void prikaziInfo() const {
        cout << "\nBroj racuna: " << broj_racuna << endl;
        cout << "Stanje: " << stanje << " RSD" << endl;
        cout << "Broj transakcija: " << broj_transakcija << endl;
    }
};

// ===== UPRAVLJAČ RAČUNA =====
class Upravac_Racuna {
private:
    vector<Bankovni_Racun*> racuni;

public:
    void dodajRacun(Bankovni_Racun* racun) {
        if (racun == nullptr) {
            throw invalid_argument("Racun ne sme biti nullptr!");
        }
        racuni.push_back(racun);
        cout << "Racun dodat u upravljac" << endl;
    }

    Bankovni_Racun* pronajdiRacun(const string& broj) {
        for (auto racun : racuni) {
            if (racun->getBrojRacuna() == broj) {
                return racun;
            }
        }
        throw out_of_range("Racun sa brojem '" + broj + "' nije pronaden!");
    }

    Bankovni_Racun* getRacunNaPoziciji(int indeks) {
        if (indeks < 0 || indeks >= (int)racuni.size()) {
            throw out_of_range("Indeks " + to_string(indeks) + " je van opsega!");
        }
        return racuni[indeks];
    }

    int getBrojRacuna() const {
        return racuni.size();
    }

    void prikaziSveRacune() const {
        cout << "\n=== SVI RACUNI ===" << endl;
        for (size_t i = 0; i < racuni.size(); i++) {
            cout << "\nRacun " << (i + 1) << ":";
            racuni[i]->prikaziInfo();
        }
        cout << "==================" << endl;
    }

    ~Upravac_Racuna() {
        for (auto racun : racuni) {
            delete racun;
        }
    }
};

int main() {
    cout << "=== PRIMER 2: Standardni Izuzeci sa Kontejnerima ===" << endl << endl;

    Upravac_Racuna upravac;

    // ===== KREIRANJE RACUNA =====
    cout << "--- Kreiranje Racuna ---" << endl;
    try {
        Bankovni_Racun* r1 = new Bankovni_Racun("123456789012345678", 10000);
        Bankovni_Racun* r2 = new Bankovni_Racun("987654321098765432", 5000);
        Bankovni_Racun* r3 = new Bankovni_Racun("555555555555555555", 15000);

        // Pokušaj kreiranja sa negativnim stanjem
        // Bankovni_Racun* r4 = new Bankovni_Racun("111111111111111111", -1000);

        upravac.dodajRacun(r1);
        upravac.dodajRacun(r2);
        upravac.dodajRacun(r3);

    } catch (invalid_argument& e) {
        cout << "GRESKA: " << e.what() << endl;
    }

    upravac.prikaziSveRacune();

    // ===== OPERACIJE NA RACUNIMA =====
    cout << "\n--- Operacije na Racunima ---" << endl;
    try {
        Bankovni_Racun* racun = upravac.getRacunNaPoziciji(0);
        racun->uplata(5000);
        racun->isplata(2000);
        racun->isplata(20000); // IZUZETAK - nedovoljno sredstava
    } catch (out_of_range& e) {
        cout << "GRESKA: " << e.what() << endl;
    } catch (invalid_argument& e) {
        cout << "GRESKA: " << e.what() << endl;
    }

    // ===== PRONALAŽENJE RACUNA =====
    cout << "\n--- Pronalazenje Racuna ---" << endl;
    try {
        Bankovni_Racun* r = upravac.pronajdiRacun("987654321098765432");
        cout << "Pronaden racun:" << endl;
        r->prikaziInfo();

        Bankovni_Racun* nepostojeći = upravac.pronajdiRacun("000000000000000000");
    } catch (out_of_range& e) {
        cout << "GRESKA: " << e.what() << endl;
    }

    // ===== POKUŠAJ PRISTUPA RACUNU NA NEVALIDNOJ POZICIJI =====
    cout << "\n--- Pristup Nevalidnoj Poziciji ---" << endl;
    try {
        cout << "Pokušaj pristupa racunu na poziciji 10..." << endl;
        Bankovni_Racun* r = upravac.getRacunNaPoziciji(10);
    } catch (out_of_range& e) {
        cout << "GRESKA: " << e.what() << endl;
    }

    // ===== PROMENICA BROJA RACUNA =====
    cout << "\n--- Promenica Broja Racuna ---" << endl;
    try {
        Bankovni_Racun* r = upravac.getRacunNaPoziciji(1);

        // Pokušaj sa praznim stringom
        r->promeniRacun("");
    } catch (invalid_argument& e) {
        cout << "GRESKA: " << e.what() << endl;
    } catch (length_error& e) {
        cout << "GRESKA: " << e.what() << endl;
    }

    try {
        Bankovni_Racun* r = upravac.getRacunNaPoziciji(1);
        // Pokušaj sa pogešnom dužinom
        r->promeniRacun("123456");
    } catch (length_error& e) {
        cout << "GRESKA: " << e.what() << endl;
    }

    try {
        Bankovni_Racun* r = upravac.getRacunNaPoziciji(1);
        r->promeniRacun("111111111111111111");
        r->prikaziInfo();
    } catch (exception& e) {
        cout << "GRESKA: " << e.what() << endl;
    }

    // ===== KONAČAN PRIKAZ =====
    upravac.prikaziSveRacune();

    cout << "\n--- Kraj programa ---" << endl;
    return 0;
}
