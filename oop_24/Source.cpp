#include <iostream>
#include <cstring>
using namespace std;

class ClinicaVeterinara {
private:
    const int idClinica;
    static int numarClinici;
    char* nume;
    string oras;
    float tarifConsultatie;
    int nrZileMonitorizate;
    int* pacientiPeZi;

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

    void setOras(string o) {
        if (!o.empty()) this->oras = o;
    }

    string getOras() {
        return this->oras;
    }

    void setPacientiPeZi(int nrZile, int* valori) {
        if (nrZile > 0 && valori) {
            this->nrZileMonitorizate = nrZile;
            if (this->pacientiPeZi) delete[] this->pacientiPeZi;
            this->pacientiPeZi = new int[nrZile];
            for (int i = 0; i < nrZile; i++)
                this->pacientiPeZi[i] = valori[i];
        }
    }

    int getPacientiZi(int index) {
        if (index >= 0 && index < nrZileMonitorizate) return pacientiPeZi[index];
        throw 404;
    }

    int getNrZileMonitorizate() {
        return this->nrZileMonitorizate;
    }

    int getIdClinica() {
        return this->idClinica;
    }

    static int getNumarClinici() {
        return numarClinici;
    }

    ClinicaVeterinara() : idClinica(++numarClinici) {
        nume = nullptr;
        oras = "Necunoscut";
        tarifConsultatie = 0;
        nrZileMonitorizate = 0;
        pacientiPeZi = nullptr;
    }

    ClinicaVeterinara(const char* nume, string oras, float tarifConsultatie,
        int nrZile, const int* pacienti)
        : idClinica(++numarClinici)
    {
        this->oras = oras;
        this->tarifConsultatie = tarifConsultatie >= 0 ? tarifConsultatie : 0;
        this->nrZileMonitorizate = nrZile > 0 ? nrZile : 0;

        if (nume && strlen(nume) > 0) {
            this->nume = new char[strlen(nume) + 1];
            strcpy_s(this->nume, strlen(nume) + 1, nume);
        }
        else {
            this->nume = nullptr;
        }

        if (this->nrZileMonitorizate > 0 && pacienti) {
            this->pacientiPeZi = new int[this->nrZileMonitorizate];
            for (int i = 0; i < this->nrZileMonitorizate; i++)
                this->pacientiPeZi[i] = pacienti[i];
        }
        else {
            this->pacientiPeZi = nullptr;
            this->nrZileMonitorizate = 0;
        }
    }

    ClinicaVeterinara(const ClinicaVeterinara& c)
        : idClinica(++numarClinici)
    {
        oras = c.oras;
        tarifConsultatie = c.tarifConsultatie;
        nrZileMonitorizate = c.nrZileMonitorizate;

        if (c.nume) {
            nume = new char[strlen(c.nume) + 1];
            strcpy_s(nume, strlen(c.nume) + 1, c.nume);
        }
        else nume = nullptr;

        if (c.pacientiPeZi && c.nrZileMonitorizate > 0) {
            pacientiPeZi = new int[c.nrZileMonitorizate];
            for (int i = 0; i < c.nrZileMonitorizate; i++)
                pacientiPeZi[i] = c.pacientiPeZi[i];
        }
        else pacientiPeZi = nullptr;
    }

    void operator=(const ClinicaVeterinara& c) {
        if (this == &c) return;

        oras = c.oras;
        tarifConsultatie = c.tarifConsultatie;
        nrZileMonitorizate = c.nrZileMonitorizate;

        if (nume) delete[] nume;
        if (c.nume) {
            nume = new char[strlen(c.nume) + 1];
            strcpy_s(nume, strlen(c.nume) + 1, c.nume);
        }
        else nume = nullptr;

        if (pacientiPeZi) delete[] pacientiPeZi;
        if (c.pacientiPeZi && c.nrZileMonitorizate > 0) {
            pacientiPeZi = new int[c.nrZileMonitorizate];
            for (int i = 0; i < c.nrZileMonitorizate; i++)
                pacientiPeZi[i] = c.pacientiPeZi[i];
        }
        else {
            pacientiPeZi = nullptr;
            nrZileMonitorizate = 0;
        }
    }

