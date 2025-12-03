#include <iostream>
#include <cstring>
using namespace std;

class Biblioteca {
private:
    const int idBiblioteca;
    static int numarBiblioteci;
    char* nume;
    string adresa;
    float suprafata;
    int nrSectiuni;
    int* cartiPeSectiune;

public:
    void setSuprafata(float suprafata) {
        if (suprafata > 0) this->suprafata = suprafata;
    }

    float getSuprafata() {
        return this->suprafata;
    }

    char* getNume() {
        return this->nume;
    }

    void setNume(const char* numeNou) {
        if (numeNou && strlen(numeNou) > 0) {
            if (this->nume) delete[] this->nume;
            this->nume = new char[strlen(numeNou) + 1];
            strcpy_s(this->nume, strlen(numeNou) + 1, numeNou);
        }
    }

    void setAdresa(string adr) {
        if (!adr.empty()) this->adresa = adr;
    }

    string getAdresa() {
        return this->adresa;
    }

    void setCartiPeSectiune(int nrSectiuni, int* carti) {
        if (nrSectiuni > 0 && carti) {
            this->nrSectiuni = nrSectiuni;
            if (this->cartiPeSectiune) delete[] this->cartiPeSectiune;
            this->cartiPeSectiune = new int[nrSectiuni];
            for (int i = 0; i < nrSectiuni; i++)
                this->cartiPeSectiune[i] = carti[i];
        }
    }

    int getCartiSectiune(int index) {
        if (index >= 0 && index < nrSectiuni) return cartiPeSectiune[index];
        throw 404;
    }

    int getNrSectiuni() {
        return this->nrSectiuni;
    }

    int getIdBiblioteca() {
        return this->idBiblioteca;
    }

    static int getNumarBiblioteci() {
        return numarBiblioteci;
    }

    Biblioteca() : idBiblioteca(++numarBiblioteci) {
        nume = nullptr;
        adresa = "Necunoscuta";
        suprafata = 0;
        nrSectiuni = 0;
        cartiPeSectiune = nullptr;
    }

    Biblioteca(const char* nume, string adresa, float suprafata,
        int nrSectiuni, const int* carti)
        : idBiblioteca(++numarBiblioteci)
    {
        this->adresa = adresa;
        this->suprafata = suprafata > 0 ? suprafata : 0;
        this->nrSectiuni = nrSectiuni > 0 ? nrSectiuni : 0;

        if (nume && strlen(nume) > 0) {
            this->nume = new char[strlen(nume) + 1];
            strcpy_s(this->nume, strlen(nume) + 1, nume);
        }
        else {
            this->nume = nullptr;
        }

        if (this->nrSectiuni > 0 && carti) {
            this->cartiPeSectiune = new int[this->nrSectiuni];
            for (int i = 0; i < this->nrSectiuni; i++)
                this->cartiPeSectiune[i] = carti[i];
        }
        else {
            this->cartiPeSectiune = nullptr;
            this->nrSectiuni = 0;
        }
    }

    Biblioteca(const Biblioteca& b) : idBiblioteca(++numarBiblioteci) {
        adresa = b.adresa;
        suprafata = b.suprafata;
        nrSectiuni = b.nrSectiuni;

        if (b.nume) {
            nume = new char[strlen(b.nume) + 1];
            strcpy_s(nume, strlen(b.nume) + 1, b.nume);
        }
        else nume = nullptr;

        if (b.cartiPeSectiune && b.nrSectiuni > 0) {
            cartiPeSectiune = new int[b.nrSectiuni];
            for (int i = 0; i < b.nrSectiuni; i++)
                cartiPeSectiune[i] = b.cartiPeSectiune[i];
        }
        else cartiPeSectiune = nullptr;
    }

