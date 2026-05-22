#include <iostream>
#include <thread>
#include <chrono>

class Kalkulator {
private:
    int id_niti;
    int delilac;
    int pauza_sekunde;

public:
    Kalkulator(int id, int n, int sekunde) 
        : id_niti(id), delilac(n), pauza_sekunde(sekunde) {}

    void izracunaj() {
        if (pauza_sekunde > 0) {
            std::cout << "Nit " << id_niti << " ide na spavanje " << pauza_sekunde << " sekundi...\n";
            std::this_thread::sleep_for(std::chrono::seconds(pauza_sekunde));
            std::cout << "Nit " << id_niti << " se probudila!\n";
        }

        std::cout << "Nit " << id_niti << " pocinje ispis brojeva do 100 deljivih sa " << delilac << ":\n";
        
        for (int i = 1; i <= 100; ++i) {
            if (i % delilac == 0) {
                std::cout << "[Nit " << id_niti << "] Broj: " << i << "\n";
            }
        }
        
        std::cout << "Nit " << id_niti << " je zavrsila sa radom.\n";
    }
};

int main() {
    std::cout << "Glavni program pocinje.\n\n";

    Kalkulator objekat1(1, 7, 10); 
    Kalkulator objekat2(2, 5, 0);  

    std::thread nit1(&Kalkulator::izracunaj, &objekat1);
    std::thread nit2(&Kalkulator::izracunaj, &objekat2);

    nit1.join();
    nit2.join();

    std::cout << "\nSve niti su zavrsile. Glavni program se gasi.\n";

    return 0;
}