    ~ClinicaVeterinara() {
        if (nume) delete[] nume;
        if (pacientiPeZi) delete[] pacientiPeZi;
    }

    void operator+=(float x) {
        tarifConsultatie += x;
    }

    friend ClinicaVeterinara operator+=(float x, ClinicaVeterinara& c) {
        c.tarifConsultatie += x;
        return c;
    }

    bool operator<(const ClinicaVeterinara& c) {
        return tarifConsultatie < c.tarifConsultatie;
    }

    bool operator!() {
        return tarifConsultatie == 0;
    }

    int operator()(int index) {
        return getPacientiZi(index);
    }

    char& operator[](int index) {
        if (!nume) throw "Nume inexistent!";
        if (index < 0 || index >= (int)strlen(nume)) throw "Index invalid!";
        return nume[index];
    }

    explicit operator int() {
        int total = 0;
        for (int i = 0; i < nrZileMonitorizate; i++) total += pacientiPeZi[i];
        return total;
    }

    ClinicaVeterinara operator++(int) {
        ClinicaVeterinara copie = *this;
        tarifConsultatie++;
        return copie;
    }

    ClinicaVeterinara operator++() {
        tarifConsultatie++;
        return *this;
    }

    void afisare() {
        cout << endl << idClinica << ". Clinica veterinara: "
            << (nume ? nume : "Fara nume")
            << " | Oras: " << oras
            << " | Tarif consultatie: " << tarifConsultatie
            << " | Zile monitorizate: " << nrZileMonitorizate;
        if (nrZileMonitorizate > 0 && pacientiPeZi) {
            cout << " | Pacienti/zi: ";
            for (int i = 0; i < nrZileMonitorizate; i++)
                cout << pacientiPeZi[i] << (i < nrZileMonitorizate - 1 ? ", " : "");
        }
    }

    friend void operator<<(ostream& out, ClinicaVeterinara c) {
        out << endl << "ID: " << c.idClinica;
        out << endl << "Nume: " << (c.nume ? c.nume : (char*)"N/A");
        out << endl << "Oras: " << c.oras;
        out << endl << "Tarif consultatie: " << c.tarifConsultatie;
        out << endl << "Zile monitorizate: " << c.nrZileMonitorizate;
        if (c.pacientiPeZi && c.nrZileMonitorizate > 0) {
            out << endl << "Pacienti pe zi: ";
            for (int i = 0; i < c.nrZileMonitorizate; i++)
                out << c.pacientiPeZi[i] << " ";
        }
    }

    friend void operator>>(istream& in, ClinicaVeterinara& c) {
        char buf[100];
        in >> buf;
        c.setNume(buf);
        in >> c.oras;
        in >> c.tarifConsultatie;
        in >> c.nrZileMonitorizate;
        if (c.pacientiPeZi) {
            delete[] c.pacientiPeZi;
            c.pacientiPeZi = nullptr;
        }
        if (c.nrZileMonitorizate > 0) {
            c.pacientiPeZi = new int[c.nrZileMonitorizate];
            for (int i = 0; i < c.nrZileMonitorizate; i++)
                in >> c.pacientiPeZi[i];
        }
        else {
            c.pacientiPeZi = nullptr;
        }
    }
};

int ClinicaVeterinara::numarClinici = 0;

int main() {
    int v[5] = { 12, 15, 18, 10, 20 };

    ClinicaVeterinara c1("VetCare", "Bucuresti", 150.0f, 5, v);
    ClinicaVeterinara c2 = c1;

    c1.afisare();
    c2.afisare();

    cout << c1;

    c1 += 25;
    c1.afisare();

    cout << endl << "Pacienti in ziua 2: " << c1(1);
    cout << endl << "Litera din nume[1]: " << c1[1];

    cout << endl << "Total pacienti (cast la int): " << (int)c1;

    cout << endl << "Numar clinici create: " << ClinicaVeterinara::getNumarClinici();

    return 0;
}
