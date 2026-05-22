# C++ Primeri: Rad sa Izuzecima (Exceptions)

## Pregled Tema

### 1. **01_standardni_izuzeci.cpp** - Standardni Izuzeci

**Try-Catch Blok:**
```cpp
try {
    // Kod koji može baciti izuzetak
    int rezultat = deli(10, 0);  // IZUZETAK!
} catch (invalid_argument& e) {
    // Hvatanje specifičnog izuzetka
    cout << "Greška: " << e.what() << endl;
} catch (exception& e) {
    // Hvatanje opšte klase
    cout << "Opšti izuzetak: " << e.what() << endl;
}
```

**Standardni Izuzeci iz `<stdexcept>`:**

| Izuzetak | Opis |
|----------|------|
| `invalid_argument` | Nevalidan argument funkcije |
| `out_of_range` | Indeks/vrednost van opsega |
| `length_error` | Predugo tekstualno polje |
| `overflow_error` | Prekoračenje dozvoljene vrednosti |
| `runtime_error` | Greška pri izvršavanju |
| `logic_error` | Logička greška |

**Primeri u fajlu:**
- Deljenje sa nulom → `invalid_argument`
- Pristup nizu → `out_of_range`
- Konverzija stringa → `invalid_argument`
- Validacija broja → Različiti izuzeci

---

### 2. **02_standardni_izuzeci_naprednije.cpp** - Standardni Izuzeci sa Klasama

**Bankovni sistem sa izuzecima:**

```cpp
class Bankovni_Racun {
    void uplata(double iznos) {
        if (iznos <= 0) {
            throw invalid_argument("Iznos uplate mora biti pozitivan!");
        }
        stanje += iznos;
    }

    void isplata(double iznos) {
        if (iznos > stanje) {
            throw out_of_range("Nedovoljno sredstava!");
        }
        stanje -= iznos;
    }
};
```

**Upravljač racuna sa pronalaženjem:**
```cpp
Bankovni_Racun* pronajdiRacun(const string& broj) {
    for (auto racun : racuni) {
        if (racun->getBrojRacuna() == broj) {
            return racun;
        }
    }
    throw out_of_range("Racun nije pronaden!");  // Bacanje izuzetka
}
```

**Ključni koncepti:**
- Bacanje izuzetka sa `throw`
- Hvatanje sa `catch`
- Redosled catch blokova (specifičan pre opšteg)
- Destruktor sa čisćenjem memorije

---

### 3. **03_custom_izuzeci_bankovni.cpp** - Prilagođeni Izuzeci

**Bazna klasa za izuzetke:**
```cpp
class BankovniIzuzetak : public exception {
protected:
    string poruka;

public:
    BankovniIzuzetak(const string& p) : poruka(p) { }

    const char* what() const noexcept override {
        return poruka.c_str();
    }

    virtual void prikaziDetalje() const {
        cout << "Bankovni izuzetak: " << poruka << endl;
    }
};
```

**Derivovani Izuzetak 1 - NedovoljnoSredstavaIzuzetak:**
```cpp
class NedovoljnoSredstavaIzuzetak : public BankovniIzuzetak {
private:
    double dostupno;
    double trazeno;

public:
    double nedostaje() const { return trazeno - dostupno; }
    void prikaziDetalje() const override { ... }
};
```

**Derivovani Izuzetak 2 - InvalidanIznos:**
```cpp
class InvalidanIznos : public BankovniIzuzetak {
private:
    double iznos;
    string tip_operacije;

public:
    void prikaziDetalje() const override { ... }
};
```

**Korišćenje:**
```cpp
try {
    racun.isplata(50000);  // Nedovoljno sredstava
} catch (NedovoljnoSredstavaIzuzetak& e) {
    e.prikaziDetalje();  // Specijalne informacije
    cout << "Nedostaje: " << e.nedostaje() << " RSD" << endl;
} catch (BankovniIzuzetak& e) {
    cout << "Bankovni izuzetak: " << e.what() << endl;
}
```

---

### 4. **04_custom_izuzeci_matematika.cpp** - Kompleksniji Sistem

**Bazna klasa - MatematiCkiIzuzetak:**
```cpp
class MatematiCkiIzuzetak : public exception {
protected:
    string poruka;
    string operacija;

public:
    string getOperacija() const { return operacija; }
    virtual void prikaziDetalje() const { ... }
};
```

**Tri derivovane klase:**

1. **DeljenjeSaNulom** - Deljenje sa nulom
   - Čuva brojilac
   - Prikazuje da deljenje sa nulom nije definisano

2. **KorenNegativnogBroja** - Kvadratni koren negativnog
   - Čuva broj
   - Predlaže kompleksne brojeve

3. **DomenaPrekracena** - Vrednost van dozvoljenog raspona
   - Čuva vrednost i granice
   - Prikazuje dozvoljeno polje

**Primer korišćenja:**
```cpp
try {
    double x = Kalkulator::deli(100, 0);
} catch (DeljenjeSaNulom& e) {
    e.prikaziDetalje();
    double b = e.getBrojilac();
}
```

---

## Ključni Koncepti

### Try-Catch Mehanizam

```cpp
try {
    // Kod koji može baciti izuzetak
    int rezultat = deli(10, 0);
    cout << rezultat;  // Neće se izvršiti ako ima izuzetka
} catch (invalid_argument& e) {
    // Specifičan catch
    cout << e.what();
} catch (exception& e) {
    // Opšti catch
    cout << e.what();
}
// Izvršavanje nastavlja ovde
```

