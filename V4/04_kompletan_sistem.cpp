#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
using namespace std;

// ===== BAZNA KLASA =====
class Zivotinja {
protected:
    string ime;
    int godine;
    double tezina;
    static int ukupnoZivotinja;

public:
    Zivotinja(string i, int g, double t)
        : ime(i), godine(g), tezina(t) {
        ukupnoZivotinja++;
        cout << "[RODJENA] Zivotinja: " << ime << endl;
    }

    virtual ~Zivotinja() {
        ukupnoZivotinja--;
        cout << "[UMRLA] Zivotinja: " << ime << endl;
    }

    virtual void zvuk() const {
        cout << ime << " izdaje neki zvuk" << endl;
    }

    virtual void hrani() const {
        cout << ime << " jede hranu" << endl;
    }

    virtual void spi() const {
        cout << ime << " spava" << endl;
    }

    virtual void prikaziInfo() const {
        cout << "\n--- " << getVrsta() << " ---" << endl;
        cout << "Ime: " << ime << endl;
        cout << "Godine: " << godine << endl;
        cout << "Tezina: " << tezina << " kg" << endl;
    }

    virtual string getVrsta() const { return "Zivotinja"; }

    string getIme() const { return ime; }
    int getGodine() const { return godine; }
    double getTezina() const { return tezina; }

    static int getUkupno() { return ukupnoZivotinja; }
};

int Zivotinja::ukupnoZivotinja = 0;

// ===== IZVEDENA KLASA 1: PAS =====
class Pas : public Zivotinja {
private:
    string rasa;
    bool je_dresiran;

public:
    Pas(string i, int g, double t, string r, bool d)
        : Zivotinja(i, g, t), rasa(r), je_dresiran(d) {
        cout << "[PAS] " << ime << " pas je dodat u sistem" << endl;
    }

    ~Pas() {
        cout << "[PAS] " << ime << " je otpustен" << endl;
    }

    void zvuk() const override {
        cout << ime << " laje: Vau! Vau!" << endl;
    }

    void hrani() const override {
        cout << ime << " jede mesо i kroquete" << endl;
    }

    void prikaziInfo() const override {
        Zivotinja::prikaziInfo();
        cout << "Vrsta: Pas" << endl;
        cout << "Rasa: " << rasa << endl;
        cout << "Dresiran: " << (je_dresiran ? "DA" : "NE") << endl;
    }

    void igrajSeLopty() {
        cout << ime << " igra se lopty sa vlasnikom!" << endl;
    }

    void uci_komande() {
        if (!je_dresiran) {
            cout << ime << " uci nove komande..." << endl;
            je_dresiran = true;
        } else {
            cout << ime << " je vec dresiran!" << endl;
        }
    }

    string getVrsta() const override { return "Pas"; }
};

// ===== IZVEDENA KLASA 2: MACA =====
class Maca : public Zivotinja {
private:
    string boja;
    int broj_zivota;

public:
    Maca(string i, int g, double t, string b)
        : Zivotinja(i, g, t), boja(b), broj_zivota(9) {
        cout << "[MACA] " << ime << " maca je dodana u sistem" << endl;
    }

    ~Maca() {
        cout << "[MACA] " << ime << " je otpustena" << endl;
    }

    void zvuk() const override {
        cout << ime << " mjau: Mjaaaaau!" << endl;
    }

    void hrani() const override {
        cout << ime << " jede ribu i pastu" << endl;
    }

    void prikaziInfo() const override {
        Zivotinja::prikaziInfo();
        cout << "Vrsta: Maca" << endl;
        cout << "Boja: " << boja << endl;
        cout << "Zivota preostalo: " << broj_zivota << endl;
    }

    void lizе_sebe() {
        cout << ime << " se lize i cistи svoju dlaku" << endl;
    }

    void izgubi_zivot() {
        if (broj_zivota > 0) {
            broj_zivota--;
            cout << ime << " je izgubila jedan zivot! Preostalo: " << broj_zivota << endl;
        } else {
            cout << ime << " je ostala bez zivota!" << endl;
        }
    }

    string getVrsta() const override { return "Maca"; }
};

// ===== IZVEDENA KLASA 3: PTICA =====
class Ptica : public Zivotinja {
private:
    bool moze_leteti;
    string tip;

public:
    Ptica(string i, int g, double t, string tip_p, bool leta)
        : Zivotinja(i, g, t), tip(tip_p), moze_leteti(leta) {
        cout << "[PTICA] " << ime << " ptica je dodata u sistem" << endl;
    }

