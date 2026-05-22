#include <iostream>
#include <string>
using namespace std;

class BankovniNalog {
private:
    string brojNaloga;
    double stanje;
    string vlasnik;
    static int brojNaloga_brojac;

public:
    // Konstruktor
    BankovniNalog(string vlasnik, double pocetnoStanje)
        : vlasnik(vlasnik), stanje(pocetnoStanje) {
        brojNaloga_brojac++;
        brojNaloga = "NAL-" + to_string(brojNaloga_brojac);
        cout << "Otvoren nalog: " << brojNaloga << " za " << vlasnik << endl;
    }

    // ===== INSPEKTORI (GETTERS) =====
    string getBrojNaloga() const {
        return brojNaloga;
    }

    string getVlasnik() const {
        return vlasnik;
    }

    double getStanje() const {
        return stanje;
    }

    // ===== MUTATORI (SETTERS) =====
    void setVlasnik(string novoIme) {
        if (novoIme.length() > 0) {
            vlasnik = novoIme;
            cout << "Vlasnik promenjen na: " << vlasnik << endl;
        } else {
            cout << "GRESKA: Ime ne sme biti prazno!" << endl;
        }
    }

    void uplata(double iznos) {
        if (iznos > 0) {
            stanje += iznos;
            cout << "Uplacen iznos: " << iznos << " RSD. Novo stanje: " << stanje << " RSD" << endl;
        } else {
            cout << "GRESKA: Iznos mora biti pozitivan!" << endl;
        }
    }

    void isplata(double iznos) {
        if (iznos > 0 && iznos <= stanje) {
            stanje -= iznos;
            cout << "Isplacen iznos: " << iznos << " RSD. Novo stanje: " << stanje << " RSD" << endl;
        } else if (iznos > stanje) {
            cout << "GRESKA: Nedovoljno sredstava! Dostupno: " << stanje << " RSD" << endl;
        } else {
            cout << "GRESKA: Iznos mora biti pozitivan!" << endl;
        }
    }

    // Statička metoda
    static int getUkupnoNaloga() {
        return brojNaloga_brojac;
    }

    void prikaziInformacije() const {
        cout << "\n--- NALOG ---" << endl;
        cout << "Broj: " << brojNaloga << endl;
        cout << "Vlasnik: " << vlasnik << endl;
        cout << "Stanje: " << stanje << " RSD" << endl;
        cout << "----------" << endl;
    }
};

// Inicijalizacija statičke varijable
int BankovniNalog::brojNaloga_brojac = 0;

int main() {
    cout << "=== PRIMER 1: Inspektori i Mutatori ===" << endl << endl;

    BankovniNalog nalog1("Petar Petrovic", 10000);
    BankovniNalog nalog2("Ana Anic", 5000);

    nalog1.prikaziInformacije();

    cout << "\nOperacije na nalogu 1:" << endl;
    nalog1.uplata(5000);
    nalog1.isplata(3000);
    nalog1.isplata(50000); // Greška - nedovoljno sredstava

    cout << "\nPromjena vlasnika:" << endl;
    nalog1.setVlasnik("Petar Markovic");

    nalog1.prikaziInformacije();

    cout << "\nStaticke informacije:" << endl;
    cout << "Ukupno naloga u banci: " << BankovniNalog::getUkupnoNaloga() << endl;

    return 0;
}
