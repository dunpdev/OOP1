#include <iostream>
#include <memory>
#include <string>

class Automobil; 

class Osoba {
public:
    std::string ime;
    // Osoba DELI vlasništvo nad automobilom sa drugima
    std::shared_ptr<Automobil> mojAuto; 

    Osoba(const std::string& ime) : ime(ime) {
        std::cout << "  [+] Osoba " << ime << " je kreirana." << std::endl;
    }
    ~Osoba() {
        std::cout << "  [-] Osoba " << ime << " je unistena." << std::endl;
    }
};

class Automobil {
public:
    std::string model;
    // Automobil NE POSEDUJE osobu, samo je "posmatra". 
    // Da smo ovde stavili shared_ptr, imali bismo CIKLUS i curenje memorije!
    std::weak_ptr<Osoba> vlasnik; 

    Automobil(const std::string& model) : model(model) {
        std::cout << "  [+] Automobil " << model << " je kreiran." << std::endl;
    }
    ~Automobil() {
        std::cout << "  [-] Automobil " << model << " je unisten." << std::endl;
    }
    
    void ispisiVlasnika() {
        // Da bismo koristili weak_ptr, moramo ga "zakljucati" (lock) 
        // cime ga privremeno pretvaramo u shared_ptr ako objekat jos postoji.
        if (std::shared_ptr<Osoba> privremeniVlasnik = vlasnik.lock()) {
            std::cout << "Vlasnik auta " << model << " je " << privremeniVlasnik->ime << std::endl;
        } else {
            std::cout << "Auto " << model << " trenutno nema vlasnika (ili je unisten)." << std::endl;
        }
    }
};

int main() {
    std::cout << "=== 1. nullptr ===" << std::endl;
    // nullptr zamenjuje stari NULL (koji je bio samo int 0). 
    // nullptr je strogo tipiziran (std::nullptr_t) i ne moze se slucajno pomesati sa brojem.
    int* stariPokazivac = nullptr; 
    if (stariPokazivac == nullptr) {
        std::cout << "Pokazivac je bezbedno null.\n\n";
    }

    std::cout << "=== 2. std::unique_ptr ===" << std::endl;
    {
        // unique_ptr ima EKSKLUZIVNO (1 na 1) vlasnistvo nad memorijom.
        // std::make_unique je najbezbedniji nacin za kreiranje (C++14).
        std::unique_ptr<int> jedinstveni = std::make_unique<int>(100);
        
        std::cout << "Vrednost unique_ptr: " << *jedinstveni << std::endl;
        
        // std::unique_ptr<int> kopija = jedinstveni; // OVO CE BACITI GRESKU! Ne moze se kopirati!
        
        // Vlasnistvo se mora EKSPLICITNO PREBACITI koriscenjem std::move
        std::unique_ptr<int> noviVlasnik = std::move(jedinstveni);
        
        if (jedinstveni == nullptr) {
             std::cout << "Stari pokazivac je sada nullptr, vlasnistvo je preneto.\n";
        }
        std::cout << "Nova vrednost: " << *noviVlasnik << "\n";
    } // Ovde 'noviVlasnik' izlazi iz opsega (scope) i memorija (100) se AUTOMATSKI brise.
    std::cout << "Memorija od unique_ptr je automatski oslobodjena.\n\n";


    std::cout << "=== 3. i 4. std::shared_ptr i std::weak_ptr ===" << std::endl;
    {
        // shared_ptr dozvoljava VISE pokazivaca na istu memoriju. 
        // Vodi evidenciju (Reference Count) koliko ih ima.
        std::shared_ptr<Osoba> marko = std::make_shared<Osoba>("Marko");
        std::shared_ptr<Automobil> bmw = std::make_shared<Automobil>("BMW M3");

        std::cout << "Reference count za BMW: " << bmw.use_count() << std::endl;

        // Marko kupuje BMW
        marko->mojAuto = bmw;
        std::cout << "Reference count za BMW nakon sto ga je Marko kupio: " << bmw.use_count() << std::endl;

        // BMW bezi vlasnika u weak_ptr
        bmw->vlasnik = marko;
        // Primeti: weak_ptr NE POVECAVA reference count od 'marko'!
        std::cout << "Reference count za Marka: " << marko.use_count() << " (weak_ptr ga ne povecava)" << std::endl;

        bmw->ispisiVlasnika();
        
        std::cout << "\n[!] Unistavam Marka (izlazak iz bloka)...\n";
    } 
    // 1. Unistava se 'marko' (ref count pada na 0). Poziva se destruktor Osobe.
    // 2. Posto se unistava 'marko', unistava se i njegov shared_ptr 'mojAuto'.
    // 3. To smanjuje ref count za BMW na 0. Poziva se destruktor Automobila.
    // Nema curenja memorije!
    
    std::cout << "Program zavrsen uspesno.\n";
    return 0;
}
