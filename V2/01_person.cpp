#include <iostream>
#include <string>
using namespace std;

class Person {
private:
    string name;
    int age;

public:
    // Konstruktor sa parametrima
    Person(string n, int a) {
        name = n;
        age = a;
        cout << "Konstruktor: Osoba " << name << " je kreirana." << endl;
    }

    // Destruktor
    ~Person() {
        cout << "Destruktor: Osoba " << name << " je obrisana." << endl;
    }

    void display() {
        cout << "Ime: " << name << ", Godine: " << age << endl;
    }
};

int main() {
    cout << "=== PRIMER 1: Osoba ===" << endl;

    Person p1("Ana", 25);
    p1.display();

    {
        Person p2("Marko", 30);
        p2.display();
    } // Destruktor od p2 se izvršava ovde

    p1.display();

    return 0;
} // Destruktor od p1 se izvršava ovde