    void operator=(const Biblioteca& b) {
        if (this == &b) return;

        adresa = b.adresa;
        suprafata = b.suprafata;
        nrSectiuni = b.nrSectiuni;

        if (nume) delete[] nume;
        if (b.nume) {
            nume = new char[strlen(b.nume) + 1];
            strcpy_s(nume, strlen(b.nume) + 1, b.nume);
        }
        else nume = nullptr;

        if (cartiPeSectiune) delete[] cartiPeSectiune;
        if (b.cartiPeSectiune && b.nrSectiuni > 0) {
            cartiPeSectiune = new int[b.nrSectiuni];
            for (int i = 0; i < b.nrSectiuni; i++)
                cartiPeSectiune[i] = b.cartiPeSectiune[i];
        }
        else {
            cartiPeSectiune = nullptr;
            nrSectiuni = 0;
        }
    }

    ~Biblioteca() {
        if (nume) delete[] nume;
        if (cartiPeSectiune) delete[] cartiPeSectiune;
    }

    void operator+=(float x) {
        suprafata += x;
    }

    friend Biblioteca operator+=(float x, Biblioteca& b) {
        b.suprafata += x;
        return b;
    }

    bool operator<(const Biblioteca& b) {
        return suprafata < b.suprafata;
    }

    bool operator!() {
        return suprafata == 0;
    }

    int operator()(int index) {
        return getCartiSectiune(index);
    }

    char& operator[](int index) {
        if (!nume) throw "Nume inexistent!";
        if (index < 0 || index >= (int)strlen(nume)) throw "Index invalid!";
        return nume[index];
    }

    explicit operator int() {
        int total = 0;
        for (int i = 0; i < nrSectiuni; i++) total += cartiPeSectiune[i];
        return total;
    }

    Biblioteca operator++(int) {
        Biblioteca copie = *this;
        suprafata++;
        return copie;
    }

    Biblioteca operator++() {
        suprafata++;
        return *this;
    }

    void afisare() {
        cout << endl << idBiblioteca << ". Biblioteca: "
            << (nume ? nume : "Fara nume")
            << " | Adresa: " << adresa
            << " | Suprafata: " << suprafata
            << " mp | Sectiuni: " << nrSectiuni;
        if (nrSectiuni > 0 && cartiPeSectiune) {
            cout << " | Carti pe sectiune: ";
            for (int i = 0; i < nrSectiuni; i++)
                cout << cartiPeSectiune[i] << (i < nrSectiuni - 1 ? ", " : "");
        }
    }

    friend void operator<<(ostream& out, Biblioteca b) {
        out << endl << "ID: " << b.idBiblioteca;
        out << endl << "Nume: " << (b.nume ? b.nume : (char*)"N/A");
        out << endl << "Adresa: " << b.adresa;
        out << endl << "Suprafata: " << b.suprafata;
        out << endl << "Nr sectiuni: " << b.nrSectiuni;
        if (b.cartiPeSectiune && b.nrSectiuni > 0) {
            out << endl << "Carti: ";
            for (int i = 0; i < b.nrSectiuni; i++)
                out << b.cartiPeSectiune[i] << " ";
        }
    }

    friend void operator>>(istream& in, Biblioteca& b) {
        char buf[100];
        in >> buf;
        b.setNume(buf);
        in >> b.adresa;
        in >> b.suprafata;
        in >> b.nrSectiuni;
        if (b.cartiPeSectiune) delete[] b.cartiPeSectiune;
        if (b.nrSectiuni > 0) {
            b.cartiPeSectiune = new int[b.nrSectiuni];
            for (int i = 0; i < b.nrSectiuni; i++)
                in >> b.cartiPeSectiune[i];
        }
        else {
            b.cartiPeSectiune = nullptr;
        }
    }
};

int Biblioteca::numarBiblioteci = 0;

int main() {
    int v[3] = { 1000, 1500, 2000 };

    Biblioteca b1("BibliotecaUPB", "Bucuresti", 500, 3, v);
    Biblioteca b2 = b1;

    b1.afisare();
    b2.afisare();

    cout << b1;

    b1 += 20;
    b1.afisare();

    cout << endl << "Carti in sectiunea 2: " << b1(1);
    cout << endl << "Litera din nume[2]: " << b1[2];

    cout << endl << "Total carti (cast la int): " << (int)b1;

    cout << endl << "Numar biblioteci create: " << Biblioteca::getNumarBiblioteci();

    return 0;
}
