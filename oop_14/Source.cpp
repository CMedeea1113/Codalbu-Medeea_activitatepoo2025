#include <iostream>
#include <cstring>
using namespace std;

class MagazinAlimentar {
private:
    const int idMagazin;
    static int numarMagazine;
    char* nume;
    string adresa;
    float cifraAfaceri;
    int nrProduse;
    float* preturiProduse;

public:
    void setCifraAfaceri(float cifra) {
        if (cifra >= 0) this->cifraAfaceri = cifra;
    }

    float getCifraAfaceri() {
        return this->cifraAfaceri;
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

    void setPreturiProduse(int nr, float* preturi) {
        if (nr > 0 && preturi) {
            this->nrProduse = nr;
            if (this->preturiProduse) delete[] this->preturiProduse;
            this->preturiProduse = new float[nr];
            for (int i = 0; i < nr; i++)
                this->preturiProduse[i] = preturi[i];
        }
    }

    float getPretProdus(int index) {
        if (index >= 0 && index < nrProduse) return preturiProduse[index];
        throw 404;
    }

    int getNrProduse() {
        return this->nrProduse;
    }

    int getIdMagazin() {
        return this->idMagazin;
    }

    static int getNumarMagazine() {
        return numarMagazine;
    }

    MagazinAlimentar() : idMagazin(++numarMagazine) {
        nume = nullptr;
        adresa = "Necunoscuta";
        cifraAfaceri = 0;
        nrProduse = 0;
        preturiProduse = nullptr;
    }

    MagazinAlimentar(const char* nume, string adresa, float cifraAfaceri,
        int nrProduse, const float* preturi)
        : idMagazin(++numarMagazine)
    {
        this->adresa = adresa;
        this->cifraAfaceri = cifraAfaceri >= 0 ? cifraAfaceri : 0;
        this->nrProduse = nrProduse > 0 ? nrProduse : 0;

        if (nume && strlen(nume) > 0) {
            this->nume = new char[strlen(nume) + 1];
            strcpy_s(this->nume, strlen(nume) + 1, nume);
        }
        else {
            this->nume = nullptr;
        }

        if (this->nrProduse > 0 && preturi) {
            this->preturiProduse = new float[this->nrProduse];
            for (int i = 0; i < this->nrProduse; i++)
                this->preturiProduse[i] = preturi[i];
        }
        else {
            this->preturiProduse = nullptr;
            this->nrProduse = 0;
        }
    }

    MagazinAlimentar(const MagazinAlimentar& m) : idMagazin(++numarMagazine) {
        adresa = m.adresa;
        cifraAfaceri = m.cifraAfaceri;
        nrProduse = m.nrProduse;

        if (m.nume) {
            nume = new char[strlen(m.nume) + 1];
            strcpy_s(nume, strlen(m.nume) + 1, m.nume);
        }
        else nume = nullptr;

        if (m.preturiProduse && m.nrProduse > 0) {
            preturiProduse = new float[m.nrProduse];
            for (int i = 0; i < m.nrProduse; i++)
                preturiProduse[i] = m.preturiProduse[i];
        }
        else preturiProduse = nullptr;
    }

    void operator=(const MagazinAlimentar& m) {
        if (this == &m) return;

        adresa = m.adresa;
        cifraAfaceri = m.cifraAfaceri;
        nrProduse = m.nrProduse;

        if (nume) delete[] nume;
        if (m.nume) {
            nume = new char[strlen(m.nume) + 1];
            strcpy_s(nume, strlen(m.nume) + 1, m.nume);
        }
        else nume = nullptr;

        if (preturiProduse) delete[] preturiProduse;
        if (m.preturiProduse && m.nrProduse > 0) {
            preturiProduse = new float[m.nrProduse];
            for (int i = 0; i < m.nrProduse; i++)
                preturiProduse[i] = m.preturiProduse[i];
        }
        else {
            preturiProduse = nullptr;
            nrProduse = 0;
        }
    }

    ~MagazinAlimentar() {
        if (nume) delete[] nume;
        if (preturiProduse) delete[] preturiProduse;
    }

    void operator+=(float x) {
        cifraAfaceri += x;
    }

    friend MagazinAlimentar operator+=(float x, MagazinAlimentar& m) {
        m.cifraAfaceri += x;
        return m;
    }

    bool operator<(const MagazinAlimentar& m) {
        return cifraAfaceri < m.cifraAfaceri;
    }

    bool operator!() {
        return cifraAfaceri == 0;
    }

    float operator()(int index) {
        return getPretProdus(index);
    }

    char& operator[](int index) {
        if (!nume) throw "Nume inexistent!";
        if (index < 0 || index >= (int)strlen(nume)) throw "Index invalid!";
        return nume[index];
    }

    explicit operator int() {
        return nrProduse;
    }

    MagazinAlimentar operator++(int) {
        MagazinAlimentar copie = *this;
        cifraAfaceri++;
        return copie;
    }

    MagazinAlimentar operator++() {
        cifraAfaceri++;
        return *this;
    }

    void afisare() {
        cout << endl << idMagazin << ". Magazin alimentar: "
            << (nume ? nume : "Fara nume")
            << " | Adresa: " << adresa
            << " | Cifra afaceri: " << cifraAfaceri
            << " | Nr. produse: " << nrProduse;
        if (nrProduse > 0 && preturiProduse) {
            cout << " | Preturi: ";
            for (int i = 0; i < nrProduse; i++)
                cout << preturiProduse[i] << (i < nrProduse - 1 ? ", " : "");
        }
    }

    friend void operator<<(ostream& out, MagazinAlimentar m) {
        out << endl << "ID: " << m.idMagazin;
        out << endl << "Nume: " << (m.nume ? m.nume : (char*)"N/A");
        out << endl << "Adresa: " << m.adresa;
        out << endl << "Cifra afaceri: " << m.cifraAfaceri;
        out << endl << "Nr. produse: " << m.nrProduse;
        if (m.preturiProduse && m.nrProduse > 0) {
            out << endl << "Preturi produse: ";
            for (int i = 0; i < m.nrProduse; i++)
                out << m.preturiProduse[i] << " ";
        }
    }

    friend void operator>>(istream& in, MagazinAlimentar& m) {
        char buf[100];
        in >> buf;
        m.setNume(buf);
        in >> m.adresa;
        in >> m.cifraAfaceri;
        in >> m.nrProduse;
        if (m.preturiProduse) {
            delete[] m.preturiProduse;
            m.preturiProduse = nullptr;
        }
        if (m.nrProduse > 0) {
            m.preturiProduse = new float[m.nrProduse];
            for (int i = 0; i < m.nrProduse; i++)
                in >> m.preturiProduse[i];
        }
        else {
            m.preturiProduse = nullptr;
        }
    }
};

int MagazinAlimentar::numarMagazine = 0;

int main() {
    float v[4] = { 5.5f, 3.2f, 10.0f, 2.3f };

    MagazinAlimentar m1("LaGhiocel", "Str. Florilor 10", 150000, 4, v);
    MagazinAlimentar m2 = m1;

    m1.afisare();
    m2.afisare();

    cout << m1;

    m1 += 5000;
    m1.afisare();

    cout << endl << "Pret produs 2: " << m1(1);
    cout << endl << "Litera din nume[1]: " << m1[1];

    cout << endl << "Nr. produse (cast la int): " << (int)m1;

    cout << endl << "Numar magazine alimentare create: " << MagazinAlimentar::getNumarMagazine();

    return 0;
}
