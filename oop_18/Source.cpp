#include <iostream>
#include <cstring>
using namespace std;

class ComponentaCalculator {
private:
    const int idComponenta;
    static int numarComponente;
    char* denumire;
    string tip;
    float pretBaza;
    int nrMagazine;
    float* preturiMagazine;

public:
    void setPretBaza(float pret) {
        if (pret >= 0) this->pretBaza = pret;
    }

    float getPretBaza() {
        return this->pretBaza;
    }

    char* getDenumire() {
        return this->denumire;
    }

    void setDenumire(const char* numeNou) {
        if (numeNou && strlen(numeNou) > 0) {
            if (this->denumire) delete[] this->denumire;
            this->denumire = new char[strlen(numeNou) + 1];
            strcpy_s(this->denumire, strlen(numeNou) + 1, numeNou);
        }
    }

    void setTip(string t) {
        if (!t.empty()) this->tip = t;
    }

    string getTip() {
        return this->tip;
    }

    void setPreturiMagazine(int nr, float* preturi) {
        if (nr > 0 && preturi) {
            this->nrMagazine = nr;
            if (this->preturiMagazine) delete[] this->preturiMagazine;
            this->preturiMagazine = new float[nr];
            for (int i = 0; i < nr; i++)
                this->preturiMagazine[i] = preturi[i];
        }
    }

    float getPretInMagazin(int index) {
        if (index >= 0 && index < nrMagazine) return preturiMagazine[index];
        throw 404;
    }

    int getNrMagazine() {
        return this->nrMagazine;
    }

    int getIdComponenta() {
        return this->idComponenta;
    }

    static int getNumarComponente() {
        return numarComponente;
    }

    ComponentaCalculator() : idComponenta(++numarComponente) {
        denumire = nullptr;
        tip = "Necunoscut";
        pretBaza = 0;
        nrMagazine = 0;
        preturiMagazine = nullptr;
    }

    ComponentaCalculator(const char* denumire, string tip, float pretBaza,
        int nrMagazine, const float* preturi)
        : idComponenta(++numarComponente)
    {
        this->tip = tip;
        this->pretBaza = pretBaza >= 0 ? pretBaza : 0;
        this->nrMagazine = nrMagazine > 0 ? nrMagazine : 0;

        if (denumire && strlen(denumire) > 0) {
            this->denumire = new char[strlen(denumire) + 1];
            strcpy_s(this->denumire, strlen(denumire) + 1, denumire);
        }
        else {
            this->denumire = nullptr;
        }

        if (this->nrMagazine > 0 && preturi) {
            this->preturiMagazine = new float[this->nrMagazine];
            for (int i = 0; i < this->nrMagazine; i++)
                this->preturiMagazine[i] = preturi[i];
        }
        else {
            this->preturiMagazine = nullptr;
            this->nrMagazine = 0;
        }
    }

    ComponentaCalculator(const ComponentaCalculator& c)
        : idComponenta(++numarComponente)
    {
        tip = c.tip;
        pretBaza = c.pretBaza;
        nrMagazine = c.nrMagazine;

        if (c.denumire) {
            denumire = new char[strlen(c.denumire) + 1];
            strcpy_s(denumire, strlen(c.denumire) + 1, c.denumire);
        }
        else denumire = nullptr;

        if (c.preturiMagazine && c.nrMagazine > 0) {
            preturiMagazine = new float[c.nrMagazine];
            for (int i = 0; i < c.nrMagazine; i++)
                preturiMagazine[i] = c.preturiMagazine[i];
        }
        else preturiMagazine = nullptr;
    }

    void operator=(const ComponentaCalculator& c) {
        if (this == &c) return;

        tip = c.tip;
        pretBaza = c.pretBaza;
        nrMagazine = c.nrMagazine;

        if (denumire) delete[] denumire;
        if (c.denumire) {
            denumire = new char[strlen(c.denumire) + 1];
            strcpy_s(denumire, strlen(c.denumire) + 1, c.denumire);
        }
        else denumire = nullptr;

        if (preturiMagazine) delete[] preturiMagazine;
        if (c.preturiMagazine && c.nrMagazine > 0) {
            preturiMagazine = new float[c.nrMagazine];
            for (int i = 0; i < c.nrMagazine; i++)
                preturiMagazine[i] = c.preturiMagazine[i];
        }
        else {
            preturiMagazine = nullptr;
            nrMagazine = 0;
        }
    }

