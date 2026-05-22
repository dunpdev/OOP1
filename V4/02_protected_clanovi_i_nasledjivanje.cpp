#include <iostream>
#include <string>
#include <vector>
using namespace std;

// ===== BAZNA KLASA =====
class Zaposlenik {
protected:  // Zaštiteni - dostupni izvedenim klasama
    string ime;
    string prezime;
    string email;
    double baznaPlata;
    static int ukupnoZaposlenika;

public:
    Zaposlenik(string i, string p, string e, double b)
        : ime(i), prezime(p), email(e), baznaPlata(b) {
        ukupnoZaposlenika++;
        cout << "Zaposlenik " << ime << " " << prezime << " je zaposlен" << endl;
    }

    virtual ~Zaposlenik() {
        ukupnoZaposlenika--;
        cout << "Zaposlenik " << ime << " je otpustен" << endl;
    }

    // Javne metode
    virtual void prikaziInfo() const {
        cout << "\n--- Zaposlenik ---" << endl;
        cout << "Ime: " << ime << " " << prezime << endl;
        cout << "Email: " << email << endl;
        cout << "Bazna plata: " << baznaPlata << " RSD" << endl;
    }

    virtual double izracunajPlatu() const {
        return baznaPlata;
    }

    virtual void radi() {
        cout << ime << " radi na osnovnom poslu" << endl;
    }

    string getIme() const { return ime + " " + prezime; }
    string getEmail() const { return email; }

    static int getUkupnoZaposlenika() { return ukupnoZaposlenika; }

    static void prikaziStatistiku() {
        cout << "[STATISTIKA] Ukupno zaposlenika: " << ukupnoZaposlenika << endl;
    }
};

int Zaposlenik::ukupnoZaposlenika = 0;

// ===== IZVEDENA KLASA 1 =====
class Menadzer : public Zaposlenik {
private:
    int brojPodredjenih;
    double bonus;

public:
    Menadzer(string i, string p, string e, double b, int br, double bon)
        : Zaposlenik(i, p, e, b), brojPodredjenih(br), bonus(bon) {
        cout << "Menadzer " << ime << " je kreiran" << endl;
    }

    ~Menadzer() {
        cout << "Menadzer " << ime << " je obrisan" << endl;
    }

    void prikaziInfo() const override {
        Zaposlenik::prikaziInfo();
        cout << "Pozicija: Menadzer" << endl;
        cout << "Broj podredjenih: " << brojPodredjenih << endl;
        cout << "Bonus: " << bonus << " RSD" << endl;
    }

    double izracunajPlatu() const override {
        double plata = baznaPlata + bonus;
        plata += (brojPodredjenih * 500); // Dodatak po podredjenom
        return plata;
    }

    void radi() override {
        cout << ime << " upravlja timom od " << brojPodredjenih << " osoba" << endl;
    }

    void vodiBrojReunion() {
        cout << "Menadzer " << ime << " vodi poslovni sastanak" << endl;
    }

    void dodajBonus(double b) {
        bonus += b;
        cout << "Bonus menadžeru " << ime << " je povećan na " << bonus << " RSD" << endl;
    }
};

// ===== IZVEDENA KLASA 2 =====
class Programer : public Zaposlenik {
private:
    string programskiJezik;
    int nivoPistenosti; // 1-5

public:
    Programer(string i, string p, string e, double b, string jezik, int nivo)
        : Zaposlenik(i, p, e, b), programskiJezik(jezik), nivoPistenosti(nivo) {
        cout << "Programer " << ime << " je kreiran" << endl;
    }

    ~Programer() {
        cout << "Programer " << ime << " je obrisan" << endl;
    }

    void prikaziInfo() const override {
        Zaposlenik::prikaziInfo();
        cout << "Pozicija: Programer" << endl;
        cout << "Programski jezik: " << programskiJezik << endl;
        cout << "Nivo pistenosti: " << nivoPistenosti << "/5" << endl;
    }

    double izracunajPlatu() const override {
        double plata = baznaPlata;
        plata += (nivoPistenosti * 1000); // Dodatak po nivou
        return plata;
    }

    void radi() override {
        cout << ime << " program kod u " << programskiJezik << endl;
    }

    void posvecujeKodu(int sati) {
        cout << "Programer " << ime << " radi " << sati << " sati na kodu" << endl;
    }

    void uciBaznuTematiku() {
        cout << ime << " uči novu biblioteku u " << programskiJezik << endl;
    }
};

// ===== IZVEDENA KLASA 3 =====
class Dizajner : public Zaposlenik {
private:
    string softver;
    vector<string> specijalizacije;

public:
    Dizajner(string i, string p, string e, double b, string s)
        : Zaposlenik(i, p, e, b), softver(s) {
        cout << "Dizajner " << ime << " je kreiran" << endl;
    }

    ~Dizajner() {
        cout << "Dizajner " << ime << " je obrisan" << endl;
    }

    void prikaziInfo() const override {
        Zaposlenik::prikaziInfo();
        cout << "Pozicija: Dizajner" << endl;
        cout << "Softver: " << softver << endl;
        cout << "Specijalizacije: ";
        for (size_t i = 0; i < specijalizacije.size(); i++) {
            cout << specijalizacije[i];
            if (i < specijalizacije.size() - 1) cout << ", ";
        }
        cout << endl;
    }

    double izracunajPlatu() const override {
        double plata = baznaPlata;
        plata += (specijalizacije.size() * 2000); // Po specijalizaciji
        return plata;
    }

    void radi() override {
        cout << ime << " dizajnira u " << softver << endl;
    }

    void dodajSpecijalizaciju(string spec) {
        specijalizacije.push_back(spec);
        cout << "Dizajner " << ime << " je stekao specijalizaciju: " << spec << endl;
    }
};

int main() {
    cout << "=== PRIMER 2: Nasledjivanje sa Protected Članovima ===" << endl << endl;

    cout << "--- Kreiranje zaposlenika ---" << endl;
    Menadzer m1("Marko", "Markovic", "marko@firma.com", 50000, 5, 10000);
    Programer p1("Ana", "Anic", "ana@firma.com", 45000, "C++", 4);
    Dizajner d1("Jovana", "Jovanovic", "jovana@firma.com", 42000, "Figma");

    cout << "\n--- Informacije o zaposlenicima ---" << endl;
    m1.prikaziInfo();
    p1.prikaziInfo();
    d1.prikaziInfo();

    cout << "\n--- Rad zaposlenika ---" << endl;
    m1.radi();
    p1.radi();
    d1.radi();

    cout << "\n--- Specifične aktivnosti ---" << endl;
    m1.vodiBrojReunion();
    p1.posvecujeKodu(8);
    d1.dodajSpecijalizaciju("UI/UX");
    d1.dodajSpecijalizaciju("Web Design");

    cout << "\n--- Izračunavanje plata ---" << endl;
    cout << "Plata Menadžera: " << m1.izracunajPlatu() << " RSD" << endl;
    cout << "Plata Programera: " << p1.izracunajPlatu() << " RSD" << endl;
    cout << "Plata Dizajnera: " << d1.izracunajPlatu() << " RSD" << endl;

    cout << "\n--- Dodatan bonus menadžeru ---" << endl;
    m1.dodajBonus(5000);
    cout << "Nova plata Menadžera: " << m1.izracunajPlatu() << " RSD" << endl;

    cout << "\n--- Statističke informacije ---" << endl;
    Zaposlenik::prikaziStatistiku();

    cout << "\n--- Brisanje zaposlenika ---" << endl;
    return 0;
}
