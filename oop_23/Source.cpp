#include <iostream>
#include <cstring>
using namespace std;

class CabinetStomatologic {
private:
    const int idCabinet;
    static int numarCabinete;
    char* nume;
    string adresa;
    float tarifConsultatie;
    int nrServicii;
    float* tarifeServicii;

public:
    void setTarifConsultatie(float tarif) {
        if (tarif >= 0) this->tarifConsultatie = tarif;
    }

    float getTarifConsultatie() {
        return this->tarifConsultatie;
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

    void setTarifeServicii(int nr, float* tarife) {
        if (nr > 0 && tarife) {
            this->nrServicii = nr;
            if (this->tarifeServicii) delete[] this->tarifeServicii;
            this->tarifeServicii = new float[nr];
            for (int i = 0; i < nr; i++)
                this->tarifeServicii[i] = tarife[i];
        }
    }

    float getTarifServiciu(int index) {
        if (index >= 0 && index < nrServicii) return tarifeServicii[index];
        throw 404;
    }

    int getNrServicii() {
        return this->nrServicii;
    }

    int getIdCabinet() {
        return this->idCabinet;
    }

    static int getNumarCabinete() {
        return numarCabinete;
    }

    CabinetStomatologic() : idCabinet(++numarCabinete) {
        nume = nullptr;
        adresa = "Necunoscuta";
        tarifConsultatie = 0;
        nrServicii = 0;
        tarifeServicii = nullptr;
    }

    CabinetStomatologic(const char* nume, string adresa, float tarifConsultatie,
        int nrServicii, const float* tarife)
        : idCabinet(++numarCabinete)
    {
        this->adresa = adresa;
        this->tarifConsultatie = tarifConsultatie >= 0 ? tarifConsultatie : 0;
        this->nrServicii = nrServicii > 0 ? nrServicii : 0;

        if (nume && strlen(nume) > 0) {
            this->nume = new char[strlen(nume) + 1];
            strcpy_s(this->nume, strlen(nume) + 1, nume);
        }
        else {
            this->nume = nullptr;
        }

        if (this->nrServicii > 0 && tarife) {
            this->tarifeServicii = new float[this->nrServicii];
            for (int i = 0; i < this->nrServicii; i++)
                this->tarifeServicii[i] = tarife[i];
        }
        else {
            this->tarifeServicii = nullptr;
            this->nrServicii = 0;
        }
    }

    CabinetStomatologic(const CabinetStomatologic& c)
        : idCabinet(++numarCabinete)
    {
        adresa = c.adresa;
        tarifConsultatie = c.tarifConsultatie;
        nrServicii = c.nrServicii;

        if (c.nume) {
            nume = new char[strlen(c.nume) + 1];
            strcpy_s(nume, strlen(c.nume) + 1, c.nume);
        }
        else nume = nullptr;

        if (c.tarifeServicii && c.nrServicii > 0) {
            tarifeServicii = new float[c.nrServicii];
            for (int i = 0; i < c.nrServicii; i++)
                tarifeServicii[i] = c.tarifeServicii[i];
        }
        else tarifeServicii = nullptr;
    }

    void operator=(const CabinetStomatologic& c) {
        if (this == &c) return;

        adresa = c.adresa;
        tarifConsultatie = c.tarifConsultatie;
        nrServicii = c.nrServicii;

        if (nume) delete[] nume;
        if (c.nume) {
            nume = new char[strlen(c.nume) + 1];
            strcpy_s(nume, strlen(c.nume) + 1, c.nume);
        }
        else nume = nullptr;

        if (tarifeServicii) delete[] tarifeServicii;
        if (c.tarifeServicii && c.nrServicii > 0) {
            tarifeServicii = new float[c.nrServicii];
            for (int i = 0; i < c.nrServicii; i++)
                tarifeServicii[i] = c.tarifeServicii[i];
        }
        else {
            tarifeServicii = nullptr;
            nrServicii = 0;
        }
    }

    ~CabinetStomatologic() {
        if (nume) delete[] nume;
        if (tarifeServicii) delete[] tarifeServicii;
    }

    void operator+=(float x) {
        tarifConsultatie += x;
    }

    friend CabinetStomatologic operator+=(float x, CabinetStomatologic& c) {
        c.tarifConsultatie += x;
        return c;
    }

    bool operator<(const CabinetStomatologic& c) {
        return tarifConsultatie < c.tarifConsultatie;
    }

    bool operator!() {
        return tarifConsultatie == 0;
    }

    float operator()(int index) {
        return getTarifServiciu(index);
    }

    char& operator[](int index) {
        if (!nume) throw "Nume inexistent!";
        if (index < 0 || index >= (int)strlen(nume)) throw "Index invalid!";
        return nume[index];
    }

    explicit operator int() {
        return nrServicii;
    }

    CabinetStomatologic operator++(int) {
        CabinetStomatologic copie = *this;
        tarifConsultatie++;
        return copie;
    }

    CabinetStomatologic operator++() {
        tarifConsultatie++;
        return *this;
    }

    void afisare() {
        cout << endl << idCabinet << ". Cabinet stomatologic: "
            << (nume ? nume : "Fara nume")
            << " | Adresa: " << adresa
            << " | Tarif consultatie: " << tarifConsultatie
            << " | Nr. servicii: " << nrServicii;
        if (nrServicii > 0 && tarifeServicii) {
            cout << " | Tarife servicii: ";
            for (int i = 0; i < nrServicii; i++)
                cout << tarifeServicii[i] << (i < nrServicii - 1 ? ", " : "");
        }
    }

    friend void operator<<(ostream& out, CabinetStomatologic c) {
        out << endl << "ID: " << c.idCabinet;
        out << endl << "Nume: " << (c.nume ? c.nume : (char*)"N/A");
        out << endl << "Adresa: " << c.adresa;
        out << endl << "Tarif consultatie: " << c.tarifConsultatie;
        out << endl << "Nr. servicii: " << c.nrServicii;
        if (c.tarifeServicii && c.nrServicii > 0) {
            out << endl << "Tarife servicii: ";
            for (int i = 0; i < c.nrServicii; i++)
                out << c.tarifeServicii[i] << " ";
        }
    }

    friend void operator>>(istream& in, CabinetStomatologic& c) {
        char buf[100];
        in >> buf;
        c.setNume(buf);
        in >> c.adresa;
        in >> c.tarifConsultatie;
        in >> c.nrServicii;
        if (c.tarifeServicii) {
            delete[] c.tarifeServicii;
            c.tarifeServicii = nullptr;
        }
        if (c.nrServicii > 0) {
            c.tarifeServicii = new float[c.nrServicii];
            for (int i = 0; i < c.nrServicii; i++)
                in >> c.tarifeServicii[i];
        }
        else {
            c.tarifeServicii = nullptr;
        }
    }
};

int CabinetStomatologic::numarCabinete = 0;

int main() {
    float tarife[4] = { 200.0f, 350.0f, 500.0f, 150.0f };

    CabinetStomatologic c1("SmileDent", "Bucuresti", 150.0f, 4, tarife);
    CabinetStomatologic c2 = c1;

    c1.afisare();
    c2.afisare();

    cout << c1;

    c1 += 20;
    c1.afisare();

    cout << endl << "Tarif serviciu 2: " << c1(1);
    cout << endl << "Litera din nume[1]: " << c1[1];

    cout << endl << "Nr. servicii (cast la int): " << (int)c1;

    cout << endl << "Numar cabinete create: " << CabinetStomatologic::getNumarCabinete();

    return 0;
}
