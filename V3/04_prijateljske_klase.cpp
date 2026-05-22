#include <iostream>
#include <string>
using namespace std;

class Licni_Nalog;  // Predgovora za Licni_Nalog

// Klasa Revizor je prijatelj klase Licni_Nalog
class Revizor {
private:
    string imeRevizora;

public:
    Revizor(string ime) : imeRevizora(ime) {
        cout << "Revizor " << imeRevizora << " je angažovan" << endl;
    }

    // Ova metoda može pristupiti PRIVATNIM članovima od Licni_Nalog
    // jer je Revizor deklarisan kao prijatelj (friend)
    void revidiraj(Licni_Nalog& nalog);

    void prikaziIme() const {
        cout << "Revizor: " << imeRevizora << endl;
    }
};

// ===== GLAVNA KLASA =====
class Licni_Nalog {
private:
    string JMBG;
    double stanje;
    string PIN;
    int brojanjeTransakcija;

    // PRIJATELJ - Revizor može pristupiti privatnim članovima!
    friend class Revizor;
    friend void prikaziFinansijskiIzvestaj(const Licni_Nalog& nalog);

public:
    string vlasnik;

    // Konstruktor
    Licni_Nalog(string vlasnik, string jmbg, double pocetnoStanje)
        : vlasnik(vlasnik), JMBG(jmbg), stanje(pocetnoStanje), PIN("1234") {
        brojanjeTransakcija = 0;
        cout << "Licni nalog " << vlasnik << " je otvoren" << endl;
    }

    // ===== JAVNE METODE =====
    void uplata(double iznos) {
        if (iznos > 0) {
            stanje += iznos;
            brojanjeTransakcija++;
            cout << "Uplacen iznos: " << iznos << " RSD" << endl;
        }
    }

    void isplata(double iznos) {
        if (iznos > 0 && iznos <= stanje) {
            stanje -= iznos;
            brojanjeTransakcija++;
            cout << "Isplacen iznos: " << iznos << " RSD" << endl;
        } else {
            cout << "GRESKA: Nedovoljno sredstava!" << endl;
        }
    }

    double getStanje() const {
        return stanje;
    }

    // Privatna metoda - samo klasa može pozvati
    void loguj(string akcija) {
        cout << "[LOG] " << vlasnik << ": " << akcija << endl;
    }

    void prikaziJavneInfo() const {
        cout << "Vlasnik: " << vlasnik << endl;
        cout << "Stanje: " << stanje << " RSD" << endl;
    }
};

// Implementacija revidirane metode Revizora
void Revizor::revidiraj(Licni_Nalog& nalog) {
    cout << "\n========== REVIZIJA ==========" << endl;
    cout << "Revizor: " << imeRevizora << endl;
    cout << "Vlasnik naloga: " << nalog.vlasnik << endl;

    // Pristupam PRIVATNIM članovima jer je Revizor prijatelj!
    cout << "JMBG (PRIVATNO): " << nalog.JMBG << endl;
    cout << "PIN (PRIVATNO): " << nalog.PIN << endl;
    cout << "Stanje: " << nalog.stanje << " RSD" << endl;
    cout << "Broj transakcija: " << nalog.brojanjeTransakcija << endl;
    cout << "=============================" << endl;
}

// Prijateljska funkcija - može pristupiti privatnim članovima
void prikaziFinansijskiIzvestaj(const Licni_Nalog& nalog) {
    cout << "\n========== FINANSIJSKI IZVESTAJ ==========" << endl;
    cout << "Vlasnik: " << nalog.vlasnik << endl;
    cout << "JMBG: " << nalog.JMBG << " (pristup preko prijateljske funkcije)" << endl;
    cout << "Trenutno stanje: " << nalog.stanje << " RSD" << endl;
    cout << "Broj transakcija: " << nalog.brojanjeTransakcija << endl;
    cout << "========================================" << endl;
}

int main() {
    cout << "=== PRIMER 4: Prijateljske Klase ===" << endl << endl;

    Licni_Nalog nalog("Jovana Jovanovic", "1234567890123", 10000);

    cout << "\n--- Obicne operacije ---" << endl;
    nalog.uplata(5000);
    nalog.isplata(2000);
    nalog.prikaziJavneInfo();

    // Direktan pristup privatnim članovima - NIJE MOGUĆE!
    // cout << nalog.JMBG;     // GRESKA - privatno!
    // cout << nalog.stanje;   // GRESKA - privatno!
    // cout << nalog.PIN;      // GRESKA - privatno!

    cout << "\n--- Revizija (Revizor je prijatelj) ---" << endl;
    Revizor revizor("Dusan Dusanic");
    revizor.revidiraj(nalog); // Revizor može pristupiti privatnim člankama!

    cout << "\n--- Prijateljska funkcija ---" << endl;
    prikaziFinansijskiIzvestaj(nalog); // Funkcija je deklarisana kao prijatelj

    cout << "\n--- Vise operacija ---" << endl;
    nalog.uplata(3000);
    nalog.isplata(1000);

    revizor.revidiraj(nalog); // Revizija nakon novih transakcija

    return 0;
}
