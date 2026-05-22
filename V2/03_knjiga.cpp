#include <iostream>
#include <string>
using namespace std;

class Knjiga {
private:
    string naslov;
    string autor;
    int godineIzdanja;
    int brojStrana;
    static int ukupnoKnjiga; // Statička varijabla

public:
    // Konstruktor
    Knjiga(string n, string a, int g, int s)
        : naslov(n), autor(a), godineIzdanja(g), brojStrana(s) {
        ukupnoKnjiga++;
        cout << "Nova knjiga: " << naslov << " (" << autor << ")" << endl;
    }

    // Copy konstruktor
    Knjiga(const Knjiga& druga) {
        naslov = druga.naslov;
        autor = druga.autor;
        godineIzdanja = druga.godineIzdanja;
        brojStrana = druga.brojStrana;
        ukupnoKnjiga++;
        cout << "Kopija knjige: " << naslov << endl;
    }

    // Destruktor
    ~Knjiga() {
        ukupnoKnjiga--;
        cout << "Knjiga obrisana: " << naslov << endl;
    }

    void prikazi() {
        cout << "\nNaslov: " << naslov << endl;
        cout << "Autor: " << autor << endl;
        cout << "Godina: " << godineIzdanja << endl;
        cout << "Strana: " << brojStrana << endl;
    }

    // Statička metoda
    static void prikaziUkupno() {
        cout << "\nUkupno knjiga u biblioteci: " << ukupnoKnjiga << endl;
    }
};

// Inicijalizacija statičke varijable
int Knjiga::ukupnoKnjiga = 0;

int main() {
    cout << "=== PRIMER 3: Knjiga ===" << endl;

    {
        Knjiga k1("1984", "George Orwell", 1949, 328);
        k1.prikazi();
        Knjiga::prikaziUkupno();

        Knjiga k2("Desankas Sapci", "Ivo Andric", 1945, 356);
        k2.prikazi();
        Knjiga::prikaziUkupno();

        Knjiga k3 = k1; // Copy konstruktor
        Knjiga::prikaziUkupno();
    }

    Knjiga::prikaziUkupno();

    return 0;
}
