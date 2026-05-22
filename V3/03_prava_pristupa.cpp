#include <iostream>
#include <string>
using namespace std;

class Zaposlenik {
private:
    // PRIVATNI ČLANOVI - dostupni samo unutar klase
    string lozinka;
    double plata;
    int brZaposlenika;

protected:
    // ZAŠTITENI ČLANOVI - dostupni u klasi i u izvedenim klasama
    string departman;

public:
    // JAVNI ČLANOVI - dostupni svima
    string ime;
    string prezime;

    // Konstruktor
    Zaposlenik(string i, string p, string d, int br, double pl)
        : ime(i), prezime(p), departman(d), brZaposlenika(br), plata(pl) {
        lozinka = "sif123"; // Početna lozinka
        cout << "Zaposlenik " << ime << " " << prezime << " je zaposlен" << endl;
    }

    // ===== JAVNE METODE =====
    // Mogu biti pozvane od bilo koga
    void prikaziJavneInfo() {
        cout << "Ime: " << ime << " " << prezime << endl;
        cout << "Departman: " << departman << endl;
    }

    // ===== INSPEKTORI ZA PRIVATNE ČLANOVE =====
    string getIme() const {
        return ime;
    }

    int getBrZaposlenika() const {
        return brZaposlenika;
    }

    double getPlata() const {
        return plata;
    }

    // ===== MUTATORI ZA PRIVATNE ČLANOVE =====
    void setPlata(double novaPlata) {
        if (novaPlata > 0) {
            plata = novaPlata;
            cout << "Plata azurirana na: " << plata << " RSD" << endl;
        } else {
            cout << "GRESKA: Plata mora biti pozitivna!" << endl;
        }
    }

    // Promenici lozinke sa validacijom
    void setLozinka(string staraLozinka, string novaLozinka) {
        if (staraLozinka == lozinka) {
            if (novaLozinka.length() >= 6) {
                lozinka = novaLozinka;
                cout << "Lozinka je promenjena!" << endl;
            } else {
                cout << "GRESKA: Lozinka mora imati bar 6 karaktera!" << endl;
            }
        } else {
            cout << "GRESKA: Stara lozinka je pogrešna!" << endl;
        }
    }

    // Privatna metoda - može se pozvati samo iz ove klase
    void prikaziSveInfo() {
        cout << "\n=== SVE INFORMACIJE (PRIVATNO) ===" << endl;
        cout << "Ime: " << ime << " " << prezime << endl;
        cout << "Broj zaposlenika: " << brZaposlenika << endl;
        cout << "Departman: " << departman << endl;
        cout << "Plata: " << plata << " RSD" << endl;
        cout << "Lozinka: " << lozinka << endl; // Pristup privatnom članu
        cout << "===================================" << endl;
    }

    // Javna metoda koja poziva privatnu
    void prijaviSeNaSystem() {
        cout << "Zaposlenik " << ime << " se prijavljuje..." << endl;
        prikaziSveInfo();
    }
};

int main() {
    cout << "=== PRIMER 3: Prava Pristupa ===" << endl << endl;

    Zaposlenik z1("Marko", "Markovic", "IT", 1001, 50000);

    cout << "\n--- Pristup JAVNIM članovima ---" << endl;
    cout << "Ime: " << z1.ime << endl;
    cout << "Prezime: " << z1.prezime << endl;
    // cout << z1.lozinka; // GRESKA - privatno!

    cout << "\n--- Pristup preko INSPEKTORA ---" << endl;
    cout << "Broj zaposlenika: " << z1.getBrZaposlenika() << endl;
    cout << "Plata: " << z1.getPlata() << " RSD" << endl;

    cout << "\n--- Modifikacija preko MUTATORA ---" << endl;
    z1.setPlata(55000);
    z1.setPlata(-1000); // Greška - validacija

    cout << "\n--- Promenica lozinke ---" << endl;
    z1.setLozinka("pogreska", "nova1234"); // Greška
    z1.setLozinka("sif123", "novaLoz123"); // Uspešno
    z1.setLozinka("sif123", "s12"); // Greška - kratka

    cout << "\n--- Javne metode ---" << endl;
    z1.prikaziJavneInfo();

    cout << "\n--- Prijava na sistem (pristup privatnim podacima) ---" << endl;
    z1.prijaviSeNaSystem();

    return 0;
}
