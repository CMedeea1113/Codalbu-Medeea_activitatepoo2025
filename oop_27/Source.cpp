#include <iostream>
#include <cstring>
using namespace std;

class Pizzerie {
private:
    const int idPizzerie;
    static int numarPizzerii;
    char* nume;
    string locatie;
    float pretBaza;
    int nrTipuriPizza;
    float* preturiPizza;

public:
    void setPretBaza(float pret) {
        if (pret >= 0) this->pretBaza = pret;
    }

    float getPretBaza() {
        return this->pretBaza;
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

    void setPreturiPizza(int nr, float* preturi) {
        if (nr > 0 && preturi) {
            this->nrTipuriPizza = nr;
            if (this->preturiPizza) delete[] this->preturiPizza;
            this->preturiPizza = new float[nr];
            for (int i = 0; i < nr; i++)
                this->preturiPizza[i] = preturi[i];
        }
    }

    float getPretPizza(int index) {
        if (index >= 0 && index < nrTipuriPizza) return preturiPizza[index];
        throw 404;
    }

    int getNrTipuriPizza() {
        return this->nrTipuriPizza;
    }

    int getIdPizzerie() {
        return this->idPizzerie;
    }

    static int getNumarPizzerii() {
        return numarPizzerii;
    }

    Pizzerie() : idPizzerie(++numarPizzerii) {
        nume = nullptr;
        locatie = "Necunoscuta";
        pretBaza = 0;
        nrTipuriPizza = 0;
        preturiPizza = nullptr;
    }

    Pizzerie(const char* nume, string locatie, float pretBaza,
        int nrTipuriPizza, const float* preturi)
        : idPizzerie(++numarPizzerii)
    {
        this->locatie = locatie;
        this->pretBaza = pretBaza >= 0 ? pretBaza : 0;
        this->nrTipuriPizza = nrTipuriPizza > 0 ? nrTipuriPizza : 0;

        if (nume && strlen(nume) > 0) {
            this->nume = new char[strlen(nume) + 1];
            strcpy_s(this->nume, strlen(nume) + 1, nume);
        }
        else {
            this->nume = nullptr;
        }

        if (this->nrTipuriPizza > 0 && preturi) {
            this->preturiPizza = new float[this->nrTipuriPizza];
            for (int i = 0; i < this->nrTipuriPizza; i++)
                this->preturiPizza[i] = preturi[i];
        }
        else {
            this->preturiPizza = nullptr;
            this->nrTipuriPizza = 0;
        }
    }

    Pizzerie(const Pizzerie& p)
        : idPizzerie(++numarPizzerii)
    {
        locatie = p.locatie;
        pretBaza = p.pretBaza;
        nrTipuriPizza = p.nrTipuriPizza;

        if (p.nume) {
            nume = new char[strlen(p.nume) + 1];
            strcpy_s(nume, strlen(p.nume) + 1, p.nume);
        }
        else nume = nullptr;

        if (p.preturiPizza && p.nrTipuriPizza > 0) {
            preturiPizza = new float[p.nrTipuriPizza];
            for (int i = 0; i < p.nrTipuriPizza; i++)
                preturiPizza[i] = p.preturiPizza[i];
        }
        else preturiPizza = nullptr;
    }

    void operator=(const Pizzerie& p) {
        if (this == &p) return;

        locatie = p.locatie;
        pretBaza = p.pretBaza;
        nrTipuriPizza = p.nrTipuriPizza;

        if (nume) delete[] nume;
        if (p.nume) {
            nume = new char[strlen(p.nume) + 1];
            strcpy_s(nume, strlen(p.nume) + 1, p.nume);
        }
        else nume = nullptr;

        if (preturiPizza) delete[] preturiPizza;
        if (p.preturiPizza && p.nrTipuriPizza > 0) {
            preturiPizza = new float[p.nrTipuriPizza];
            for (int i = 0; i < p.nrTipuriPizza; i++)
                preturiPizza[i] = p.preturiPizza[i];
        }
        else {
            preturiPizza = nullptr;
            nrTipuriPizza = 0;
        }
    }

    ~Pizzerie() {
        if (nume) delete[] nume;
        if (preturiPizza) delete[] preturiPizza;
    }

    void operator+=(float x) {
        pretBaza += x;
    }

    friend Pizzerie operator+=(float x, Pizzerie& p) {
        p.pretBaza += x;
        return p;
    }

    bool operator<(const Pizzerie& p) {
        return pretBaza < p.pretBaza;
    }

    bool operator!() {
        return pretBaza == 0;
    }

    float operator()(int index) {
        return getPretPizza(index);
    }

    char& operator[](int index) {
        if (!nume) throw "Nume inexistent!";
        if (index < 0 || index >= (int)strlen(nume)) throw "Index invalid!";
        return nume[index];
    }

    explicit operator int() {
        return nrTipuriPizza;
    }

    Pizzerie operator++(int) {
        Pizzerie copie = *this;
        pretBaza++;
        return copie;
    }

    Pizzerie operator++() {
        pretBaza++;
        return *this;
    }

    void afisare() {
        cout << endl << idPizzerie << ". Pizzerie: "
            << (nume ? nume : "Fara nume")
            << " | Locatie: " << locatie
            << " | Pret baza pizza: " << pretBaza
            << " | Nr. tipuri pizza: " << nrTipuriPizza;
        if (nrTipuriPizza > 0 && preturiPizza) {
            cout << " | Preturi pizza: ";
            for (int i = 0; i < nrTipuriPizza; i++)
                cout << preturiPizza[i] << (i < nrTipuriPizza - 1 ? ", " : "");
        }
    }

    friend void operator<<(ostream& out, Pizzerie p) {
        out << endl << "ID: " << p.idPizzerie;
        out << endl << "Nume: " << (p.nume ? p.nume : (char*)"N/A");
        out << endl << "Locatie: " << p.locatie;
        out << endl << "Pret baza pizza: " << p.pretBaza;
        out << endl << "Nr. tipuri pizza: " << p.nrTipuriPizza;
        if (p.preturiPizza && p.nrTipuriPizza > 0) {
            out << endl << "Preturi pizza: ";
            for (int i = 0; i < p.nrTipuriPizza; i++)
                out << p.preturiPizza[i] << " ";
        }
    }

    friend void operator>>(istream& in, Pizzerie& p) {
        char buf[100];
        in >> buf;
        p.setNume(buf);
        in >> p.locatie;
        in >> p.pretBaza;
        in >> p.nrTipuriPizza;
        if (p.preturiPizza) {
            delete[] p.preturiPizza;
            p.preturiPizza = nullptr;
        }
        if (p.nrTipuriPizza > 0) {
            p.preturiPizza = new float[p.nrTipuriPizza];
            for (int i = 0; i < p.nrTipuriPizza; i++)
                in >> p.preturiPizza[i];
        }
        else {
            p.preturiPizza = nullptr;
        }
    }
};

int Pizzerie::numarPizzerii = 0;

int main() {
    float preturi[4] = { 25.0f, 32.5f, 29.0f, 40.0f };

    Pizzerie p1("LaNapoletana", "Bucuresti", 22.0f, 4, preturi);
    Pizzerie p2 = p1;

    p1.afisare();
    p2.afisare();

    cout << p1;

    p1 += 3.5f;
    p1.afisare();

    cout << endl << "Pret pizza 2: " << p1(1);
    cout << endl << "Litera din nume[1]: " << p1[1];

    cout << endl << "Nr. tipuri pizza (cast la int): " << (int)p1;

    cout << endl << "Numar pizzerii create: " << Pizzerie::getNumarPizzerii();

    return 0;
}
