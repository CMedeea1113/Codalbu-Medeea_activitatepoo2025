#include <iostream>
#include <cstring>
using namespace std;

class ParcareAuto {
private:
    const int idParcare;
    static int numarParcari;
    char* nume;
    string adresa;
    float tarifOra;
    int nrNiveluri;
    int* locuriPeNivel;

public:
    void setTarifOra(float tarif) {
        if (tarif >= 0) this->tarifOra = tarif;
    }

    float getTarifOra() {
        return this->tarifOra;
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

    void setLocuriPeNivel(int nr, int* locuri) {
        if (nr > 0 && locuri) {
            this->nrNiveluri = nr;
            if (this->locuriPeNivel) delete[] this->locuriPeNivel;
            this->locuriPeNivel = new int[nr];
            for (int i = 0; i < nr; i++)
                this->locuriPeNivel[i] = locuri[i];
        }
    }

    int getLocuriNivel(int index) {
        if (index >= 0 && index < nrNiveluri) return locuriPeNivel[index];
        throw 404;
    }

    int getNrNiveluri() {
        return this->nrNiveluri;
    }

    int getIdParcare() {
        return this->idParcare;
    }

    static int getNumarParcari() {
        return numarParcari;
    }

    ParcareAuto() : idParcare(++numarParcari) {
        nume = nullptr;
        adresa = "Necunoscuta";
        tarifOra = 0;
        nrNiveluri = 0;
        locuriPeNivel = nullptr;
    }

    ParcareAuto(const char* nume, string adresa, float tarifOra,
        int nrNiveluri, const int* locuri)
        : idParcare(++numarParcari)
    {
        this->adresa = adresa;
        this->tarifOra = tarifOra >= 0 ? tarifOra : 0;
        this->nrNiveluri = nrNiveluri > 0 ? nrNiveluri : 0;

        if (nume && strlen(nume) > 0) {
            this->nume = new char[strlen(nume) + 1];
            strcpy_s(this->nume, strlen(nume) + 1, nume);
        }
        else {
            this->nume = nullptr;
        }

        if (this->nrNiveluri > 0 && locuri) {
            this->locuriPeNivel = new int[this->nrNiveluri];
            for (int i = 0; i < this->nrNiveluri; i++)
                this->locuriPeNivel[i] = locuri[i];
        }
        else {
            this->locuriPeNivel = nullptr;
            this->nrNiveluri = 0;
        }
    }

    ParcareAuto(const ParcareAuto& p)
        : idParcare(++numarParcari)
    {
        adresa = p.adresa;
        tarifOra = p.tarifOra;
        nrNiveluri = p.nrNiveluri;

        if (p.nume) {
            nume = new char[strlen(p.nume) + 1];
            strcpy_s(nume, strlen(p.nume) + 1, p.nume);
        }
        else nume = nullptr;

        if (p.locuriPeNivel && p.nrNiveluri > 0) {
            locuriPeNivel = new int[p.nrNiveluri];
            for (int i = 0; i < p.nrNiveluri; i++)
                locuriPeNivel[i] = p.locuriPeNivel[i];
        }
        else locuriPeNivel = nullptr;
    }

    void operator=(const ParcareAuto& p) {
        if (this == &p) return;

        adresa = p.adresa;
        tarifOra = p.tarifOra;
        nrNiveluri = p.nrNiveluri;

        if (nume) delete[] nume;
        if (p.nume) {
            nume = new char[strlen(p.nume) + 1];
            strcpy_s(nume, strlen(p.nume) + 1, p.nume);
        }
        else nume = nullptr;

        if (locuriPeNivel) delete[] locuriPeNivel;
        if (p.locuriPeNivel && p.nrNiveluri > 0) {
            locuriPeNivel = new int[p.nrNiveluri];
            for (int i = 0; i < p.nrNiveluri; i++)
                locuriPeNivel[i] = p.locuriPeNivel[i];
        }
        else {
            locuriPeNivel = nullptr;
            nrNiveluri = 0;
        }
    }

    ~ParcareAuto() {
        if (nume) delete[] nume;
        if (locuriPeNivel) delete[] locuriPeNivel;
    }

    void operator+=(float x) {
        tarifOra += x;
    }

    friend ParcareAuto operator+=(float x, ParcareAuto& p) {
        p.tarifOra += x;
        return p;
    }

    bool operator<(const ParcareAuto& p) {
        return tarifOra < p.tarifOra;
    }

    bool operator!() {
        return tarifOra == 0;
    }

    int operator()(int index) {
        return getLocuriNivel(index);
    }

    char& operator[](int index) {
        if (!nume) throw "Nume inexistent!";
        if (index < 0 || index >= (int)strlen(nume)) throw "Index invalid!";
        return nume[index];
    }

    explicit operator int() {
        int total = 0;
        for (int i = 0; i < nrNiveluri; i++) total += locuriPeNivel[i];
        return total;
    }

    ParcareAuto operator++(int) {
        ParcareAuto copie = *this;
        tarifOra++;
        return copie;
    }

    ParcareAuto operator++() {
        tarifOra++;
        return *this;
    }

    void afisare() {
        cout << endl << idParcare << ". Parcare auto: "
            << (nume ? nume : "Fara nume")
            << " | Adresa: " << adresa
            << " | Tarif/ora: " << tarifOra
            << " | Nr. niveluri: " << nrNiveluri;
        if (nrNiveluri > 0 && locuriPeNivel) {
            cout << " | Locuri/nivel: ";
            for (int i = 0; i < nrNiveluri; i++)
                cout << locuriPeNivel[i] << (i < nrNiveluri - 1 ? ", " : "");
        }
    }

    friend void operator<<(ostream& out, ParcareAuto p) {
        out << endl << "ID: " << p.idParcare;
        out << endl << "Nume: " << (p.nume ? p.nume : (char*)"N/A");
        out << endl << "Adresa: " << p.adresa;
        out << endl << "Tarif/ora: " << p.tarifOra;
        out << endl << "Nr. niveluri: " << p.nrNiveluri;
        if (p.locuriPeNivel && p.nrNiveluri > 0) {
            out << endl << "Locuri pe nivel: ";
            for (int i = 0; i < p.nrNiveluri; i++)
                out << p.locuriPeNivel[i] << " ";
        }
    }

    friend void operator>>(istream& in, ParcareAuto& p) {
        char buf[100];
        in >> buf;
        p.setNume(buf);
        in >> p.adresa;
        in >> p.tarifOra;
        in >> p.nrNiveluri;
        if (p.locuriPeNivel) {
            delete[] p.locuriPeNivel;
            p.locuriPeNivel = nullptr;
        }
        if (p.nrNiveluri > 0) {
            p.locuriPeNivel = new int[p.nrNiveluri];
            for (int i = 0; i < p.nrNiveluri; i++)
                in >> p.locuriPeNivel[i];
        }
    }
};

int ParcareAuto::numarParcari = 0;

int main() {
    int v[3] = { 50, 60, 40 };

    ParcareAuto p1("ParcareUPB", "Splaiul Independentei 313", 5.5f, 3, v);
    ParcareAuto p2 = p1;

    p1.afisare();
    p2.afisare();

    cout << p1;

    p1 += 1.0f;
    p1.afisare();

    cout << endl << "Locuri nivel 2: " << p1(1);
    cout << endl << "Litera din nume[1]: " << p1[1];

    cout << endl << "Total locuri (cast la int): " << (int)p1;

    cout << endl << "Numar parcari create: " << ParcareAuto::getNumarParcari();

    return 0;
}
