#include <iostream>
#include <cstring>
using namespace std;

class Produs {
private:
    char* nume;
    double pret;
    char* categorie;
    int stoc;
    bool disponibil;

public:
    Produs() {
        nume = nullptr;
        categorie = nullptr;
        pret = 0;
        stoc = 0;
        disponibil = false;
    }

    Produs(const char* nume, double pret, const char* categorie, int stoc, bool disponibil) {
        if (nume && strlen(nume) > 0) {
            this->nume = new char[strlen(nume) + 1];
            strcpy_s(this->nume, strlen(nume) + 1, nume);
        }
        else {
            this->nume = new char[8];
            strcpy_s(this->nume, 8, "Anonim");
        }

        if (pret > 0) this->pret = pret;
        else this->pret = 0;

        if (categorie && strlen(categorie) > 0) {
            this->categorie = new char[strlen(categorie) + 1];
            strcpy_s(this->categorie, strlen(categorie) + 1, categorie);
        }
        else {
            this->categorie = new char[9];
            strcpy_s(this->categorie, 9, "General");
        }

        if (stoc >= 0) this->stoc = stoc;
        else this->stoc = 0;

        this->disponibil = disponibil;
    }

    Produs(const Produs& p) {
        if (p.nume) {
            this->nume = new char[strlen(p.nume) + 1];
            strcpy_s(this->nume, strlen(p.nume) + 1, p.nume);
        }
        else this->nume = nullptr;

        if (p.categorie) {
            this->categorie = new char[strlen(p.categorie) + 1];
            strcpy_s(this->categorie, strlen(p.categorie) + 1, p.categorie);
        }
        else this->categorie = nullptr;

        this->pret = p.pret;
        this->stoc = p.stoc;
        this->disponibil = p.disponibil;
    }

    Produs& operator=(const Produs& p) {
        if (this == &p) return *this;

        if (nume) delete[] nume;
        if (categorie) delete[] categorie;

        if (p.nume) {
            nume = new char[strlen(p.nume) + 1];
            strcpy_s(nume, strlen(p.nume) + 1, p.nume);
        }
        else nume = nullptr;

        if (p.categorie) {
            categorie = new char[strlen(p.categorie) + 1];
            strcpy_s(categorie, strlen(p.categorie) + 1, p.categorie);
        }
        else categorie = nullptr;

        pret = p.pret;
        stoc = p.stoc;
        disponibil = p.disponibil;

        return *this;
    }

    ~Produs() {
        if (nume) delete[] nume;
        if (categorie) delete[] categorie;
    }

    double getPret() const { return pret; }
    void setPret(double pret) { if (pret > 0) this->pret = pret; }

    int getStoc() const { return stoc; }
    void setStoc(int stoc) { if (stoc >= 0) this->stoc = stoc; }

    bool getDisponibil() const { return disponibil; }
    void setDisponibil(bool disponibil) { this->disponibil = disponibil; }

    void afisare() const {
        cout << "Produs: ";
        if (nume) cout << nume; else cout << "N/A";
        cout << ", categorie: ";
        if (categorie) cout << categorie; else cout << "N/A";
        cout << ", pret: " << pret << ", stoc: " << stoc
            << ", disponibil: " << (disponibil ? "da" : "nu") << endl;
    }
};

int main() {
    Produs p1;
    p1.afisare();

    Produs p2("Laptop", 3500.5, "Electronice", 10, true);
    p2.afisare();

    cout << p2.getPret() << endl;
    p2.setPret(3200.75);
    cout << p2.getPret() << endl;

    Produs p3 = p2;
    p3.afisare();

    Produs p4("Telefon", 2500, "Electronice", 20, true);
    p4 = p2;
    p4.afisare();

    p4 = p4;

    return 0;
}
