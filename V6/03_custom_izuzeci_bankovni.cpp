#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

// ===== BAZNA KLASA ZA IZUZETKE =====
class BankovniIzuzetak : public exception {
protected:
    string poruka;

public:
    BankovniIzuzetak(const string& p) : poruka(p) {
        cout << "[BANKOVNI IZUZETAK] Kreiran sa porukom: " << poruka << endl;
    }

    virtual const char* what() const noexcept override {
        return poruka.c_str();
    }

    virtual void prikaziDetalje() const {
        cout << "Bankovni izuzetak: " << poruka << endl;
    }

    virtual ~BankovniIzuzetak() {}
};

// ===== PRVI CUSTOM IZUZETAK =====
class NedovoljnoSredstavaIzuzetak : public BankovniIzuzetak {
private:
    double dostupno;
    double trazeno;

public:
    NedovoljnoSredstavaIzuzetak(double d, double t)
        : BankovniIzuzetak("Nedovoljno sredstava!"),
          dostupno(d), trazeno(t) {
        poruka += " (Dostupno: " + to_string(dostupno) + ", Traženo: " + to_string(trazeno) + ")";
    }

    double getDostupno() const { return dostupno; }
    double getTrazeno() const { return trazeno; }
    double nedostaje() const { return trazeno - dostupno; }

    void prikaziDetalje() const override {
        cout << "NEDOVOLJNA SREDSTVA:" << endl;
        cout << "  Dostupno: " << dostupno << " RSD" << endl;
        cout << "  Traženo: " << trazeno << " RSD" << endl;
        cout << "  Nedostaje: " << nedostaje() << " RSD" << endl;
    }

    ~NedovoljnoSredstavaIzuzetak() {}
};

// ===== DRUGI CUSTOM IZUZETAK =====
class InvalidanIznos : public BankovniIzuzetak {
private:
    double iznos;
    string tip_operacije;

public:
    InvalidanIznos(double i, const string& tip)
        : BankovniIzuzetak("Invalidan iznos!"),
          iznos(i), tip_operacije(tip) {
        poruka += " (Iznos: " + to_string(iznos) + ", Operacija: " + tip_operacije + ")";
    }

    double getIznos() const { return iznos; }
    string getTipOperacije() const { return tip_operacije; }

    void prikaziDetalje() const override {
        cout << "INVALIDAN IZNOS:" << endl;
        cout << "  Iznos: " << iznos << " RSD" << endl;
        cout << "  Operacija: " << tip_operacije << endl;
        cout << "  Problem: Iznos mora biti pozitivan!" << endl;
    }

    ~InvalidanIznos() {}
};

// ===== KLASA ZA BANKOVNI RACUN =====
class Racun {
private:
    string broj_racuna;
    double stanje;

public:
    Racun(const string& broj, double s)
        : broj_racuna(broj), stanje(s) {
        cout << "Racun " << broj_racuna << " je kreiran" << endl;
    }

    void uplata(double iznos) {
        if (iznos <= 0) {
            throw InvalidanIznos(iznos, "UPLATA");
        }
        stanje += iznos;
        cout << "Uplacen iznos: " << iznos << " RSD. Novo stanje: " << stanje << " RSD" << endl;
    }

    void isplata(double iznos) {
        if (iznos <= 0) {
            throw InvalidanIznos(iznos, "ISPLATA");
        }
        if (iznos > stanje) {
            throw NedovoljnoSredstavaIzuzetak(stanje, iznos);
        }
        stanje -= iznos;
        cout << "Isplacen iznos: " << iznos << " RSD. Novo stanje: " << stanje << " RSD" << endl;
    }

    double getStanje() const { return stanje; }
    string getBroj() const { return broj_racuna; }

    void prikaziInfo() const {
        cout << "Broj: " << broj_racuna << " | Stanje: " << stanje << " RSD" << endl;
    }
};

