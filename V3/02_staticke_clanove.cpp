#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Automobil {
private:
    string marka;
    string registarskaOznaka;
    static int ukupnoAutomobila;
    static double ukupnaVrednost;
    double vrednost;

public:
    // Konstruktor
    Automobil(string m, double v) : marka(m), vrednost(v) {
        ukupnoAutomobila++;
        ukupnaVrednost += v;
        registarskaOznaka = "REG-" + to_string(ukupnoAutomobila);
        cout << "Automobil " << marka << " je registrovan (" << registarskaOznaka << ")" << endl;
    }

    ~Automobil() {
        ukupnoAutomobila--;
        ukupnaVrednost -= vrednost;
        cout << "Automobil " << marka << " je deregistrovan" << endl;
    }

    string getMarka() const { return marka; }
    string getRegistarskaOznaka() const { return registarskaOznaka; }
    double getVrednost() const { return vrednost; }

    // ===== STATICKE METODE =====
    static int getUkupnoAutomobila() {
        return ukupnoAutomobila;
    }

    static double getUkupnaVrednost() {
        return ukupnaVrednost;
    }

    static double prosecnaVrednost() {
        if (ukupnoAutomobila == 0) return 0;
        return ukupnaVrednost / ukupnoAutomobila;
    }

    static void prikaziStatistiku() {
        cout << "\n===== STATISTIKA FLOTE =====" << endl;
        cout << "Ukupno automobila: " << ukupnoAutomobila << endl;
        cout << "Ukupna vrednost: " << ukupnaVrednost << " RSD" << endl;
        cout << "Prosecna vrednost: " << prosecnaVrednost() << " RSD" << endl;
        cout << "============================" << endl;
    }

    void prikaziInfo() const {
        cout << marka << " (" << registarskaOznaka << ") - " << vrednost << " RSD" << endl;
    }
};

// Inicijalizacija statičkih varijabli
int Automobil::ukupnoAutomobila = 0;
double Automobil::ukupnaVrednost = 0;

int main() {
    cout << "=== PRIMER 2: Staticke Clanove Klase ===" << endl << endl;

    cout << "--- Kreiranje automobila ---" << endl;
    Automobil auto1("BMW X5", 800000);
    Automobil auto2("Mercedes C-Class", 650000);
    Automobil auto3("Audi A4", 700000);

    Automobil::prikaziStatistiku();

    cout << "\n--- Lista automobila ---" << endl;
    auto1.prikaziInfo();
    auto2.prikaziInfo();
    auto3.prikaziInfo();

    cout << "\n--- Pristup statickim članovima ---" << endl;
    cout << "Automobila u floti: " << Automobil::getUkupnoAutomobila() << endl;
    cout << "Ukupna vrednost flote: " << Automobil::getUkupnaVrednost() << " RSD" << endl;
    cout << "Prosecna cena: " << Automobil::prosecnaVrednost() << " RSD" << endl;

    {
        cout << "\n--- Kreiranje privremenog automobila ---" << endl;
        Automobil auto4("Tesla Model 3", 1200000);
        Automobil::prikaziStatistiku();
    } // auto4 se briše

    cout << "\n--- Posle brisanja privremenog automobila ---" << endl;
    Automobil::prikaziStatistiku();

    return 0;
}
