#include <iostream>
#include <cstring>
using namespace std;

class Masina {
private:
    const int IdMasina;
    static int numarMasini;

    char* nume;
    string culoare;
    float pret;
    int anFabricatie;

public:

    
    void setpret(float pret) {
        if (pret > 0) this->pret = pret;
    }

    float getpret() const {
        return this->pret;
    }

    char* getNume() const {
        return this->nume;
    }

    void setNume(const char* nume) {
        if (nume && strlen(nume) > 0) {
            if (this->nume != nullptr) delete[] this->nume;
            this->nume = new char[strlen(nume) + 1];
            strcpy_s(this->nume, strlen(nume) + 1, nume);
        }
    }

    void setCuloare(string culoare) {
        if (!culoare.empty()) this->culoare = culoare;
    }

    string getCuloare() const {
        return this->culoare;
    }

    int getanFabricatie() const {
        return this->anFabricatie;
    }

    int getIdMasina() const {
        return this->IdMasina;
    }

    static int getnumarMasini() {
        return numarMasini;
    }

    
    Masina() : IdMasina(++numarMasini) {
        this->nume = nullptr;
        this->culoare = "Necunoscuta";
        this->pret = 0;
        this->anFabricatie = 0;
    }

    // ---------- CONSTRUCTOR COMPLET ----------
    Masina(const char* nume, string culoare, float pret, int anFabricatie)
        : IdMasina(++numarMasini)
    {
        // nume
        if (nume) {
            this->nume = new char[strlen(nume) + 1];
            strcpy_s(this->nume, strlen(nume) + 1, nume);
        }
        else {
            this->nume = nullptr;
        }

        this->culoare = culoare;
        this->pret = pret;
        this->anFabricatie = anFabricatie;
    }

    
    Masina(const Masina& m) : IdMasina(++numarMasini) {
        this->culoare = m.culoare;
        this->pret = m.pret;
        this->anFabricatie = m.anFabricatie;

        if (m.nume) {
            this->nume = new char[strlen(m.nume) + 1];
            strcpy_s(this->nume, strlen(m.nume) + 1, m.nume);
        }
        else {
            this->nume = nullptr;
        }
    }

  
    Masina& operator=(const Masina& m) {
        if (this == &m) return *this;

        this->culoare = m.culoare;
        this->pret = m.pret;
        this->anFabricatie = m.anFabricatie;

        if (this->nume) delete[] this->nume;

        if (m.nume) {
            this->nume = new char[strlen(m.nume) + 1];
            strcpy_s(this->nume, strlen(m.nume) + 1, m.nume);
        }
        else {
            this->nume = nullptr;
        }

        return *this;
    }

    
    void afisareMasina() const {
        cout << endl << this->getIdMasina() << ". Masina ";

        if (this->nume) cout << this->nume;
        else cout << "Neidentificata";

        cout << ", culoare: " << this->culoare
            << ", pret: " << this->pret << " EUR"
            << ", anul fabricatiei: " << this->anFabricatie;
    }

    
    void operator+=(float valoare) {
        this->pret += valoare;
    }

    bool operator<(const Masina& m) const {
        return this->pret < m.pret;
    }

    bool operator!() const {
        return this->anFabricatie != 0;
    }

    
    ~Masina() {
        if (this->nume) delete[] this->nume;
    }
};

int Masina::numarMasini = 0;

int main() {
    Masina m1("Dacia Logan", "Alb", 5000, 2012);
    Masina m2("Audi A4", "Negru", 12000, 2018);

    m1.afisareMasina();
    m2.afisareMasina();

    m1 += 500;
    m1.afisareMasina();

    if (m1 < m2) cout << "\nMasina 1 este mai ieftina.";
    else cout << "\nMasina 2 este mai ieftina.";

    Masina copie = m2;
    copie.afisareMasina();

    return 0;
}
