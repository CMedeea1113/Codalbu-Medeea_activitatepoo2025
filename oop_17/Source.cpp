#include <iostream>
#include <cstring>
using namespace std;

class MagaziePieseAeronautice {
private:
    const int idMagazie;
    static int numarMagazii;
    char* nume;
    string locatie;
    int nrTipuriPiese;
    int* cantitatiPiese;
    float valoareTotala;

public:
    MagaziePieseAeronautice() : idMagazie(++numarMagazii) {
        nume = nullptr;
        locatie = "Necunoscuta";
        nrTipuriPiese = 0;
        cantitatiPiese = nullptr;
        valoareTotala = 0;
    }

    MagaziePieseAeronautice(const char* nume, string locatie,
        int nrTipuriPiese, const int* cantitatiPiese,
        float valoareTotala)
        : idMagazie(++numarMagazii)
    {
        if (nume && strlen(nume) > 0) {
            this->nume = new char[strlen(nume) + 1];
            strcpy_s(this->nume, strlen(nume) + 1, nume);
        }
        else {
            this->nume = nullptr;
        }

        this->locatie = locatie;
        this->nrTipuriPiese = nrTipuriPiese > 0 ? nrTipuriPiese : 0;

        if (this->nrTipuriPiese > 0 && cantitatiPiese) {
            this->cantitatiPiese = new int[this->nrTipuriPiese];
            for (int i = 0; i < this->nrTipuriPiese; i++)
                this->cantitatiPiese[i] = cantitatiPiese[i];
        }
        else {
            this->cantitatiPiese = nullptr;
            this->nrTipuriPiese = 0;
        }

        this->valoareTotala = valoareTotala >= 0 ? valoareTotala : 0;
    }

    MagaziePieseAeronautice(const MagaziePieseAeronautice& m)
        : idMagazie(++numarMagazii)
    {
        locatie = m.locatie;
        nrTipuriPiese = m.nrTipuriPiese;
        valoareTotala = m.valoareTotala;

        if (m.nume) {
            nume = new char[strlen(m.nume) + 1];
            strcpy_s(nume, strlen(m.nume) + 1, m.nume);
        }
        else nume = nullptr;

        if (m.cantitatiPiese && m.nrTipuriPiese > 0) {
            cantitatiPiese = new int[m.nrTipuriPiese];
            for (int i = 0; i < m.nrTipuriPiese; i++)
                cantitatiPiese[i] = m.cantitatiPiese[i];
        }
        else cantitatiPiese = nullptr;
    }

    void operator=(const MagaziePieseAeronautice& m) {
        if (this == &m) return;

        locatie = m.locatie;
        nrTipuriPiese = m.nrTipuriPiese;
        valoareTotala = m.valoareTotala;

        if (nume) delete[] nume;
        if (m.nume) {
            nume = new char[strlen(m.nume) + 1];
            strcpy_s(nume, strlen(m.nume) + 1, m.nume);
        }
        else nume = nullptr;

        if (cantitatiPiese) delete[] cantitatiPiese;
        if (m.cantitatiPiese && m.nrTipuriPiese > 0) {
            cantitatiPiese = new int[m.nrTipuriPiese];
            for (int i = 0; i < m.nrTipuriPiese; i++)
                cantitatiPiese[i] = m.cantitatiPiese[i];
        }
        else {
            cantitatiPiese = nullptr;
            nrTipuriPiese = 0;
        }
    }

    ~MagaziePieseAeronautice() {
        if (nume) delete[] nume;
        if (cantitatiPiese) delete[] cantitatiPiese;
    }

    void setNume(const char* numeNou) {
        if (numeNou && strlen(numeNou) > 0) {
            if (nume) delete[] nume;
            nume = new char[strlen(numeNou) + 1];
            strcpy_s(nume, strlen(numeNou) + 1, numeNou);
        }
    }

    char* getNume() { return nume; }

    void setLocatie(string loc) {
        if (!loc.empty()) locatie = loc;
    }

    string getLocatie() { return locatie; }

    void setValoareTotala(float v) {
        if (v >= 0) valoareTotala = v;
    }

    float getValoareTotala() { return valoareTotala; }

