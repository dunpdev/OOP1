#include <iostream>
#include <string>
#include <cmath>
#include <stdexcept>
using namespace std;

// ===== BAZNA KLASA ZA MATEMATIČKE IZUZETKE =====
class MatematiCkiIzuzetak : public exception {
protected:
    string poruka;
    string operacija;

public:
    MatematiCkiIzuzetak(const string& op, const string& p)
        : operacija(op), poruka(p) {
        cout << "[MATEMATIČKI IZUZETAK] Kreiran za operaciju: " << operacija << endl;
    }

    virtual const char* what() const noexcept override {
        return poruka.c_str();
    }

    string getOperacija() const { return operacija; }

    virtual void prikaziDetalje() const {
        cout << "Matematički izuzetak u operaciji '" << operacija << "': " << poruka << endl;
    }

    virtual ~MatematiCkiIzuzetak() {}
};

// ===== PRVI DERIVOVANI IZUZETAK =====
class DeljenjeSaNulom : public MatematiCkiIzuzetak {
private:
    double brojilac;

public:
    DeljenjeSaNulom(double b)
        : MatematiCkiIzuzetak("DELJENJE", "Ne mogu deliti sa nulom!"),
          brojilac(b) {
        poruka += " (Brojilac: " + to_string(b) + ")";
    }

    double getBrojilac() const { return brojilac; }

    void prikaziDetalje() const override {
        cout << "DELJENJE SA NULOM:" << endl;
        cout << "  Brojilac: " << brojilac << endl;
        cout << "  Imenilac: 0" << endl;
        cout << "  Problem: Deljenje sa nulom nije definisano!" << endl;
    }

    ~DeljenjeSaNulom() {}
};

// ===== DRUGI DERIVOVANI IZUZETAK =====
class KorenNegativnogBroja : public MatematiCkiIzuzetak {
private:
    double broj;

public:
    KorenNegativnogBroja(double b)
        : MatematiCkiIzuzetak("KVADRATNI KOREN", "Ne mogu izvlačiti koren negativnog broja!"),
          broj(b) {
        poruka += " (Broj: " + to_string(b) + ")";
    }

    double getBroj() const { return broj; }

    void prikaziDetalje() const override {
        cout << "KOREN NEGATIVNOG BROJA:" << endl;
        cout << "  Broj: " << broj << endl;
        cout << "  Problem: sqrt(" << broj << ") nije realan broj!" << endl;
        cout << "  Mogućnost: Kompleksan broj = " << sqrt(abs(broj)) << "i" << endl;
    }

    ~KorenNegativnogBroja() {}
};

// ===== TREĆI DERIVOVANI IZUZETAK =====
class DomenaPrekracena : public MatematiCkiIzuzetak {
private:
    double vrednost;
    double min_granica;
    double max_granica;

public:
    DomenaPrekracena(const string& op, double v, double min_g, double max_g)
        : MatematiCkiIzuzetak(op, "Vrednost je van dozvoljene domene!"),
          vrednost(v), min_granica(min_g), max_granica(max_g) {
        poruka += " (Domen: [" + to_string(min_g) + ", " + to_string(max_g) + "])";
    }

    double getVrednost() const { return vrednost; }
    double getMinGranica() const { return min_granica; }
    double getMaxGranica() const { return max_granica; }

    void prikaziDetalje() const override {
        cout << "DOMENA PREKRACENA:" << endl;
        cout << "  Operacija: " << operacija << endl;
        cout << "  Vrednost: " << vrednost << endl;
        cout << "  Dozvoljeno: [" << min_granica << ", " << max_granica << "]" << endl;
        cout << "  Problem: Vrednost nije u dozvoljenom rasponu!" << endl;
    }

    ~DomenaPrekracena() {}
};

// ===== MATEMATIČKI KALKULATOR =====
class Kalkulator {
public:
    static double deli(double a, double b) {
        if (b == 0) {
            throw DeljenjeSaNulom(a);
        }
        return a / b;
    }

    static double kvadratniKoren(double x) {
        if (x < 0) {
            throw KorenNegativnogBroja(x);
        }
        return sqrt(x);
    }

    static double logaritam(double x) {
        if (x <= 0) {
            throw DomenaPrekracena("LOGARITAM", x, 0.001, 1000000);
        }
        return log(x);
    }

    static double arcsin(double x) {
        if (x < -1 || x > 1) {
            throw DomenaPrekracena("ARCSIN", x, -1, 1);
        }
        return asin(x);
    }

    static double stepen(double a, int n) {
        if (n < 0) {
            throw DomenaPrekracena("STEPEN", n, 0, 1000);
        }
        double rezultat = 1;
        for (int i = 0; i < n; i++) {
            rezultat *= a;
        }
        return rezultat;
    }
};