### Bacanje Izuzetka

```cpp
double deli(double a, double b) {
    if (b == 0) {
        throw invalid_argument("Ne mogu deliti sa nulom!");  // Bacanje
    }
    return a / b;
}
```

### Hvatanje Izuzetka

```cpp
try {
    // ...
} catch (const exception& e) {
    // BEST PRACTICE: const reference
    cout << e.what();
}
```

### Custom Izuzeci

```cpp
class MojIzuzetak : public exception {
private:
    string poruka;

public:
    MojIzuzetak(const string& p) : poruka(p) { }

    const char* what() const noexcept override {
        return poruka.c_str();
    }
};
```

### Redosled Catch Blokova

```cpp
try {
    // ...
} catch (DervirovanaKlasa& e) {
    // PRVO specifičnija
} catch (BaznaKlasa& e) {
    // ZATIM opštija
} catch (exception& e) {
    // POSLE i opštija
} catch (...) {
    // POSLEDNJA - hvata sve!
}
```

---

## Hierarchija Standardnih Izuzetaka

```
exception
├── logic_error
│   ├── invalid_argument
│   ├── length_error
│   ├── out_of_range
│   └── ...
└── runtime_error
    ├── overflow_error
    ├── underflow_error
    └── ...
```

---

## Kompajliranje i Pokretanje

```bash
# Primer 1 - Standardni izuzeci
g++ -o standardni 01_standardni_izuzeci.cpp
./standardni

# Primer 2 - Naprednije sa klasama
g++ -o naprednije 02_standardni_izuzeci_naprednije.cpp
./naprednije

# Primer 3 - Custom bankovni izuzeci
g++ -o bankovni 03_custom_izuzeci_bankovni.cpp
./bankovni

# Primer 4 - Matematički izuzeci
g++ -o matematika 04_custom_izuzeci_matematika.cpp
./matematika
```

---

## Best Practices

### ✓ DOBRO:

```cpp
// 1. Hvataj const referencom
try {
    // ...
} catch (const exception& e) {
    cout << e.what();
}

// 2. Specifičnija pre opštije
catch (DerjivovanaKlasa& e) { }
catch (BaznaKlasa& e) { }
catch (exception& e) { }

// 3. Baci right, sa detaljnom porukom
throw invalid_argument("Iznos mora biti > 0!");

// 4. Override what() - noexcept
const char* what() const noexcept override {
    return poruka.c_str();
}

// 5. Čistiti resurse (RAII)
try {
    FILE* f = fopen("file.txt", "r");
    // ...
} catch (...) {
    // Resursi se čiste automatski
}
```

### ✗ LOŠE:

```cpp
// 1. Hvatanje po vrednosti - loše!
catch (exception e) {
    cout << e.what();  // Slicing problem
}

// 2. Golfy catch - ne govori šta se dešava
catch (...) { }

// 3. Prosljeđivanje greške u void
void funkcija() {
    // Ako baci izuzetak, uvek će biti problem
}

// 4. Bacanje od void*
throw 5;  // LOŠE - bacam int, a ne exception!

// 5. Memorijske curenja
try {
    int* ptr = new int(10);
    throw exception();
    delete ptr;  // NIKAD se neće izvršiti!
} catch (...) { }
```

---

## Česta Pitanja

**P: Šta je razlika između throw i throw?**
O: `throw;` sa samo ključnom reči ponovno baca trenutni izuzetak, a `throw new_exception()` baca novi.

**P: Mogu li baciti bilo šta?**
O: Tehnički DA, ali trebao bi bacati `exception` ili njegove izvedene klase.

**P: Šta je `noexcept`?**
O: Obećanje da funkcija neće baciti izuzetak. Korisno za optimizaciju.

**P: Šta se dešava ako nema catch bloka?**
O: Program se prekida (crash) sa greškom.

**P: Mogu li koristiti izuzetke u destruktoru?**
O: NE - destruktor treba biti `noexcept` i ne sme bacati izuzetke.

---

## Praktični Primeri Upotrebe

```cpp
// 1. Validacija ulaza
if (vrednost < 0) {
    throw invalid_argument("Vrednost ne sme biti negativna!");
}

// 2. Pristup kontejneru
if (indeks >= size()) {
    throw out_of_range("Indeks van opsega!");
}

// 3. File operacije
if (!file_open) {
    throw runtime_error("Datoteka se nije mogla otvoriti!");
}

// 4. Alokacija memorije
if (!memory) {
    throw bad_alloc();
}
```

---

## Vežbe za Proširenje

1. **Bankovni sistem**: Dodaj `PrekracenLimitIzuzetak` za prekoračenje dnevnog limita
2. **Matematika**: Dodaj `MatricaIzuzetak` za operacije sa matricama
3. **Datoteke**: Kreiraj sistem za rad sa datotekama sa custom izuzecima
4. **Lanac uhvatanja**: Kreiraj sistem gde se izuzetak baca kroz više nivoa

---

## Sve Datoteke

- `01_standardni_izuzeci.cpp` - Osnovni standardni izuzeci
- `02_standardni_izuzeci_naprednije.cpp` - Sa klasama i upravljačem
- `03_custom_izuzeci_bankovni.cpp` - Prilagođeni bankovni izuzeci
- `04_custom_izuzeci_matematika.cpp` - Prilagođeni matematički izuzeci
- `README.md` - Ovaj fajl