    void setCantitatiPiese(int nr, int* cantitati) {
        if (nr > 0 && cantitati) {
            nrTipuriPiese = nr;
            if (cantitatiPiese) delete[] cantitatiPiese;
            cantitatiPiese = new int[nr];
            for (int i = 0; i < nr; i++)
                cantitatiPiese[i] = cantitati[i];
        }
    }

    int getCantitatePiesa(int index) {
        if (index >= 0 && index < nrTipuriPiese) return cantitatiPiese[index];
        throw 404;
    }

    int getNrTipuriPiese() { return nrTipuriPiese; }

    int getIdMagazie() { return idMagazie; }

    static int getNumarMagazii() { return numarMagazii; }

    void afisare() {
        cout << endl << idMagazie << ". Magazie piese aeronautice: "
            << (nume ? nume : "Fara nume")
            << " | Locatie: " << locatie
            << " | Nr. tipuri piese: " << nrTipuriPiese
            << " | Valoare totala: " << valoareTotala;
        if (nrTipuriPiese > 0 && cantitatiPiese) {
            cout << " | Cantitati: ";
            for (int i = 0; i < nrTipuriPiese; i++)
                cout << cantitatiPiese[i] << (i < nrTipuriPiese - 1 ? ", " : "");
        }
    }

    void operator+=(float x) {
        valoareTotala += x;
    }

    friend MagaziePieseAeronautice operator+=(float x, MagaziePieseAeronautice& m) {
        m.valoareTotala += x;
        return m;
    }

    bool operator<(const MagaziePieseAeronautice& m) {
        return valoareTotala < m.valoareTotala;
    }

    bool operator!() {
        return valoareTotala == 0;
    }

    int operator()(int index) {
        return getCantitatePiesa(index);
    }

    char& operator[](int index) {
        if (!nume) throw "Nume inexistent!";
        if (index < 0 || index >= (int)strlen(nume)) throw "Index invalid!";
        return nume[index];
    }

    explicit operator int() {
        int total = 0;
        for (int i = 0; i < nrTipuriPiese; i++) total += cantitatiPiese[i];
        return total;
    }

    MagaziePieseAeronautice operator++(int) {
        MagaziePieseAeronautice copie = *this;
        valoareTotala++;
        return copie;
    }

    MagaziePieseAeronautice operator++() {
        valoareTotala++;
        return *this;
    }

    friend void operator<<(ostream& out, MagaziePieseAeronautice m) {
        out << endl << "ID: " << m.idMagazie;
        out << endl << "Nume: " << (m.nume ? m.nume : (char*)"N/A");
        out << endl << "Locatie: " << m.locatie;
        out << endl << "Nr tipuri piese: " << m.nrTipuriPiese;
        out << endl << "Valoare totala: " << m.valoareTotala;
        if (m.cantitatiPiese && m.nrTipuriPiese > 0) {
            out << endl << "Cantitati pe tip: ";
            for (int i = 0; i < m.nrTipuriPiese; i++)
                out << m.cantitatiPiese[i] << " ";
        }
    }

    friend void operator>>(istream& in, MagaziePieseAeronautice& m) {
        char buf[100];
        in >> buf;
        m.setNume(buf);
        in >> m.locatie;
        in >> m.valoareTotala;
        in >> m.nrTipuriPiese;
        if (m.cantitatiPiese) {
            delete[] m.cantitatiPiese;
            m.cantitatiPiese = nullptr;
        }
        if (m.nrTipuriPiese > 0) {
            m.cantitatiPiese = new int[m.nrTipuriPiese];
            for (int i = 0; i < m.nrTipuriPiese; i++)
                in >> m.cantitatiPiese[i];
        }
        else {
            m.cantitatiPiese = nullptr;
        }
    }
};

int MagaziePieseAeronautice::numarMagazii = 0;

int main() {
    int cantitati[4] = { 120, 50, 30, 200 };

    MagaziePieseAeronautice m1("HangarPieseA320", "OTP", 4, cantitati, 250000);
    MagaziePieseAeronautice m2 = m1;

    m1.afisare();
    m2.afisare();

    cout << m1;

    m1 += 10000;
    m1.afisare();

    cout << endl << "Cantitate piesa 2: " << m1(1);
    cout << endl << "Litera din nume[1]: " << m1[1];

    cout << endl << "Total piese (cast la int): " << (int)m1;

    cout << endl << "Numar magazii create: " << MagaziePieseAeronautice::getNumarMagazii();

    return 0;
}