int main() {
    cout << "=== PRIMER 4: Custom Izuzeci - Matematički Sistem ===" << endl << endl;

    // ===== TEST 1: DELJENJE SA NULOM =====
    cout << "--- Test 1: Deljenje sa Nulom ---" << endl;
    try {
        cout << "Delim 100 sa 0..." << endl;
        double rezultat = Kalkulator::deli(100, 0);
        cout << "Rezultat: " << rezultat << endl;
    } catch (DeljenjeSaNulom& e) {
        cout << "UHVACEN IZUZETAK:" << endl;
        cout << "what(): " << e.what() << endl;
        e.prikaziDetalje();
    } catch (MatematiCkiIzuzetak& e) {
        cout << "Matematički izuzetak: " << e.what() << endl;
    }

    // ===== TEST 2: KVADRATNI KOREN NEGATIVNOG =====
    cout << "\n--- Test 2: Kvadratni Koren Negativnog Broja ---" << endl;
    try {
        cout << "Tražim koren od -16..." << endl;
        double rezultat = Kalkulator::kvadratniKoren(-16);
        cout << "Rezultat: " << rezultat << endl;
    } catch (KorenNegativnogBroja& e) {
        cout << "UHVACEN IZUZETAK:" << endl;
        cout << "what(): " << e.what() << endl;
        e.prikaziDetalje();
    } catch (MatematiCkiIzuzetak& e) {
        cout << "Matematički izuzetak: " << e.what() << endl;
    }

    // ===== TEST 3: LOGARITAM NULE =====
    cout << "\n--- Test 3: Logaritam Nule ---" << endl;
    try {
        cout << "Tražim log(0)..." << endl;
        double rezultat = Kalkulator::logaritam(0);
        cout << "Rezultat: " << rezultat << endl;
    } catch (DomenaPrekracena& e) {
        cout << "UHVACEN IZUZETAK:" << endl;
        cout << "what(): " << e.what() << endl;
        e.prikaziDetalje();
    } catch (MatematiCkiIzuzetak& e) {
        cout << "Matematički izuzetak: " << e.what() << endl;
    }

    // ===== TEST 4: ARCSIN VREDNOSTI VAN DOMENE =====
    cout << "\n--- Test 4: Arcsin Vrednosti van Domene ---" << endl;
    try {
        cout << "Tražim arcsin(2)..." << endl;
        double rezultat = Kalkulator::arcsin(2);
        cout << "Rezultat: " << rezultat << endl;
    } catch (DomenaPrekracena& e) {
        cout << "UHVACEN IZUZETAK:" << endl;
        cout << "what(): " << e.what() << endl;
        e.prikaziDetalje();
    } catch (MatematiCkiIzuzetak& e) {
        cout << "Matematički izuzetak: " << e.what() << endl;
    }

    // ===== TEST 5: STEPEN SA NEGATIVNIM EKSPONENTOM =====
    cout << "\n--- Test 5: Stepen sa Negativnim Eksponentom ---" << endl;
    try {
        cout << "Tražim 2^(-3)..." << endl;
        double rezultat = Kalkulator::stepen(2, -3);
        cout << "Rezultat: " << rezultat << endl;
    } catch (DomenaPrekracena& e) {
        cout << "UHVACEN IZUZETAK:" << endl;
        e.prikaziDetalje();
    } catch (MatematiCkiIzuzetak& e) {
        cout << "Matematički izuzetak: " << e.what() << endl;
    }

    // ===== TEST 6: VALIDNE OPERACIJE =====
    cout << "\n--- Test 6: Validne Operacije ---" << endl;
    try {
        cout << "100 / 5 = " << Kalkulator::deli(100, 5) << endl;
        cout << "sqrt(16) = " << Kalkulator::kvadratniKoren(16) << endl;
        cout << "log(10) = " << Kalkulator::logaritam(10) << endl;
        cout << "arcsin(0.5) = " << Kalkulator::arcsin(0.5) << " rad" << endl;
        cout << "2^5 = " << Kalkulator::stepen(2, 5) << endl;
    } catch (MatematiCkiIzuzetak& e) {
        cout << "Matematički izuzetak: " << e.what() << endl;
    }

    // ===== TEST 7: UGNEŽDENI POKUŠAJI =====
    cout << "\n--- Test 7: Ugneždeni Pokušaji ---" << endl;
    try {
        cout << "Pokušavam seriju operacija..." << endl;
        double x = Kalkulator::deli(50, 2);
        cout << "1. 50 / 2 = " << x << endl;

        double y = Kalkulator::kvadratniKoren(x);
        cout << "2. sqrt(" << x << ") = " << y << endl;

        double z = Kalkulator::logaritam(y);
        cout << "3. log(" << y << ") = " << z << endl;

        double w = Kalkulator::stepen(2, (int)z + 3);
        cout << "4. 2^" << ((int)z + 3) << " = " << w << endl;
    } catch (DeljenjeSaNulom& e) {
        cout << "Deljenje sa nulom: " << e.what() << endl;
    } catch (KorenNegativnogBroja& e) {
        cout << "Koren negativnog: " << e.what() << endl;
    } catch (DomenaPrekracena& e) {
        cout << "Domena prekračena: " << e.what() << endl;
    } catch (MatematiCkiIzuzetak& e) {
        cout << "Matematički izuzetak: " << e.what() << endl;
    }

    cout << "\n--- Kraj programa ---" << endl;
    return 0;
}
