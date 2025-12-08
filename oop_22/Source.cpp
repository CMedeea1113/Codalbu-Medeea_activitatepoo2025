#include <iostream>
#include <cstring>
using namespace std;

class SalonManichiura {
private:
    const int idSalon;
    static int numarSaloane;
    char* nume;
    string locatie;
    float pretBazaManichiura;
    int nrServicii;
    float* preturiServicii;

public:
    void setPretBazaManichiura(float pret) {
        if (pret >= 0) this->pretBazaManichiura = pret;
    }

    float getPretBazaManichiura() {
        return this->pretBazaManichiura;
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

    void setPreturiServicii(int nr, float* preturi) {
        if (nr > 0 && preturi) {
            this->nrServicii = nr;
            if (this->preturiServicii) delete[] this->preturiServicii;
            this->preturiServicii = new float[nr];
            for (int i = 0; i < nr; i++)
                this->preturiServicii[i] = preturi[i];
        }
    }

    float getPretServiciu(int index) {
        if (index >= 0 && index < nrServicii) return preturiServicii[index];
        throw 404;
    }

    int getNrServicii() {
        return this->nrServicii;
    }

    int getIdSalon() {
        return this->idSalon;
    }

    static int getNumarSaloane() {
        return numarSaloane;
    }

    SalonManichiura() : idSalon(++numarSaloane) {
        nume = nullptr;
        locatie = "Necunoscuta";
        pretBazaManichiura = 0;
        nrServicii = 0;
        preturiServicii = nullptr;
    }

    SalonManichiura(const char* nume, string locatie, float pretBazaManichiura,
        int nrServicii, const float* preturi)
        : idSalon(++numarSaloane)
    {
        this->locatie = locatie;
        this->pretBazaManichiura = pretBazaManichiura >= 0 ? pretBazaManichiura : 0;
        this->nrServicii = nrServicii > 0 ? nrServicii : 0;

        if (nume && strlen(nume) > 0) {
            this->nume = new char[strlen(nume) + 1];
            strcpy_s(this->nume, strlen(nume) + 1, nume);
        }
        else {
            this->nume = nullptr;
        }

        if (this->nrServicii > 0 && preturi) {
            this->preturiServicii = new float[this->nrServicii];
            for (int i = 0; i < this->nrServicii; i++)
                this->preturiServicii[i] = preturi[i];
        }
        else {
            this->preturiServicii = nullptr;
            this->nrServicii = 0;
        }
    }

    SalonManichiura(const SalonManichiura& s)
        : idSalon(++numarSaloane)
    {
        locatie = s.locatie;
        pretBazaManichiura = s.pretBazaManichiura;
        nrServicii = s.nrServicii;

        if (s.nume) {
            nume = new char[strlen(s.nume) + 1];
            strcpy_s(nume, strlen(s.nume) + 1, s.nume);
        }
        else nume = nullptr;

        if (s.preturiServicii && s.nrServicii > 0) {
            preturiServicii = new float[s.nrServicii];
            for (int i = 0; i < s.nrServicii; i++)
                preturiServicii[i] = s.preturiServicii[i];
        }
        else preturiServicii = nullptr;
    }

    void operator=(const SalonManichiura& s) {
        if (this == &s) return;

        locatie = s.locatie;
        pretBazaManichiura = s.pretBazaManichiura;
        nrServicii = s.nrServicii;

        if (nume) delete[] nume;
        if (s.nume) {
            nume = new char[strlen(s.nume) + 1];
            strcpy_s(nume, strlen(s.nume) + 1, s.nume);
        }
        else nume = nullptr;

        if (preturiServicii) delete[] preturiServicii;
        if (s.preturiServicii && s.nrServicii > 0) {
            preturiServicii = new float[s.nrServicii];
            for (int i = 0; i < s.nrServicii; i++)
                preturiServicii[i] = s.preturiServicii[i];
        }
        else {
            preturiServicii = nullptr;
            nrServicii = 0;
        }
    }

    ~SalonManichiura() {
        if (nume) delete[] nume;
        if (preturiServicii) delete[] preturiServicii;
    }

    void operator+=(float x) {
        pretBazaManichiura += x;
    }

    friend SalonManichiura operator+=(float x, SalonManichiura& s) {
        s.pretBazaManichiura += x;
        return s;
    }

    bool operator<(const SalonManichiura& s) {
        return pretBazaManichiura < s.pretBazaManichiura;
    }

    bool operator!() {
        return pretBazaManichiura == 0;
    }

    float operator()(int index) {
        return getPretServiciu(index);
    }

    char& operator[](int index) {
        if (!nume) throw "Nume inexistent!";
        if (index < 0 || index >= (int)strlen(nume)) throw "Index invalid!";
        return nume[index];
    }

    explicit operator int() {
        return nrServicii;
    }

    SalonManichiura operator++(int) {
        SalonManichiura copie = *this;
        pretBazaManichiura++;
        return copie;
    }

    SalonManichiura operator++() {
        pretBazaManichiura++;
        return *this;
    }

    void afisare() {
        cout << endl << idSalon << ". Salon manichiura: "
            << (nume ? nume : "Fara nume")
            << " | Locatie: " << locatie
            << " | Pret baza manichiura: " << pretBazaManichiura
            << " | Nr. servicii: " << nrServicii;
        if (nrServicii > 0 && preturiServicii) {
            cout << " | Preturi servicii: ";
            for (int i = 0; i < nrServicii; i++)
                cout << preturiServicii[i] << (i < nrServicii - 1 ? ", " : "");
        }
    }

    friend void operator<<(ostream& out, SalonManichiura s) {
        out << endl << "ID: " << s.idSalon;
        out << endl << "Nume: " << (s.nume ? s.nume : (char*)"N/A");
        out << endl << "Locatie: " << s.locatie;
        out << endl << "Pret baza manichiura: " << s.pretBazaManichiura;
        out << endl << "Nr. servicii: " << s.nrServicii;
        if (s.preturiServicii && s.nrServicii > 0) {
            out << endl << "Preturi servicii: ";
            for (int i = 0; i < s.nrServicii; i++)
                out << s.preturiServicii[i] << " ";
        }
    }

    friend void operator>>(istream& in, SalonManichiura& s) {
        char buf[100];
        in >> buf;
        s.setNume(buf);
        in >> s.locatie;
        in >> s.pretBazaManichiura;
        in >> s.nrServicii;
        if (s.preturiServicii) {
            delete[] s.preturiServicii;
            s.preturiServicii = nullptr;
        }
        if (s.nrServicii > 0) {
            s.preturiServicii = new float[s.nrServicii];
            for (int i = 0; i < s.nrServicii; i++)
                in >> s.preturiServicii[i];
        }
        else {
            s.preturiServicii = nullptr;
        }
    }
};

int SalonManichiura::numarSaloane = 0;

int main() {
    float preturi[4] = { 60.0f, 80.0f, 100.0f, 120.0f };

    SalonManichiura s1("NailArtStudio", "Bucuresti", 70.0f, 4, preturi);
    SalonManichiura s2 = s1;

    s1.afisare();
    s2.afisare();

    cout << s1;

    s1 += 10;
    s1.afisare();

    cout << endl << "Pret serviciu 2: " << s1(1);
    cout << endl << "Litera din nume[1]: " << s1[1];

    cout << endl << "Nr. servicii (cast la int): " << (int)s1;

    cout << endl << "Numar saloane create: " << SalonManichiura::getNumarSaloane();

    return 0;
}