    ~Ptica() {
        cout << "[PTICA] " << ime << " je otpustena" << endl;
    }

    void zvuk() const override {
        cout << ime << " pjeva: Cvrčit čvrčit!" << endl;
    }

    void hrani() const override {
        cout << ime << " jede semе i insekte" << endl;
    }

    void prikaziInfo() const override {
        Zivotinja::prikaziInfo();
        cout << "Vrsta: Ptica" << endl;
        cout << "Tip: " << tip << endl;
        cout << "Moze leteti: " << (moze_leteti ? "DA" : "NE") << endl;
    }

    void leti() {
        if (moze_leteti) {
            cout << ime << " leti kroz vazduh sa brzinom!" << endl;
        } else {
            cout << ime << " ne moze leteti" << endl;
        }
    }

    void pravi_gnezdo() {
        cout << ime << " pravi gnezdo od granrica i travе" << endl;
    }

    string getVrsta() const override { return "Ptica"; }
};

// ===== ZOLOSKA BASTA =====
class ZoolskaBasta {
private:
    string naziv;
    vector<Zivotinja*> zivotinje;

public:
    ZoolskaBasta(string n) : naziv(n) {
        cout << "\n*** Zoloska basta '" << naziv << "' je otvorena! ***\n" << endl;
    }

    ~ZoolskaBasta() {
        cout << "\n*** Zoloska basta '" << naziv << "' je zatvorena! ***\n" << endl;
    }

    void dodajZivotinju(Zivotinja* z) {
        zivotinje.push_back(z);
        cout << "Zivotinja je dodata u bastu" << endl;
    }

    void sve_zivotinje_se_hrane() {
        cout << "\n[VREME HRANE] Sve zivotinje se hrane:" << endl;
        for (size_t i = 0; i < zivotinje.size(); i++) {
            zivotinje[i]->hrani();
        }
    }

    void sve_zivotinje_prave_zvuk() {
        cout << "\n[ZVUCI U BASTI]:" << endl;
        for (size_t i = 0; i < zivotinje.size(); i++) {
            zivotinje[i]->zvuk();
        }
    }

    void sve_zivotinje_spe() {
        cout << "\n[VREME ZA SPA]:" << endl;
        for (size_t i = 0; i < zivotinje.size(); i++) {
            zivotinje[i]->spi();
        }
    }

    void prikaziSveZivotinje() {
        cout << "\n========== SVE ZIVOTINJE U BASTI ==========" << endl;
        for (size_t i = 0; i < zivotinje.size(); i++) {
            zivotinje[i]->prikaziInfo();
        }
        cout << "===========================================\n" << endl;
    }

    int getBrojZivotinja() const { return zivotinje.size(); }
};

int main() {
    cout << "=== PRIMER 4: Kompletan Sistem sa Zivotinjama ===" << endl;

    ZoolskaBasta basta("Beljarica");

    cout << "--- Dodavanje zivotinja ---" << endl;
    Pas p1("Reks", 5, 25, "Nemacki Ovcar", true);
    Pas p2("Milo", 3, 20, "Labrador", false);
    Maca m1("Maca Mija", 4, 4, "Bela");
    Ptica pt1("Slavuj", 2, 0.05, "Певац", true);
    Ptica pt2("Strut", 15, 100, "Strut", false);

    basta.dodajZivotinju(&p1);
    basta.dodajZivotinju(&p2);
    basta.dodajZivotinju(&m1);
    basta.dodajZivotinju(&pt1);
    basta.dodajZivotinju(&pt2);

    basta.prikaziSveZivotinje();

    cout << "--- Aktivnosti u basti ---" << endl;
    basta.sve_zivotinje_prave_zvuk();

    p1.igrajSeLopty();
    p2.uci_komande();
    m1.lizе_sebe();
    pt1.leti();
    pt2.pravi_gnezdo();

    basta.sve_zivotinje_se_hrane();

    cout << "\n--- Dogadjaj sa macijicom ---" << endl;
    m1.izgubi_zivot();
    m1.prikaziInfo();

    cout << "\n--- Vreme za spa ---" << endl;
    basta.sve_zivotinje_spe();

    cout << "\n--- Statistika ---" << endl;
    cout << "Ukupno zivotinja u basti: " << basta.getBrojZivotinja() << endl;
    cout << "Ukupno zivotinja u sistemu: " << Zivotinja::getUkupno() << endl;

    return 0;
}
