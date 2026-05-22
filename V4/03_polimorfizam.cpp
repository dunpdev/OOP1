#include <iostream>
#include <cmath>
#include <string>
#include <vector>
using namespace std;

const double PI = 3.14159265359;

// ===== APSTRAKTNA BAZNA KLASA =====
class Oblik {
protected:
    string naziv;

public:
    Oblik(string n) : naziv(n) {
        cout << "Oblik '" << naziv << "' je kreiran" << endl;
    }

    virtual ~Oblik() {
        cout << "Oblik '" << naziv << "' je obrisan" << endl;
    }

    // Pure virtual metode - moraju biti implementirane u izvedenim klasama
    virtual double izracunajPovrsinu() const = 0;
    virtual double izracunajObim() const = 0;

    virtual void prikaziInfo() const {
        cout << "\n=== " << naziv << " ===" << endl;
        cout << "Povrsina: " << izracunajPovrsinu() << endl;
        cout << "Obim: " << izracunajObim() << endl;
    }

    string getNaziv() const { return naziv; }
};

// ===== IZVEDENA KLASA 1: PRAVOUGAONIK =====
class Pravougaonik : public Oblik {
protected:
    double sirina;
    double visina;

public:
    Pravougaonik(double s, double v)
        : Oblik("Pravougaonik"), sirina(s), visina(v) {
        if (sirina <= 0 || visina <= 0) {
            cout << "GRESKA: Dimenzije moraju biti pozitivne!" << endl;
        }
    }

    ~Pravougaonik() {}

    double izracunajPovrsinu() const override {
        return sirina * visina;
    }

    double izracunajObim() const override {
        return 2 * (sirina + visina);
    }

    void prikaziInfo() const override {
        Oblik::prikaziInfo();
        cout << "Sirina: " << sirina << endl;
        cout << "Visina: " << visina << endl;
    }

    double getSirina() const { return sirina; }
    double getVisina() const { return visina; }
};

// ===== IZVEDENA KLASA 2: KVADRAT =====
class Kvadrat : public Pravougaonik {
private:
    double strana;

public:
    Kvadrat(double s)
        : Pravougaonik(s, s), strana(s) {
        naziv = "Kvadrat";
    }

    ~Kvadrat() {}

    void prikaziInfo() const override {
        cout << "\n=== " << naziv << " ===" << endl;
        cout << "Povrsina: " << izracunajPovrsinu() << endl;
        cout << "Obim: " << izracunajObim() << endl;
        cout << "Strana: " << strana << endl;
    }

    double getStrana() const { return strana; }
};

// ===== IZVEDENA KLASA 3: KRUG =====
class Krug : public Oblik {
private:
    double radius;

public:
    Krug(double r)
        : Oblik("Krug"), radius(r) {
        if (radius <= 0) {
            cout << "GRESKA: Radius mora biti pozitivan!" << endl;
        }
    }

    ~Krug() {}

    double izracunajPovrsinu() const override {
        return PI * radius * radius;
    }

    double izracunajObim() const override {
        return 2 * PI * radius;
    }

    void prikaziInfo() const override {
        Oblik::prikaziInfo();
        cout << "Radius: " << radius << endl;
    }

    double getRadius() const { return radius; }
};

// ===== IZVEDENA KLASA 4: TROUGAO =====
class Trougao : public Oblik {
private:
    double a, b, c; // Stranice

public:
    Trougao(double sa, double sb, double sc)
        : Oblik("Trougao"), a(sa), b(sb), c(sc) {
        // Provera da li je validna trougao
        if (a + b <= c || b + c <= a || a + c <= b) {
            cout << "GRESKA: Nevalidne stranice za trougao!" << endl;
        }
    }

    ~Trougao() {}

    double izracunajPovrsinu() const override {
        // Heronova formula
        double s = (a + b + c) / 2.0;
        return sqrt(s * (s - a) * (s - b) * (s - c));
    }

    double izracunajObim() const override {
        return a + b + c;
    }

    void prikaziInfo() const override {
        Oblik::prikaziInfo();
        cout << "Stranice: a=" << a << ", b=" << b << ", c=" << c << endl;
    }

    double getA() const { return a; }
    double getB() const { return b; }
    double getC() const { return c; }
};

// ===== POMOCNA FUNKCIJA =====
void prikaziSveObolike(const vector<Oblik*>& oblici) {
    cout << "\n========== PREGLED SVIH OBLIKA ==========" << endl;
    double ukupnaPovrsina = 0;

    for (size_t i = 0; i < oblici.size(); i++) {
        oblici[i]->prikaziInfo();
        ukupnaPovrsina += oblici[i]->izracunajPovrsinu();
    }

    cout << "\n========================================" << endl;
    cout << "Ukupna povrsina svih oblika: " << ukupnaPovrsina << endl;
    cout << "Broj oblika: " << oblici.size() << endl;
    cout << "========================================" << endl;
}

int main() {
    cout << "=== PRIMER 3: Polimorfizam i Nasledjivanje ===" << endl << endl;

    cout << "--- Kreiranje geometrijskih oblika ---" << endl;
    vector<Oblik*> oblici;

    Pravougaonik p1(5, 3);
    oblici.push_back(&p1);

    Kvadrat k1(4);
    oblici.push_back(&k1);

    Krug kr1(2);
    oblici.push_back(&kr1);

    Trougao t1(3, 4, 5); // Pitagorin trougao
    oblici.push_back(&t1);

    prikaziSveObolike(oblici);

    cout << "\n--- Polimorfna obrada ---" << endl;
    for (size_t i = 0; i < oblici.size(); i++) {
        cout << "Oblik " << (i + 1) << ": " << oblici[i]->getNaziv()
             << " - Povrsina: " << oblici[i]->izracunajPovrsinu() << endl;
    }

    cout << "\n--- Specifične metode izvedenih klasa ---" << endl;
    cout << "Pravougaonik sirina: " << p1.getSirina() << endl;
    cout << "Kvadrat strana: " << k1.getStrana() << endl;
    cout << "Krug radius: " << kr1.getRadius() << endl;
    cout << "Trougao stranica a: " << t1.getA() << endl;

    cout << "\n--- Brisanje oblika ---" << endl;
    return 0;
}
