#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Student {
private:
    string ime;
    double prosek;
    int godina;

public:
    // Podrazumevani konstruktor
    Student() : ime("Nepoznato"), prosek(0), godina(1) {
        cout << "Kreiram studenta - podrazumevani konstruktor" << endl;
    }

    // Parametrizovani konstruktor
    Student(string i, double p, int g) : ime(i), prosek(p), godina(g) {
        cout << "Kreiram studenta: " << ime << endl;
    }

    // Destruktor
    ~Student() {
        cout << "Brisem studenta: " << ime << endl;
    }

    // Getteri
    string getIme() const { return ime; }
    double getProsek() const { return prosek; }
    int getGodina() const { return godina; }

    void prikazi() const {
        cout << "  " << ime << " (Godina: " << godina << ", Prosek: " << prosek << ")" << endl;
    }
};

class Grupa {
private:
    string naziv;
    vector<Student> studenti;

public:
    Grupa(string n) : naziv(n) {
        cout << "Grupa " << naziv << " je kreirana!" << endl;
    }

    ~Grupa() {
        cout << "Grupa " << naziv << " je obrisana!" << endl;
    }

    void dodajStudenta(const Student& s) {
        studenti.push_back(s);
    }

    void prikaziStudente() const {
        cout << "\n--- Grupa: " << naziv << " (" << studenti.size() << " studenta) ---" << endl;
        for (int i = 0; i < studenti.size(); i++) {
            studenti[i].prikazi();
        }
    }

    double prosecnaProseka() const {
        if (studenti.size() == 0) return 0;
        double zbir = 0;
        for (int i = 0; i < studenti.size(); i++) {
            zbir += studenti[i].getProsek();
        }
        return zbir / studenti.size();
    }
};

int main() {
    cout << "=== PRIMER 4: Grupa Studenata ===" << endl << endl;

    Grupa grupa("Informatika 2024");

    grupa.dodajStudenta(Student("Petar Nikolic", 9.2, 1));
    grupa.dodajStudenta(Student("Marija Jovanovic", 8.5, 1));
    grupa.dodajStudenta(Student("Aleksandra Lazic", 9.8, 1));

    grupa.prikaziStudente();

    cout << "\nProsecna proseka u grupi: " << grupa.prosecnaProseka() << endl;

    return 0;
}
