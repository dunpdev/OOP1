#include <iostream>
#include <string>
using namespace std;

// ===== BAZNA KLASA =====
class Vozilo {
protected:  // Pristupačno izvedenim klasama
    string marka;
    string model;
    int godProdukciјe;
    double cena;

public:
    // Konstruktor
    Vozilo(string m, string mo, int g, double c)
        : marka(m), model(mo), godProdukciјe(g), cena(c) {
        cout << "Konstruktor Vozila: " << marka << " " << model << endl;
    }

    // Destruktor
    virtual ~Vozilo() {
        cout << "Destruktor Vozila: " << marka << " " << model << endl;
    }

    // Javne metode
    void prikaziInfo() const {
        cout << "\n--- Vozilo Info ---" << endl;
        cout << "Marka: " << marka << endl;
        cout << "Model: " << model << endl;
        cout << "Godina: " << godProdukciјe << endl;
        cout << "Cena: " << cena << " RSD" << endl;
    }

    virtual void pokazi() const {
        cout << "Vozilo: " << marka << " " << model << endl;
    }

    double getCena() const { return cena; }
};

// ===== IZVEDENA KLASA =====
class Automobil : public Vozilo {  // Javno nasleđivanje
private:
    int brojVrata;
    string tip; // sedan, SUV, kupé

public:
    // Konstruktor izvedene klase
    // : Vozilo() poziva konstruktor bazne klase
    Automobil(string m, string mo, int g, double c, int vrata, string t)
        : Vozilo(m, mo, g, c), brojVrata(vrata), tip(t) {
        cout << "Konstruktor Automobila" << endl;
    }

    ~Automobil() {
        cout << "Destruktor Automobila" << endl;
    }

    void prikaziInfo() const {
        Vozilo::prikaziInfo();  // Pozovi baznu verziju
        cout << "Broj vrata: " << brojVrata << endl;
        cout << "Tip: " << tip << endl;
    }

    void pokazi() const override {  // Override - nadjačava
        cout << "Automobil: " << marka << " " << model << " (" << tip << ")" << endl;
    }

    void voznja(double km) {
        cout << "Vozim " << marka << " " << model << " za " << km << " km" << endl;
    }

    int getBrojVrata() const { return brojVrata; }
    string getTip() const { return tip; }
};

// ===== DRUGA IZVEDENA KLASA =====
class Motocikl : public Vozilo {
private:
    int cc;  // Kubni centimetri
    bool imaGerb;

public:
    Motocikl(string m, string mo, int g, double c, int kubni, bool gerb)
        : Vozilo(m, mo, g, c), cc(kubni), imaGerb(gerb) {
        cout << "Konstruktor Motocikla" << endl;
    }

    ~Motocikl() {
        cout << "Destruktor Motocikla" << endl;
    }

    void prikaziInfo() const {
        Vozilo::prikaziInfo();
        cout << "Kubni centimetri: " << cc << " cc" << endl;
        cout << "Ima gerb: " << (imaGerb ? "DA" : "NE") << endl;
    }

    void pokazi() const override {
        cout << "Motocikl: " << marka << " " << model << " (" << cc << " cc)" << endl;
    }

    void voznja(double km) {
        cout << "Vozim brz motocikl " << marka << " " << model << " za " << km << " km" << endl;
    }
};

int main() {
    cout << "=== PRIMER 1: Osnovno Nasledjivanje ===" << endl << endl;

    cout << "--- Kreiranje automobila ---" << endl;
    Automobil auto1("BMW", "X5", 2023, 800000, 5, "SUV");
    auto1.prikaziInfo();

    cout << "\n--- Kreiranje motocikla ---" << endl;
    Motocikl moto1("Harley-Davidson", "Street 750", 2022, 350000, 750, true);
    moto1.prikaziInfo();

    cout << "\n--- Koriscenje metoda izvedenih klasa ---" << endl;
    auto1.voznja(150);
    moto1.voznja(100);

    cout << "\n--- Polimorfizam - virtual metode ---" << endl;
    auto1.pokazi();
    moto1.pokazi();

    cout << "\n--- Pristup zastitenim članovima kroz metode ---" << endl;
    cout << "Cena automobila: " << auto1.getCena() << " RSD" << endl;
    cout << "Cena motocikla: " << moto1.getCena() << " RSD" << endl;

    cout << "\n--- Brisanje objekata ---" << endl;
    return 0;
}
