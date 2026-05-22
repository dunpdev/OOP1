#include <iostream>
#include <vector>
#include <thread>
#include <cmath>
#include <chrono>

class PretrazivacProstih {
private:
    int start, kraj;
    std::string ime_niti;
    std::vector<int> pronadjeni_brojevi; 

public:
    PretrazivacProstih(std::string ime, int s, int k) 
        : ime_niti(ime), start(s), kraj(k) {}

    bool daLiJeProst(int n) {
        if (n <= 1) return false;
        if (n <= 3) return true;
        if (n % 2 == 0 || n % 3 == 0) return false;
        
        for (int i = 5; i * i <= n; i = i + 6) {
            if (n % i == 0 || n % (i + 2) == 0)
                return false;
        }
        return true;
    }

    void operacija() {
        std::cout << "[Sistem] Nit '" << ime_niti << "' pokrece pretragu od " << start << " do " << kraj << "...\n";
        
        for (int i = start; i <= kraj; ++i) {
            if (daLiJeProst(i)) {
                pronadjeni_brojevi.push_back(i);
            }
        }
        
        std::cout << "[Sistem] Nit '" << ime_niti << "' je zavrsila. Pronasla je " << pronadjeni_brojevi.size() << " prostih brojeva.\n";
    }

    void prikaziRezultate() {
        std::cout << "Rezultati za " << ime_niti << ": ";
        for (int br : pronadjeni_brojevi) {
            std::cout << br << " ";
        }
        std::cout << "\n\n";
    }
};

int main() {
    int max_broj = 500;
    int sredina = max_broj / 2;

    PretrazivacProstih radnik1("Nizak-Opseg", 1, sredina);
    PretrazivacProstih radnik2("Visok-Opseg", sredina + 1, max_broj);

    std::cout << "--- START PARALELNE OBRADE ---\n";

    std::thread t1(&PretrazivacProstih::operacija, &radnik1);
    std::thread t2(&PretrazivacProstih::operacija, &radnik2);

    t1.join();
    t2.join();

    std::cout << "--- OBRADA ZAVRSENA ---\n";

    radnik1.prikaziRezultate();
    radnik2.prikaziRezultate();

    return 0;
}
