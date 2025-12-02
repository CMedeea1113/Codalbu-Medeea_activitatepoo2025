#include <iostream>
#include <cstring>
using namespace std;

class Magazin {
private:
    const int idMagazin;
    static int numarMagazine;
    char* nume;
    string adresa;
    float venitAnual;
    int nrAngajati;
    float* salarii;

public:
    void setVenitAnual(float venit) {
        if (venit >= 0) this->venitAnual = venit;
    }

    float getVenitAnual() { return venitAnual; }

    char* getNume() { return nume; }

    void setNume(const char* numeNou) {
        if (numeNou && strlen(numeNou) > 0) {
            if (nume) delete[] nume;
            nume = new char[strlen(numeNou) + 1];
            strcpy_s(nume, strlen(numeNou) + 1, numeNou);
        }
    }

    void setAdresa(string adr) {
        if (!adr.empty()) adresa = adr;
    }

    string getAdresa() { return adresa; }

    void setSalarii(int nr, float* src) {
        if (nr > 0 && src) {
            nrAngajati = nr;
            if (salarii) delete[] salarii;
            salarii = new float[nr];
            for (int i = 0; i < nr; i++) salarii[i] = src[i];
        }
    }

    float getSalariuAngajat(int index) {
        if (index >= 0 && index < nrAngajati) return salarii[index];
        throw 404;
    }

    int getNrAngajati() { return nrAngajati; }
    int getIdMagazin() { return idMagazin; }
    static int getNumarMagazine() { return numarMagazine; }

    Magazin() : idMagazin(++numarMagazine) {
        nume = nullptr;
        adresa = "Necunoscuta";
        venitAnual = 0;
        nrAngajati = 0;
        salarii = nullptr;
    }

    Magazin(const char* nume, string adresa, float venitAnual,
        int nrAngajati, const float* salarii)
        : idMagazin(++numarMagazine)
    {
        this->adresa = adresa;
        this->venitAnual = venitAnual >= 0 ? venitAnual : 0;
        this->nrAngajati = nrAngajati > 0 ? nrAngajati : 0;

        if (nume && strlen(nume) > 0) {
            this->nume = new char[strlen(nume) + 1];
            strcpy_s(this->nume, strlen(nume) + 1, nume);
        }
        else {
            this->nume = nullptr;
        }

        if (this->nrAngajati > 0 && salarii) {
            this->salarii = new float[this->nrAngajati];
            for (int i = 0; i < this->nrAngajati; i++)
                this->salarii[i] = salarii[i];
        }
        else {
            this->salarii = nullptr;
            this->nrAngajati = 0;
        }
    }

    Magazin(const Magazin& m) : idMagazin(++numarMagazine) {
        adresa = m.adresa;
        venitAnual = m.venitAnual;
        nrAngajati = m.nrAngajati;

        if (m.nume) {
            nume = new char[strlen(m.nume) + 1];
            strcpy_s(nume, strlen(m.nume) + 1, m.nume);
        }
        else nume = nullptr;

        if (m.salarii && m.nrAngajati > 0) {
            salarii = new float[m.nrAngajati];
            for (int i = 0; i < m.nrAngajati; i++)
                salarii[i] = m.salarii[i];
        }
        else salarii = nullptr;
    }

    void operator=(const Magazin& m) {
        if (this == &m) return;

        adresa = m.adresa;
        venitAnual = m.venitAnual;
        nrAngajati = m.nrAngajati;

        if (nume) delete[] nume;
        if (m.nume) {
            nume = new char[strlen(m.nume) + 1];
            strcpy_s(nume, strlen(m.nume) + 1, m.nume);
        }
        else nume = nullptr;

        if (salarii) delete[] salarii;
        if (m.salarii && m.nrAngajati > 0) {
            salarii = new float[m.nrAngajati];
            for (int i = 0; i < m.nrAngajati; i++)
                salarii[i] = m.salarii[i];
        }
        else {
            salarii = nullptr;
            nrAngajati = 0;
        }
    }

    ~Magazin() {
        if (nume) delete[] nume;
        if (salarii) delete[] salarii;
    }

    void operator+=(float x) {
        venitAnual += x;
    }

    friend Magazin operator+=(float x, Magazin& m) {
        m.venitAnual += x;
        return m;
    }

    bool operator<(const Magazin& m) {
        return venitAnual < m.venitAnual;
    }

    bool operator!() {
        return venitAnual == 0;
    }

    float operator()(int index) {
        return getSalariuAngajat(index);
    }

    char& operator[](int index) {
        if (!nume) throw "Nume inexistent!";
        if (index < 0 || index >= (int)strlen(nume)) throw "Index invalid!";
        return nume[index];
    }

    explicit operator int() {
        return (int)venitAnual;
    }

    Magazin operator++(int) {
        Magazin copie = *this;
        venitAnual++;
        return copie;
    }

    Magazin operator++() {
        venitAnual++;
        return *this;
    }

    void afisare() {
        cout << endl << idMagazin << ". Magazin: "
            << (nume ? nume : "Fara nume")
            << " | Adresa: " << adresa
            << " | Venit anual: " << venitAnual
            << " | Nr. angajati: " << nrAngajati;
    }

    friend void operator<<(ostream& out, Magazin m) {
        out << endl << "ID: " << m.idMagazin;
        out << endl << "Nume: " << (m.nume ? m.nume : (char*)"N/A");
        out << endl << "Adresa: " << m.adresa;
        out << endl << "Venit anual: " << m.venitAnual;
        out << endl << "Nr. angajati: " << m.nrAngajati;
        if (m.salarii && m.nrAngajati > 0) {
            out << endl << "Salarii: ";
            for (int i = 0; i < m.nrAngajati; i++)
                out << m.salarii[i] << " ";
        }
    }

    friend void operator>>(istream& in, Magazin& m) {
        char buf[100];
        in >> buf;
        m.setNume(buf);
        in >> m.adresa;
        in >> m.venitAnual;
        in >> m.nrAngajati;
        if (m.salarii) delete[] m.salarii;
        if (m.nrAngajati > 0) {
            m.salarii = new float[m.nrAngajati];
            for (int i = 0; i < m.nrAngajati; i++)
                in >> m.salarii[i];
        }
        else {
            m.salarii = nullptr;
        }
    }
};

int Magazin::numarMagazine = 0;

int main() {
    float v[3] = { 3000, 3200, 2800 };

    Magazin m1("MegaImage", "Bucuresti", 150000, 3, v);
    Magazin m2 = m1;

    m1.afisare();
    m2.afisare();

    cout << m1;

    m1 += 5000;
    m1.afisare();

    cout << endl << "Salariu angajat 1: " << m1(1);
    cout << endl << "Litera din nume[2]: " << m1[2];

    cout << endl << "Numar magazine create: " << Magazin::getNumarMagazine();

    return 0;
}
