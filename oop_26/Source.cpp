#include <iostream>
#include <cstring>
using namespace std;

class Cafenea {
private:
    const int idCafenea;
    static int numarCafenele;
    char* nume;
    string locatie;
    float pretCafeaBaza;
    int nrSortimente;
    float* preturiSortimente;

public:
    void setPretCafeaBaza(float pret) {
        if (pret >= 0) this->pretCafeaBaza = pret;
    }

    float getPretCafeaBaza() {
        return this->pretCafeaBaza;
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

    void setLocatie(string loc) {
        if (!loc.empty()) this->locatie = loc;
    }

    string getLocatie() {
        return this->locatie;
    }

    void setPreturiSortimente(int nr, float* preturi) {
        if (nr > 0 && preturi) {
            this->nrSortimente = nr;
            if (this->preturiSortimente) delete[] this->preturiSortimente;
            this->preturiSortimente = new float[nr];
            for (int i = 0; i < nr; i++)
                this->preturiSortimente[i] = preturi[i];
        }
    }

    float getPretSortiment(int index) {
        if (index >= 0 && index < nrSortimente) return preturiSortimente[index];
        throw 404;
    }

    int getNrSortimente() {
        return this->nrSortimente;
    }

    int getIdCafenea() {
        return this->idCafenea;
    }

    static int getNumarCafenele() {
        return numarCafenele;
    }

    Cafenea() : idCafenea(++numarCafenele) {
        nume = nullptr;
        locatie = "Necunoscuta";
        pretCafeaBaza = 0;
        nrSortimente = 0;
        preturiSortimente = nullptr;
    }

    Cafenea(const char* nume, string locatie, float pretCafeaBaza,
        int nrSortimente, const float* preturi)
        : idCafenea(++numarCafenele)
    {
        this->locatie = locatie;
        this->pretCafeaBaza = pretCafeaBaza >= 0 ? pretCafeaBaza : 0;
        this->nrSortimente = nrSortimente > 0 ? nrSortimente : 0;

        if (nume && strlen(nume) > 0) {
            this->nume = new char[strlen(nume) + 1];
            strcpy_s(this->nume, strlen(nume) + 1, nume);
        }
        else {
            this->nume = nullptr;
        }

        if (this->nrSortimente > 0 && preturi) {
            this->preturiSortimente = new float[this->nrSortimente];
            for (int i = 0; i < this->nrSortimente; i++)
                this->preturiSortimente[i] = preturi[i];
        }
        else {
            this->preturiSortimente = nullptr;
            this->nrSortimente = 0;
        }
    }

    Cafenea(const Cafenea& c)
        : idCafenea(++numarCafenele)
    {
        locatie = c.locatie;
        pretCafeaBaza = c.pretCafeaBaza;
        nrSortimente = c.nrSortimente;

        if (c.nume) {
            nume = new char[strlen(c.nume) + 1];
            strcpy_s(nume, strlen(c.nume) + 1, c.nume);
        }
        else nume = nullptr;

        if (c.preturiSortimente && c.nrSortimente > 0) {
            preturiSortimente = new float[c.nrSortimente];
            for (int i = 0; i < c.nrSortimente; i++)
                preturiSortimente[i] = c.preturiSortimente[i];
        }
        else preturiSortimente = nullptr;
    }

    void operator=(const Cafenea& c) {
        if (this == &c) return;

        locatie = c.locatie;
        pretCafeaBaza = c.pretCafeaBaza;
        nrSortimente = c.nrSortimente;

        if (nume) delete[] nume;
        if (c.nume) {
            nume = new char[strlen(c.nume) + 1];
            strcpy_s(nume, strlen(c.nume) + 1, c.nume);
        }
        else nume = nullptr;

        if (preturiSortimente) delete[] preturiSortimente;
        if (c.preturiSortimente && c.nrSortimente > 0) {
            preturiSortimente = new float[c.nrSortimente];
            for (int i = 0; i < c.nrSortimente; i++)
                preturiSortimente[i] = c.preturiSortimente[i];
        }
        else {
            preturiSortimente = nullptr;
            nrSortimente = 0;
        }
    }

    ~Cafenea() {
        if (nume) delete[] nume;
        if (preturiSortimente) delete[] preturiSortimente;
    }

    void operator+=(float x) {
        pretCafeaBaza += x;
    }

    friend Cafenea operator+=(float x, Cafenea& c) {
        c.pretCafeaBaza += x;
        return c;
    }

    bool operator<(const Cafenea& c) {
        return pretCafeaBaza < c.pretCafeaBaza;
    }

    bool operator!() {
        return pretCafeaBaza == 0;
    }

    float operator()(int index) {
        return getPretSortiment(index);
    }

    char& operator[](int index) {
        if (!nume) throw "Nume inexistent!";
        if (index < 0 || index >= (int)strlen(nume)) throw "Index invalid!";
        return nume[index];
    }

    explicit operator int() {
        return nrSortimente;
    }

    Cafenea operator++(int) {
        Cafenea copie = *this;
        pretCafeaBaza++;
        return copie;
    }

    Cafenea operator++() {
        pretCafeaBaza++;
        return *this;
    }

    void afisare() {
        cout << endl << idCafenea << ". Cafenea: "
            << (nume ? nume : "Fara nume")
            << " | Locatie: " << locatie
            << " | Pret cafea baza: " << pretCafeaBaza
            << " | Nr. sortimente: " << nrSortimente;
        if (nrSortimente > 0 && preturiSortimente) {
            cout << " | Preturi sortimente: ";
            for (int i = 0; i < nrSortimente; i++)
                cout << preturiSortimente[i] << (i < nrSortimente - 1 ? ", " : "");
        }
    }

    friend void operator<<(ostream& out, Cafenea c) {
        out << endl << "ID: " << c.idCafenea;
        out << endl << "Nume: " << (c.nume ? c.nume : (char*)"N/A");
        out << endl << "Locatie: " << c.locatie;
        out << endl << "Pret cafea baza: " << c.pretCafeaBaza;
        out << endl << "Nr. sortimente: " << c.nrSortimente;
        if (c.preturiSortimente && c.nrSortimente > 0) {
            out << endl << "Preturi sortimente: ";
            for (int i = 0; i < c.nrSortimente; i++)
                out << c.preturiSortimente[i] << " ";
        }
    }

    friend void operator>>(istream& in, Cafenea& c) {
        char buf[100];
        in >> buf;
        c.setNume(buf);
        in >> c.locatie;
        in >> c.pretCafeaBaza;
        in >> c.nrSortimente;
        if (c.preturiSortimente) {
            delete[] c.preturiSortimente;
            c.preturiSortimente = nullptr;
        }
        if (c.nrSortimente > 0) {
            c.preturiSortimente = new float[c.nrSortimente];
            for (int i = 0; i < c.nrSortimente; i++)
                in >> c.preturiSortimente[i];
        }
        else {
            c.preturiSortimente = nullptr;
        }
    }
};

int Cafenea::numarCafenele = 0;

int main() {
    float preturi[4] = { 10.0f, 12.5f, 15.0f, 18.0f };

    Cafenea c1("BeanBrew", "Bucuresti", 9.0f, 4, preturi);
    Cafenea c2 = c1;

    c1.afisare();
    c2.afisare();

    cout << c1;

    c1 += 1.5f;
    c1.afisare();

    cout << endl << "Pret sortiment 2: " << c1(1);
    cout << endl << "Litera din nume[1]: " << c1[1];

    cout << endl << "Nr. sortimente (cast la int): " << (int)c1;

    cout << endl << "Numar cafenele create: " << Cafenea::getNumarCafenele();

    return 0;
}