    ~ComponentaCalculator() {
        if (denumire) delete[] denumire;
        if (preturiMagazine) delete[] preturiMagazine;
    }

    void operator+=(float x) {
        pretBaza += x;
    }

    friend ComponentaCalculator operator+=(float x, ComponentaCalculator& c) {
        c.pretBaza += x;
        return c;
    }

    bool operator<(const ComponentaCalculator& c) {
        return pretBaza < c.pretBaza;
    }

    bool operator!() {
        return pretBaza == 0;
    }

    float operator()(int index) {
        return getPretInMagazin(index);
    }

    char& operator[](int index) {
        if (!denumire) throw "Denumire inexistenta!";
        if (index < 0 || index >= (int)strlen(denumire)) throw "Index invalid!";
        return denumire[index];
    }

    explicit operator int() {
        return nrMagazine;
    }

    ComponentaCalculator operator++(int) {
        ComponentaCalculator copie = *this;
        pretBaza++;
        return copie;
    }

    ComponentaCalculator operator++() {
        pretBaza++;
        return *this;
    }

    void afisare() {
        cout << endl << idComponenta << ". Componenta: "
            << (denumire ? denumire : "Fara nume")
            << " | Tip: " << tip
            << " | Pret baza: " << pretBaza
            << " | Nr. magazine: " << nrMagazine;
        if (nrMagazine > 0 && preturiMagazine) {
            cout << " | Preturi magazine: ";
            for (int i = 0; i < nrMagazine; i++)
                cout << preturiMagazine[i] << (i < nrMagazine - 1 ? ", " : "");
        }
    }

    friend void operator<<(ostream& out, ComponentaCalculator c) {
        out << endl << "ID: " << c.idComponenta;
        out << endl << "Denumire: " << (c.denumire ? c.denumire : (char*)"N/A");
        out << endl << "Tip: " << c.tip;
        out << endl << "Pret baza: " << c.pretBaza;
        out << endl << "Nr. magazine: " << c.nrMagazine;
        if (c.preturiMagazine && c.nrMagazine > 0) {
            out << endl << "Preturi in magazine: ";
            for (int i = 0; i < c.nrMagazine; i++)
                out << c.preturiMagazine[i] << " ";
        }
    }

    friend void operator>>(istream& in, ComponentaCalculator& c) {
        char buf[100];
        in >> buf;
        c.setDenumire(buf);
        in >> c.tip;
        in >> c.pretBaza;
        in >> c.nrMagazine;
        if (c.preturiMagazine) {
            delete[] c.preturiMagazine;
            c.preturiMagazine = nullptr;
        }
        if (c.nrMagazine > 0) {
            c.preturiMagazine = new float[c.nrMagazine];
            for (int i = 0; i < c.nrMagazine; i++)
                in >> c.preturiMagazine[i];
        }
        else {
            c.preturiMagazine = nullptr;
        }
    }
};

int ComponentaCalculator::numarComponente = 0;

int main() {
    float preturi[3] = { 499.99f, 479.50f, 510.00f };

    ComponentaCalculator c1("RTX4070", "PlacaVideo", 480.0f, 3, preturi);
    ComponentaCalculator c2 = c1;

    c1.afisare();
    c2.afisare();

    cout << c1;

    c1 += 20;
    c1.afisare();

    cout << endl << "Pret in magazinul 2: " << c1(1);
    cout << endl << "Litera din denumire[1]: " << c1[1];

    cout << endl << "Nr. magazine (cast la int): " << (int)c1;

    cout << endl << "Numar componente create: " << ComponentaCalculator::getNumarComponente();

    return 0;
}
