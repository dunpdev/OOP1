#include <iostream>
#include <string>
using namespace std;

class Automobil {
private:
    string marka;
    double kapacitetRezervoara;
    double trenutnoGoriva;
    double potronja; // litara po km

public:
    // Konstruktor
    Automobil(string m, double kapacitet, double pot)
        : marka(m), kapacitetRezervoara(kapacitet), potronja(pot) {
        trenutnoGoriva = kapacitet;
        cout << "Automobil " << marka << " je kupljen!" << endl;
        cout << "Kapacitet: " << kapacitetRezervoara << "L, Potrosnja: "
             << potronja << "L/km" << endl;
    }

    // Destruktor
    ~Automobil() {
        cout << "Automobil " << marka << " je odbijen iz servisa!" << endl;
    }

    // Metoda za vožnju
    void voznja(double distanca) {
        double utroseno = distanca * potronja;

        if (utroseno > trenutnoGoriva) {
            cout << "GRESKA: Nema dovoljno goriva!" << endl;
            cout << "Potrebno: " << utroseno << "L, Dostupno: " << trenutnoGoriva << "L" << endl;
            return;
        }

        trenutnoGoriva -= utroseno;
        cout << "Vozim " << marka << " - " << distanca << "km" << endl;
        cout << "Utroseno: " << utroseno << "L, Preostalo: " << trenutnoGoriva << "L" << endl;
    }

    // Punjenje rezervoara
    void punjiRezervoar() {
        double potrebno = kapacitetRezervoara - trenutnoGoriva;
        cout << "Punim rezervoar od " << marka << " - " << potrebno << "L" << endl;
        trenutnoGoriva = kapacitetRezervoara;
    }

    // Prikazivanje stanja
    void stanje() {
        cout << "\n--- STANJE AUTOMOBILA ---" << endl;
        cout << "Marka: " << marka << endl;
        cout << "Trenutno goriva: " << trenutnoGoriva << "L / " << kapacitetRezervoara << "L" << endl;
        cout << "Preostali domet: " << (trenutnoGoriva / potronja) << "km" << endl;
        cout << "------------------------" << endl;
    }
};

int main() {
    cout << "=== PRIMER 2: Automobil ===" << endl << endl;

    Automobil auto1("BMW", 60, 0.08);
    auto1.stanje();

    auto1.voznja(100);
    auto1.stanje();

    auto1.voznja(150);
    auto1.stanje();

    auto1.voznja(500); // Dovoljno goriva?

    auto1.punjiRezervoar();
    auto1.stanje();

    auto1.voznja(200);
    auto1.stanje();

    return 0;
}
