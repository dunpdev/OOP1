#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Forward declaration
class Admin;

class Korisnik {
private:
    string korisnickoIme;
    string lozinka;
    double kredit;
    static int ukupnoKorisnika;
    int IDKorisnika;

    friend class Admin; // Admin može pristupiti privatnim članovima
    friend void prikaziAdminskyIzvestaj(const vector<Korisnik*>& korisnici);

protected:
    string email;

public:
    // Konstruktor
    Korisnik(string korisnicko, string sifra, string mail, double pocetniKredit)
        : korisnickoIme(korisnicko), lozinka(sifra), email(mail), kredit(pocetniKredit) {
        ukupnoKorisnika++;
        IDKorisnika = ukupnoKorisnika;
        cout << "[SISTEM] Korisnik '" << korisnickoIme << "' je registrovan (ID: " << IDKorisnika << ")" << endl;
    }

    // ===== INSPEKTORI =====
    string getKorisnickoIme() const {
        return korisnickoIme;
    }

    double getKredit() const {
        return kredit;
    }

    int getID() const {
        return IDKorisnika;
    }

    // ===== MUTATORI =====
    void dodajKredit(double iznos) {
        if (iznos > 0) {
            kredit += iznos;
            cout << "Dodat kredit: " << iznos << " RSD. Novo stanje: " << kredit << " RSD" << endl;
        } else {
            cout << "GRESKA: Iznos mora biti pozitivan!" << endl;
        }
    }

    bool trosiKredit(double iznos) {
        if (iznos > 0 && iznos <= kredit) {
            kredit -= iznos;
            cout << "Troseno: " << iznos << " RSD. Preostalo: " << kredit << " RSD" << endl;
            return true;
        } else if (iznos > kredit) {
            cout << "GRESKA: Nedovoljno kredita! Dostupno: " << kredit << " RSD" << endl;
            return false;
        }
        return false;
    }

    void promeniLozinku(string staraLozinka, string novaLozinka) {
        if (staraLozinka == lozinka) {
            if (novaLozinka.length() >= 6) {
                lozinka = novaLozinka;
                cout << "Lozinka je uspešno promenjena!" << endl;
            } else {
                cout << "GRESKA: Lozinka mora imati bar 6 karaktera!" << endl;
            }
        } else {
            cout << "GRESKA: Netačna trenutna lozinka!" << endl;
        }
    }

    // ===== JAVNE METODE =====
    void prikaziJavneInformacije() const {
        cout << "\n--- Javne informacije ---" << endl;
        cout << "Korisnicko ime: " << korisnickoIme << endl;
        cout << "Email: " << email << endl;
        cout << "ID: " << IDKorisnika << endl;
    }

    // ===== STATIČKA METODA =====
    static int getUkupnoKorisnika() {
        return ukupnoKorisnika;
    }

    static void prikaziStatistiku() {
        cout << "\n[STATISTIKA] Ukupno registrovanih korisnika: " << ukupnoKorisnika << endl;
    }
};

// Inicijalizacija statičke varijable
int Korisnik::ukupnoKorisnika = 0;

// ===== ADMIN KLASA =====
class Admin {
private:
    string adminIme;

public:
    Admin(string ime) : adminIme(ime) {
        cout << "[ADMIN] Administrator " << ime << " je ulogovan" << endl;
    }

    // Admin može pristupiti privatnim članovima jer je prijatelj
    void pregledajKorisnika(const Korisnik& korisnik) {
        cout << "\n=== ADMIN PREGLED ===" << endl;
        cout << "Administrator: " << adminIme << endl;
        cout << "Korisnicko ime: " << korisnik.korisnickoIme << endl;
        cout << "Email: " << korisnik.email << endl;
        cout << "ID: " << korisnik.IDKorisnika << endl;
        cout << "LOZINKA (PRIVATNO): " << korisnik.lozinka << " (samo admin vidi)" << endl;
        cout << "Kredit: " << korisnik.kredit << " RSD" << endl;
        cout << "====================" << endl;
    }

    void resetujLozinku(Korisnik& korisnik, string novaLozinka) {
        if (novaLozinka.length() >= 6) {
            korisnik.lozinka = novaLozinka;
            cout << "[ADMIN] Lozinka korisnika '" << korisnik.korisnickoIme << "' je resetovana!" << endl;
        } else {
            cout << "[ADMIN] GRESKA: Lozinka mora biti dužine bar 6 karaktera!" << endl;
        }
    }

    void prikaziAdminskyStatus() const {
        cout << "[ADMIN] Administrator '" << adminIme << "' je aktivan" << endl;
    }
};

// Prijateljska funkcija
void prikaziAdminskyIzvestaj(const vector<Korisnik*>& korisnici) {
    cout << "\n========== ADMINISTRATIVNI IZVESTAJ ==========" << endl;
    cout << "Broj korisnika: " << korisnici.size() << endl;
    for (size_t i = 0; i < korisnici.size(); i++) {
        cout << "\nKorisnik " << (i + 1) << ":" << endl;
        cout << "  Ime: " << korisnici[i]->korisnickoIme << endl;
        cout << "  Email: " << korisnici[i]->email << endl;
        cout << "  Kredit: " << korisnici[i]->kredit << " RSD" << endl;
        cout << "  LOZINKA: " << korisnici[i]->lozinka << endl;
    }
    cout << "============================================" << endl;
}

int main() {
    cout << "=== PRIMER 5: Kombinovani Koncept ===" << endl << endl;

    cout << "--- Registracija korisnika ---" << endl;
    Korisnik k1("marko_m", "lozinka123", "marko@example.com", 1000);
    Korisnik k2("ana_a", "sigurna456", "ana@example.com", 1500);
    Korisnik k3("petar_p", "tajno789", "petar@example.com", 2000);

    Korisnik::prikaziStatistiku();

    cout << "\n--- Obicne operacije korisnika ---" << endl;
    k1.prikaziJavneInformacije();
    k1.dodajKredit(500);
    k1.trosiKredit(300);

    cout << "\n--- Promenica lozinke ---" << endl;
    k1.promeniLozinku("lozinka123", "novaLozinka456");
    k1.promeniLozinku("pogresna", "nekaLozinka");

    cout << "\n--- Admin pristup (prijateljska klasa) ---" << endl;
    Admin admin("Igor Igorevic");
    admin.pregledajKorisnika(k1); // Admin vidi i privatne podatke!
    admin.resetujLozinku(k2, "resetovana123");

    cout << "\n--- Prijateljska funkcija ---" << endl;
    vector<Korisnik*> sviKorisnici;
    sviKorisnici.push_back(&k1);
    sviKorisnici.push_back(&k2);
    sviKorisnici.push_back(&k3);
    prikaziAdminskyIzvestaj(sviKorisnici);

    cout << "\n--- Finalne operacije ---" << endl;
    k2.trosiKredit(2000); // Pokušaj da se utroši više nego što ima
    k3.prikaziJavneInformacije();

    return 0;
}