int main() {
    cout << "=== PRIMER 3: Custom Izuzeci Nasledjeni iz Bazne Klase ===" << endl << endl;

    cout << "--- Kreiranje racuna ---" << endl;
    Racun racun("123456789012345678", 10000);
    racun.prikaziInfo();

    // ===== TEST 1: INVALIDAN IZNOS =====
    cout << "\n--- Test 1: Invalidan Iznos ---" << endl;
    try {
        cout << "Pokušaj uplate sa negativnim iznosom..." << endl;
        racun.uplata(-5000);
    } catch (InvalidanIznos& e) {
        cout << "UHVACEN IZUZETAK:" << endl;
        cout << "what(): " << e.what() << endl;
        e.prikaziDetalje();
    } catch (BankovniIzuzetak& e) {
        cout << "Opšti bankovni izuzetak: " << e.what() << endl;
        e.prikaziDetalje();
    }

    // ===== TEST 2: NEDOVOLJNA SREDSTVA =====
    cout << "\n--- Test 2: Nedovoljna Sredstva ---" << endl;
    try {
        cout << "Pokušaj isplate od 50000 RSD..." << endl;
        racun.isplata(50000);
    } catch (NedovoljnoSredstavaIzuzetak& e) {
        cout << "UHVACEN IZUZETAK:" << endl;
        cout << "what(): " << e.what() << endl;
        e.prikaziDetalje();
        cout << "Nedostaje još: " << e.nedostaje() << " RSD" << endl;
    } catch (BankovniIzuzetak& e) {
        cout << "Opšti bankovni izuzetak: " << e.what() << endl;
        e.prikaziDetalje();
    }

    // ===== TEST 3: VALIDNE OPERACIJE =====
    cout << "\n--- Test 3: Validne Operacije ---" << endl;
    try {
        racun.uplata(5000);
        racun.prikaziInfo();

        racun.isplata(3000);
        racun.prikaziInfo();

        racun.isplata(100); // OK
        racun.prikaziInfo();
    } catch (BankovniIzuzetak& e) {
        cout << "Izuzetak: " << e.what() << endl;
        e.prikaziDetalje();
    }

    // ===== TEST 4: ZERO IZNOS =====
    cout << "\n--- Test 4: Zero Iznos ---" << endl;
    try {
        cout << "Pokušaj uplate od 0 RSD..." << endl;
        racun.uplata(0);
    } catch (InvalidanIznos& e) {
        cout << "UHVACEN IZUZETAK:" << endl;
        e.prikaziDetalje();
        cout << "Tip operacije: " << e.getTipOperacije() << endl;
    } catch (exception& e) {
        cout << "Opšti izuzetak: " << e.what() << endl;
    }

    // ===== TEST 5: PONOVNA ISPLATA NEDOVOLJNIH SREDSTAVA =====
    cout << "\n--- Test 5: Ponovna Isplata Nedovoljnih Sredstava ---" << endl;
    try {
        cout << "Pokušaj isplate od 20000 RSD..." << endl;
        racun.isplata(20000);
    } catch (NedovoljnoSredstavaIzuzetak& e) {
        cout << "UHVACEN IZUZETAK:" << endl;
        cout << "Dostupno: " << e.getDostupno() << " RSD" << endl;
        cout << "Traženo: " << e.getTrazeno() << " RSD" << endl;
        cout << "Može se isplatiti samo: " << (e.getDostupno() - 100) << " RSD (sa rezervom od 100)" << endl;

        try {
            racun.isplata(e.getDostupno() - 100);
            cout << "Druga isplata je uspešna!" << endl;
            racun.prikaziInfo();
        } catch (BankovniIzuzetak& e2) {
            cout << "Druga greška: " << e2.what() << endl;
        }
    } catch (BankovniIzuzetak& e) {
        cout << "Bankovni izuzetak: " << e.what() << endl;
    }

    cout << "\n--- Finalno stanje racuna ---" << endl;
    racun.prikaziInfo();

    return 0;
}
